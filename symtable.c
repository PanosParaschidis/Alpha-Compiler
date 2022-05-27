#include "symtable.h"
#include "quads.h"


/*
flex -olex.c al.l
bison --yacc --defines --output=parser.c parser.y

gcc -o al.out lex.c parser.c symtable.c functions.c quads.c targetCode.c avm.c

*/

node *scopeArray[MAX_SCOPE];

unsigned int HashFunction(const char* name){
	unsigned int hashed=0;
	size_t i;
	for(i=0; name[i]!='\0'; i++){
		hashed=hashed*HASHER+name[i];
	}
	return hashed%SIZE;
	
}

SymTable* createSymbolTable(void){
	int i;
	SymTable* newTable=malloc(sizeof(struct symboltable));

	for(i=0;i<SIZE;i++){
		newTable->hashtab[i]=NULL;
	}
	for(i=0;i<MAX_SCOPE;i++){
		scopeArray[i]=NULL;
	}
	return newTable;
}
//var=0 --> variable
//var=1 -->function
node* createEntry(int var,enum SymTableType type,char *name,unsigned int scope, unsigned int line){
	node* ins=malloc(sizeof(struct stoixeio));
		ins->Active=1;
		ins->name=strdup(name);
		ins->line=line;
		ins->scope=scope;
		ins->isFunc=var;
		ins->argList=NULL;
		ins->type=type;
		ins->offset=currScopeOffset();
		ins->scope_t=currScopeSpace();
	return ins;
}





void insertSymbol(SymTable* table,node* newnode){
	unsigned int index;
	index=HashFunction(newnode->name);

	
	if(table->hashtab[index]==NULL){

		table->hashtab[index]=newnode;
		newnode->next=NULL;
	}else{
		newnode->next=table->hashtab[index];
		table->hashtab[index]=newnode;

	}
	table->length++;
	int i;
	char* what;
	
	for(i=0;i<SIZE;i++){
		if(table->hashtab[i]!=NULL){
			if(table->hashtab[i]->isFunc!=0){
				what="function";
			}else{
				what="variable";
			}
			//printf("is: %s name:%s line: %d scope: %d \n",what,table->hashtab[i]->name,table->hashtab[i]->line,table->hashtab[i]->scope);

		}
	}
	}

void insertScopeList(node* newnode){
	
		if(scopeArray[newnode->scope]==NULL){
			scopeArray[newnode->scope]=newnode;
			newnode->nextScope=NULL;
		}else{
			newnode->nextScope=scopeArray[newnode->scope];
			scopeArray[newnode->scope]=newnode;
		}
}

void printArgs(SymTable *table,const char* fname){
	node* temp=lookupNode(table,fname);
	Arg* tempa;
	tempa=temp->argList;
	while(tempa!=NULL){
		printf("Arguments: %s\n",tempa->name );
		tempa=tempa->next;
	}
}

int insertArgs(SymTable *table,const char* fname,char* arg,int scope){
	
		int found=0;
		Arg* tempa,*search;
		Arg* newnode;
		node* temp=lookupNode(table,fname);
		newnode=(Arg *)malloc(sizeof(Arg));
		newnode->name=strdup(arg);
		newnode->next=NULL;
		tempa=temp->argList;
		search=temp->argList;
		if(tempa==NULL){
			temp->argList=newnode;
			return 1;
		}
		while(search!=NULL){
			if(strcmp(search->name,arg)==0){
				found=1;
				return 0;
			}
		search=search->next;
	}
		while(tempa->next!=NULL){
			tempa=tempa->next;
		}
		tempa->next=newnode;
	
		return 1;
}

node* lookupNode(SymTable* table,const char* name){
	unsigned int index=HashFunction(name);
	node* temp=table->hashtab[index];
	node* found;
	while(temp!=NULL){
		if(strcmp(temp->name,name)==0 && temp->Active==1){
			found=temp;
			return found;
		}
		temp=temp->next;
	}
	return NULL;

}

node* lookupScope(const char* name,int scope){
	node* temp=scopeArray[scope];
	node* found;	
	while(temp!=NULL){
		if(strcmp(temp->name,name)==0 && temp->Active==1){
			found=temp;
			return found;
		}
		temp=temp->nextScope;
	}
	return NULL;
}
	
void hideVar(SymTable* table, int scopeHide){
	int i;
	
	for(i=0;i<SIZE;i++){
		node* temp1=table->hashtab[i];
		while(temp1!=NULL){
			if(temp1->scope==scopeHide && temp1->Active==1){
				temp1->Active=0;
			}
			temp1=temp1->next;
		}
	}
	
	for(i=0;i<MAX_SCOPE;i++){
		node* temp2=scopeArray[i];
		while(temp2!=NULL){
			if(temp2->scope==scopeHide && temp2->Active==1){
				temp2->Active=0;
			}
			temp2=temp2->nextScope;
		}
	}
}	

int searchForFunction(SymTable* symTable,node* old,int line){
	int exLine=old->line;
	int i,y;
	for(i=line;i>exLine;i--){
		for(y=0;y<MAX_SCOPE;y++){
			node* temp=scopeArray[y];
			while(temp!=NULL){
				if(temp->type==USERFUNC && temp->line==i){
					return 1;
				}
				temp=temp->next;
			}	
		}
		
	}
	return 0;
}

void printTable(SymTable* symTable){
	int i;
	node *temp;
	Arg* tempa;
	printf("Print Table\n");
	for(i=0;i<SIZE;i++){
		if(symTable->hashtab[i]!=NULL){
			temp=symTable->hashtab[i];

			while(temp!=NULL){
				if(temp->type!=LIBFUNC){
				printf(" %s is: %s in line: %d has scope: %d isActive: %d\n",temp->name,enumToString(temp->type),temp->line,temp->scope,temp->Active );
				 if(temp->isFunc!=0){
					tempa=temp->argList;
					if(tempa!=NULL){
					printf("	with arguments: ");	
				}
					while(tempa!=NULL){
						printf("-%s \t",tempa->name );
						tempa=tempa->next;
					}
				}
				printf("\n");
			 }
				temp=temp->next;
			
			}


		}
	}
	printf("Library Functions:\n");
	for(i=0;i<SIZE;i++){
		if(symTable->hashtab[i]!=NULL){
			temp=symTable->hashtab[i];

			while(temp!=NULL){
				if(temp->type==LIBFUNC){
				printf(" %s is: %s in line: %d has scope: %d isActive: %d\n",temp->name,enumToString(temp->type),temp->line,temp->scope,temp->Active );
				 if(temp->isFunc!=0){
					tempa=temp->argList;
					if(tempa!=NULL){
					printf("	with arguments: ");	
				}
					while(tempa!=NULL){
						printf("-%s \t",tempa->name );
						tempa=tempa->next;
					}
				}
				printf("\n");
			 }
				temp=temp->next;
			
			}
			

		}
	}
}
 int collideLibFunc(char* name){
 	node* temp=scopeArray[0];
 	while(temp!=NULL){
		if(strcmp(temp->name,name)==0 && temp->type==LIBFUNC){
			return 1;
		}
		temp=temp->nextScope;
	}
	return 0;
 }
	//print all
//print scope

char* enumToString(enum SymTableType type){
	switch(type){
		case GLOBAL:
			return "Global";
		case FORMAL:
			return "Formal";
		case USERFUNC:
			return "UserFunc";
		case LIBFUNC:
			return "LibFunc";
		case LOCKAL:
			return "Local";
	}
}
