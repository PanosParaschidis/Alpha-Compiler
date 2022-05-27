#include "avm.h"
#include "targetCode.h"
#include <math.h>
#include <ctype.h>
typedef void (*execute_func_t)(instruction *);
typedef void (*memclear_func_t)(avm_memcell*);
typedef char* (*tostring_func_t)(avm_memcell*);
typedef double (*arithmetic_func_t) (double x, double y);
typedef void (*library_func_t) (void);
typedef unsigned char (*tobool_func_t)(avm_memcell*);

library_func_t libraryFuncs[12]={0};
library_func_t avm_getlibraryfunc (char *id);
void avm_registerlibfunc(char *name, library_func_t index);

execute_func_t executeFuncs[]={
	execute_assign , 
	execute_add,				
	execute_sub,
	execute_mul,
	execute_div,
	execute_mod,
	0, 
	0, 
	0, 
	0,
	execute_jeq,
	execute_jne,
	execute_jgt,
	execute_jlt,
	execute_jge,
	execute_jle,
	execute_jump,
	execute_call,
	execute_funcenter,
	execute_funcexit,
	execute_newtable,
	execute_tablegetelem,
	execute_tablesetelem,
	execute_pusharg,
	0,
	0,
	0
	
};


memclear_func_t memclearFuncs[] =//
{
  0, 
  memclear_string,
  0, 
  memclear_table,
  0, 
  0,
  0, 
  0  
};

tostring_func_t tostringFuncs[]=
{
  number_tostring,
  string_tostring,
  bool_tostring,
  table_tostring,
  userfunc_tostring,
  libfunc_tostring,
  nil_tostring,
  undef_tostring
};

tobool_func_t toboolFuncs[]=
{
  number_tobool,
  string_tobool,
  bool_tobool,
  table_tobool,
  userfunc_tobool,
  libfunc_tobool,
  nil_tobool,
  undef_tobool
};

arithmetic_func_t arithmeticFuncs[] = {
  0,
  add_impl,
  sub_impl,
  mul_impl,
  div_impl,
  mod_impl
 };

char *typeStrings[]=
{
  "number", 	
  "string", 	
  "bool",   	
  "table",  	
  "userfunc",	
  "libfunc",  	
  "nil",		
  "undef"		
};



unsigned int NtotalStrings=0;
unsigned int NtotalNums=0;
unsigned int NtotalUserfuncs=0;
unsigned int NtotalLibfuncs=0;
unsigned char 	executionFinished = 0;
unsigned int	pc = 0;
unsigned int	currLine = 0;
unsigned int	codeSize = 0;

unsigned totalActuals=0;
instruction*	code = NULL;

char* avm_tostring(avm_memcell* m){
	assert(m->type>=0 && m->type <= undef_m);
		return (*tostringFuncs[m->type])(m);
	
}

void memclear_string(avm_memcell* m){
	assert(m->data.strVal);
	free(m->data.strVal);
}

void memclear_table(avm_memcell* m){
	assert(m->data.tableVal);
	avm_tabledecrefcounter(m->data.tableVal);
}

void avm_memcellclear(avm_memcell* m){
	if(m->type!=undef_m){
		memclear_func_t f=memclearFuncs[m->type];
		if(f){
			(*f)(m);
		}
		m->data.numVal =0;
		m->data.funcVal=0;
		m->data.libfuncVal=NULL;
		m->type=undef_m;
	}
}

static void avm_initstack(void)
{
  unsigned int i;
  for(i=0; i<AVM_STACKSIZE;i++)
  {
      AVM_WIPEOUT(stack[i]);
      stack[i].type = undef_m;
  }
}




void execute_cycle(){

	unsigned int oldPc=0;
	if(executionFinished){
		printf("STOP! execution finished\n");
		return;
	}
	else{
		if(pc==AVM_ENDING_PC){
			printf("Finished Execution.\n");
			executionFinished =1;
			return;
		}

		
		assert(pc< AVM_ENDING_PC);
		instruction * i=inst +pc;
		assert(i->opcode>=0 && i->opcode<=AVM_MAX_INSTRUCTIONS);
		
		if(i->srcLine>=0){
			currLine=i->srcLine;
			oldPc=pc;
			printf("top: %d topsp: %d pc: %d opcode:",top,topsp,pc);
			iOpcode_tostring(i);
			printf("\n");
			(*executeFuncs[i->opcode])(i);
		}

		if(pc==oldPc){
			
			++pc;
		}
	}
}



void readBinary(){
	FILE *in=fopen("BinFile.bin","rb");
	if(!in){
		fprintf(stderr, "can't open Binary file\n" );
	}

	int magic,i,tmp;
	instruction* t;
	fread(&magic,sizeof(int),1,in);
	
	if(magic!=1234){
		fprintf(stderr, "Wrong Magic Number, Terminating..\n" );
		exit(-1);
	}

	fread(&NtotalStrings,sizeof(int),1,in);
	NstringArray=malloc(NtotalStrings*sizeof(char*));
	for(i=0;i<NtotalStrings;++i){
		fread(&NstringArray[i],sizeof(char*),1,in);
	}

	fread(&NtotalNums,sizeof(int),1,in);
	NnumArray=malloc(NtotalNums*sizeof(double));
	for(i=0;i<NtotalNums;++i){
		fread(&NnumArray[i],sizeof(double),1,in);
	}

	fread(&NtotalLibfuncs,sizeof(int),1,in);
	NlibFuncArray=malloc(NtotalLibfuncs*sizeof(char *));
	for(i=0;i<NtotalLibfuncs;++i){
		fread(&NlibFuncArray[i],sizeof(char *),1,in);
	}

	fread(&NtotalUserfuncs,sizeof(int),1,in);
	NuserFuncArray=malloc(NtotalUserfuncs*sizeof(userFunc));
	for(i=0;i<NtotalUserfuncs;++i){
		fread(&NuserFuncArray[i].id,sizeof(char*),1,in);
		fread(&NuserFuncArray[i].address,sizeof(int),1,in);
		fread(&NuserFuncArray[i].localSize,sizeof(int),1,in);

	}

	fread(&codeSize,sizeof(int),1,in);
	if(codeSize==0){
		fprintf(stderr, "Zero instructions, Terminating..\n" );
		exit(-1);
	}
	code=malloc(codeSize*sizeof(instruction));
	for(i=0; i<codeSize;++i){
		t=code+i;
		fread(&(t->opcode),sizeof(int),1,in);

		switch(t->opcode){

			case add_v:
			case sub_v:
			case mul_v:
			case mod_v:
			case div_v:
			case jgt_v:
			case jlt_v:
			case jge_v:
			case jeq_v:
			case jle_v:
			case jne_v:
			case tablegetelem_v:
			case tablesetelem_v:{
				t->arg1=malloc(sizeof(vmarg));
				fread(&(t->arg1->type),sizeof(int),1,in);
				fread(&(t->arg1->val),sizeof(int),1,in);

				t->arg2=malloc(sizeof(vmarg));
				fread(&(t->arg2->type),sizeof(int),1,in);
				fread(&(t->arg2->val),sizeof(int),1,in);

				t->result=malloc(sizeof(vmarg));
				fread(&(t->result->type),sizeof(int),1,in);
				fread(&(t->result->val),sizeof(int),1,in);
				break;
			}

			case assign_v:{
				t->arg1=malloc(sizeof(vmarg));
				fread(&(t->arg1->type),sizeof(int),1,in);
				fread(&(t->arg1->val),sizeof(int),1,in);

				t->result=malloc(sizeof(vmarg));
				fread(&(t->result->type),sizeof(int),1,in);
				fread(&(t->result->val),sizeof(int),1,in);
				break;
			}

			case call_v:
			case pusharg_v:{
				t->arg1=malloc(sizeof(vmarg));
				fread(&(t->arg1->type),sizeof(int),1,in);
				fread(&(t->arg1->val),sizeof(int),1,in);
				break;
			}

			case funcenter_v:
			case funcexit_v:
			case jump_v:
			case newtable_v:{
				t->result=malloc(sizeof(vmarg));
				fread(&(t->result->type),sizeof(int),1,in);
				fread(&(t->result->val),sizeof(int),1,in);
				break;
			}

		}
	}
	initiateEverything();
	
	fclose(in);

}

void initiateEverything(){
	

	avm_initstack();
	avm_registerlibfunc("print",libfunc_print);
	avm_registerlibfunc("sin", libfunc_sin);
	avm_registerlibfunc("cos", libfunc_cos);
	avm_registerlibfunc("typeof", libfunc_typeof);
	avm_registerlibfunc("totalarguments", libfunc_totalarguments);
	avm_registerlibfunc("objecttotalmembers", libfunc_objecttotalmembers);
	avm_registerlibfunc("strtonum", libfunc_strtonum);
	avm_registerlibfunc("sqrt", libfunc_sqrt);
	avm_registerlibfunc("input", libfunc_input);
	avm_registerlibfunc("objectmemberkeys", libfunc_objectmemberkeys);
	avm_registerlibfunc("argument", libfunc_argument);
	avm_registerlibfunc("objectcopy", libfunc_objectcopy);

 	unsigned int global=AVM_STACKSIZE - programVarOffset-1;
 	top = global-1;
 	topsp=top;
 	printf("\nTop is : %d \nTopsp  is :  %d\n\n", top,topsp);
 

while(!executionFinished){
	execute_cycle();
	}
	Print_Stack();
}


void Print_Stack(){
	unsigned int i;
  	printf("\nSTACK\n");
  	for(i=AVM_STACKSIZE-1; i>0; i--){
    	if(stack[i].type!=undef_m){
			printf("%d: \t",i);
			print_cell(&stack[i]);
			printf("\n");
      }
  	}
}

double consts_getnumber(unsigned int index){

	return NnumArray[index];
}

char* consts_getstring(unsigned int index){
	return NstringArray[index];
}

char* libfuncs_getused(unsigned int index){
	return NlibFuncArray[index];
}

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg){
	if(reg==NULL){
		reg=malloc(sizeof(avm_memcell));
	}
	switch(arg->type){
		case global_a: return &stack[AVM_STACKSIZE-1-arg->val];
		case local_a: return &stack[topsp-arg->val];
		case formal_a: return &stack[topsp+AVM_STACKENV_SIZE+1+arg->val];//possibly +1
		case retval_a: return &retval;
		case number_a:{
			reg->type=number_m;
			reg->data.numVal=consts_getnumber(arg->val);
			return reg;
		}
		case string_a:{
			reg->type=string_m;
			reg->data.strVal=strdup(consts_getstring(arg->val));
			return reg;
		}
		case bool_a:{
			reg->type=bool_m;
			reg->data.boolVal=arg->val;
			return reg;
		}
		case nil_a: reg->type=nil_m; return reg;
		case userfunc_a:{
			reg->type=userfunc_m;
			reg->data.funcVal=arg->val;//index of function in userfunc array
			return reg;
		}
		case libfunc_a:{
			reg->type=libfunc_m;
			reg->data.libfuncVal=strdup(libfuncs_getused(arg->val));
			return reg;
		}

		default: {
			printf("arg->type: %d arg->value: %d\n",arg->type,arg->val );
			assert(0);
			break;
		}
	}
}


void execute_assign(instruction *instr){
	avm_memcell* lv=avm_translate_operand(instr->result,NULL);
	avm_memcell* rv=avm_translate_operand(instr->arg1, &ax);
	//printf("lv->type %d rv->type %d\n",lv->type,rv->type );
	assert(lv || lv== &retval);
	
	//assert(&stack[top]<= lv);
	
	//assert(&stack[AVM_STACKSIZE]> lv );
	
	assert(rv);	

	avm_assign(lv,rv);
}

void avm_assign(avm_memcell *lv, avm_memcell *rv){
	if(lv==rv){
		return;
	}
	if(lv->type==table_m && rv->type==table_m && lv->data.tableVal==rv->data.tableVal){
		return;
	}
	if(rv->type==undef_m){
		printf("assigning from undef content!\n");
	}
	avm_memcellclear(lv);
	memcpy(lv,rv,sizeof(avm_memcell));
	if(lv->type==string_m){
		lv->data.strVal=strdup(rv->data.strVal);
	}else if(lv->type==table_m && rv->type==table_m){
		lv -> data.tableVal = rv -> data.tableVal;
		avm_tableincrefcounter(lv->data.tableVal);
	}else if(lv->type==userfunc_m){
		lv->data.funcVal=rv->data.funcVal;
	}else if(lv->type==libfunc_m){
		lv->data.libfuncVal=strdup(rv->data.libfuncVal);
	}else if(lv->type==number_m){
		lv->data.numVal=rv->data.numVal;
	}
	lv->type=rv->type;
}

void execute_call(instruction* instr){
	avm_memcell* func=avm_translate_operand(instr->arg1, &ax);
	assert(func);
	avm_callsaveenvironment();
	switch(func->type){
		case userfunc_m:{
			pc=NuserFuncArray[func->data.funcVal].address;
			assert(pc<AVM_ENDING_PC);
			assert(code[pc].opcode==funcenter_v);
			break;
		}

		case string_m: avm_calllibfunc(func->data.strVal); break;
		case libfunc_m: avm_calllibfunc(func->data.libfuncVal); break;
		
		default:{
			
			char *s=avm_tostring(func);
			printf("call: cannot bind %s to function!",s);
			free(s);
			executionFinished=1;//mporei na mpei stin error
		}
	}
}

void avm_dec_top(){
	if(!top){
		printf("stack overflow");
		executionFinished=1;
	}else{
		--top;
	}
}

void avm_push_envvalue(unsigned int val){
	stack[top].type=number_m;
	stack[top].data.numVal=val;
	avm_dec_top();
}

void avm_callsaveenvironment(){
	avm_push_envvalue(totalActuals);
	avm_push_envvalue(pc+1);
	avm_push_envvalue(top+totalActuals+2);
	avm_push_envvalue(topsp);
}

void execute_funcenter(instruction* instr){
	avm_memcell* func=avm_translate_operand(instr->result, &ax);
	assert(func);
	assert(pc==NuserFuncArray[func->data.funcVal].address);

	totalActuals=0;
	//userfunc* funcinfo=avm_getfuncinfo(pc);
	topsp=top;
	top=top-NuserFuncArray[func->data.funcVal].localSize;
}

unsigned int avm_get_envvalue(unsigned int i){
	if(stack[i].type==number_m){
		unsigned val=(unsigned)stack[i].data.numVal;
		assert(stack[i].data.numVal==(double) val);
		return val;	
	}else if(stack[i].type==nil_m){
		return 0;
	}
	
}

void execute_funcexit(instruction *unused){//possible
	unsigned int oldTop=top;
	top=avm_get_envvalue(topsp+AVM_SAVEDTOP_OFFSET);
	pc=avm_get_envvalue(topsp+AVM_SAVEDPC_OFFSET);
	topsp=avm_get_envvalue(topsp+AVM_SAVEDTOPSP_OFFSET);
	while(++oldTop<=top){
		avm_memcellclear(&stack[oldTop]);
		
	}
}

library_func_t avm_getlibraryfunc (char *id){
  int index=libfuncs_newused(id);
  if(index>=0 && index<=11){
  	return libraryFuncs[index];
  }else{
  	return NULL;
  }
 
}

void avm_calllibfunc(char *id){
	library_func_t f=avm_getlibraryfunc(id);
	if(!f){
		printf("unsupported lib func %s called",id);
		executionFinished=1;
	}else{
		topsp=top;
		totalActuals=0;
		(*f)();
		if(!executionFinished){
			execute_funcexit(NULL);
		}
	}
}

unsigned int avm_totalactuals(){
	return avm_get_envvalue(topsp+AVM_NUMACTUALS_OFFSET);
}

avm_memcell* avm_getactual(unsigned int i){
	assert(i<avm_totalactuals());
	return &stack[topsp+AVM_STACKENV_SIZE+1+i];
}


void execute_pusharg(instruction* instr){
	avm_memcell* arg=avm_translate_operand(instr->arg1,&ax);
	assert(arg);
	avm_assign(&stack[top],arg);
	++totalActuals;
	avm_dec_top();
}

char* number_tostring(avm_memcell* m){
	assert(m->type==number_m);
	char* buffer=malloc(20*sizeof(char));
	snprintf(buffer, 20, "%0.2f", m->data.numVal);
	return buffer;
}

char* string_tostring(avm_memcell* m){
	assert(m->type==string_m);
	char* buffer=strdup(m->data.strVal);
	return buffer;
}

char* bool_tostring(avm_memcell* m){
	assert(m->type==bool_m);
	char* buffer;
	if(m->data.boolVal==1){
		buffer=strdup("true");
	}else{
		buffer=strdup("false");
	}
	return buffer;
}

char* userfunc_tostring(avm_memcell* m){
	assert(m->type==userfunc_m);
	char* buffer=strdup(NuserFuncArray[m->data.funcVal].id);
	return buffer;
}

char* libfunc_tostring(avm_memcell* m){
	assert(m->type==libfunc_m);
	char* buffer=strdup(m->data.libfuncVal);
	return buffer;
}

char* nil_tostring(avm_memcell* m){
	assert(m->type==nil_m);
	return "nil";
}

char* undef_tostring(avm_memcell* m){
	assert(m->type==undef_m);
	return "undef";
}

char* table_tostring(avm_memcell* m){
	assert(m->type==table_m);
	char * temp=strdup("table");
	return temp;
}

double add_impl(double x,double y){
	return x+y;
}

double sub_impl(double x,double y){
	return x-y;
}

double mul_impl(double x,double y){
	return x*y;
}

double div_impl(double x,double y){
	if(y==0){
		printf("division by zero!!");
		return x;
	}
	return x/y;
}

double mod_impl(double x,double y){
	if(y==0){
		printf("Modulo by zero!!");
		return x;
	}
	return (((unsigned)x)%((unsigned)y));
}

void execute_arithmetic(instruction *instr){
	avm_memcell *lv=avm_translate_operand(instr->result,NULL);
	avm_memcell *rv1=avm_translate_operand(instr->arg1, &ax);
	avm_memcell *rv2=avm_translate_operand(instr->arg2, &bx);

	//assert(lv && (&stack[top] <= lv && &stack[AVM_STACKSIZE] > lv || lv == &retval));
  	assert(rv1 && rv2);

  	if(rv1->type!=number_m || rv2->type!=number_m){
  		printf("not a number in arithmetic\n");
  		printf("rv1->type: %d rv2->type %d\n",rv1->type,rv2->type );
  		executionFinished=1;
  	}else{
  		arithmetic_func_t op=arithmeticFuncs[instr->opcode];
  		avm_memcellclear(lv);
  		lv->type=number_m;
  		lv->data.numVal=(*op)(rv1->data.numVal,rv2->data.numVal);
  	}
}

void avm_error(char *s,...){

}
void avm_tableincrefcounter(avm_table* t){
	++t->refCounter;
}
void avm_tabledecrefcounter(avm_table* t){
	assert(t->refCounter>0);
	if(--t->refCounter==0){
		avm_tabledestroy(t);
	}
}
void execute_jeq(instruction* instr){
	assert(instr->result->type==label_a);
	avm_memcell* rv1=avm_translate_operand(instr->arg1, &ax);
	avm_memcell* rv2=avm_translate_operand(instr->arg2, &bx);
	unsigned char result=0;
	
	if(rv1->type==undef_m|| rv2->type==undef_m){
		printf("undef involved in equality");
		executionFinished=1;
	}else if(rv1->type==nil_m||rv2->type==nil_m){
		result=(rv1->type ==nil_m && rv2->type==nil_m);
	}else if(rv1->type==bool_m || rv2->type==bool_m){
		result=(avm_tobool(rv1)==avm_tobool(rv2));
	}else if(rv1->type != rv2->type){
		printf("%s == %s is illegal!\n", typeStrings[rv1->type], typeStrings[rv2->type]);
	}else{
		if(rv1->type == string_m ){
			if(strcmp(rv1->data.strVal,rv2->data.strVal)==0){
			result=1;
			}
		}
		if(rv1->type == userfunc_m){
			result = (rv1->data.funcVal == rv2->data.funcVal) ;
		}
		if(rv1->type == libfunc_m){
			if(strcmp(rv1->data.libfuncVal, rv2->data.libfuncVal)==0){
					result = 1;
			}
		}
		if(rv1->type == number_m && rv2->type == number_m){
			result = (rv1->data.numVal == rv2->data.numVal);
		}
		if(rv1->type == table_m){
			result = (rv1->data.tableVal == rv2->data.tableVal);
		}
      }

    if(!executionFinished && result ){
    	pc = instr->result->val;
    }
}


void execute_jne(instruction* instr){
	assert(instr->result->type==label_a);
	avm_memcell* rv1=avm_translate_operand(instr->arg1, &ax);
	avm_memcell* rv2=avm_translate_operand(instr->arg2, &bx);
	unsigned char result=0;

	if(rv1->type==undef_m|| rv2->type==undef_m){
		printf("undef involved in equality");
		executionFinished=1;
	}else if(rv1->type==nil_m||rv2->type==nil_m){
		result=rv1->type ==nil_m && rv2->type==nil_m;
	}else if(rv1->type==bool_m || rv2->type==bool_m){
		result=(avm_tobool(rv1)==avm_tobool(rv2));
	}else if(rv1->type != rv2->type){
		printf("%s == %s is illegal!\n", typeStrings[rv1->type], typeStrings[rv2->type]);
	}else{
		if(rv1->type == string_m ){
			result = strcmp(rv1->data.strVal,rv2->data.strVal);
		}
		if(rv1->type == userfunc_m){
			result = rv1->data.funcVal != rv2->data.funcVal ;
		}
		if(rv1->type == libfunc_m){
			result = strcmp(rv1->data.libfuncVal, rv2->data.libfuncVal);
		}
		if(rv1->type == number_m && rv2->type == number_m){
			result = rv1->data.numVal != rv2->data.numVal;
		}
		if(rv1->type == table_m){
			result = (rv1->data.tableVal != rv2->data.tableVal);
		}
      }

    if(!executionFinished && result ){
    	pc = instr->result->val;
    }
}
void execute_jgt(instruction* instr){
	assert(instr->result->type==label_a);
	avm_memcell* rv1=avm_translate_operand(instr->arg1, &ax);
	avm_memcell* rv2=avm_translate_operand(instr->arg2, &bx);
	unsigned char result=0;

	if(rv1->type==undef_m|| rv2->type==undef_m){
		printf("undef involved in equality");
		executionFinished=1;
	}else if(rv1->type==nil_m||rv2->type==nil_m){
		result=rv1->type ==nil_m && rv2->type==nil_m;
	}else if(rv1->type==bool_m || rv2->type==bool_m){
		result=(avm_tobool(rv1)==avm_tobool(rv2));
	}else if(rv1->type != rv2->type){
		printf("%s == %s is illegal!\n", typeStrings[rv1->type], typeStrings[rv2->type]);
	}else{
		if(rv1->type == string_m ){
			result = strcmp(rv1->data.strVal,rv2->data.strVal);
		}
		if(rv1->type == userfunc_m){
			result = rv1->data.funcVal > rv2->data.funcVal ;
		}
		if(rv1->type == libfunc_m){
			result = strcmp(rv1->data.libfuncVal, rv2->data.libfuncVal);
		}
		if(rv1->type == number_m && rv2->type == number_m){
			result = rv1->data.numVal > rv2->data.numVal;
		}
		if(rv1->type == table_m){
			result = (rv1->data.tableVal > rv2->data.tableVal);
		}
      }

    if(!executionFinished && result ){
    	pc = instr->result->val;
    }

}
void execute_jlt(instruction* instr){
	assert(instr->result->type==label_a);
	avm_memcell* rv1=avm_translate_operand(instr->arg1, &ax);
	avm_memcell* rv2=avm_translate_operand(instr->arg2, &bx);
	unsigned char result=0;

	if(rv1->type==undef_m|| rv2->type==undef_m){
		printf("undef involved in equality");
		executionFinished=1;
	}else if(rv1->type==nil_m||rv2->type==nil_m){
		result=rv1->type ==nil_m && rv2->type==nil_m;
	}else if(rv1->type==bool_m || rv2->type==bool_m){
		result=(avm_tobool(rv1)==avm_tobool(rv2));
	}else if(rv1->type != rv2->type){
		printf("%s == %s is illegal!\n", typeStrings[rv1->type], typeStrings[rv2->type]);
	}else{
		if(rv1->type == string_m ){
			result = strcmp(rv2->data.strVal,rv1->data.strVal);
		}
		if(rv1->type == userfunc_m){
			result = rv1->data.funcVal < rv2->data.funcVal ;
		}
		if(rv1->type == libfunc_m){
			result = strcmp(rv2->data.libfuncVal,rv1->data.libfuncVal);
		}
		if(rv1->type == number_m && rv2->type == number_m){
			result = rv1->data.numVal < rv2->data.numVal;
		}
		if(rv1->type == table_m){
			result = (rv1->data.tableVal < rv2->data.tableVal);
		}
      }

    if(!executionFinished && result ){
    	pc = instr->result->val;
    }
}
void execute_jge(instruction* instr){
	assert(instr->result->type==label_a);
	avm_memcell* rv1=avm_translate_operand(instr->arg1, &ax);
	avm_memcell* rv2=avm_translate_operand(instr->arg2, &bx);
	unsigned char result=0;

	if(rv1->type==undef_m|| rv2->type==undef_m){
		printf("undef involved in equality");
		executionFinished=1;
	}else if(rv1->type==nil_m||rv2->type==nil_m){
		result=rv1->type ==nil_m && rv2->type==nil_m;
	}else if(rv1->type==bool_m || rv2->type==bool_m){
		result=(avm_tobool(rv1)==avm_tobool(rv2));
	}else if(rv1->type != rv2->type){
		printf("%s == %s is illegal!\n", typeStrings[rv1->type], typeStrings[rv2->type]);
	}else{
		if(rv1->type == string_m ){
			result = strcmp(rv1->data.strVal,rv2->data.strVal);
			if(result==0) ++result;
		}
		if(rv1->type == userfunc_m){
			result = rv1->data.funcVal >= rv2->data.funcVal ;
		}
		if(rv1->type == libfunc_m){
			result = strcmp(rv1->data.libfuncVal,rv2->data.libfuncVal);
			if(result==0) ++result;
		}
		if(rv1->type == number_m && rv2->type == number_m){
			result = rv1->data.numVal >= rv2->data.numVal;
		}
		if(rv1->type == table_m){
			result = (rv1->data.tableVal >= rv2->data.tableVal);
		}
      }

    if(!executionFinished && result ){
    	pc = instr->result->val;
    }

}
void execute_jle(instruction* instr){
	assert(instr->result->type==label_a);
	avm_memcell* rv1=avm_translate_operand(instr->arg1, &ax);
	avm_memcell* rv2=avm_translate_operand(instr->arg2, &bx);
	unsigned char result=0;

	if(rv1->type==undef_m|| rv2->type==undef_m){
		printf("undef involved in equality");
		executionFinished=1;
	}else if(rv1->type==nil_m||rv2->type==nil_m){
		result=rv1->type ==nil_m && rv2->type==nil_m;
	}else if(rv1->type==bool_m || rv2->type==bool_m){
		result=(avm_tobool(rv1)==avm_tobool(rv2));
	}else if(rv1->type != rv2->type){
		printf("%s == %s is illegal!\n", typeStrings[rv1->type], typeStrings[rv2->type]);
	}else{
		if(rv1->type == string_m ){
			result = strcmp(rv2->data.strVal,rv1->data.strVal);
			if(result==0) ++result;
		}
		if(rv1->type == userfunc_m){
			result = rv1->data.funcVal <= rv2->data.funcVal ;
		}
		if(rv1->type == libfunc_m){
			result = strcmp(rv2->data.libfuncVal,rv1->data.libfuncVal);
			if(result==0) ++result;
		}
		if(rv1->type == number_m && rv2->type == number_m){
			result = rv1->data.numVal <= rv2->data.numVal;
		}
		if(rv1->type == table_m){
			result = (rv1->data.tableVal <= rv2->data.tableVal);
		}
      }

    if(!executionFinished && result ){
    	pc = instr->result->val;
    }
}
void execute_jump(instruction* instr){
	if(!executionFinished && instr->result ){
		pc=instr->result->val;	
	}
	
}
void execute_newtable(instruction* instr){
	avm_memcell* lv=avm_translate_operand(instr->arg1,NULL);
	//assert(lv && (&stack[top]   <= lv && &stack[AVM_STACKSIZE] > lv || lv == &retval));
	
	avm_memcellclear(lv);
	lv->type=table_m;
	lv->data.tableVal=avm_tablenew();
	avm_tableincrefcounter(lv->data.tableVal);
}

void execute_tablegetelem(instruction* instr){
	avm_memcell* lv=avm_translate_operand(instr->result,NULL);
	avm_memcell* t=avm_translate_operand(instr->arg1,NULL);
	avm_memcell* i=avm_translate_operand(instr->arg2,&ax);
	//printf("top %d lv->type %d instr->result->type %d\n",top,lv->type,instr->result->type );
	//assert(lv && (&stack[top] <= lv && &stack[AVM_STACKSIZE] > lv || lv==&retval));
	//assert(t && &stack[top] <= t && &stack[AVM_STACKSIZE] >t);
	avm_memcellclear(lv);
	lv->type=nil_m;

	if(t->type!=table_m){
		printf("illegal use of type %s as table\n",typeStrings[t->type]);
		executionFinished=1;
	}else{
		avm_memcell* content=avm_tablegetelem(t->data.tableVal,i);
		if(content){
			avm_assign(lv,content);
		}else{
			char* ts=avm_tostring(t);
			char* is=avm_tostring(i);
			printf("warning %s[%s] not found!\n",ts,is );
			//avm_warning("%s[%s] not found!",ts,is);
			free(ts);
			free(is);
		}
	}

}
void execute_tablesetelem(instruction* instr){
	avm_memcell* t=avm_translate_operand(instr->arg1,NULL);
	avm_memcell* i=avm_translate_operand(instr->arg2,&ax);
	avm_memcell* c=avm_translate_operand(instr->result,&bx);

	//assert(t && &stack[top] <= t && &stack[AVM_STACKSIZE] > t);
  	assert ( i && c);

  	if(t->type!=table_m){
  		printf("illegal use of type %s as table!\n", typeStrings[t->type]);
  		executionFinished=1;
  	}else{
  		avm_tablesetelem(t->data.tableVal,i,c);
  	}
}

unsigned char number_tobool(avm_memcell* m){
	return m->data.numVal!=0;
}

 unsigned char string_tobool(avm_memcell* m){
 	return m->data.strVal[0]!=0;
 }

unsigned char bool_tobool(avm_memcell* m){
	return m->data.boolVal;
}

unsigned char table_tobool(avm_memcell* m){
	return 1;
}

unsigned char userfunc_tobool(avm_memcell* m){
	return 1;
}

unsigned char libfunc_tobool(avm_memcell* m){
	return 1;
}

unsigned char nil_tobool(avm_memcell* m){
	return 0;
}

unsigned char undef_tobool(avm_memcell* m){
	return 0;
}

unsigned char avm_tobool (avm_memcell *m)
{
  assert(m->type >=0 && m->type <undef_m);
  return (*toboolFuncs[m->type])(m);
}



avm_table* avm_tablenew(){
	avm_table *t=malloc(sizeof(avm_table));
	AVM_WIPEOUT(*t);
	t->refCounter=0;
	t->total=0;
	unsigned int i;
	avm_tablebucketsinit(t->numIndexed);
	avm_tablebucketsinit(t->strIndexed);
	return t;
}

void avm_tablebucketsinit(avm_table_bucket** p){
	unsigned int i;
	for(i=0;i<AVM_TABLE_HASHSIZE;++i){
		p[i]=NULL;
	}
}

void avm_tablebucketsdestroy(avm_table_bucket ** p){
	avm_table_bucket* b,*del;
	unsigned int i;
	for(i=0;i<AVM_TABLE_HASHSIZE;++i){//check again(removed ++p and works)

		for(b=*p;b;){
			del=b;
			b=b->next;
			avm_memcellclear(del->key);
			avm_memcellclear(del->value);
			free(del);
		}
		p[i]=(avm_table_bucket*)0;
	}

}

void avm_tabledestroy(avm_table* t){
	avm_tablebucketsdestroy(t->strIndexed);
	avm_tablebucketsdestroy(t->numIndexed);
}

unsigned int avm_hash(avm_memcell* i){
	unsigned int hash=0;
	unsigned int res=0;
	unsigned char* tmp;
	int y=0;
	if(i->type==number_m){
		if(i->data.numVal<0){
			res=1%AVM_TABLE_HASHSIZE;
		}else{
			res=(int)i->data.numVal%AVM_TABLE_HASHSIZE;
		}
		
	}else if(i->type==string_m){
		tmp=i->data.strVal;
		for(y=0;tmp[y]!='\0';++y){
			hash=hash*23+tmp[y];
		}
		res=hash%AVM_TABLE_HASHSIZE;
	}else if(i->type==libfunc_m){
		tmp=i->data.libfuncVal;
			for(y=0;tmp[y]!='\0';++y){
			hash=hash*23+tmp[y];
		}
		res=hash%AVM_TABLE_HASHSIZE;
	}else if(i->type==userfunc_m){
		if(i->data.funcVal<0){
			res=1%AVM_TABLE_HASHSIZE;
		}else{
			res=(int)i->data.funcVal%AVM_TABLE_HASHSIZE;
		}
	}else{
		res=-1;
	}

	return res;
}

void avm_tablesetelem( avm_table *table, avm_memcell *index, avm_memcell *content){
	unsigned int hash=avm_hash(index);
	avm_table_bucket *curr;
	avm_memcell *temp;
	if(hash<0){
		printf("in tablesetelem wrong index\n");
		executionFinished=1;
	}else{
		if(index->type==number_m){
			if(content->type!=nil_m){
				table->numIndexed[hash]=avm_insertNewBucket(table->numIndexed[hash],index,content);
				++table->total;
			}
		}else if(index->type==string_m || index->type==libfunc_m){
			if(content->type!=nil_m){
				table->strIndexed[hash]=avm_insertNewBucket(table->strIndexed[hash],index,content);
				++table->total;
			}
		}else if(index->type==table_m){
			if(content->type!=nil_m){
			avm_assign(index,content);
			++table->total;
		}
		}else if(index->type==userfunc_m){
			if(content->type!=nil_m){
				table->numIndexed[hash]=avm_insertNewBucket(table->numIndexed[hash],index,content);
				++table->total;
			}
		}
	}
}
avm_memcell* avm_tablegetelem(avm_table* table, avm_memcell* index){
	unsigned int hash=avm_hash(index);
	avm_table_bucket *curr;
	avm_memcell *temp;
	if(hash<0){
		printf("in tablegetelem wrong index\n");
		executionFinished=1;
		return NULL;
	}
	
	if(index->type==string_m){
		curr=table->strIndexed[hash];
		
		while(curr!=NULL){
			temp=curr->key;
			if(strcmp(temp->data.strVal,index->data.strVal)==0){
				return curr->value;
			}
			curr=curr->next;
		}
	}else if(index->type==libfunc_m){
		curr=table->strIndexed[hash];
		while(curr!=NULL){
			temp=curr->key;
			if(strcmp(temp->data.libfuncVal,index->data.libfuncVal)==0){
				return curr->value;
			}
			curr=curr->next;
		}
	}else if(index->type==number_m){
		curr=table->numIndexed[hash];
		while(curr!=NULL){
			temp=curr->key;
			if(temp->data.numVal==index->data.numVal){
				return curr->value;
			}
			curr=curr->next;
		}
	}else if(index->type==userfunc_m){
		curr=table->numIndexed[hash];
		while(curr!=NULL){
			temp=curr->key;
			if(temp->data.funcVal==index->data.funcVal){
				return curr->value;
			}
			curr=curr->next;
		}
	}
	return NULL;
}

avm_table_bucket* avm_insertNewBucket(avm_table_bucket *head, avm_memcell *index, avm_memcell *content){
	avm_table_bucket *temp=head;
	avm_table_bucket *new=malloc(sizeof(avm_table_bucket));
	int flag=0;
	new->key=malloc(sizeof(avm_memcell));
	new->value=malloc(sizeof(avm_memcell));
	if(index->type==number_m ){
		while(temp!=NULL){
			if(temp->key->data.numVal==index->data.numVal){
				flag=1;
				break;
			}
			temp=temp->next;
		}
		if(flag==1){
			switch(content->type){
			case number_m:{
				temp->value->data.numVal=content->data.numVal;	
				break;	
			}
			case string_m:{
				temp->value->data.strVal=strdup(content->data.strVal);
				break;
			}
			case bool_m:{
				temp->value->data.boolVal=content->data.boolVal;
				break;
			}
			case libfunc_m:{
				temp->value->data.libfuncVal=strdup(content->data.libfuncVal);
				break;
			}
			case userfunc_m:{
				temp->value->data.funcVal=content->data.funcVal;
				break;
			}
			case table_m:{
				temp->value->data.tableVal=content->data.tableVal;
				avm_tableincrefcounter(content->data.tableVal);
				avm_tableincrefcounter(temp->value->data.tableVal);
				break;
			}
			
	}
		}else{
		new->key->type=number_m;
		new->next=NULL;
		new->value->type=content->type;
		new->key->data.numVal=index->data.numVal;
		switch(content->type){
			case number_m:{
				new->value->data.numVal=content->data.numVal;	
				break;	
			}
			case string_m:{
				new->value->data.strVal=strdup(content->data.strVal);
				break;
			}
			case bool_m:{
				new->value->data.boolVal=content->data.boolVal;
				break;
			}
			case libfunc_m:{
				new->value->data.libfuncVal=strdup(content->data.libfuncVal);
				break;
			}
			case userfunc_m:{
				new->value->data.funcVal=content->data.funcVal;
				break;
			}
			case table_m:{
				new->value->data.tableVal=content->data.tableVal;
				avm_tableincrefcounter(content->data.tableVal);
				avm_tableincrefcounter(new->value->data.tableVal);
				break;
			}
			
	}
}
	
	}else if(index->type==string_m){
			while(temp!=NULL){
			if(strcmp(temp->key->data.strVal,index->data.strVal)==0){
				flag=1;
				break;
			}
			temp=temp->next;
		}
		if(flag==1){
			switch(content->type){
			case number_m:{
				temp->value->data.numVal=content->data.numVal;	
				break;	
			}
			case string_m:{
				temp->value->data.strVal=strdup(content->data.strVal);
				break;
			}
			case bool_m:{
				temp->value->data.boolVal=content->data.boolVal;
				break;
			}
			case libfunc_m:{
				temp->value->data.libfuncVal=strdup(content->data.libfuncVal);
				break;
			}
			case userfunc_m:{
				temp->value->data.funcVal=content->data.funcVal;
				break;
			}
			case table_m:{
				temp->value->data.tableVal=content->data.tableVal;
				avm_tableincrefcounter(content->data.tableVal);
				avm_tableincrefcounter(temp->value->data.tableVal);
				break;
			}
			
	}
		}else{
		new->key->type=string_m;
		new->next=NULL;
		new->value->type=content->type;
		new->key->data.strVal=strdup(index->data.strVal);
			switch(content->type){
			case number_m:{
				new->value->data.numVal=content->data.numVal;	
				break;	
			}
			case string_m:{
				new->value->data.strVal=strdup(content->data.strVal);
				break;
			}
			case bool_m:{
				new->value->data.boolVal=content->data.boolVal;
				break;
			}
			case libfunc_m:{
				new->value->data.libfuncVal=strdup(content->data.libfuncVal);
				break;
			}
			case userfunc_m:{
				new->value->data.funcVal=content->data.funcVal;
				break;
			}
			case table_m:{
				new->value->data.tableVal=content->data.tableVal;
				avm_tableincrefcounter(content->data.tableVal);
				avm_tableincrefcounter(new->value->data.tableVal);
				break;
			}
			}
	}
	}else if(index->type==libfunc_m){
			while(temp!=NULL){
			if(strcmp(temp->key->data.libfuncVal,index->data.libfuncVal)==0){
				flag=1;
				break;
			}
			temp=temp->next;
		}
		if(flag==1){
			switch(content->type){
			case number_m:{
				temp->value->data.numVal=content->data.numVal;	
				break;	
			}
			case string_m:{
				temp->value->data.strVal=strdup(content->data.strVal);
				break;
			}
			case bool_m:{
				temp->value->data.boolVal=content->data.boolVal;
				break;
			}
			case libfunc_m:{
				temp->value->data.libfuncVal=strdup(content->data.libfuncVal);
				break;
			}
			case userfunc_m:{
				temp->value->data.funcVal=content->data.funcVal;
				break;
			}
			case table_m:{
				temp->value->data.tableVal=content->data.tableVal;
				avm_tableincrefcounter(content->data.tableVal);
				avm_tableincrefcounter(temp->value->data.tableVal);
				break;
			}
			
	}
		}else{
		new->key->type=libfunc_m;
		new->next=NULL;
		new->value->type=content->type;
		new->key->data.libfuncVal=strdup(index->data.libfuncVal);
			switch(content->type){
			case number_m:{
				new->value->data.numVal=content->data.numVal;	
				break;	
			}
			case string_m:{
				new->value->data.strVal=strdup(content->data.strVal);
				break;
			}
			case bool_m:{
				new->value->data.boolVal=content->data.boolVal;
				break;
			}
			case libfunc_m:{
				new->value->data.libfuncVal=strdup(content->data.libfuncVal);
				break;
			}
			case userfunc_m:{
				new->value->data.funcVal=content->data.funcVal;
				break;
			}
			case table_m:{
				new->value->data.tableVal=content->data.tableVal;
				avm_tableincrefcounter(content->data.tableVal);
				avm_tableincrefcounter(new->value->data.tableVal);
				break;
			}
			}
	}
	}if(index->type==userfunc_m){
		while(temp!=NULL){
			if(temp->key->data.funcVal==index->data.funcVal){
				flag=1;
				break;
			}
			temp=temp->next;
		}
		if(flag==1){
			switch(content->type){
			case number_m:{
				temp->value->data.numVal=content->data.numVal;	
				break;	
			}
			case string_m:{
				temp->value->data.strVal=strdup(content->data.strVal);
				break;
			}
			case bool_m:{
				temp->value->data.boolVal=content->data.boolVal;
				break;
			}
			case libfunc_m:{
				temp->value->data.libfuncVal=strdup(content->data.libfuncVal);
				break;
			}
			case userfunc_m:{
				temp->value->data.funcVal=content->data.funcVal;
				break;
			}
			case table_m:{
				temp->value->data.tableVal=content->data.tableVal;
				avm_tableincrefcounter(content->data.tableVal);
				avm_tableincrefcounter(temp->value->data.tableVal);
				break;
			}
			
	}
		}else{
		new->key->type=userfunc_m;
		new->next=NULL;
		new->value->type=content->type;
		new->key->data.funcVal=index->data.funcVal;
		switch(content->type){
			case number_m:{
				new->value->data.numVal=content->data.numVal;	
				break;	
			}
			case string_m:{
				new->value->data.strVal=strdup(content->data.strVal);
				break;
			}
			case bool_m:{
				new->value->data.boolVal=content->data.boolVal;
				break;
			}
			case libfunc_m:{
				new->value->data.libfuncVal=strdup(content->data.libfuncVal);
				break;
			}
			case userfunc_m:{
				new->value->data.funcVal=content->data.funcVal;
				break;
			}
			case table_m:{
				new->value->data.tableVal=content->data.tableVal;
				avm_tableincrefcounter(content->data.tableVal);
				avm_tableincrefcounter(new->value->data.tableVal);
				break;
			}
			
	}
}
	
	}

if(flag==1){
	return head;
}else{
	if(head==NULL){
		return new;
	}else{
		temp=head;
		while(temp->next!=NULL){
			temp=temp->next;
		}
		temp->next=new;
		return head;
	}
}

}

void print_buckets(avm_table_bucket* head){
	 avm_table_bucket* temp=head;
	 
	 while(temp!=NULL){
	 	printf("{");
	 	print_cell(temp->key);
	 	printf(":");
	 	print_cell(temp->value);
	 	printf("}," );
	 	temp=temp->next;
	 }
}

void avm_registerlibfunc(char *name, library_func_t index){
	int i=libfuncs_newused(name);
	if(i>=0 && i<=11){
		libraryFuncs[i]=index;
	}else{
		fprintf(stderr, "libfunc not found\n" );
	}
}

//library functions
void libfunc_print(){
	unsigned int n=avm_totalactuals();
	unsigned int i;
	printf("\n");
	for(i=0;i<n; ++i){
		char* s=strdup(avm_tostring(avm_getactual(i)));
		printf("%s\n",s );
		if(strcmp(s,"table")==0){
			print_table(avm_getactual(i));
			printf("\n");
		}
		free(s);
	}
	

}

void libfunc_typeof(void){
	unsigned int n=avm_totalactuals();
	if(n!=1){
		printf("one argument (not %d) expected in typeof!",n);
		executionFinished=1;
	}else{
		avm_memcellclear(&retval);
		retval.type=string_m;
		retval.data.strVal=strdup(typeStrings[avm_getactual(0)->type]);
	}
}

void	libfunc_input (void){
	char *str = malloc( sizeof( 1024 ) );
	scanf( "%s" , str );
	int i = 0;
	int dig= 0;
	int dot = 0;
	int letters = 0;

	while( i < strlen( str ) ){
		if( isdigit( str[ i ] ) ){
			dig++;
		}
		else if( str[i] == '.' ){
			dot++;
}
		else if( isalpha( str[ i ] ) ){
			letters++;
		}
		i++;
	}


	if( ((dig+dot)== strlen( str ))  && ( letters == 0) ){
		retval.type = number_m;
		retval.data.numVal = atof( str );
	}
	else if( letters > 0 ){ 
		retval.type = string_m;
		retval.data.strVal = str;
	}
	else if(strcmp( str , "nil" )==0 ){
		retval.type = nil_m;
	}
	else if(strcmp( str , "true" )==0){
		retval.type = bool_m;
		retval.data.boolVal=1;
	}else if(strcmp( str , "false")==0 ){
		retval.type = bool_m;
		retval.data.boolVal=0;
	}
}
void	libfunc_objectmemberkeys (void){
	
	avm_memcell* m=avm_getactual(0);
	int sum=avm_totalactuals();
	if(m->type!=table_m){
		printf("arguments is not a table in objectmemberkeys\n");
		executionFinished=1;
		return;
	}
	if(sum!=1){
		printf("one argument (not %d) expected in objectmemberkeys!",sum);
		executionFinished=1;
		return;
	}
		
	//avm_memcell* temp=m;
	avm_memcell* ret;
	ret->type=table_m;

	ret->data.tableVal=avm_tablenew();
	avm_memcell* index=malloc(sizeof(avm_memcell));
	int i=0,j=0;
	while(i<AVM_TABLE_HASHSIZE){
		//index->type=temp->data.tableVal->strIndexed[i]->key->type;
		if(m->data.tableVal->strIndexed[i]!=NULL){
			index->data.numVal=j;
			++j;
			index->type=number_m;
			avm_tablesetelem(ret->data.tableVal,index,
			m->data.tableVal->strIndexed[i]->key);
			m->data.tableVal->strIndexed[i]=m->data.tableVal->strIndexed[i]->next;
		}
		if(m->data.tableVal->numIndexed[i]!=NULL){
			index->data.numVal=j;
			++j;
			index->type=number_m;
			avm_tablesetelem(ret->data.tableVal,index,
			m->data.tableVal->numIndexed[i]->key);
			m->data.tableVal->numIndexed[i]=m->data.tableVal->numIndexed[i]->next;
		}
		++i;
	}
	retval.type=table_m;
	retval.data.tableVal=ret->data.tableVal;
	avm_tableincrefcounter(ret->data.tableVal);
}
void	libfunc_objecttotalmembers (void){
	int sum=avm_totalactuals();
	avm_memcell* m=avm_getactual(0);
	
	if(m->type!=table_m){
		printf("arguments is not a table in objecttotalmembers\n");
		executionFinished=1;
	}
	if(sum!=1){
		printf("one argument (not %d) expected in objecttotalmembers!",sum);
		executionFinished=1;
	}else{
		unsigned int count=m->data.tableVal->total;
		retval.type=number_m;
		retval.data.numVal=count;
	}
}
void	libfunc_objectcopy (void){
	
}
void 	libfunc_totalarguments (void){

	unsigned i=avm_get_envvalue(topsp+AVM_SAVEDTOPSP_OFFSET);
	avm_memcellclear(&retval);
	if(i==0){
		printf("libfunc TotalArguments called, but not in a function\n");
		retval.type=nil_m;
		retval.data.numVal=0;
	}else{
		retval.type=number_m;
		retval.data.numVal=avm_get_envvalue(i+AVM_NUMACTUALS_OFFSET);
	}

}
void	libfunc_argument (void){
	unsigned int sum=avm_totalactuals();
	unsigned int temp=0;
	unsigned int tempTsp=0;
	avm_memcell* func=malloc(sizeof(avm_memcell));
	if(sum!=1){
		printf("one argument (not %d) expected in argument!",sum);
		executionFinished=1;
	}
	tempTsp=avm_get_envvalue(topsp+AVM_SAVEDTOPSP_OFFSET);
	avm_memcellclear(&retval);
	func=avm_getactual(0);
	assert(func->type==number_m);
	temp=func->data.numVal;
	avm_assign(&retval,&stack[tempTsp+AVM_NUMACTUALS_OFFSET+temp+1]);
}

void	libfunc_strtonum (void){
	int sum=avm_totalactuals();
	avm_memcell *m=avm_getactual(0);
	if(m->type!=string_m){
			printf("arguments is not a string in strtonum\n");
		executionFinished=1;
	}
	if(sum!=1){
		printf("one argument (not %d) expected in strtonum!",sum);
		executionFinished=1;
	}else{
		unsigned int num=atof(strdup(m->data.strVal));
		retval.type=number_m;
		retval.data.numVal=num;
	}
}
void	libfunc_sqrt (void){
	int sum=avm_totalactuals();
	avm_memcell *m=avm_getactual(0);
	if(m->type!=number_m){
		printf("argument is not a number in sqrt\n");
		executionFinished=1;
		return;
	}
	if(sum!=1){
		printf("one argument (not %d) expected in sqrt!",sum);
		executionFinished=1;
		return;
	}
	if(m->data.numVal<0){
		printf("can't calculate sqrt of negative number\n");
		retval.type=nil_m;
	
		return;
	}else{
		retval.type=number_m;
		retval.data.numVal=sqrt(m->data.numVal);
	}
}
void	libfunc_cos (void){
	int sum=avm_totalactuals();
	avm_memcell *m=avm_getactual(0);
	if(m->type!=number_m){
		printf("argument is not a number in cos\n");
		executionFinished=1;
		return;
	}
	if(sum!=1){
		printf("one argument (not %d) expected in cos!",sum);
		executionFinished=1;
		return;
	}
	if(m->data.numVal<0 || m->data.numVal>360){
		printf("can't calculate cos of numbers > 360 & numbers < 0\n");
		retval.type=nil_m;
		retval.data.strVal=strdup("nil_m");
		executionFinished=1;
		return;
	}else{
		retval.type=number_m;
		double pi=3.14159265;
		double val=pi/180;
		double res=cos(m->data.numVal*val);
		retval.data.numVal=res;
	}
}
void	libfunc_sin (void){
	int sum=avm_totalactuals();
	avm_memcell *m=avm_getactual(0);
	if(m->type!=number_m){
		printf("argument is not a number in sin\n");
		executionFinished=1;
		return;
	}
	if(sum!=1){
		printf("one argument (not %d) expected in sin!",sum);
		executionFinished=1;
		return;
	}
	if(m->data.numVal<0 || m->data.numVal>360){
		printf("can't calculate sin of numbers > 360 & numbers < 0\n");
		retval.type=nil_m;
		retval.data.strVal=strdup("nil_m");
		executionFinished=1;
		return;
	}else{
		retval.type=number_m;
		double pi=3.14159265;
		double val=pi/180;
		double res=sin(m->data.numVal*val);
		retval.data.numVal=res;
	}
}


void iOpcode_tostring(instruction *temp){
	if(temp->opcode==assign_v){
			printf("ASSIGN\t");
		}else if(temp->opcode==add_v){
			printf("ADD\t");
		}else if(temp->opcode==mul_v){
			printf("MUL\t");
		}else if(temp->opcode==div_v){
			printf("DIV\t");
		}else if(temp->opcode==sub_v){
			printf("SUB\t");
		}else if(temp->opcode==mod_v){
			printf("MOD\t");
		}else if(temp->opcode==and_v){
			printf("AND\t");
		}else if(temp->opcode==or_v){
			printf("OR\t");
		}else if(temp->opcode==not_v){
			printf("NOT\t");
		}else if(temp->opcode==jump_v){
			printf("JUMP\t");
		}else if(temp->opcode==jeq_v){
			printf("JEQ\t");
		}else if(temp->opcode==jne_v){
			printf("JNE\t");
		}else if(temp->opcode==jle_v){
			printf("JLE\t");
		}else if(temp->opcode==jlt_v){
			printf("JLT\t");
		}else if(temp->opcode==jge_v){
			printf("JGE\t");
		}else if(temp->opcode==jgt_v){
			printf("JGT\t");
		}else if(temp->opcode==call_v){
			printf("CALL\t");
		}else if(temp->opcode==getretval_v){
			printf("GETRETVAL\t");
		}else if(temp->opcode==funcenter_v){
			printf("FUNCENTER\t");
		}else if(temp->opcode==funcexit_v){
			printf("FUNCEXIT\t");
		}else if(temp->opcode==tablesetelem_v){
			printf("TABLESETELEM\t");
		}else if(temp->opcode==tablegetelem_v){
			printf("TABLEGETELEM\t");
		}else if(temp->opcode==newtable_v){
			printf("NEWTABLE\t");
		}else if(temp->opcode==ret_v){
			printf("RETURN\t");
		}else if(temp->opcode==pusharg_v){
			printf("PUSHARG\t");
		}else if(temp->opcode==uminus_v){
			printf("UMINUS\t");
		}else if(temp->opcode==nop_v){
			printf("NOP\t");
		}else{
			printf("---\t");
		}
}

void print_cell(avm_memcell* m){
	int i=0;
	avm_table_bucket* temp;
	switch(m->type){
		case string_m:{
			printf(" %s",m->data.strVal );
			break;
		}
		case number_m:{
			printf(" %0.2f",m->data.numVal );
			break;
		}
		case bool_m:{
			printf("%s",bool_tostring(m) );
			break;
		}
		case libfunc_m:{
			printf(" %s",m->data.libfuncVal );
			break;
		}
		case userfunc_m:{
			printf("%s", userfunc_tostring(m) );
			break;
		}
		case table_m:{
			printf("[");
			for(i=0;i<AVM_TABLE_HASHSIZE;++i){
				if(m->data.tableVal->strIndexed[i]!=NULL){
					 temp=m->data.tableVal->strIndexed[i];
					print_buckets(temp);
				}
				if(m->data.tableVal->numIndexed[i]!=NULL){
					temp=m->data.tableVal->numIndexed[i];
					print_buckets(temp);
				
				}
			}
			printf("]");
			break;
		}
		default:{
			printf("------\n");
		}
	}
}

void print_table(avm_memcell* m){
	 int i=0;
	avm_table_bucket* temp;
	printf("[" );
	for(i=0;i<AVM_TABLE_HASHSIZE;++i){
		if(m->data.tableVal->numIndexed[i]!=NULL){
			temp=m->data.tableVal->numIndexed[i];
			while(temp!=NULL){
				print_buckets(temp);
				temp=temp->next;
			}
		}
		if(m->data.tableVal->strIndexed[i]!=NULL){
			temp=m->data.tableVal->strIndexed[i];
			while(temp!=NULL){
				print_buckets(temp);
				temp=temp->next;
			}
		}
	}
	printf("]" );

}
char * memcell_tochar(avm_memcell* temp){
 avm_memcell* m=temp;
    char *string;
	
	switch(m->type){
		case string_m:{
			return m->data.strVal;
		}
		case bool_m:{
			string=strdup(bool_tostring(m));
			return string;
		}
		case userfunc_m:{
			string=strdup(userfunc_tostring(m));
			return string;
		}
		case libfunc_m:{
			return m->data.libfuncVal;
		}
		case number_m:{
			string=strdup(number_tostring(m));
			return string;
		}
	}
  

 
}
