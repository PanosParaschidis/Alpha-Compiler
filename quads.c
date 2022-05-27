
#include "symtable.h"
#include "quads.h"




unsigned total=0;
unsigned int currQuad=0;
quad* quads=(quad*) 0;
int tempCounter=1;
char cated_string[5];

char * newTempName(){
	char string[]="_t";
	
	sprintf(cated_string,"%s%d",string,tempCounter);
	++tempCounter;
	return cated_string;
}

void resetCounter(){
	tempCounter=1;
}

expr* NewExprInt(int value){
	expr* new = malloc (sizeof(struct expr) );
	new->iValue = value;
	new->type = constint_e;
	new->sValue=NULL;
	return new;
}

expr* NewExpDouble(double value){
	expr* new = malloc (sizeof(struct expr) );
	new->dValue = value;
	new->type = constdouble_e;
	new->sValue=NULL;
	return new;
}
expr* NewNilExp(){
	expr *new = malloc (sizeof(struct expr));
	new->type = nil_e;
	new->sValue=NULL;
    return new;
}
expr* NewBoolExp(int value){
	expr* new = malloc (sizeof(struct expr) );
	new->boolValue = value;
	new->type = constbool_e;
	new->sValue=NULL;
	return new;
}

struct stoixeio * newTemp(struct symboltable* table){
	char *name=newTempName();
	struct stoixeio* sym=lookupNode(table,name);
	if(sym==NULL){
		sym=createEntry(0,GLOBAL,name,0,0);
		insertSymbol(table,sym);
		inCurrScopeOffset();
		//printf("\t\ttemp name:%s counter:%d\n",sym->name,tempCounter );
		return sym;
	}else{

		//printf("\t\ttemp name:%s counter:%d\n",sym->name,tempCounter );
		return sym;
	}
}



loopList* createLoopList(int loopCounter, loopList* head){
	loopList* new=malloc(sizeof(loopList));
	new->counter=loopCounter;
	new->next=head;
	return new;
}

functionLocals* createLocalsList(unsigned int locals,functionLocals* head){
	functionLocals* new=malloc(sizeof(functionLocals));
	new->locals=locals;
	new->next=head;
	return new;
}


unsigned int popLoopList(loopList** head){
	loopList* temp=*head;
	unsigned int val=temp->counter;
	if(temp->next==NULL){
		*head=NULL;
	}else{
		*head=temp->next;	
	}
	
	return val;
}

unsigned int popLocalsList(functionLocals** head){
	functionLocals* temp=*head;
	unsigned int val=temp->locals;
	if(temp->next==NULL){
		*head=NULL;
	}else{
		*head=temp->next;
	}
	return val;
}


void expand (){
	assert(total==currQuad);
	quad *p=(quad*)malloc(NEW_SIZE);
	if(quads){
		memcpy(p,quads,CURR_SIZE);
		free(quads);
	}
	quads=p;
	total+=EXPAND_SIZE;
}

void emit(iopcode op,expr* arg1,expr* arg2,expr* res, unsigned int label, unsigned int line){
	if(currQuad==total){
		expand();
	}
	quad* p=quads+currQuad++;
	p->op=op;

	p->arg1=arg1;
	p->arg2=arg2;
	p->result=res;
	p->label=label;
	p->line=line;

}

enum scopespace_t currScopeSpace(){
	if(scopeSpaceCounter==1){
		return programvar;
	}else{
		if(scopeSpaceCounter%2==0){
			return formalarg;
		}else{
			return functionlocal;
		}
	}
}

unsigned int currScopeOffset(){
	switch(currScopeSpace()){
		case programvar : { 
			
			return programVarOffset;}
		case functionlocal : {
			
			return functionLocalOffset;}
		case formalarg : {
			
			return formalArgOffset;}
		default : assert(0); 
	}
}

void inCurrScopeOffset(){
	switch (currScopeSpace()){
		case programvar : ++programVarOffset;  break;
		case functionlocal : ++functionLocalOffset; break;
		case formalarg : ++formalArgOffset; break;
		default: assert(0);
	}
}

void enterScopeSpace(){
	++scopeSpaceCounter;
}

void exitScopeSpace(){
	assert(scopeSpaceCounter>1);
	--scopeSpaceCounter;
}

expr* lvalue_expr(struct stoixeio * sym){
	expr* new=malloc(sizeof(expr));
	new->symbol=sym;
	new->sValue=strdup(sym->name);
	switch(sym->type){
		case USERFUNC : new->type=programfunc_e; break;
		case LIBFUNC : new->type=libraryfunc_e; break;
		default: new->type=var_e;
	}
	new->next=NULL;
	new->index=malloc(sizeof(expr));

	return new;
}

expr* make_normcall(expr* elist){
	expr* norm=malloc(sizeof(expr));
	norm->callList=malloc(sizeof(struct callStruct));
	norm->callList->elist=elist;
	norm->callList->method=0;
	norm->callList->name=NULL;
	return norm;
}

expr* make_methodcall(char* two, expr* four){
	expr* method=malloc(sizeof(expr));
	method->callList=malloc(sizeof(struct callStruct));
	method->callList->elist=four;
	method->callList->method=1;
	method->callList->name=strdup(two);
	return method;
}

expr * tableMake(struct symboltable* table, expr * elist){
	expr* new=newExpr(newtable_e);
	new->symbol=newTemp(table);
	new->sValue=strdup(new->symbol->name);
	emit(tablecreate,new,NULL,NULL,-1,currQuad);
	int i=0;
	expr* temp=elist;
	while(temp!=NULL){
		emit(tablesetelem,new,NewExprInt(i++),temp,-1,currQuad);
		temp=temp->next;
	}
	return new;

}

expr* tableMakeIndex(struct symboltable* table, struct indexed * indexed){
		expr* new=newExpr(newtable_e);
	new->symbol=newTemp(table);
	new->sValue=strdup(new->symbol->name);
	emit(tablecreate,new,NULL,NULL,-1,currQuad);
	int i=0;
	struct indexed* temp=indexed;
	while(temp!=NULL){
		emit(tablesetelem,new,temp->name,temp->value,-1,currQuad);
		temp=temp->next;
	}
	return new;
}

expr* make_call(struct symboltable* table, expr* lvalue,expr* elist){
	expr* func=emit_ifTableItem(table,lvalue);

	expr *paramet=ReverseList(elist);
	while(paramet!=NULL){
		emit(param,paramet,NULL,NULL,-1,currQuad);
		paramet=paramet->next;
	}
	emit(call,func,NULL,NULL,-1,currQuad);
	expr *result=newExpr(var_e);
	result->symbol=newTemp(table);
	result->sValue=strdup(result->symbol->name);
	result->symbol->scope_t=programvar;
	emit(getretval,result,NULL,NULL,-1,currQuad);
	return result;
}


list* createList(int tempQuad, list* head){
	list* new=malloc(sizeof(list));
	new->tempQuad=tempQuad;
	new->next=head;
	return new;
}

expr* ReverseList(expr* head)
{
    expr* prev   = NULL;
    expr* current = head;
    expr* next;
    while (current != NULL)
    {
        next  = current->next;  
        current->next = prev;   
        prev = current;
        current = next;
    }
    return prev;
}

expr* newExpr(expr_t type){
	expr* new=(expr*)malloc(sizeof(expr));
	new->type=type;
	return new;
}


expr* NewStringExp(char *value){
	expr *new=newExpr(conststring_e);
	new->sValue=strdup(value);
	return new;
}

expr* emit_ifTableItem(struct symboltable* table,expr *e){
	if(e->type!= tableitem_e){
		return e;
	}else{
		
		expr *result=newExpr(var_e);
		result->symbol=newTemp(table);
		result->sValue=strdup(result->symbol->name);
		emit(tablegetelem,e,e->index,result,-1,currQuad);
		return result;
	}
}

expr* member_item(struct symboltable* table,expr *lvalue,char *name){
	lvalue=emit_ifTableItem(table,lvalue);
	expr* item=newExpr(tableitem_e);
	item->symbol=lvalue->symbol;
	item->index=NewStringExp(name);
	item->sValue=strdup(lvalue->sValue);
	return item;
}

expr* member_item1(struct symboltable* table,expr *lvalue,int name){
	lvalue=emit_ifTableItem(table,lvalue);
	expr* item=newExpr(tableitem_e);
	item->symbol=lvalue->symbol;
	item->index=NewExprInt(name);
	item->sValue=strdup(lvalue->sValue);
	return item;
}

void resetFormalArgsOffset(){
	formalArgOffset=0;
}

void resetFunctionLocalsOffset(){
	functionLocalOffset=0;
}

void restoreCurrScopeOffset(unsigned int n){
	switch(currScopeSpace()){
		case programvar : programVarOffset=n; break;
		case functionlocal : functionLocalOffset=n; break;
		case formalarg : formalArgOffset=n; break;
		default : assert(0);
	}
}

unsigned nextQuadLabel(){
	return currQuad;
}

void patchLabel(unsigned int quadNo, unsigned int label){
	assert(quadNo<currQuad);
	quads[quadNo].label=label;
}

 
void checkuminus(expr* e){
    if(e->type == constbool_e || e->type == conststring_e || e->type == nil_e || e->type == newtable_e || e->type == programfunc_e || e->type == libraryfunc_e || e->type == boolexpr_e) {
        printf("Illegal expr to unary -\n");
}
}
 
unsigned int istempname(const char* s){
    return *s == '_';
}
 
unsigned int istempexpr(expr* e){
    return e->symbol && e->symbol->type == var_s && istempname(e->symbol->name);
}


char* toString(struct expr* e){
	char *value;
	
	if (e->type==var_e || e->type==tableitem_e || e->type==programfunc_e || e->type==libraryfunc_e || e->type==arithexpr_e || e->type==boolexpr_e || e->type==assgnexpr_e || e->type==newtable_e || e->type==conststring_e){
	
		return e->sValue;

		}

	else if(e->type==constbool_e){
		if(e->boolValue==1){
			return "TRUE";
		}else{
			return "FALSE";
		}
			}  
	else if(e->type==nil_e){
		return "null";
	}
	else{
	  	return value="***";
	}

	


}

void PrintEx(expr *e){
	if(e==NULL){
		return;
	}
	if(e->type==constint_e){
		printf("%d\t",e->iValue );
	}else if(e->type==constdouble_e){
		printf("%.2lf\t",e->dValue );
	}else{
		char* value=toString(e);
		printf("%s\t",value );
	}
	
}

void PrintQuads(){

	int j=0;
	quad *temp = quads;
	printf("\n\n\nQUADS\n");
	printf("\n\n  opcode\targ1\targ2\tres\n\n");
	while(j < currQuad){
	  	
		printf("%d:  ",j);
		temp= quads+j++;
		if(temp->op==assign){
			printf("ASSIGN\t");
		}else if(temp->op==add){
			printf("ADD\t");
		}else if(temp->op==mul){
			printf("MUL\t");
		}else if(temp->op==divv){
			printf("DIV\t");
		}else if(temp->op==sub){
			printf("SUB\t");
		}else if(temp->op==mod){
			printf("MOD\t");
		}else if(temp->op==and){
			printf("AND\t");
		}else if(temp->op==or){
			printf("OR\t");
		}else if(temp->op==not){
			printf("NOT\t");
		}else if(temp->op==jump){
			printf("JUMP\t");
		}else if(temp->op==if_eq){
			printf("IF_EQ\t");
		}else if(temp->op==if_noteq){
			printf("IF_NOTEQ\t");
		}else if(temp->op==if_less){
			printf("IF_LESS\t");
		}else if(temp->op==if_lesseq){
			printf("IF_LESSEQ\t");
		}else if(temp->op==if_greater){
			printf("IF_GREATER\t");
		}else if(temp->op==if_greatereq){
			printf("IF_GREATEREQ\t");
		}else if(temp->op==call){
			printf("CALL\t");
		}else if(temp->op==getretval){
			printf("GETRETVAL\t");
		}else if(temp->op==funcend){
			printf("FUNCEND\t");
		}else if(temp->op==funcstart){
			printf("FUNCSTART\t");
		}else if(temp->op==tablesetelem){
			printf("TABLESETELEM\t");
		}else if(temp->op==tablegetelem){
			printf("TABLEGETELEM\t");
		}else if(temp->op==tablecreate){
			printf("TABLECREATE\t");
		}else if(temp->op==ret){
			printf("RETURN\t");
		}else if(temp->op==param){
			printf("PARAM\t");
		}else if(temp->op==uminus){
			printf("UMINUS\t");
		}else{
			printf("----\t");
		}
		
		if(temp->arg1!=NULL)
		      PrintEx(temp->arg1);
		if(temp->arg2!=NULL)
		      PrintEx(temp->arg2);
		  if(temp->result!=NULL)
		      PrintEx(temp->result);
		
		if(temp->label != -1)
		      printf("%d",temp->label);
		printf("\n");
	}
}
