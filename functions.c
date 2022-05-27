#include "functions.h"
#include "symtable.h"

static int counter=0;

int yyerror (char* errorMessage)
{
	fprintf(stderr, "\t ERROR, %s: in line %d, before: '%s'\n", errorMessage, yylineno, yytext);
}

node* handleFuncId(SymTable* symTable,char *name,int scope,int line){
	node *temp=lookupNode(symTable,name);
	if(temp==NULL){
		node *newnode=createEntry(1,USERFUNC,name,scope,line);
		insertSymbol(symTable,newnode);
		insertScopeList(newnode);
		return newnode;
	}else if(temp->isFunc==1 && temp->scope==scope){
		fprintf(stderr, "\t ERROR redeclaration of function: %s in line: %d\n",name,line );
		return NULL;
	}else if(temp->isFunc==1 && temp->scope!=scope){
			node *newnode=createEntry(1,USERFUNC,name,scope,line);
		insertSymbol(symTable,newnode);
		insertScopeList(newnode);
		return newnode;
	}else if(temp->type==LIBFUNC){
		fprintf(stderr, "\t ERROR shadowing of library function: %s in line: %d\n",name,line );
		return NULL;
	}else if(temp->isFunc==0 && temp->scope==scope && temp->Active==1){
		fprintf(stderr, "\t ERROR  '%s' already exists as a variable in line: %d \n",name,line);
		return NULL;
	}
	
	
}

node *handleFuncNoId(SymTable *symTable,char *name,int scope,int line){
	char string[]="$def_func_";
	char cated_string[20];
	sprintf(cated_string,"%s%d",string,counter);
	counter++;
	node *temp=lookupNode(symTable,cated_string);
	if(temp==NULL){
		node *newnode=createEntry(1,USERFUNC,cated_string,scope,line);
		insertSymbol(symTable,newnode);
		insertScopeList(newnode);
		return newnode;
	}else if(temp->scope==scope){
		fprintf(stderr, "\t ERROR redeclaration of function: %s in line: %d\n",cated_string,line );
	}else if(temp->type==LIBFUNC){
		fprintf(stderr, "\t ERROR shadowing of library function: %s in line: %d\n",cated_string,line );
	}
	
	return NULL;

}

void handleArgs(SymTable* symTable,char* argName,const char* funcName,int scope,int line){
	int res;
	node *temp=lookupNode(symTable,argName);
	if (temp==NULL){
		node *newnode=createEntry(0,FORMAL,argName,scope,line);
		insertSymbol(symTable,newnode);
		insertScopeList(newnode);
		res=insertArgs(symTable,funcName,argName,scope-1);
	}else if(temp->scope==scope && temp->Active==1 && temp->type!=LIBFUNC){
		fprintf(stderr, "\t ERROR formal argument: %s is already a variable in line: %d\n",argName,line);
	}else if(temp->type==LIBFUNC){
		fprintf(stderr, "\t ERROR formal arguments shadows library function: %s in line: %d\n",temp->name,line );
	}
	

}

node * handleId(SymTable* symTable,char *name,int scope,int line){
	/*for future reference: edw to temp anikei sto scopeArray kai oxi sto hashtable*/
	int i;
	node *newnode;
	node *temp,*temp1;
	
	for(i=scope;i>-1;i--){
		temp=lookupScope(name,i);
		if(temp!=NULL){
			
			break;
		}
	}
	if(temp==NULL){
		
		if(scope==0){
			newnode=createEntry(0,GLOBAL,name,scope,line);	
		}else{
			newnode=createEntry(0,LOCKAL,name,scope,line);
		}
		insertSymbol(symTable,newnode);
		insertScopeList(newnode);
		
		return newnode;
	}else if(temp->type==LOCKAL || temp->type==FORMAL){
		temp1=lookupNode(symTable,name);
		int flag=searchForFunction(symTable,temp,line);
		if(flag==1){
			fprintf(stderr, "\t ERROR cannot access %s there is function between %d and %d \n",name, temp->line,line );
			return temp1;
		}else{
			
			return temp1;
		}
	}else{
		temp1=lookupNode(symTable,name);
		return temp1;
	}
}

node * handleLocalId(SymTable* symTable,char* name,int scope,int line){
	/*for future reference: edw to temp anikei sto scopeArray kai oxi sto hashtable*/
	node *temp=lookupScope(name,scope);
	node *newnode,*temp1;
	if(temp==NULL){
		if(scope==0){
			newnode=createEntry(0,GLOBAL,name,scope,line);	
		}else{
			newnode=createEntry(0,LOCKAL,name,scope,line);
		}
		insertSymbol(symTable,newnode);
		insertScopeList(newnode);
		return newnode;
	}else{
		int flag=collideLibFunc(name);
		if(flag==1){
			temp1=lookupNode(symTable,name);
			fprintf(stderr, "\t ERROR local variable shadows library function: %s in line: %d\n",name,line );
			return temp1;
		}
	}
}

node* handleScopeId(SymTable* symTable,char* name,int line){
	/*for future reference: edw to temp anikei sto scopeArray kai oxi sto hashtable*/
	node *temp=lookupScope(name,0);
	if(temp==NULL){
		fprintf(stderr, "\t ERROR global variable: %s doesn't exist, in line: %d\n",name,line );
	}
	return temp;
}


void handleLvalue(SymTable* symTable, char* name, int line){
	int i;
	node *temp;
	temp=lookupNode(symTable,name);
	
	if(temp!=NULL){
		if(temp->type==USERFUNC){
			fprintf(stderr, "\t ERROR can't access: %s which is a user function, line: %d \n",name,line);
		}else if(temp->type==LIBFUNC){
			fprintf(stderr, "\t ERROR can't access: %s which is a library function, line: %d \n",name,line);
		}
}

}

void initSumbolTable(SymTable* symTable,char *name){
	node* newnode=createEntry(1,LIBFUNC,name,0,0);
	insertSymbol(symTable,newnode);
	insertScopeList(newnode);
	
}
