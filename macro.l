%{
#include"y.tab.h"
%}

%%
"START" { return START;}
"END" {return END;}
"MACRO" { return MACRO;}
"MEND" {return MEND;}
("ADD"|"ADDF"|"ADDR"|"AND"|"CLEAR"|"COMP"|"COMPF"|"COMPR"|"DIV"|"DIVF"|"DIVR"|"FIX"|"FLOAT"|"HIO"|"J"|"JEQ"|"JGT"|"JLT"|"JSUB"|"LDA"|"LDB"|"LDCH"|"LDF"|"LDL"|"LDS"|"LDT"|"LDX"|"LPS"|"MUL"|"MULF"|"MULR"|"NORM"|"OR"|"RD"|"RMO"|"RSUB"|"SHIFTL"|"SHIFTR"|"SIO"|"SSK"|"STA"|"STB"|"STCH"|"STF"|"STI"|"STL"|"STS"|"STSW"|"STT"|"STX"|"SUB"|"SUBF"|"SUBR"|"SVC"|"TD"|"TIO"|"TIX"|"TIXR"|"WD"|"RESW"|"RESB"|"WORD"|"+LDT"|"-LDT"|"BYTE") { return OP;}
[A-Z]+ { return LABEL; }
[0-9]+ {return NUM;}
[+-=*#]*[A-Z0-9'&]+ { return OPR;}
[A-Z0-9,]+ {return COMMA;}
[ \t\n] ;
. { return yytext[0];}
%%

