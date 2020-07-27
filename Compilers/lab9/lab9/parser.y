%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"


#define MEM(size) ((char *)malloc(sizeof(char) * (size + 1)))

	char * make_tabs(long indent) {
    char *res = (char *)malloc(indent + 1);
    for (long i = 0; i < indent; i++) {
        res[i] = ' ';
    }
    res[indent] = '\0';
    return res;
}

%}

%define api.pure
%locations
%lex-param {yyscan_t scanner}
%parse-param {yyscan_t scanner}
%parse-param { long env[26]}

%union {
	char* ident;
	long number;
}

%token <ident> IDENT
%token <number> NUMBER
%token COMMA SEMICOLON LBRACE RBRACE CLASS PUBLIC PRIVATE LBRACKET RBRACKET

%type<ident> Object class body method prefix Start

%{
int yylex(YYSTYPE *yylval_param, YYLTYPE *yylloc_param , yyscan_t scanner);
void yyerror(YYLTYPE *yylloc, yyscan_t scanner, long env[26], const char *msg);
%}


%%

Start:		Object 	
			{ printf("%s\n",$1); };

Object:		prefix CLASS IDENT LBRACE add_indent body 
			{ $$ =  MEM(strlen($1)+strlen($3)+strlen($6)+30); sprintf($$, "%s class %s { %s", $1, $3, $6);};
			| CLASS IDENT LBRACE add_indent body 
			{ $$ =  MEM(strlen($2)+strlen($5)+30); sprintf($$, "class %s { %s}", $2, $5);};


body:       class body
			{ $$ = MEM(strlen($1)+strlen($2)+30); sprintf($$, "\n%s \n%s", $1, $2); };
			|method body 
			{ $$ = MEM(strlen($1)+strlen($2)+30); sprintf($$, "\n%s \n%s", $1, $2); };
			| RBRACE
			{ env[0] = env[0]-5; char *sp = make_tabs(env[0]);  $$ = MEM(10); sprintf($$, "\n\n%s}", sp);free(sp);};


class:      prefix CLASS IDENT LBRACE body 
			{ char *sp = make_tabs(env[0]);  $$ =  MEM(strlen($1)+strlen($3)+strlen($5)+30); sprintf($$, "\n%s%s class %s { %s", sp, $1, $3, $5);free(sp);};
			| CLASS IDENT LBRACE body 
			{ char *sp = make_tabs(env[0]); $$ =  MEM(strlen($2)+strlen($4)+30); sprintf($$, "%sclass %s { %s",sp,  $2, $4); free(sp);};


method:     prefix IDENT LBRACKET RBRACKET LBRACE RBRACE
			{ char *sp = make_tabs(env[0]-10); $$ =  MEM(strlen($1)+strlen($2)+30); sprintf($$, "%s%s %s(){\n\n%s}",sp, $1, $2, sp);free(sp);};

			| IDENT LBRACKET RBRACKET LBRACE RBRACE
			{ char *sp = make_tabs(env[0]-10); $$ =  MEM(strlen($1)+30); sprintf($$, "%s(){\n\n%s}", $1, sp); free(sp);};


prefix:     PUBLIC 
			{ $$ =  MEM(30); sprintf($$, "public");};
			| PRIVATE
			{ $$ =  MEM(30); sprintf($$, "private");};
add_indent:                               {env[0]=env[0]+5; }
    ;
remove_indent:                            {   env[0]=env[0]-5;  }
    ;



%%    

int main()
{
	char * buffer = 0;
	long length;
	long env[26];
    	env[0] = 10;

    char *sp= make_tabs(env[0]);
    free(sp);
	FILE * f = fopen ("input.txt", "rb");

	if (f) {
		fseek (f, 0, SEEK_END);
		length = ftell (f);
		fseek (f, 0, SEEK_SET);
		buffer = malloc (length);
		if (buffer) 
			fread (buffer, 1, length, f);
		fclose (f);
	}

	if (buffer) {
		printf("************** input **************\n");
		printf("%s\n", buffer);
		printf("************** output **************\n\n");
		yyscan_t scanner;
		struct Extra extra;
		init_scanner(buffer, &scanner, &extra);
		yyparse(scanner, env);
		destroy_scanner(scanner);

		free(buffer);
	}
	return 0;
}
