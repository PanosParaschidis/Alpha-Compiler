#ifndef __AVM_H__
#define __AVM_H__
#include "symtable.h"
#include "quads.h"
#include "targetCode.h"

#define AVM_STACKSIZE 4096
#define AVM_WIPEOUT(m)  memset( &(m), 0, sizeof(m))
#define AVM_TABLE_HASHSIZE 211
#define AVM_STACKENV_SIZE 4
#define AVM_ENDING_PC codeSize
#define AVM_MAX_INSTRUCTIONS nop_v

#define AVM_NUMACTUALS_OFFSET 	4
#define AVM_SAVEDPC_OFFSET	3
#define AVM_SAVEDTOP_OFFSET	2
#define AVM_SAVEDTOPSP_OFFSET	1


#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic


typedef enum avm_memcell_t {
  number_m, 	
  string_m,		
  bool_m,		
  table_m,		
  userfunc_m,	
  libfunc_m,	
  nil_m,		
  undef_m,		
}avm_memcell_t;

typedef struct avm_table
{
  unsigned 		refCounter;
  struct avm_table_bucket* 	strIndexed[AVM_TABLE_HASHSIZE];
  struct avm_table_bucket*	numIndexed[AVM_TABLE_HASHSIZE];
  unsigned		total;
}avm_table;

typedef struct avm_memcells{

  avm_memcell_t type;
  union
  {
    double numVal;
    char * strVal;
    unsigned int boolVal;
    avm_table * tableVal;
    unsigned int funcVal;
    char * libfuncVal;
  }data;
}avm_memcell;

typedef struct avm_table_bucket{
  avm_memcell	*key;
  avm_memcell 	*value;
  struct avm_table_bucket * next;
}avm_table_bucket;

avm_memcell stack[AVM_STACKSIZE];
avm_memcell retval;
avm_memcell ax, bx, cx;
unsigned int  top,topsp;

extern unsigned char 	executionFinished;
extern unsigned int	pc;
extern unsigned int	currLine;
extern unsigned int	codeSize;
extern unsigned totalActuals;
extern instruction*	code ;


unsigned int  top,topsp;

extern unsigned int NtotalStrings;
extern unsigned int NtotalNums;
extern unsigned int NtotalUserfuncs;
extern unsigned int NtotalLibfuncs;

char** NstringArray;
char** NlibFuncArray;
double* NnumArray;
userFunc* NuserFuncArray;

static void avm_initstack(void);
void execute_assign(instruction*);
void execute_add(instruction*);
void execute_sub(instruction*);
void execute_mul(instruction*);
void execute_div(instruction*);
void execute_mod(instruction*);
void execute_jeq(instruction*);
void execute_jne(instruction*);
void execute_jgt(instruction*);
void execute_jlt(instruction*);
void execute_jge(instruction*);
void execute_jle(instruction*);
void execute_jump(instruction*);
void execute_call(instruction*);
void execute_funcenter(instruction*);
void execute_funcexit(instruction*);
void execute_newtable(instruction*);
void execute_tablegetelem(instruction*);
void execute_tablesetelem(instruction*);
void execute_pusharg(instruction*);
void execute_nop(instruction*);

char* number_tostring(avm_memcell* m);
char* string_tostring(avm_memcell* m);
char* bool_tostring(avm_memcell* m);
char* userfunc_tostring(avm_memcell* m);
char* libfunc_tostring(avm_memcell* m);
char* nil_tostring(avm_memcell* m);
char* undef_tostring(avm_memcell* m);
char* table_tostring(avm_memcell* m);

double add_impl(double x,double y);
double sub_impl(double x,double y);
double mul_impl(double x,double y);
double div_impl(double x,double y);
double mod_impl(double x,double y);

unsigned char number_tobool(avm_memcell* m);
unsigned char string_tobool(avm_memcell* m);
unsigned char bool_tobool(avm_memcell* m);
unsigned char table_tobool(avm_memcell* m);
unsigned char userfunc_tobool(avm_memcell* m);
unsigned char libfunc_tobool(avm_memcell* m);
unsigned char nil_tobool(avm_memcell* m);
unsigned char undef_tobool(avm_memcell* m);
unsigned char avm_tobool (avm_memcell *m);

void memclear_string(avm_memcell* m);
void memclear_table(avm_memcell* m);
void avm_memcellclear(avm_memcell* m);
avm_memcell * avm_translate_operand (vmarg *arg, avm_memcell *reg);
void execute_cycle();
void avm_assign(avm_memcell *lv, avm_memcell *rv);
void avm_callsaveenvironment();
double consts_getnumber(unsigned int index);
char* consts_getstring(unsigned int index);
char* libfuncs_getused(unsigned int index);
void avm_dec_top();
void avm_push_envvalue(unsigned int val);
unsigned int avm_get_envvalue(unsigned int i);
void avm_calllibfunc(char *id);
unsigned int avm_totalactuals();
avm_memcell* avm_getactual(unsigned int i);



void avm_error(char *s,...);
void avm_tableincrefcounter(avm_table*);
void avm_tabledecrefcounter(avm_table*);

void avm_tabledestroy(avm_table* t);
avm_table* avm_tablenew();
void avm_tablesetelem( avm_table *table, avm_memcell *index, avm_memcell *content);
avm_memcell* avm_tablegetelem(avm_table* table, avm_memcell* index);
void avm_tablebucketsinit(avm_table_bucket** p);
void avm_tablebucketsdestroy(avm_table_bucket ** p);
avm_table_bucket* avm_insertNewBucket(avm_table_bucket *head, avm_memcell *index, avm_memcell *content);
void initiateEverything();

//libfuncs
void libfunc_print();//given
void	libfunc_input (void);
void	libfunc_objectmemberkeys (void);
void	libfunc_objecttotalmembers (void);
void	libfunc_objectcopy (void);
void 	libfunc_totalarguments (void);		
void	libfunc_argument (void);
void 	libfunc_typeof (void);			
void	libfunc_strtonum (void);
void	libfunc_sqrt (void);
void	libfunc_cos (void);
void	libfunc_sin (void);
void iOpcode_tostring(instruction *temp);
void print_cell(avm_memcell* m);
void print_buckets(avm_table_bucket* head);
void print_table(avm_memcell* m);
char * memcell_tochar(avm_memcell* m);
void readBinary();
void Print_Stack();
#endif