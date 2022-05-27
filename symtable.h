#ifndef __SYMTABLE_H__
#define __SYMTABLE_H__

#include "quads.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#define HASHER 65599
#define SIZE 509
#define MAX_SCOPE 1000

	int yyerror (char* errorMessage);
	int yylex (void);
	
	extern int yylineno;
	extern char * yyval;
	extern char * yytext;
	extern FILE * yyin;
	extern FILE * yyout;

typedef struct Args
{
	char *name;
	struct Args *next;
}Arg;


enum SymTableType{
	GLOBAL,LOCKAL,FORMAL, USERFUNC,LIBFUNC
};



typedef struct stoixeio
{
	char *name;
	struct Args *argList;
	unsigned int scope;
	enum scopespace_t scope_t;
	unsigned int offset;
	unsigned int line;
	int Active;
	int isFunc;
	unsigned int totalLocals;
	unsigned int iAddress;
	enum SymTableType type;
	struct stoixeio *next;
	struct stoixeio *nextScope;
}node;

typedef struct symboltable
{
	unsigned int length;
	node *hashtab[SIZE];
}SymTable;

unsigned int HashFunction(const char* name);
SymTable* createSymbolTable(void);
node* createEntry(int var,enum SymTableType type,char *name,unsigned int scope, unsigned int line);
void insertSymbol(SymTable* table,node* newnode);
void insertScopeList(node* newnode);
int insertArgs(SymTable *table,const char* fname,char* arg,int scope);
node* lookupNode(SymTable* table,const char* name);
node* lookupScope(const char* name,int scope);
void hideVar(SymTable* table, int scopeHide);
void printArgs(SymTable *table,const char* fname);
void printTable(SymTable* symTable);
int searchForFunction(SymTable* symTable,node* old,int line);
int collideLibFunc(char* name);
char* enumToString(enum SymTableType type);
//new functions for phase 3
struct stoixeio * newTemp(struct symboltable* table);
expr* emit_ifTableItem(struct symboltable* table,expr *e);
expr* member_item(struct symboltable* table,expr *lvalue,char *name);
expr* member_item1(struct symboltable* table,expr *lvalue,int name);
expr* make_call(struct symboltable* table, expr* lvalue,expr* elist);
expr * tableMake(struct symboltable *table, expr * elist);
expr* tableMakeIndex(struct symboltable* table, struct indexed * indexed);





#endif