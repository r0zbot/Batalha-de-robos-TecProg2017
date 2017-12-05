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
static int labelPilha[90];
static int indiceLabel = 0;
static int labelPilhaTop = 0;

void AddInstr(OpCode op, int val) {
  prog[ip++] = (INSTR) {op,  {NUM, {val}}};
}
%}

/*  Declaracoes */
%union {
  double val;
  /* symrec *cod; */
  char cod[30];
  char dir[2];
}


/* %type  Expr */

%token <val> NUMt
%token <cod> ID
%token <dir> DIR
%token ADDt SUBt MULt DIVt ASGN OPEN CLOSE RETt EOL
%token EQt NEt LTt LEt GTt GEt ABRE FECHA SEP
%token IF WHILE FUNC PRINT TERR CRI OCP BAS MOV ATKM ATKS ATKL COL DRP SEEt

%right ASGN
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

Comando: Expr EOL
       | Cond
       | Loop
       | Func
	   | PRINT Expr EOL { AddInstr(PRN, 0); printf("PRN 0\n");}
	   | RETt EOL {
		 	     AddInstr(LEAVE, 0);
		 	     printf("LEAVE 0\n");
			     AddInstr(RET,0);
			     printf("RET 0\n");
 			  }
	   | RETt OPEN  Expr CLOSE EOL {
		 	     AddInstr(LEAVE, 0);	
		 	     printf("LEAVE 0\n");
			     AddInstr(RET,0);
			     printf("RET 0\n");
 		      }
 	   | MOV OPEN DIR CLOSE EOL {
 	      AddInstr(ADD, 0);
 	      char *direc;
 	      direc = $3;
 	      printf("SYS {ACTION, {MOVE, %s}}\n", direc);
 	   }
 	   | ATKM OPEN DIR CLOSE EOL {
 	      AddInstr(ADD, 0);
 	      char *direc;
 	      direc = $3;
 	      printf("SYS {ACTION, {ATKMELEE, %s}}\n", direc);
 	   }
 	   | ATKS OPEN DIR CLOSE EOL {
 	      AddInstr(ADD, 0);
 	      char *direc;
 	      direc = $3;
 	      printf("SYS {ACTION, {ATKSHORT, %s}}\n", direc);
 	   }
 	   | ATKL OPEN DIR CLOSE EOL {
 	      AddInstr(ADD, 0);
 	      char *direc;
 	      direc = $3;
 	      printf("SYS {ACTION, {ATKLONG, %s}}\n", direc);
 	   }
 	   | COL OPEN DIR CLOSE EOL {
 	      AddInstr(ADD, 0);
 	      char *direc;
 	      direc = $3;
 	      printf("SYS {ACTION, {COLLECT, %s}}\n", direc);
 	   }
 	   | DRP OPEN DIR CLOSE EOL {
 	      AddInstr(ADD, 0);
 	      char *direc;
 	      direc = $3;
 	      printf("SYS {ACTION, {DROP, %s}}\n", direc);
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
	

	| Chamada 
    | Expr ADDt Expr { AddInstr(ADD,  0); printf("ADD 0\n");}
	| Expr SUBt Expr { AddInstr(SUB,  0); printf("SUB 0\n");}
	| Expr MULt Expr { AddInstr(MUL,  0); printf("MUL 0\n");}
	| Expr DIVt Expr { AddInstr(DIV,  0); printf("DIV 0\n");}
    | '-' Expr %prec NEG  { printf(" {CHS 0},\n"); }
	| OPEN Expr CLOSE
	| Expr LTt Expr  { AddInstr(LT,   0); printf("LT 0\n");}
	| Expr GTt Expr  { AddInstr(GT,   0); printf("GT 0\n");}
	| Expr LEt Expr  { AddInstr(LE,   0); printf("LE 0\n");}
	| Expr GEt Expr  { AddInstr(GE,   0); printf("GE 0\n");}
	| Expr EQt Expr  { AddInstr(EQ,   0); printf("EQ 0\n");}
	| Expr NEt Expr  { AddInstr(NE,   0); printf("NE 0\n");}
;

Cond: IF OPEN  Expr {
  	  	 	   salva_end(ip);
			   AddInstr(JIF,  0);
			   printf("JIF label%i\n", indiceLabel);
			   labelPilha[labelPilhaTop++] = indiceLabel++;
 		 }
		 CLOSE  Bloco {
		   AddInstr(ADD, 0);
		   printf("label%i: NOP 0\n", labelPilha[--labelPilhaTop]);
		   prog[pega_end()].op.val.n = ip;
		 };

Loop: WHILE OPEN  {salva_end(ip);}
	  		Expr  { 
	  			salva_end(ip); 
	  			AddInstr(JIF, 0);
	  			printf("JIF label%i\n", indiceLabel); 
			    labelPilha[labelPilhaTop++] = indiceLabel++;
	  		}
	  		CLOSE Bloco {
			  int ip2 = pega_end();
			  AddInstr(JMP, pega_end());
			  printf("JMP %i\n", pega_end());
			  AddInstr(ADD, 0); 
			  printf("label%i: NOP 0\n", labelPilha[--labelPilhaTop]);
			  prog[ip2].op.val.n = ip;
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
	  Args CLOSE  Bloco
	  {
		AddInstr(LEAVE, 0);
		printf("LEAVE 0\n");
		AddInstr(RET, 0);
		printf("RET 0\n");
		AddInstr(ADD, 0); 
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
			 AddInstr( STO, --parmcnt);
			 printf("STO %i\n", parmcnt);
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
  fprintf(stderr, "ERRO: %s",msg);
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
