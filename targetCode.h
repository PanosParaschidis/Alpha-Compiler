#ifndef __TARGETCODE_H__
#define __TARGETCODE_H__

#include "symtable.h"
#include "quads.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define EXPAND_SIZE_I 1024
#define CURR_SIZE_I (totalInstr*sizeof(instruction))
#define NEW_SIZE_I (EXPAND_SIZE*sizeof(instruction)+CURR_SIZE_I)



typedef enum vmargs_t ///final code types
{
	label_a,    global_a,  formal_a,
	local_a,    number_a,
	string_a,   bool_a,    nil_a,
	userfunc_a, libfunc_a, retval_a,
} vmarg_t;

typedef enum vmopcodes ///final code opcodes
{	assign_v,	add_v,  	sub_v,
	mul_v, 		div_v, 		mod_v,
	uminus_v, 	and_v, 		or_v,
	not_v, 		jeq_v, 		jne_v,
	jgt_v, 		jlt_v, 		jge_v,
	jle_v, 		jump_v, 	call_v,
	funcenter_v, 	funcexit_v, 	newtable_v,
	tablegetelem_v,	tablesetelem_v,	pusharg_v,
	nop_v, ret_v, getretval_v

}vmopcode;

typedef struct vmarg ///arg of instruction
{
  vmarg_t type;
  unsigned int val;
  //struct stoixeio *sym;
}vmarg;

typedef struct instruction ///instruction of final code
{
  vmopcode opcode;
  vmarg    *result;
  vmarg    *arg1;
  vmarg    *arg2;
  unsigned srcLine;

}instruction;

/** List for incomplete jump patching*/
typedef struct incomplete_jumps
{
	unsigned int instrNo; /* The jump instruction number. */
	unsigned int iaddress; /* The i-code jump-target address */
	struct incomplete_jumps *next; /* A trivial linked list */
} incomplete_jump;

typedef struct userFunc
{
  unsigned int address;
  unsigned int endaddress;
  unsigned int localSize;
  char*	   id;
}userFunc;

typedef struct returnList
{
	unsigned int label; 
	struct returnList *next;
} returnList;

typedef struct funcStack
{
	struct stoixeio *sym;
	returnList* head;
	unsigned int startJump;
	struct funcStack* next;

} funcStack;

typedef void (*generator_func_t) (quad*);
extern quad* quads;
extern unsigned int currQuad;
extern instruction *inst;
extern char ** stringArray;
extern unsigned totalStrings;

extern double* numArray;
extern unsigned totalNums;

extern char ** libFuncArray;
extern unsigned totalLibFuncs;

extern userFunc * userFuncArray;
extern unsigned totalUserFuncs;




vmarg* make_operand(expr* );
vmarg* make_booloperand();
vmarg* make_retvaloperand(vmarg* arg);
vmarg* make_numberoperand(double val);

void run_generate(void);
void generate(vmopcode , quad *);
void generate_relational(vmopcode op, quad* q);

void generate_add(quad* q);
void generate_sub(quad* q);
void generate_mul(quad* q);
void generate_div(quad* q);
void generate_mod(quad* q);
void generate_newtable(quad* q);
void generate_tablegetelem(quad* q);
void generate_tablesetelem(quad* q);
void generate_assign(quad* q);
void generate_nop();
void generate_jump(quad* q);
void generate_uminus(quad *q);
void generate_if_eq(quad* q);
void generate_if_noteq(quad* q);
void generate_if_greater(quad* q);
void generate_if_greatereq(quad* q);
void generate_if_less(quad* q);
void generate_if_lesseq(quad* q);
void generate_and(quad* q);
void generate_not(quad* q);
void generate_or(quad* q);
void generate_param(quad* q);
void generate_call(quad* q);
void generate_getretval(quad* q);
void generate_funcstart(quad* q);
void generate_return(quad* q);
void generate_funcend(quad* q);





unsigned int consts_newstring(char *s);
unsigned consts_newnumber(double value);
unsigned int libfuncs_newused(char* name);
unsigned int userfuncs_newfunc(struct stoixeio* sym);
void generate_uminus(quad *q);
void initiator();
void PrintArg(vmarg *arg);
void printInstruction();
 void emit_i(instruction* t);
void expand_i();
void add_incomplete_jump(unsigned int instrNo, unsigned int iaddress);
void patch_incomplete_jumps();
vmarg* reset_operand();
void pushReturnList(unsigned int label);
void pushFunctionList(struct stoixeio* func);
funcStack* popFunctionList();
void backpatchReturn(funcStack* f);
void PrintIstrText();
void PrintAllTables();
void writeBinary();
#endif