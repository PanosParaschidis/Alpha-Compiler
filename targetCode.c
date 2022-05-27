#include "targetCode.h"
	
generator_func_t generators_t[] = {
	generate_assign,
	generate_add,
	generate_sub,
	generate_mul,
	generate_div,
	generate_mod,
	generate_uminus,
	generate_and,
	generate_or,
	generate_not,
	generate_if_eq,
	generate_if_noteq,
	generate_if_lesseq,
	generate_if_greatereq,
	generate_if_less,
	generate_if_greater,
	generate_jump,
	generate_call,
	generate_param,
	generate_return,
	generate_getretval,
	generate_funcstart,
	generate_funcend,
	generate_newtable,
	generate_tablegetelem,
	generate_tablesetelem,
	generate_nop,
	
	
};

unsigned int currInstr = 0;
unsigned int currPquad=0;
unsigned totalInstr=0;
incomplete_jump *ij_head =(incomplete_jump*) 0;
unsigned ij_total = 0;

instruction *inst = NULL;
funcStack *functionHead=NULL;
extern unsigned int currQuad;

char ** stringArray;
unsigned totalStrings=0;

double* numArray;
unsigned totalNums=0;

char ** libFuncArray;
unsigned totalLibFuncs=0;

userFunc * userFuncArray;
unsigned totalUserFuncs=0;


void initiator(){
	for(currPquad=0;currPquad<currQuad;currPquad++){


		(*generators_t[quads[currPquad].op]) (quads+currPquad);

	}

	patch_incomplete_jumps();

	printInstruction();
	PrintIstrText();
	writeBinary();
}

void expand_i(){
	assert(totalInstr==currInstr);
	instruction *i=(instruction*)malloc(NEW_SIZE_I); 
	if(inst){
		memcpy(i,inst,CURR_SIZE_I);
		free(inst);
	}
	inst=i;
	totalInstr+=EXPAND_SIZE_I;
}


void emit_i(instruction* i){
	assert(i);

	if(currInstr==totalInstr){
		expand_i();
	}

	instruction* new=inst+currInstr++;
	new->arg1=i->arg1;
	new->arg2=i->arg2;
	new->result=i->result;
	new->opcode=i->opcode;
	new->srcLine=currInstr-1;
	
}

vmarg* make_operand(expr* e){
	vmarg* arg=malloc(sizeof(vmarg));
	if(e==NULL){
		return NULL;
	}
	switch(e->type){
		case var_e:
		case tableitem_e:
		case arithexpr_e:
		case boolexpr_e:
		case newtable_e:
		case assgnexpr_e:{
			assert(e->symbol);
			arg->val=e->symbol->offset;

			switch(e->symbol->scope_t){
				case programvar: {
					arg->type=global_a;
					break;
				}
				case functionlocal: {
					arg->type=local_a;
					break;
				}
				case formalarg: {
					arg->type=formal_a; 
					break;
				}
				default: assert(0);
			}
			break;
		}

		case constbool_e:{
			arg->val=e->boolValue;
			arg->type=bool_a;
			break;
		}

		case conststring_e:{
			arg->val=consts_newstring(e->sValue);
			arg->type=string_a; 
			break;
		}

		case constdouble_e:{
			arg->val=consts_newnumber(e->dValue);
			arg->type=number_a; 
			break;
		}

		case constint_e:{
			arg->val=consts_newnumber(e->iValue);
			arg->type=number_a; 
			break;
		}

		case nil_e:{
			arg->type=nil_a; 
			break;
		}

		case programfunc_e:{
			arg->type=userfunc_a;
			arg->val=userfuncs_newfunc(e->symbol);
			break;
		}

		case libraryfunc_e:{
			arg->type=libfunc_a;
			arg->val=libfuncs_newused(e->symbol->name);
			break;
		}	
		default:assert(0);
	}
}

unsigned int nextInstLabel(){
	return currInstr;
}

void patch_incomplete_jumps(){
	incomplete_jump* temp=ij_head;
	while(temp!=NULL){
		if(temp->iaddress==currQuad){
			inst[temp->instrNo].result->val=nextInstLabel();
		}else{
			inst[temp->instrNo].result->val=quads[temp->iaddress].taddress;
		}
		temp=temp->next;
	}
}

vmarg* make_numberoperand(double val){
	vmarg* arg=malloc(sizeof(vmarg));
	arg->val=consts_newnumber(val);
	arg->type=number_a;
	return arg;
}
vmarg* make_booloperand(int val){
	vmarg* arg=malloc(sizeof(vmarg));
	arg->val=val;
	arg->type=bool_a;
	return arg;
}

vmarg* make_retvaloperand(vmarg* arg){
	arg->type=retval_a;
	return arg;
}
void generate(vmopcode op, quad* q){
	instruction* i;
	i=malloc(sizeof(instruction));
	//assert(i);
	i->opcode=op;
	i->arg1=make_operand(q->arg1);
	i->arg2=make_operand(q->arg2);
	i->result=make_operand(q->result);
	i->srcLine=q->line;
	q->taddress=nextInstLabel();
	emit_i(i);
}

void generate_add(quad *q){
	generate(add_v,q);
}

void generate_sub(quad *q){
	generate(sub_v,q);
}

void generate_mul(quad *q){
	generate(mul_v,q);
}

void generate_div(quad *q){
	generate(div_v,q);
}

void generate_mod(quad *q){
	generate(mod_v,q);
}

void generate_newtable(quad *q){
	generate(newtable_v,q);
}

void generate_tablegetelem(quad *q){
	generate(tablegetelem_v,q);
}

void generate_tablesetelem(quad *q){
	generate(tablesetelem_v,q);
}

void generate_assign(quad *q){
	generate(assign_v,q);
}

void generate_nop(){
	instruction* t;
	t=malloc(sizeof(instruction));
	t->opcode=nop_v;
	emit_i(t);
}

void generate_uminus(quad *q){
	q->taddress=nextInstLabel();
	instruction *t=malloc(sizeof(instruction));
	t->opcode=mul_v;
	t->arg1=make_operand(q->arg2);
	t->arg2=make_numberoperand(-1);
	t->result=make_operand(q->result);
	t->srcLine=q->line;
	emit_i(t);
}

void generate_relational(vmopcode op, quad *q){
	instruction* t=malloc(sizeof(instruction));
	t->opcode=op;
	t->arg1=make_operand(q->arg1);
	t->arg2=make_operand(q->arg2);
	t->result=malloc(sizeof(vmarg));
	t->result->type=label_a;
	t->srcLine=q->line;
	if(q->label<currPquad){
		t->result->val=quads[q->label].taddress;
	}else{
		add_incomplete_jump(nextInstLabel(),q->label);
	}
	q->taddress=nextInstLabel();
	emit_i(t);
}

void generate_jump(quad *q){
	generate_relational(jump_v,q);
}

void generate_if_eq(quad *q){
	generate_relational(jeq_v,q);
}

void generate_if_noteq(quad *q){
	generate_relational(jne_v,q);
}

void generate_if_greater(quad *q){
	generate_relational(jgt_v,q);
}

void generate_if_greatereq(quad *q){
	generate_relational(jge_v,q);
}

void generate_if_less(quad *q){
	generate_relational(jlt_v,q);
}

void generate_if_lesseq(quad *q){
	generate_relational(jle_v,q);
}

vmarg* reset_operand(){
	return ((vmarg*) NULL);
}

void generate_not(quad *q){
	q->taddress=nextInstLabel();
	instruction *t=malloc(sizeof(instruction));
	instruction *t1=malloc(sizeof(instruction));
	instruction *t2=malloc(sizeof(instruction));
	instruction *t3=malloc(sizeof(instruction));

	t->opcode=jeq_v;
	t->arg1=make_operand(q->arg1);
	t->arg2=make_booloperand(0);//make false
	t->result=malloc(sizeof(vmarg));
	t->result->type=label_a;
	t->result->val=nextInstLabel()+3;
	emit_i(t);

	t1->opcode=assign_v;
	t1->arg1=make_booloperand(0);//make false
	t1->arg2=reset_operand();
	t1->result=make_operand(q->result);
	emit_i(t1);

	t2->opcode=jump_v;
	t2->arg1=reset_operand();
	t2->arg2=reset_operand();
	t2->result=malloc(sizeof(vmarg));
	t2->result->type=label_a;
	t2->result->val=nextInstLabel()+2;
	emit_i(t2);

	t3->opcode=assign_v;
	t3->arg1=make_booloperand(1);//make true
	t3->arg2=reset_operand();
	t3->result=make_operand(q->result);
	
	emit_i(t3);

}

void generate_or(quad *q){
	q->taddress=nextInstLabel();
	instruction *t=malloc(sizeof(instruction));
	instruction *t1=malloc(sizeof(instruction));
	instruction *t2=malloc(sizeof(instruction));
	instruction *t3=malloc(sizeof(instruction));
	instruction *t4=malloc(sizeof(instruction));

	t->opcode=jeq_v;
	t->arg1=make_operand(q->arg1);
	t->arg2=make_booloperand(1);//make true
	t->result=malloc(sizeof(vmarg));
	t->result->type=label_a;
	t->result->val=nextInstLabel()+4;
	emit_i(t);

	t1->opcode=jeq_v;
	t1->arg1=make_operand(q->arg2);
	t1->arg2=make_booloperand(1);
	t1->result=malloc(sizeof(vmarg));
	t1->result->val=nextInstLabel()+3;
	t1->result->type=label_a;
	t1->srcLine=0;
	emit_i(t1);

	t2->opcode=assign_v;
	t2->arg1=make_booloperand(0);//make false
	t2->arg2=reset_operand();
	t2->result=make_operand(q->result);
	emit_i(t2);

	t3->opcode=jump_v;
	t3->arg1=reset_operand();
	t3->arg2=reset_operand();
	t3->result=malloc(sizeof(vmarg));
	t3->result->type=label_a;
	t3->result->val=nextInstLabel()+2;
	emit_i(t3);

	t4->opcode=assign_v;
	t4->arg1=make_booloperand(1);//make true
	t4->arg2=reset_operand();
	t4->result=make_operand(q->result);
	emit_i(t4);

}

void generate_and(quad *q){
	q->taddress=nextInstLabel();
	instruction *t=malloc(sizeof(instruction));
	instruction *t1=malloc(sizeof(instruction));
	instruction *t2=malloc(sizeof(instruction));
	instruction *t3=malloc(sizeof(instruction));
	instruction *t4=malloc(sizeof(instruction));

	t->opcode=jeq_v;
	t->arg1=make_operand(q->arg1);
	t->arg2=make_booloperand(0);//make false
	t->result=malloc(sizeof(vmarg));
	t->result->type=label_a;
	t->result->val=nextInstLabel()+4;
	emit_i(t);

	t1->opcode=jeq_v;
	t1->arg1=make_operand(q->arg2);
	t1->arg2=make_booloperand(0);
	t1->result=malloc(sizeof(vmarg));
	t1->result->type=label_a;
	t1->result->val=nextInstLabel()+3;
	emit_i(t1);

	t2->opcode=assign_v;
	t2->arg1=make_booloperand(1);//make true
	t2->arg2=reset_operand();
	printf("in generate%s  %d\n",q->result->symbol->name,q->result->type );
	t2->result=make_operand(q->result);
	printf("in genera 2 %d\n",t->result->type);
	emit_i(t2);

	t3->opcode=jump_v;
	t3->arg1=reset_operand();
	t3->arg2=reset_operand();
	t3->result=malloc(sizeof(vmarg));
	t3->result->type=label_a;
	t3->result->val=nextInstLabel()+2;
	emit_i(t3);

	t4->opcode=assign_v;
	t4->arg1=make_booloperand(0);//make true
	t4->arg2=reset_operand();
	t4->result=make_operand(q->result);
	emit_i(t4);

}

void generate_param(quad* q){
	q->taddress=nextInstLabel();
	instruction *t=malloc(sizeof(instruction));
	t->opcode=pusharg_v;
	t->arg1=make_operand(q->arg1);
	t->arg2=t->result=NULL;
	t->srcLine=q->line;
	emit_i(t);
}

void generate_call(quad *q){//thelei douleia
	q->taddress=nextInstLabel();
	assert(q->arg1->symbol);
	instruction *t=malloc(sizeof(instruction));
	t->opcode=call_v;
	t->arg1=make_operand(q->arg1);
	t->arg2=t->result=NULL;
	t->srcLine=q->line;
	emit_i(t);
	if(q->arg1->type==programfunc_e){
	unsigned int jumpLabel=userFuncArray[userfuncs_newfunc(q->arg1->symbol)].endaddress+1;
	inst[jumpLabel].result->val=nextInstLabel();
}
	/*
	if(q->arg1->type!=libraryfunc_e){
		printf("in if\n");
		
		printf("in if1\n");
		instruction* jump=malloc(sizeof(instruction));
		jump->opcode=jump_v;
		jump->result=malloc(sizeof(vmarg));
		jump->result->type=label_a;
		printf("in if2\n");
		jump->result->val=userFuncArray[userfuncs_newfunc(q->arg1->symbol)].address;
		jump->arg1=jump->arg2=NULL;
		emit_i(jump);
		printf("in if 3 %d \n",jumpLabel);
		
printf("in if4\n");
	}*/
}

void generate_getretval(quad *q){
	q->taddress=nextInstLabel();
	instruction *t=malloc(sizeof(instruction));
	t->opcode=assign_v;
	t->result=make_operand(q->arg1);
	t->arg1=malloc(sizeof(vmarg));
	t->arg1=make_retvaloperand(t->arg1);
	t->arg1->val=0;
	t->arg2=NULL;
	t->srcLine=q->line;
	emit_i(t);
}

unsigned int consts_newstring(char *s){

	if(totalStrings==0){
		stringArray= (char**)malloc(sizeof(char*));
	}else{
		stringArray =(char **) realloc(stringArray, ((totalStrings)+1)*sizeof(char*) );
	}
	stringArray[totalStrings]=strdup(s);
	++totalStrings;
	return totalStrings-1;
}

unsigned int consts_newnumber(double value){
	if(totalNums==0){
		numArray=(double*)malloc(sizeof(double));
	}else{
		numArray=(double*)realloc(numArray,((totalNums)+1)*sizeof(double));
	}
	numArray[totalNums]=value;
	unsigned int index=totalNums;
	++totalNums;
	return index;
}	

unsigned int userfuncs_newfunc(struct stoixeio* sym){
	int i=0;
	if(sym->type!=USERFUNC){
		fprintf(stderr, "Error can't insert something in userfunc array, that is not a function, line: %d \n",yylineno );
		exit(-1);
	}
	while(i<totalUserFuncs){
		if(strcmp(userFuncArray[i].id,sym->name)==0 && userFuncArray[i].address==sym->iAddress ){

			return i;

		}
		++i;
	}
	if(totalUserFuncs==0){
		userFuncArray=(userFunc*)malloc(sizeof(userFunc));
	}else{
		userFuncArray=(userFunc*)realloc(userFuncArray,((totalUserFuncs)+1)*sizeof(userFunc));
	}

	userFuncArray[totalUserFuncs].address=sym->iAddress;
	userFuncArray[totalUserFuncs].endaddress=-1;
	userFuncArray[totalUserFuncs].localSize=sym->totalLocals;
	userFuncArray[totalUserFuncs].id=strdup(sym->name);
	++totalUserFuncs;

	return (totalUserFuncs-1);
}

unsigned int libfuncs_newused(char* name){
	int i=0;
	while(i<totalLibFuncs){
		if(strcmp(libFuncArray[i],name)==0){
			return i;
		}
		++i;
	}
	if(totalLibFuncs==0){
		libFuncArray = (char**)malloc(sizeof(char *));
    }
    else{
		libFuncArray =(char **)realloc(libFuncArray, ((totalLibFuncs)+1)*sizeof(char*) );
    }

    libFuncArray[totalLibFuncs] = strdup(name);
    ++totalLibFuncs;
    return totalLibFuncs-1;

}

void add_incomplete_jump(unsigned int instrNo, unsigned int iaddress){
	incomplete_jump* temp=malloc(sizeof(incomplete_jump));

	temp->instrNo=instrNo;
	temp->iaddress=iaddress;
	if(ij_head==NULL){
		temp->next=NULL;
		ij_head=temp;
	}else{
		temp->next=ij_head;
		ij_head=temp;
	}
	++ij_total;
}

void pushReturnList(unsigned int label){
	returnList* new=malloc(sizeof(returnList));
	new->label=label;
	returnList* head=functionHead->head;
	new->next=head;
	functionHead->head=new;
}

void pushFunctionList(struct stoixeio* func){
	funcStack *new=malloc(sizeof(funcStack));
	new->sym=func;
	new->head=NULL;
	new->startJump=nextInstLabel()-1;
	
	if(functionHead==NULL){
		new->next=NULL;
		functionHead=new;
	}else{
		new->next=functionHead;
		functionHead=new;
		
	}

}

funcStack* popFunctionList(){
	if(functionHead==NULL){
		return NULL;
	}
	funcStack* pop=functionHead;
	functionHead=functionHead->next;
	return pop;
}

void generate_funcstart(quad* q){

	struct stoixeio* f=q->arg1->symbol;
	instruction* jump=malloc(sizeof(instruction));
	jump->opcode=jump_v;
	jump->result=malloc(sizeof(vmarg));
	jump->result->type=label_a;
	jump->arg1=jump->arg2=NULL;
	emit_i(jump);

	f->iAddress=nextInstLabel();
	q->taddress=nextInstLabel();

	pushFunctionList(f);

	instruction* t=malloc(sizeof(instruction));
	t->opcode=funcenter_v;
	t->result=make_operand(q->arg1);
	t->arg1=NULL;
	t->arg2=NULL;
	t->srcLine=q->line;
	emit_i(t);

	
}
void generate_return(quad* q){
	q->taddress=nextInstLabel();
	instruction* t=malloc(sizeof(instruction));
	t->opcode=assign_v;
	t->result=malloc(sizeof(vmarg));
	t->result=make_retvaloperand(t->result);
	if(q->result){
		t->arg1=make_operand(q->result);	
	}else{
		t->arg1=make_operand(NewBoolExp(0));
	}
	t->arg2=NULL;
	t->srcLine=q->line;
	emit_i(t);

	pushReturnList(nextInstLabel());
	instruction* jump=malloc(sizeof(instruction));
	jump->opcode=jump_v;
	jump->result=malloc(sizeof(vmarg));
	jump->result->type=label_a;
	jump->arg1=jump->arg2=NULL;
	emit_i(jump);
}

void backpatchReturn(funcStack* f){
	
	returnList *topReturn=f->head;
	
	while(topReturn!=NULL){
		inst[topReturn->label].result->val=nextInstLabel();
		topReturn=topReturn->next;
	}
	inst[f->startJump].result->val=nextInstLabel()+2;
}
void generate_funcend(quad* q){
	funcStack* f=popFunctionList();
	q->taddress=nextInstLabel();
	userFuncArray[userfuncs_newfunc(q->arg1->symbol)].endaddress=nextInstLabel();
	backpatchReturn(f);
	instruction* t=malloc(sizeof(instruction));
	t->opcode=funcexit_v;
	t->result=make_operand(q->arg1);
	t->arg1=t->arg2=NULL;
	t->srcLine=q->line;
	emit_i(t);

	instruction* jump=malloc(sizeof(instruction));
	jump->opcode=jump_v;
	jump->result=malloc(sizeof(vmarg));
	jump->result->type=label_a;
	jump->result->val=0;
	jump->arg1=jump->arg2=NULL;
	emit_i(jump);
}

void PrintArg(vmarg *arg){
	if(arg==NULL){
		return;
	}
	if(arg->type==number_a){
		printf("0%d(num)%d:%.1f\t",arg->type, arg->val,numArray[arg->val]);
	}else if(arg->type==string_a){
		printf("0%d(string)%d:%s\t",arg->type, arg->val,stringArray[arg->val] );
	}else if(arg->type==libfunc_a){
		printf("0%d(libfunc)%d:%s\t",arg->type, arg->val, libFuncArray[arg->val]);
	}else if(arg->type==userfunc_a){
		printf("0%d(userfunc)%d:%s\t", arg->type, arg->val, userFuncArray[arg->val].id);
	}else if(arg->type==bool_a){
		printf("0%d(boolean)%d:",arg->type, arg->val);
		if(arg->val==1){
			printf("true\t");
		}else{
			printf("false\t");
		}
	}else if(arg->type==nil_a){
		printf("0%d(nil)%d:nil\t",arg->type,arg->val);
	}else if(arg->type==label_a){
		printf("0%d(label)%d\t",arg->type ,arg->val);
	}else if(arg->type==global_a){
		printf("0%d(global)%d\t",arg->type, arg->val);
	}else if(arg->type==formal_a){
		printf("0%d(formal)%d\t",arg->type, arg->val);
	}else if(arg->type==local_a){
		printf("0%d(local)%d\t",arg->type, arg->val);
	}else if(arg->type==retval_a){
		printf("%d(retval)%d\t",arg->type, arg->val);
	}
	else{
		printf("\tnothing\t");
	}
	
}

void printInstruction(){

	int j=0;
	instruction *temp = inst;
	printf("\n\n\n INSTRUCTIONS\n");
	printf("\n\n opcode\targ1\targ2\tres\n\n");
	while(j < currInstr){
	  	
		printf("%d:  ",j);
		temp= inst+j++;
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
			printf("----\t");
		}
		
		if(temp->arg1!=NULL)
		      PrintArg(temp->arg1);
		if(temp->arg2!=NULL)
		      PrintArg(temp->arg2);
		  if(temp->result!=NULL)
		      PrintArg(temp->result);
		
		
		printf("\n");
	}
}

void PrintIstrText(){
	FILE* out=fopen("code.txt","w");
	if(!out){
		fprintf(stderr, "Error in opening code file\n");
	}	
 	int magic=1234;
	fprintf(out, "magicnumber -> %d\n",magic );
	fprintf(out, "arrays -> strings number userfunctions libfunctions\n");
	
	PrintAllTables(out);
	fprintf(out, "total instructions %d\n",currInstr );
	instruction* temp=inst;
	int i=0;
	while(i<currInstr){
		fprintf(out, "Opcode %d\n",temp->opcode );
		if(temp->arg1!=NULL){
			fprintf(out, "\tArg1\n" );
			fprintf(out, "\t\tType: %d\n",temp->arg1->type );
			fprintf(out, "\t\tValue: %d\n",temp->arg1->val );

		}
		if(temp->arg2!=NULL){
			fprintf(out, "\tArg2\n" );
			fprintf(out, "\t\tType: %d\n",temp->arg2->type );
			fprintf(out, "\t\tValue: %d\n",temp->arg2->val );

		}
		if(temp->result!=NULL){
			fprintf(out, "\tRes\n" );
			fprintf(out, "\t\tType: %d\n",temp->result->type );
			fprintf(out, "\t\tValue: %d\n",temp->result->val );

		}
		temp+=1;
		++i;
	}
	if(out) fclose(out);

}

void PrintAllTables(FILE* out){
	int i=0;
	fprintf(out, "Const Tables\n" );
	fprintf(out, "\tStrings:\n" );
	for(i=0;i<totalStrings;++i){
		fprintf(out, "\t\tIndex: %d, Data: %s\n",i,stringArray[i] );
	}

	fprintf(out, "\tNumbers:\n" );
	for(i=0;i<totalNums;++i){
		fprintf(out, "\t\tIndex: %d, Data: %lf\n",i,numArray[i] );

	}

	fprintf(out, "\tLibFuncs:\n" );
	for(i=0;i<totalLibFuncs;++i){
		fprintf(out, "\t\tIndex: %d, Data: %s\n",i,libFuncArray[i] );

	}

	fprintf(out, "\tUserFuncs:\n" );
	for(i=0;i<totalUserFuncs;++i){
		fprintf(out, "\t\tIndex: %d, Data:\n\t\t\t\ttaddress: %d,localsSize: %d, id: %s\n",i,userFuncArray[i].address,userFuncArray[i].localSize,userFuncArray[i].id );

	}
}

void writeBinary(){
	FILE* out=fopen("BinFile.bin","wb");
	instruction *t;
	int i;
	int tmp=0;
	if(!out){
		fprintf(stderr, "Error in opening Binary file\n");
	}
	int magic=1234;
	fwrite(&magic,sizeof(int),1,out);
	fwrite(&totalStrings,sizeof(int),1,out);
	for(i=0;i<totalStrings;++i){
		fwrite(&stringArray[i],sizeof(char *),1,out);
	}
	fwrite(&totalNums,sizeof(int),1,out);
	for(i=0;i<totalNums;++i){
		fwrite(&numArray[i],sizeof(double),1,out);
	}
	fwrite(&totalLibFuncs,sizeof(int),1,out);
	for(i=0;i<totalLibFuncs;++i){
		fwrite(&libFuncArray[i],sizeof(char *),1,out);
	}
	fwrite(&totalUserFuncs,sizeof(int),1,out);
	for(i=0;i<totalUserFuncs;++i){
		fwrite(&userFuncArray[i].id,sizeof(char *),1,out);
		fwrite(&userFuncArray[i].address,sizeof(int),1,out);
		fwrite(&userFuncArray[i].localSize,sizeof(int),1,out);
	}

	fwrite(&currInstr,sizeof(unsigned int),1,out);
	t=inst;
	while(tmp<currInstr){
		fwrite(&(t->opcode),sizeof(int),1,out);
		if(t->arg1){
			fwrite(&(t->arg1->type),sizeof(int),1,out);
			fwrite(&(t->arg1->val),sizeof(int),1,out);
		}
		if(t->arg2){
			fwrite(&(t->arg2->type),sizeof(int),1,out);
			fwrite(&(t->arg2->val),sizeof(int),1,out);
		}
		if(t->result){
			fwrite(&(t->result->type),sizeof(int),1,out);
			fwrite(&(t->result->val),sizeof(int),1,out);
		}
		t+=1;
		++tmp;
	}
	if(out){
		fclose(out);
	}
}