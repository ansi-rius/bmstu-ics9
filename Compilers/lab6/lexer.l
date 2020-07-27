%option noyywrap bison-bridge bison-locations

%{

#include <stdio.h>
#include <stdlib.h>

#define ARRAY   1
#define WORD  2
#define TAG_VARIABLE 3
#define TAG_WORD   4
#define TAG_SPACE  5


const char *tag_names [] = {
    "END_OF_PROGRAM", "ARRAY", "WORD","VARIABLE" , "CONSTANT", "SPACE"
};

struct Position {
    int line, pos, index;
};

void print_pos(struct Position *p) {
    printf("(%d,%d)", p->line, p->pos);
}

struct Fragment {
    struct Position starting, following;
};

typedef struct Fragment YYLTYPE;

void print_frag(struct Fragment *f) {
    print_pos(&(f->starting));
    printf("-");
    print_pos(&(f->following));
}

union Token {
    const char *ident;
    const char *word;
};

typedef union Token YYSTYPE;

int continued;
struct Position cur;

#define YY_USER_ACTION                       \
{                                            \
    int i;                                   \
    if (!continued)                          \
        yylloc->starting = cur;              \
    continued = 0;                           \
                                             \
    for (i = 0; i < yyleng; i++) {           \
        if (yytext [i] == '\n') {            \
            cur.line++;                      \
            cur.pos = 1;                     \
        } else {                             \
            cur.pos++;                       \
        }                                    \
        cur.index++;                         \
    }                                        \
    yylloc->following = cur;                 \
}

void init_scanner(const char *path) {
    continued = 0;
    cur.line = 1;
    cur.pos = 1;
    cur.index = 0;
    yyin = fopen(path, "r");
}

void err(const char *msg) {
    printf("Error");
    print_pos(&cur);
    printf(": %s\n", msg);
}

%}

SPACE [ \t\r\n\v\f]+
DIGIT [0-9]

CONSTANT #{DIGIT}* 
VARIABLE (\.|\:){DIGIT}*
ARRAY (\,|\;){DIGIT}*
WORD (PLAESE|DO|FORGET)

%%
{SPACE} {
	yylval->ident = yytext;
	BEGIN(0);
	return TAG_SPACE;
}
{CONSTANT} {
	yylval->ident = yytext;
	BEGIN(0);
	return TAG_WORD;
}
{ARRAY} {
	yylval->ident = yytext;
	BEGIN(0);
	return ARRAY;
}
{WORD} {
	yylval->ident = yytext;
	BEGIN(0);
	return WORD;
}
{VARIABLE} {
	yylval->ident = yytext;
	BEGIN(0);
	return TAG_VARIABLE;
}

. err("error");
%%

int main(int argc, const char **argv) {
    int tag;
    YYSTYPE value;
    YYLTYPE coords;
    init_scanner(argv[1]);

    while (1) {
        tag = yylex(&value, &coords);
        printf("%s ", tag_names[tag]);
        if (tag == 0) {
            printf("\n");
            break;
        }
        print_frag(&coords);
        if (tag == TAG_VARIABLE) {
            printf(": %s", value.ident);
        } else if (tag == ARRAY) {
            printf(": %s", value.ident);
        }
	else if (tag == TAG_SPACE) {
			
	}
	else {
		printf(": %s", value.ident);	
	}
        printf("\n");
    }

    return 0;
}
