D [0-9]
L [a-zA-Z_]
H [a-zA-Z_0-9]
E [Ee][+-]?{D}+

%{
#include <math.h>
#include "compila.tab.h"
%}


%%
{D}*[.]?{D}+{E}?	{ yylval.val = atof(yytext); return NUMt; }
"CE"|"NE"|"NW"|"EA"|"WE"|"SE"|"SW" { strncpy(yylval.dir, yytext, 2); return DIR; }
true { yylval.val = 1; return NUMt; }
false { yylval.val = 0; return NUMt; }
ret(urn)?  { return RETt; }

if      { return IF; }
while	{ return WHILE; }
func|def { return FUNC; }
else     { return ELSE; }
for      {return FOR; }
print   { return PRINT; }
\.terreno  { return TERR; }
\.cristais { return CRI; }
\.ocup     { return OCP; }
\.base     { return BAS; }
move       { return MOV; }
atkmelee   { return ATKM; }
atkshort   { return ATKS; }
atklong    { return ATKL; }
collect    { return COL; }
drop       { return DRP; }
see        { return SEEt; }




{L}{H}* { 
  strncpy(yylval.cod, yytext, 30);
  return ID;
}

[ \t\n]+	/* pula espacos em branco */

#.*		/* comentarios simples */

;		{ return EOL; }
,		{ return SEP; }
=		{ return ASGN; }
[(]		{ return OPEN; }
[)]		{ return CLOSE; }
[{]		{ return ABRE; }
[}]		{ return FECHA; }
[+]		{ return ADDt; }
[-]		{ return SUBt; }
[*]		{ return MULt; }
[/]		{ return DIVt; }
==		{ return EQt; }
!=		{ return NEt; }
"<"		{ return LTt; }
"<="	{ return LEt; }
">"		{ return GTt; }
">="	{ return GEt; }

	    /* { return PONTO; }  {  fprintf(stderr, "Entrada ignorada\n-->%s\n", yytext); } */

%%

/* Local Variables: */
/* mode: c */
/* End: */
