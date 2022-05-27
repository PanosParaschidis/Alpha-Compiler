#ifndef __QUADS_H__
#define __QUADS_H__

#include "symtable.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define EXPAND_SIZE 1024
#define CURR_SIZE (total*sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE*sizeof(quad)+CURR_SIZE)
extern unsigned int programVarOffset;
extern unsigned int functionLocalOffset;
extern unsigned int formalArgOffset;
extern unsigned int scopeSpaceCounter;
extern struct list* continueList;
extern struct list* breakList;

typedef enum expr_t {
	    var_e,
	    tableitem_e,
	    programfunc_e,
	    libraryfunc_e,
		arithexpr_e,
	    boolexpr_e,
	    assgnexpr_e,
	    newtable_e,
	    constint_e,
	    constdouble_e,
	    constbool_e,
	    conststring_e,
	    nil_e
}expr_t;

typedef enum iopcode{ 	
			assign, add, sub,
			mul, divv, mod,
			uminus, and, or, 
			not, if_eq, if_noteq,
			if_lesseq, if_greatereq, if_less,
			if_greater, jump, call,
			param, ret, getretval,
			funcstart, funcend, tablecreate,
			tablegetelem, tablesetelem, nop
 }iopcode;



 typedef struct expr{ 
	    expr_t type;
	   	struct stoixeio* symbol;
	    struct expr* index;
	    struct callStruct* callList;
	   	int iValue;		// int Nums
	    double dValue;	//double num
	    char* sValue;	//Strings and ids
	    unsigned int boolValue; 	//0 if false,1 if true
	 

	   	struct expr* next;
}expr;
 
 typedef struct callStruct{
 	expr* elist;
 	unsigned int method;
 	char* name;
 }calls;
 
typedef struct quad{ 
		 iopcode op;
	     expr* result;
	     expr* arg1;
	     expr* arg2;
	     unsigned int label;	//JUMPTARGET
	     unsigned int line;
	     unsigned int taddress;
}quad;

typedef struct list{
	unsigned int tempQuad;
	struct list *next;
}list;

typedef struct loopList{
	unsigned int counter;
	struct loopList* next;
}loopList;

typedef struct functionLocals
{
	unsigned int locals;
	struct functionLocals* next;	
}functionLocals;

typedef struct forprefix{
	unsigned int enter;
	unsigned int test;
}forprefix;

typedef struct indexed
{
	expr* name;
	expr* value;
	struct indexed* next;

}indexed;

enum scopespace_t{ //new
	programvar,functionlocal,formalarg
};

enum symbol_t{ //new
	var_s,programfunc_s,libraryfunc_s
};







void expand (void);
void emit(iopcode op,expr* arg1,expr* arg2,expr* res, unsigned int label, unsigned int line);
enum scopespace_t currScopeSpace();
unsigned int currScopeOffset();
void inCurrScopeOffset();
void enterScopeSpace();
void exitScopeSpace();
expr* lvalue_expr(struct stoixeio * sym);
char * newTempName();
void resetCounter();
void resetFormalArgsOffset();
void resetFunctionLocalsOffset();
void restoreCurrScopeOffset(unsigned int n);
unsigned nextQuadLabel();
void patchLabel(unsigned int quadNo, unsigned int label);
void checkuminus(expr* e);
unsigned int istempname(const char* s);
unsigned int istempexpr(expr* e);
void PrintQuads();
expr* newExpr(expr_t type);
expr* NewExprInt(int value);
expr* NewExpDouble(double value);
expr* NewNilExp();
expr* NewBoolExp(int value);
expr* NewStringExp(char *value);
expr* ReverseList(expr *head);
list* createList(int tempQuad, list* head);
loopList* createLoopList(int loopCounter, loopList* head);
unsigned int popLoopList(loopList** head);
unsigned int popLocalsList(functionLocals** head);
functionLocals* createLocalsList(unsigned int locals,functionLocals* head);
expr* make_normcall(expr* elist);
expr* make_methodcall(char* two, expr* four);

#endif