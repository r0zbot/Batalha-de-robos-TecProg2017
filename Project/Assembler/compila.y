/* Compilador */

%{
#include <stdio.h>
#include <math.h>
#include "symrec.h"
#include "acertos.h"
#include "instr.h"
#include "pilha.h"
  
int yylex();
void yyerror(char const *);
int compila(FILE *, INSTR *);
static int ip  = 0;					/* ponteiro de instruções */
static int mem = 6;					/* ponteiro da memória */
static INSTR *prog;
static int parmcnt = 0;		/* contador de parâmetros */
static int labelPilha[9000];
static int indiceLabel = 0;
static int labelPilhaTop = 0;
static int ForLabel = 0;

void AddInstr(OpCode op, int val) {
  prog[ip++] = (INSTR) {op,  {NUM, {val}}};
}
%}

/*  Declaracoes */
%union {
  double val;
  /* symrec *cod; */
  char cod[30];
  char dir[3];
}


/* %type  Expr */

%token <val> NUMt
%token <cod> ID
%token <dir> DIR
%token ADDt SUBt MULt DIVt ASGN OPEN CLOSE RETt EOL NEGA
%token EQt NEt LTt LEt GTt GEt ABRE FECHA SEP
%token IF WHILE FUNC ELSE FOR PRINT TERR CRI OCP BAS MOV ATKM ATKS ATKL COL DRP SEEt SELFt MYSELF MYARMY FUEL HP MYCR MYCELL

%right ASGN
%right NEGA
%left ADDt SUBt
%left MULt DIVt
%left NEG
%right PWR
%left LTt GTt LEt GEt EQt NEt


/* Gramatica */
%%

Programa: Comando
       | Programa Comando
	   ;

Comando: Expr EOL {AddInstr(POP, 0); printf("POP 0\n");}
       | Cond
       | Loop
       | Func
	   | PRINT Expr EOL { AddInstr(PRN, 0); printf("PRN 0\n");}
	   | RETt EOL {
			     AddInstr(RET, 0);
			     printf("RET 0\n");
 			  }
	   | RETt OPEN  Expr CLOSE EOL {	
			     AddInstr(RET, 0);
			     printf("RET 0\n");
 		      }
 	   
	   /* | EOL {printf("--> %d\n", ip);} */
;

Expr: NUMt { int valor = $1; AddInstr(PUSH, $1); printf("PUSH %i\n", valor);}
    | ID   {
	         symrec *s = getsym($1);
			 if (s==0) s = putsym($1); /* não definida */
			 AddInstr(RCL, s->val);
			 printf("RCL %i\n", s->val);
	       }       
	| ID ASGN Expr {
	         symrec *s = getsym($1);
			 if (s==0) s = putsym($1); /* não definida */
			 AddInstr(STO, s->val);
			 printf("STO %i\n", s->val);
			 AddInstr(PUSH, 0);
			 printf("PUSH 0");

 		 }
 	| ID TERR  {
	         symrec *s = getsym($1); 
			 if (s==0) s = putsym($1); /* não definida */ 
			 AddInstr(RCL, s->val);
			 printf("RCL %i\n", s->val); 
			 AddInstr(ATR, 0); 
			 printf("ATR 0\n");
 		 }
 	| ID CRI  {
	         symrec *s = getsym($1); 
			 if (s==0) s = putsym($1); /* não definida */ 
			 AddInstr(RCL, s->val);
			 printf("RCL %i\n", s->val); 
			 AddInstr(ATR, 1); 
			 printf("ATR 1\n");
 		 }
 	| ID OCP  {
	         symrec *s = getsym($1); 
			 if (s==0) s = putsym($1); /* não definida */ 
			 AddInstr(RCL, s->val);
			 printf("RCL %i\n", s->val); 
			 AddInstr(ATR, 2); 
			 printf("ATR 2\n");
 		 }
 	| ID BAS  {
	         symrec *s = getsym($1); 
			 if (s==0) s = putsym($1); /* não definida */ 
			 AddInstr(RCL, s->val);
			 printf("RCL %i\n", s->val); 
			 AddInstr(ATR, 3); 
			 printf("ATR 3\n");
 		 }
 	| Syscall
 	| SELFt self
	| Chamada 
    | Expr ADDt Expr { AddInstr(ADD,  0); printf("ADD 0\n");}
	| Expr SUBt Expr { AddInstr(SUB,  0); printf("SUB 0\n");}
	| Expr MULt Expr { AddInstr(MUL,  0); printf("MUL 0\n");}
	| Expr DIVt Expr { AddInstr(DIV,  0); printf("DIV 0\n");}
    | SUBt Expr %prec NEG  { AddInstr(PUSH, -1); printf("PUSH -1\n");  AddInstr(MUL, 0); printf("MUL 0\n");}
    | NEGA Expr {AddInstr(PUSH, 0); printf("PUSH 0\n");  AddInstr(EQ, 0); printf("EQ 0\n");}
	| OPEN Expr CLOSE
	| Expr LTt Expr  { AddInstr(LT,   0); printf("LT 0\n");}
	| Expr GTt Expr  { AddInstr(GT,   0); printf("GT 0\n");}
	| Expr LEt Expr  { AddInstr(LE,   0); printf("LE 0\n");}
	| Expr GEt Expr  { AddInstr(GE,   0); printf("GE 0\n");}
	| Expr EQt Expr  { AddInstr(EQ,   0); printf("EQ 0\n");}
	| Expr NEt Expr  { AddInstr(NE,   0); printf("NE 0\n");}
	
;

Cond: if 
		{
		   AddInstr(POP, 0);
		   printf("POP 0\n");
		} 
	| if else
	;
if: IF OPEN  Expr {
			   AddInstr(DUP, 0);
		       printf("DUP 0\n");
  	  	 	   salva_end(ip);
			   AddInstr(JIF,  0);
			   printf("JIF label%i\n", indiceLabel);
			   labelPilha[labelPilhaTop++] = indiceLabel++;
			   AddInstr(POP, 0);
			   printf("POP 0\n");

 		 }
		 CLOSE  Bloco {
		   AddInstr(PUSH, 1);
		   printf("PUSH 1\n");
		   AddInstr(NOP, 0);
		   printf("label%i: NOP 0\n", labelPilha[--labelPilhaTop]);
		   prog[pega_end()].op.val.n = ip;
		 }
;
else: ELSE {
		 	salva_end(ip);
			AddInstr(JIT,  0);
			printf("JIT label%i\n", indiceLabel);
			labelPilha[labelPilhaTop++] = indiceLabel++;
		 }
		 Bloco {
		   AddInstr(NOP, 0);
		   printf("label%i: NOP 0\n", labelPilha[--labelPilhaTop]);
		   prog[pega_end()].op.val.n = ip;
		 } 
;
Loop: while
	| for
	;
while: WHILE OPEN  {salva_end(ip);}
	  		Expr  { 
	  			salva_end(ip); 
	  			AddInstr(JIF, 0);
	  			printf("JIF label%i\n", indiceLabel); 
			    labelPilha[labelPilhaTop++] = indiceLabel++;
	  		}
	  		CLOSE Bloco {
			  int ip2 = pega_end();
			  int ipToJump = pega_end();
			  AddInstr(JMP, ipToJump);
			  printf("JMP %i\n", ipToJump); 
			  prog[ip2].op.val.n = ip;
			  AddInstr(NOP, 0);
			  printf("label%i: NOP 0\n", labelPilha[--labelPilhaTop]);
			};
for: FOR OPEN Expr {AddInstr(POP, 0); printf("POP 0")} 
			SEP {salva_end(ip);}
			Expr { 
	  			AddInstr(JIF, 0);
	  			printf("JIF label%i\n", indiceLabel); 
			    labelPilha[labelPilhaTop++] = indiceLabel++;
			    salva_end(ip);
			    AddInstr(JMP, 0);
			    printf("JMP For%i\n", ForLabel);
			}
			SEP Expr {
				int ip2 = pega_end();
				int ipToJump = pega_end();
				AddInstr(JMP, ipToJump);
			  	printf("JMP %i\n", ipToJump);
			  	prog[ip2].op.val.n = ip;
			  	AddInstr(NOP, 0);
			  	printf("For%i: NOP 0\n", ForLabel++);
			  	salva_end(ip2 + 1);
			  	salva_end(ip2 - 1);
			}
			CLOSE Bloco {
			  	int ip2 = pega_end();
			  	int ipToJump = pega_end();
			  	AddInstr(JMP, ipToJump);
			 	printf("JMP %i\n", ipToJump); 
			 	prog[ip2].op.val.n = ip;
			 	AddInstr(NOP, 0);
			 	printf("label%i: NOP 0\n", labelPilha[--labelPilhaTop]);
			};

Bloco: ABRE Comandos FECHA;

Comandos: Comando 
    | Comandos Comando
	;

Func: FUNC ID
	  {
		salva_end(ip);
		AddInstr(JMP,  0);
		printf("JMP label%i\n", indiceLabel);
		labelPilha[labelPilhaTop++] = indiceLabel++;
		symrec *s = getsym($2);
		if (s==0) s = putsym($2);
		else {
		  yyerror("Função definida duas vezes\n");
		  YYABORT;
		}
		s->val = ip;
	  } OPEN
	  {
		newtab(0);
	  }
	  Args CLOSE  Bloco {
		AddInstr(RET, 0);
		printf("RET 0\n");
		AddInstr(NOP, 0); 
		printf("label%i: NOP 0\n", labelPilha[--labelPilhaTop]);
		prog[pega_end()].op.val.n = ip;
		deltab();
	  }
	  ;

Args: 
	| ID {
	  	 putsym($1);
	  }
    | Args SEP ID {
	  	 putsym($3);
	  }
	;

Syscall: MOV OPEN DIR CLOSE {
 	      AddInstr(PUSH, 1);
 	      printf("SYS {ACTION, {MOVE, %s}}\n", $3);
 	   }
 	| ATKM OPEN DIR CLOSE {
 	      AddInstr(PUSH, 1);
 	      printf("SYS {ACTION, {ATKMELEE, %s}}\n", $3);
 	   }
    | ATKS OPEN DIR CLOSE {
 	      AddInstr(PUSH, 1);
 	      printf("SYS {ACTION, {ATKSHORT, %s}}\n", $3);
 	   }
	| ATKL OPEN DIR CLOSE {
 	      AddInstr(PUSH, 1);
 	      printf("SYS {ACTION, {ATKLONG, %s}}\n", $3);
 	   }
 	| COL OPEN DIR CLOSE {
 	      AddInstr(PUSH, 1);
 	      printf("SYS {ACTION, {COLLECT, %s}}\n", $3);
 	   }
 	| DRP OPEN DIR CLOSE {
 	      AddInstr(PUSH, 1);
 	      printf("SYS {ACTION, {DROP, %s}}\n", $3);
 	   }
 	| SEEt OPEN DIR CLOSE {
 		  AddInstr(PUSH, 1);
 	      printf("SYS {ACTION, {SEE, %s}}\n", $3);
 	}
 ;

 self: MYSELF {AddInstr(PUSH, 1); printf("MATR 0\n");}
	 | MYARMY {AddInstr(PUSH, 1); printf("MATR 1\n");}
	 | FUEL   {AddInstr(PUSH, 1); printf("MATR 2\n");}
	 | HP     {AddInstr(PUSH, 1); printf("MATR 3\n");}
	 | MYCR   {AddInstr(PUSH, 1); printf("MATR 4\n");}
	 | MYCELL {AddInstr(PUSH, 1); printf("MATR 5\n");}

Chamada: ID OPEN
		 {
			 parmcnt = 0;
			 /* posição da memória mais avançada */
		 }
		 ListParms
		 {
		   symrec *s = getsym($1);
		   if (s == 0) {
			 yyerror("Função não definida\n");
			 YYABORT;
		   }
		   AddInstr(ENTRY, lastval());
		   printf("ENTRY %i\n", lastval());
		   /* Cópia dos parâmetros */
		   while (parmcnt > 0) 
		   {
			 AddInstr( STO, --parmcnt);
			 printf("STO %i\n", parmcnt);
			}
		   AddInstr(CALL, s->val);
		   printf("CALL %i\n", s->val);
		 }
	  	 CLOSE ;


ListParms:
	| Expr { parmcnt++;}
	| Expr { parmcnt++;} SEP ListParms
;


%%
extern FILE *yyin;

void yyerror(char const *msg) {
  fprintf(stderr, "ERRO na linha %d: %s ", yylineno, msg);
}

int compilador(FILE *cod, INSTR *dest) {
  int r;
  yyin = cod;
  prog = dest;
  r = yyparse();
  AddInstr(END,0);
  printf("END 0");
  return r;
}

/* int main(int ac, char **av) */
/* { */
/*   ac --; av++; */
/*   if (ac>0) */
/* 	yyin = fopen(*av,"r"); */

/*   yyparse(); */
/*   return 0; */
/* } */
