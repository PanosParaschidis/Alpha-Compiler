%{
	#include <string.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include "symtable.h"
	#include "functions.h"
	#include "quads.h"
	#include "targetCode.h"
	#include "avm.h"

	int scope=0;
	SymTable *symTable;
	
	node* lastFunc;
	int arrayFlag=0;
	extern unsigned int currQuad;
		unsigned int programVarOffset=0;
	unsigned int functionLocalOffset=0;
	unsigned int formalArgOffset=0;
	unsigned int scopeSpaceCounter=1;
	   struct list* continueList;
	    struct list* breakList;
	    struct loopList* loopCounterStack;
	    unsigned int loopCounter=0;
	    struct functionLocals* localsHead;
	struct expr *res=NULL;
	int memberFlag;



		void printLocals(){
			printf("current Locals %d\n",functionLocalOffset);
		struct functionLocals* temp=localsHead;
		while(temp!=NULL){
			printf("previous %d\n",temp->locals );	
			temp=temp->next;
		}
		
	}
%}
%start program


%token 	IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE LOCAL TRUE FALSE NIL NOT AND OR
%token	ASSIGNMENT ADDITION SUBTRACTION MULTIPLICATION DIVISION MODULO EQUALITY INEQUALITY 
%token INCREMENT DECREMENT GREATER_THAN LESS_THAN GREATER_THAN_OR_EQ_TO LESS_THAN_OR_EQ_TO

%token  <iValue> INTCONST
%token  <dValue> REALCONST
%token  <sValue> ID 
%token  <sValue> STRING

%token	LEFT_BRACE RIGHT_BRACE LEFT_SQ_BRACKET RIGHT_SQ_BRACKET LEFT_PARENTHESES RIGHT_PARENTHESES 
%token SEMICOLON COMMA COLON DOUBLE_COLON PERIOD DOUBLE_PERIOD OTHER	

%right	ASSIGNMENT
%left	AND OR

%nonassoc	EQUALITY INEQUALITY
%nonassoc GREATER_THAN GREATER_THAN_OR_EQ_TO LESS_THAN LESS_THAN_OR_EQ_TO 
%left	ADDITION SUBTRACTION 
%left MULTIPLICATION DIVISION MODULO
%right	NOT INCREMENT DECREMENT UMINUS
%left	PERIOD DOUBLE_PERIOD

%left LEFT_PARENTHESES RIGHT_PARENTHESES LEFT_BRACE RIGHT_BRACE LEFT_SQ_BRACKET RIGHT_SQ_BRACKET
	
%nonassoc IF ELSE

%type <indexed_t> indexed indexedelem indexed2
%type <prefix> whilestart whilecond 
%type <exprs> elist2 loopstm
%type <exprs> normcall
%type <exprs> callsuffix
%type <exprs> methodcall
%type <exprs> block
%type <exprs> ifstm
%type <prefix> ifprefix
%type <prefix> elseprefix
%type <exprs> expr
%type <exprs> lvalue
%type <exprs> member
%type <exprs> primary
%type <exprs> assignexpr
%type <exprs> call
%type <exprs> term
%type <exprs> objectdef
%type <exprs> const
%type <exprs> elist
%type <exprs> stm
%type <sValue> funcname
%type <iValue> funcbody
%type <node> funcprefix
%type <node> funcdef
%type <forpref> forprefix
%type <prefix> N M
%union
{
	char* sValue;
	int iValue;
	double dValue;
	unsigned int prefix;
	struct expr* exprs;
	struct stoixeio *node;
	struct indexed *indexed_t;
	struct forprefix* forpref;
}

%%


	program	:	stmnts{printf("#%d program -> statements\n",yylineno);}
			;

	stmnts	:	stm stmnts{printf("#%d statements -> stm statements \n",yylineno);}
			|	{printf("#%d statements -> empty \n", yylineno);}
			;

	stm 	: 	expr SEMICOLON {resetCounter();
								
								
							printf("#%d statement -> expr; \n", yylineno);}
			|	ifstm {$$=$1;
						printf("#%d statement -> if statement \n", yylineno);}
			|	whilestm {$$=NULL;
						 printf("#%d statement -> while statement \n", yylineno);}
			|	forstm {$$=NULL;
						printf("#%d statement -> for statement \n", yylineno);}
			|	returnstm {$$=NULL;
						printf("#%d statement -> return; \n", yylineno);}
			| 	BREAK SEMICOLON {if(loopCounter!=0){
									breakList=createList(currQuad,breakList);
									emit(jump,NULL,NULL,NULL,-1,currQuad);
									
								}else{
									fprintf(stderr, "\t\t\tBREAK found, but not in a loop!, line: %d\n",yylineno );
								}
								
								printf("#%d statement -> break \n", yylineno);}
			|	CONTINUE SEMICOLON {if(loopCounter!=0){
									continueList=createList(currQuad,continueList);
									emit(jump,NULL,NULL,NULL,-1,currQuad);
								}else{
									fprintf(stderr, "\t\t\tCONTINUE found, but not in a loop!, line: %d\n",yylineno );
								}
								printf("#%d statement -> continue; \n", yylineno);}
			|	block {$$=$1;
						printf("#%d statement -> block \n", yylineno);}
			| 	funcdef {$$=lvalue_expr($1);
						printf("#%d statement -> funcdef \n", yylineno);}
			|	SEMICOLON {$$=NULL;
						printf("#%d statement -> ; \n", yylineno);}
			;

	expr	:	assignexpr	{$$=$1;
							printf("#%d expr -> assignexpr \n", yylineno);}
			|	expr ADDITION expr {res=lvalue_expr(newTemp(symTable));
									$$=res;
									emit(add,$1,$3,res,-1,currQuad);
									printf("#%d expr -> expr + expr \n", yylineno);}
			|	expr SUBTRACTION expr {res=lvalue_expr(newTemp(symTable));
									$$=res;
									emit(sub,$1,$3,res,-1,currQuad);
										printf("#%d expr -> expr - expr \n", yylineno);}
			|	expr MULTIPLICATION expr {res=lvalue_expr(newTemp(symTable));
										$$=res;
										emit(mul,$1,$3,res,-1,currQuad);
										printf("#%d expr -> expr * expr \n", yylineno);}
			|	expr DIVISION expr {res=lvalue_expr(newTemp(symTable));
									$$=res;
									emit(divv,$1,$3,res,-1,currQuad);
									printf("#%d expr -> expr / expr \n", yylineno);}
			|	expr MODULO expr {res=lvalue_expr(newTemp(symTable));
								  $$=res;
								  emit(mod,$1,$3,res,-1,currQuad);
								  printf("#%d expr -> expr mod expr \n", yylineno);}
			|	expr GREATER_THAN expr {emit(if_greater,$1,$3,NULL,currQuad+3,currQuad);
										res=lvalue_expr(newTemp(symTable));
										$$=res;
										emit(assign,NewBoolExp(0),NULL,res,-1,currQuad);
										emit(jump,NULL,NULL,NULL,currQuad+2,currQuad);
										emit(assign,NewBoolExp(1),NULL,$$,-1,currQuad);
					 				printf("#%d expr -> expr > expr \n", yylineno);}
			|	expr GREATER_THAN_OR_EQ_TO expr {emit(if_greatereq,$1,$3,NULL,currQuad+3,currQuad);
											res=lvalue_expr(newTemp(symTable));
											$$=res;
											emit(assign,NewBoolExp(0),NULL,res,-1,currQuad);
											emit(jump,NULL,NULL,NULL,currQuad+2,currQuad);
											emit(assign,NewBoolExp(1),NULL,$$,-1,currQuad);
										printf("#%d expr -> expr >= expr \n", yylineno);}
			|	expr LESS_THAN_OR_EQ_TO expr {emit(if_lesseq,$1,$3,NULL,currQuad+3,currQuad);
											res=lvalue_expr(newTemp(symTable));
											$$=res;
											emit(assign,NewBoolExp(0),NULL,res,-1,currQuad);
											emit(jump,NULL,NULL,NULL,currQuad+2,currQuad);
											emit(assign,NewBoolExp(1),NULL,$$,-1,currQuad);
											printf("#%d expr -> expr <= expr \n", yylineno);}
			|	expr LESS_THAN expr {emit(if_less,$1,$3,NULL,currQuad+3,currQuad);
											res=lvalue_expr(newTemp(symTable));
											$$=res;
											emit(assign,NewBoolExp(0),NULL,res,-1,currQuad);
											emit(jump,NULL,NULL,NULL,currQuad+2,currQuad);
											emit(assign,NewBoolExp(1),NULL,$$,-1,currQuad);	
									printf("#%d expr -> expr < expr \n", yylineno);}
			|	expr EQUALITY expr {emit(if_eq,$1,$3,NULL,currQuad+3,currQuad);
									res=lvalue_expr(newTemp(symTable));
									$$=res;
									emit(assign,NewBoolExp(0),NULL,res,-1,currQuad);
									emit(jump,NULL,NULL,NULL,currQuad+2,currQuad);
									emit(assign,NewBoolExp(1),NULL,$$,-1,currQuad);
									printf("#%d expr -> expr == expr \n", yylineno);}
			|	expr INEQUALITY expr {emit(if_noteq,$1,$3,NULL,currQuad+3,currQuad);
									res=lvalue_expr(newTemp(symTable));
									$$=res;
									emit(assign,NewBoolExp(0),NULL,res,-1,currQuad);
									emit(jump,NULL,NULL,NULL,currQuad+2,currQuad);
									emit(assign,NewBoolExp(1),NULL,$$,-1,currQuad);
									printf("#%d expr -> expr != expr \n", yylineno);}
			|	expr AND expr {res=lvalue_expr(newTemp(symTable));
								$$=res;
								emit(and,$1,$3,res,-1,currQuad);
								//emit(if_eq,$$,NewBoolExp(1),NULL,currQuad+3,currQuad);
								
								//emit(assign,NewBoolExp(0),NULL,res,-1,currQuad);
								//emit(jump,NULL,NULL,NULL,currQuad+2,currQuad);
								//emit(assign,NewBoolExp(1),NULL,$$,-1,currQuad);
								printf("#%d expr -> expr and expr \n", yylineno);}
			|	expr OR expr {res=lvalue_expr(newTemp(symTable));
								$$=res;
								emit(or,$1,$3,res,-1,currQuad);
								//emit(if_eq,$$,NewBoolExp(1),NULL,currQuad+3,currQuad);
								
								//emit(assign,NewBoolExp(0),NULL,res,-1,currQuad);
								//emit(jump,NULL,NULL,NULL,currQuad+2,currQuad);
								//emit(assign,NewBoolExp(1),NULL,$$,-1,currQuad);
								printf("#%d expr -> expr or expr \n", yylineno);}
			|	term {$$=$1;
				
						printf("#%d expr -> term \n", yylineno);
						
					}
			;

	term	:	LEFT_PARENTHESES expr RIGHT_PARENTHESES {$$=$2;
														printf("#%d term -> (expr) \n", yylineno);}
			|	SUBTRACTION expr %prec UMINUS {checkuminus($2);
												res=lvalue_expr(newTemp(symTable));
												$$=res;
												$$->type=arithexpr_e;
												emit(uminus,NULL,$2,res,-1,currQuad);
												printf("#%d term -> -expr \n", yylineno);}
			|	NOT expr {res=lvalue_expr(newTemp(symTable));
						$$=res;
						$$->type=boolexpr_e;
						emit(not,$2,NULL,res,-1,currQuad);
							printf("#%d term -> not expr \n", yylineno);}
			|	INCREMENT lvalue {
									if($2->type==tableitem_e){
										$$=emit_ifTableItem(symTable,$2);
										emit(add,$$,NewExprInt(1),$$,-1,currQuad);
										emit(tablesetelem,$2,$2->index,$$,-1,currQuad);
									}else{
										emit(add,$2,NewExprInt(1),$2,-1,currQuad);
										$$=newExpr(arithexpr_e);
										$$->symbol=newTemp(symTable);
										$$->sValue=strdup($$->symbol->name);
										emit(assign,$2,NULL,$$,-1,currQuad);
									}
									handleLvalue(symTable, $2->sValue, yylineno);
									printf("#%d term -> ++lvalue \n", yylineno);}
			|	lvalue {handleLvalue(symTable, $1->sValue, yylineno);} INCREMENT {$$=newExpr(var_e);
																				  $$->symbol=newTemp(symTable);
																				  $$->sValue=strdup($$->symbol->name);
																				  if($1->type==tableitem_e){
																				  
																				  		struct expr *value=emit_ifTableItem(symTable,$1);
																				  		emit(assign,value,NULL,$$,-1,currQuad);
																				  		emit(add,value,NewExprInt(1),value,-1,currQuad);
																				  		emit(tablesetelem,$1,$1->index,value,-1,currQuad);
																				  }else{
																				  		emit(assign,$1,NULL,$$,-1,currQuad);
																				  		emit(add,$1,NewExprInt(1),$1,-1,currQuad);
																				  }
																				printf("#%d term -> lvalue++ \n", yylineno);}
			|	DECREMENT lvalue {if($2->type==tableitem_e){
										$$=emit_ifTableItem(symTable,$2);
										emit(sub,$$,NewExprInt(1),$$,-1,currQuad);
										emit(tablesetelem,$2,$2->index,$$,-1,currQuad);
									}else{
										emit(sub,$2,NewExprInt(1),$2,-1,currQuad);
										$$=newExpr(arithexpr_e);
										$$->symbol=newTemp(symTable);
										$$->sValue=strdup($$->symbol->name);
										emit(assign,$2,NULL,$$,-1,currQuad);
									}
									handleLvalue(symTable,$2->sValue, yylineno);
									printf("#%d term -> --lvalue \n", yylineno);}
			| 	lvalue {handleLvalue(symTable, $1->sValue, yylineno);} DECREMENT {$$=newExpr(var_e);
																				  $$->symbol=newTemp(symTable);
																				  $$->sValue=strdup($$->symbol->name);
																				  if($1->type==tableitem_e){
																				  
																				  		struct expr *value=emit_ifTableItem(symTable,$1);
																				  		emit(assign,value,NULL,$$,-1,currQuad);
																				  		emit(sub,value,NewExprInt(1),value,-1,currQuad);
																				  		emit(tablesetelem,$1,$1->index,value,-1,currQuad);
																				  }else{
																				  		emit(assign,$1,NULL,$$,-1,currQuad);
																				  		emit(sub,$1,NewExprInt(1),$1,-1,currQuad);
																				  }
																					printf("#%d term -> lvalue-- \n", yylineno);}
			| 	primary {$$=$1;
						printf("#%d term -> primary \n", yylineno);
						}
			;

	assignexpr	:	lvalue {if(arrayFlag==0 && memberFlag==0){
		handleLvalue(symTable, $1->sValue, yylineno);
							}
							arrayFlag=0;
							
	 }
				ASSIGNMENT expr{
							if($1->type==tableitem_e){
								emit(tablesetelem,$1,$1->index,$4,-1,currQuad);
								$$=emit_ifTableItem(symTable,$1);
								$$->type=assgnexpr_e;
							}else{
								emit(assign,$4,NULL,$1,-1,currQuad);
								$$=newExpr(assgnexpr_e);
								$$->symbol=newTemp(symTable);
								
								$$->sValue=strdup($$->symbol->name);
								emit(assign,$1,NULL,$$,-1,currQuad);
								
							}
					printf("#%d assignexpr -> lvalue = expr \n", yylineno);}
				;

	primary	:	lvalue {
						$$=emit_ifTableItem(symTable,$1);
						printf("#%d primary -> lvalue \n", yylineno);}
			|	call {$$=$1;
						printf("#%d primary -> call \n", yylineno);}
			|	objectdef {$$=$1;
						printf("#%d primary -> objectdef \n", yylineno);}
			| 	LEFT_PARENTHESES funcdef RIGHT_PARENTHESES {$$=lvalue_expr($2);
															printf("#%d primary -> (funcdef) \n", yylineno);}
			|	const {$$=$1;
						printf("#%d primary -> const \n", yylineno);}
			;

	lvalue	:	ID {$$=lvalue_expr(handleId(symTable,$1,scope,yylineno));
					inCurrScopeOffset();
					
					printf("#%d lvalue -> id \n", yylineno);}
			|	LOCAL ID {$$=lvalue_expr(handleLocalId(symTable,$2,scope,yylineno));
								inCurrScopeOffset();
								
							printf("#%d lvalue -> local id \n", yylineno);}
			|	DOUBLE_COLON ID{$$=lvalue_expr(handleScopeId(symTable,$2,yylineno));
							printf("#%d lvalue -> ::id \n", yylineno);}
			|	member {$$=$1;
					
						printf("#%d lvalue -> member \n", yylineno);}
			;
 	
	member	:	lvalue PERIOD ID {$$=member_item(symTable,$1,$3);
									
									//$$->sValue=strdup($1->sValue);
		printf("#%d member -> lvalue.id \n", yylineno);}
			|	lvalue LEFT_SQ_BRACKET expr RIGHT_SQ_BRACKET {$1=emit_ifTableItem(symTable,$1);
															  $$=newExpr(tableitem_e);
															  $$->symbol=$1->symbol;
															  $$->index=$3;
															  $$->sValue=strdup($1->sValue);
															  arrayFlag=1;
															  
															  printf("#%d member -> lvalue[expr] \n", yylineno);}
			|	call PERIOD ID {$$=member_item(symTable,$1,$3);
				
							printf("#%d member -> call.id \n", yylineno);}
			|	call LEFT_SQ_BRACKET expr RIGHT_SQ_BRACKET {arrayFlag=1;
															if($3->sValue==NULL){
																$$=member_item1(symTable,$1,$3->iValue);
															}else{
																$$=member_item(symTable,$1,$3->sValue);	
															}
															
															printf("#%d member -> call[expr] \n", yylineno);}
			;

	call	:	call LEFT_PARENTHESES elist RIGHT_PARENTHESES {$$=make_call(symTable,$1,$3);
																printf("#%d call -> call(elist) \n", yylineno);}
			|	lvalue callsuffix {if($2->callList->method==1){
									//struct expr* self=$1;
									struct expr* tmp=emit_ifTableItem(symTable,member_item(symTable,$1,$2->callList->name));
									$1->next=$2->callList->elist;
									$2->callList->elist=$1;
									
			}
				$$=make_call(symTable,$1,$2->callList->elist);
									printf("#%d call -> lvalue callsuffix \n", yylineno);}
			|	LEFT_PARENTHESES funcdef RIGHT_PARENTHESES LEFT_PARENTHESES elist RIGHT_PARENTHESES {struct expr* func=newExpr(programfunc_e);
																									func->symbol=$2;
																									func->sValue=strdup($2->name);
																									$$=make_call(symTable,func,$5);
																									printf("#%d call -> (funcdec)(elist) \n", yylineno);}
			;

	callsuffix	:	normcall {$$=$1;
								printf("#%d callsuffix -> normcall \n", yylineno);}
				|	methodcall {$$=$1;
								printf("#%d callsuffix -> methodcall \n", yylineno);}
				;

	normcall 	:	LEFT_PARENTHESES elist RIGHT_PARENTHESES {
															$$=make_normcall($2);
																printf("#%d normcall -> (elist) \n", yylineno);}
				;

	methodcall	:	DOUBLE_PERIOD ID LEFT_PARENTHESES elist RIGHT_PARENTHESES {$$=make_methodcall($2,$4);
																				printf("#%d methodcall -> ..id(elist) \n", yylineno);}
				;

	elist	:	expr elist2 {$$=$1;
							$$->next=$2;
							printf("#%d elist -> expr elist2 \n", yylineno);}
			|	{$$=NULL;
				printf("#%d elist -> empty \n", yylineno);}
			;
	elist2	:	COMMA expr elist2 {$$=$2;
									$$->next=$3;
									printf("#%d elist2 -> , expr elist2 \n", yylineno);}
			|	{$$=NULL;
				printf("#%d elist2 -> empty \n", yylineno);}
			;

	objectdef 	:	LEFT_SQ_BRACKET elist RIGHT_SQ_BRACKET {$$=tableMake(symTable,$2);
															printf("#%d objectdef -> [elist] \n", yylineno);}
				| 	LEFT_SQ_BRACKET indexed	RIGHT_SQ_BRACKET {$$=tableMakeIndex(symTable,$2);
															printf("#%d objectdef -> [indexed] \n", yylineno);}
				;

	indexed		:	indexedelem indexed2 {$$=$1;
										$$->next=$2;
										printf("#%d indexed -> indexelem indexed2 \n", yylineno);}
				;

	indexed2 	:	COMMA indexedelem indexed2 {$$=$2;
												$$->next=$3;
												printf("#%d indexed2 -> , indexelem indexed2 \n", yylineno);}
				|	{$$=NULL;
					printf("#%d indexed2 -> empty \n", yylineno);}
				;

	indexedelem 	:	LEFT_BRACE expr COLON expr RIGHT_BRACE {struct indexed *new=malloc(sizeof(struct indexed));
																new->name=$2;
																if($2->sValue!=NULL){
																	new->name->sValue=strdup($2->sValue);	
																}else{
																	new->name->iValue=$2->iValue;
																}
																
																
																new->value=$4;
																$$=new;
																printf("#%d indexedelem -> {expr:expr} \n", yylineno);}
					;

	block	:	LEFT_BRACE{scope++; } RIGHT_BRACE {hideVar(symTable,scope);
												  scope--;

												  printf("#%d block -> {} \n", yylineno);}
			| 	LEFT_BRACE{scope++;   } stm stmnts RIGHT_BRACE{hideVar(symTable,scope);
													printf("#%d block -> [stmt*] \n",yylineno);
															scope--;}
			;

	funcname : ID{$$=$1;
				lastFunc=handleFuncId(symTable,$1,scope,yylineno);
						//inCurrScopeOffset();
						}
			  | {lastFunc=handleFuncNoId(symTable,"def_func_",scope,yylineno);
				$$=lastFunc->name;
			//inCurrScopeOffset();
						}
    		 ;

    funcprefix : FUNCTION funcname{
    			$$=lastFunc;
    			$$->iAddress=nextQuadLabel();
    			emit(funcstart,lvalue_expr($$),NULL,NULL,-1,currQuad);
    			
    			localsHead=createLocalsList(functionLocalOffset,localsHead);
    				//push(functioLocalStaxk,functionLocalOffset)
    			
    		    	enterScopeSpace();
    		    	
    		    	resetFormalArgsOffset();
    		    	
    		    	resetFunctionLocalsOffset();
    		    	
    	
    			
    			
    			}
    			;

    funcargs :LEFT_PARENTHESES{scope++; } idlist RIGHT_PARENTHESES{scope--;
    	
    		enterScopeSpace();
    		

    }
    		;

    funcbody : block{$$=functionLocalOffset;		restoreCurrScopeOffset(popLocalsList(&localsHead)); exitScopeSpace();exitScopeSpace();}
    	     ;

   	funcdef :   funcprefix funcargs funcblockstart funcbody funcblockend
   			{
   			
   				
   				$1->totalLocals=$4;
   				
   				$$=$1;
   				emit(funcend,lvalue_expr($1),NULL,NULL,-1,currQuad);
   			}
   	funcblockstart : {loopCounterStack=createLoopList(loopCounter,loopCounterStack);
   						loopCounter=0;
   					
    			
    			
    			}
   				   ;
   	funcblockend : {if(loopCounterStack!=NULL){
   					loopCounter=popLoopList(&loopCounterStack);
   					}
   					
   					}

	const	:	INTCONST  {$$=NewExprInt($1);
						printf("#%d const -> integer number \n", yylineno);}
			|	REALCONST  {$$=NewExpDouble($1);
							printf("#%d const -> real number \n", yylineno);}
			|	STRING  {$$=NewStringExp($1);

						printf("#%d const -> string \n", yylineno);}
			|	NIL  {$$=NewNilExp();
						printf("#%d const -> nil \n", yylineno);}
			|	TRUE  { $$=NewBoolExp(1);
						printf("#%d const -> true \n", yylineno);}
			|	FALSE  { $$=NewBoolExp(0);
						printf("#%d const -> false \n", yylineno);}
			;

	idlist	:	ID{if(lastFunc!=NULL){
					handleArgs(symTable,$1,lastFunc->name,scope,yylineno);

					inCurrScopeOffset();
					
									}
					printf("#%d idlist -> ID idlist2 \n", yylineno);} 
					idlist2
			|	{printf("#%d idlist2 -> empty \n", yylineno);}
			;

	idlist2 	:	COMMA ID{if(lastFunc!=NULL){
						handleArgs(symTable,$2,lastFunc->name,scope,yylineno);}
						printf("#%d idlist2 -> , ID idlist2 \n", yylineno);
						inCurrScopeOffset();
						
					}
					idlist2
				|	{printf("#%d idlist2 -> empty \n", yylineno);}
				;
	ifprefix : IF LEFT_PARENTHESES expr RIGHT_PARENTHESES{emit(if_eq,$3,NewBoolExp(1),NULL,nextQuadLabel()+2,currQuad);
																$$=nextQuadLabel();
																emit(jump,NULL,NULL,NULL,0,currQuad);
																}
			 ;
	elseprefix : ELSE {$$=nextQuadLabel();
						emit(jump,NULL,NULL,NULL,0,currQuad);}

	ifstm   : ifprefix stm{patchLabel($1,nextQuadLabel());
							printf("#%d ifstm -> if(expr) stm \n", yylineno);}
			| ifprefix stm elseprefix stm{patchLabel($1,$3+1);
										patchLabel($3,nextQuadLabel());
										printf("#%d ifstm -> if(expr) stm else stmt \n", yylineno);}
			;
	loopstart : {++loopCounter;}
			  ;
	loopend : {--loopCounter;}
			;
	loopstm : loopstart stm loopend {$$=$2;}
			;
	whilestart : WHILE{
					$$=nextQuadLabel();}
				;
	whilecond : LEFT_PARENTHESES expr RIGHT_PARENTHESES{
				emit(if_eq,$2,NewBoolExp(1),NULL,nextQuadLabel()+2,currQuad);
				$$=nextQuadLabel();
				emit(jump,NULL,NULL,NULL,0,currQuad);
				}
			  ;
					
	whilestm	:	whilestart whilecond loopstm {emit(jump,NULL,NULL,NULL,$1,currQuad);
												patchLabel($2,nextQuadLabel());
												if(breakList!=NULL){
													patchLabel(breakList->tempQuad,nextQuadLabel());
													breakList=NULL;
												}
												if(continueList!=NULL){
													patchLabel(continueList->tempQuad,$1);
													continueList=NULL;
												}
																								
											printf("#%d whilestm -> while(expr) stm \n", yylineno);}
				;
	M : {$$=nextQuadLabel();}
	  ;

	N : {$$=nextQuadLabel();
		emit(jump,NULL,NULL,NULL,-1,currQuad);}
	  ;

	forprefix : FOR LEFT_PARENTHESES elist SEMICOLON M expr SEMICOLON{
				$$=malloc(sizeof(struct forprefix));
				$$->test=$5;
				$$->enter=nextQuadLabel();
				emit(if_eq,$6,NewBoolExp(1),NULL,-1,currQuad);
				}
			  ;

	forstm	:	forprefix N elist RIGHT_PARENTHESES N loopstm N{
					patchLabel($1->enter,$5+1);
					patchLabel($2,nextQuadLabel());
					patchLabel($5,$1->test);
					patchLabel($7,$2+1);
					if(breakList!=NULL){
						patchLabel(breakList->tempQuad,nextQuadLabel());
					}
					if(continueList!=NULL){
						patchLabel(continueList->tempQuad,$2+1);
					}
					printf("#%d forstmt -> for(elist; expr; elist) stmt \n", yylineno);}
			;

	returnstm	:	RETURN SEMICOLON {
					emit(ret,NULL,NULL,NULL,-1,currQuad);
		printf("#%d returnstm -> return; \n", yylineno);}
				|	RETURN expr SEMICOLON {
					emit(ret,NULL,NULL,$2,-1,currQuad);
					printf("#%d returnstm -> return expr; \n", yylineno);}
				;



%%


int main(int argc, char** argv){

	FILE *in_file;
	FILE *out_file;

	char* in_name;
	char* out_name;

	in_name = argv[1];
	out_name = argv[2];

  	if(argc == 1){
  		yyin = stdin;
  	}

  	if(argc == 2){
  		in_file = fopen(in_name,"r");
  		yyin = in_file;

  	}

  	if(argc==3){
  		in_file = fopen(in_name,"r");
  		yyin = in_file; 
  		out_file = fopen(out_name,"w+");
  		yyout=out_file;
  	}
  	/*
  	//gia testing while under construction
  	node* test=createEntry(0,GLOBAL,"test",0,5);
  	printf("here\n");
	expr *expt=lvalue_expr(test);
	printf("name %s\n",expt->sValue);
	char *ex=newTempName();
	printf("%s\n",ex );
	printf("%d\n",istempname(ex) );
	ex=newTempName();
	printf("%s\n",ex );
	printf("%d\n",istempname(ex) );
	ex=newTempName();
	printf("%s\n",ex );
	printf("%d\n",istempname(ex) );
	ex=newTempName();
	printf("%s\n",ex );
	printf("%d\n",istempname(ex) );
	
	*/

	symTable=createSymbolTable();
	initSumbolTable(symTable,"print");
	initSumbolTable(symTable,"input");
	initSumbolTable(symTable,"objectmemberkeys");
	initSumbolTable(symTable,"objecttotalmembers");
	initSumbolTable(symTable,"objectcopy");
	initSumbolTable(symTable,"totalarguments");
	initSumbolTable(symTable,"argument");
	initSumbolTable(symTable,"typeof");
	initSumbolTable(symTable,"strtonum");
	initSumbolTable(symTable,"sqrt");
	initSumbolTable(symTable,"cos");
	initSumbolTable(symTable,"sin");
	

	yyparse();
	printTable(symTable);
	PrintQuads();
		initiator();
		readBinary();
	
	return 0;
}

 	
