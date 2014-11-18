%{
#include<stdio.h>
%}

%token LABEL OPR MACRO OP COMMA END START MEND NUM
%%
A : LABEL START LABEL B LABEL END LABEL
//X : LABEL F C
//F : OP | MACRO | LABEL
B : C | B C 
C : LABEL OP D | LABEL LABEL COMMA | E | LABEL LABEL D
D : LABEL  | OPR  | NUM  | COMMA 
E : LABEL MACRO COMMA B LABEL MEND LABEL | LABEL MACRO LABEL B LABEL MEND LABEL | LABEL MACRO NUM B LABEL MEND LABEL
%%

int main() 
{
printf("enter the code\n");
//FILE *yyin;
 //yyin = fopen("macro_testfile","r");
    //init();
    yyparse();
  //  fclose(yyin); 
printf("valid\n");

return 0;
}

int yyerror()
{
printf("invalid\n");
exit(0);
}
