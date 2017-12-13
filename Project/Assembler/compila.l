D [0-9]
L [a-zA-Z_]
H [a-zA-Z_0-9]
E [Ee][+-]?{D}+

%{
#include <math.h>
#include "compila.tab.h"
%}

%option yylineno

%%
{D}*[.]?{D}+{E}?	{ yylval.val = atof(yytext); return NUMt; }
"NE"|"NW"|"EA"|"WE"|"SE"|"SW"|"CE" { strncpy(yylval.dir, yytext, 3); return DIR; }
true { yylval.val = 1; return NUMt; }
false { yylval.val = 0; return NUMt; }
grass { yylval.val = 0; return NUMt; }
mountain { yylval.val = 1; return NUMt; }
street { yylval.val = 2; return NUMt; }
rock { yylval.val = 3; return NUMt; }
mud { yylval.val = 4; return NUMt; }
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
self       { return SELFt; }
\.id       { return MYSELF; }
\.army     { return MYARMY; }
\.fuel     { return FUEL; }
\.hp       { return HP; }
\.mycrystals { return MYCR; }
\.cell     { return MYCELL; }
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
!       { return NEGA; }
[(]		{ return OPEN; }
[)]		{ return CLOSE; }
[{]		{ return ABRE; }
[}]		{ return FECHA; }
[+|]	{ return ADDt; }
[-]		{ return SUBt; }
[*&]	{ return MULt; }
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
