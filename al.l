%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "parser.h"
	//#define YY_DECL int alpha_yylex (void* yylval)
	
	
%}

	
%option noyywrap
%option yylineno

/*Definitions*/

if 							"if"
else						"else"
while						"while"
for 						"for"
function					"function"
return 						"return"
break						"break"
continue					"continue"
and							"and"
or							"or"
not							"not"
local						"local"
true						"true"
false						"false"
nil							"nil"

assignment					"=" 
addition					"+"
subtraction 				"-"
multiplication 				"*"
division 					"/"
modulo 						"%" 
equality 					"==" 
inequality					"!=" 
increment					"++" 
decrement					"--"
greater_than				">" 
less_than					"<"
greater_than_or_equal_to 	">="
less_than_or_equal_to  		"<="



left_brace 					\{ 
right_brace 				\}
left_square_bracket 		\[
right_square_bracket 		\]
left_parentheses 			\(
right_parentheses 			\)	
semicolon					\;
comma 						\, 
colon						\: 
double_colon				\:\:
period 						\. 
double_period				\.\.

identifier					[a-zA-Z][a-zA-Z_0-9]*
comment_line					"//".*
comment_block					"/*"

new_line					"\n"
esc_seq 					 [\r \t\v]

intconst					[0-9]+
realconst					[0-9]*\.[0-9]+
string						\"
other						.



/*actions*/

%%
{if}						{return IF;}
{else}						{return ELSE;}		
{while}						{return WHILE;}
{for}						{return FOR;}
{function}					{return FUNCTION;}
{return}					{return RETURN;}
{break}						{return BREAK;}
{continue}					{return CONTINUE;}
{and}						{return AND;}
{or}						{return OR;}
{not}						{return NOT;}
{local}						{return LOCAL;}
{true}						{return TRUE;}
{false}						{return FALSE;}
{nil}						{return NIL;}

{assignment} 				{return ASSIGNMENT;}
{addition} 					{return ADDITION;}
{subtraction} 				{return SUBTRACTION;}
{multiplication} 			{return MULTIPLICATION;}
{division} 					{return DIVISION;}
{modulo} 					{return MODULO;}
{equality} 					{return EQUALITY;}
{inequality} 				{return INEQUALITY;}
{increment} 				{return INCREMENT;}
{decrement} 				{return DECREMENT;}
{greater_than} 				{return GREATER_THAN;}
{less_than} 				{return LESS_THAN;}
{greater_than_or_equal_to} 	{return GREATER_THAN_OR_EQ_TO;}
{less_than_or_equal_to} 	{return LESS_THAN_OR_EQ_TO;}

{left_brace}				{return LEFT_BRACE;}
{right_brace}				{return RIGHT_BRACE;}
{left_square_bracket}		{return LEFT_SQ_BRACKET;}
{right_square_bracket}		{return RIGHT_SQ_BRACKET;}
{left_parentheses}			{return LEFT_PARENTHESES;}	
{right_parentheses}			{return RIGHT_PARENTHESES;}
{semicolon}					{return SEMICOLON;}
{comma}						{return COMMA;}
{colon}						{return COLON;}
{double_colon}				{return DOUBLE_COLON;}
{period}					{return PERIOD;}
{double_period}				{return DOUBLE_PERIOD;}
{identifier}				{yylval.sValue=strdup(yytext);
							return ID;}

{new_line}					{}

	



{intconst} 					{yylval.iValue=atoi(yytext);
							return INTCONST;}
{realconst} 				{yylval.dValue=atof(yytext);
							return REALCONST;}
{string}					{ 
								int i=0,flag=1, tab=0, nl=0, slash=0;
								char a;
								
								while((a=input())!=EOF){
									if(a=='\\'){
										a=input();
										if(a=='t'){
											yytext[i]='\t';
											i++;
											tab++;
										}
										else if(a=='n'){
											yytext[i]='\n';
											i++;
											nl++;	
										}
										else if(a=='\\'){
											yytext[i]='\\';
											i++;
											slash++;
										}else if ( a == '\"' ){
											yytext[i] = '\"';
											i++;
											
										}else{
											yytext[i]=a;
											i++;
											fprintf(stderr, "\t ERROR line: %d illegal escape character: %c added to string  \n",yylineno,a );
										}
									

								}else if(a=='\"'){
										flag=0;
										break;
								}else{
										yytext[i]=a;
										i++;
									}

								}
								if(flag==0){
									yytext[i]='\0';
									yylval.sValue=strdup(yytext);
									return STRING;
								}

				
		}

{comment_line}					{}
{comment_block}		{
						char com;									/*actions gia comment block me uposthriksi nested comment blocks*/
						int counter=1;
						int line=0;
						while((com=input())!=EOF){
							if(com=='/'){
								com=input();
								if(com=='*'){
									counter++;
									line=yylineno;
								}
								else{
									unput(com);
								}
							}
							else if(com=='*'){
								com=input();
								if(com=='/'){
									counter--;
								}
								else{
									unput(com);
								}
							}
						if(counter==0){
							break;
							}
						}
						if(counter==0){
							
						}
						else{
						fprintf(stderr, "\t ERROR found unclosed comment, possibly started at line: %d  \n",line );
							}
					}



{esc_seq}		{}

{other}			{fprintf(stderr, "\t ERROR line: %d undefined token  \n",yylineno);}

%%



