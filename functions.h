#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "symtable.h"

int yyerror (char* errorMessage);
node* handleFuncId(SymTable* symTable,char *name,int scope,int line);
node *handleFuncNoId(SymTable *symTable,char *name,int scope,int line);
void handleArgs(SymTable* symTable,char* argName,const char* funcName,int scope,int line);
node* handleId(SymTable* symTable,char *name,int scope,int line);
node* handleLocalId(SymTable *symTable,char* name,int scope,int line);
node* handleScopeId(SymTable* symTable,char* name,int line);
void handleLvalue(SymTable* symTable, char* name, int line);
void initSumbolTable(SymTable* symTable,char *name);

#endif
