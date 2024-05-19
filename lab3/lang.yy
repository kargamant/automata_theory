%require "3.2"

%code requires {
	#include <stdio.h>
	int yylex(void);
}

%token ID
%token NAME

%%

greetings:
	h_word',' ID {
			$$=$3;
			printf("%d is greeted\n", $$);
			}
	| h_word',' NAME {
			$$=$3;
			printf("%d is greeted\n", $$);
			}
;
h_word:
      "Hello" {}
      | "Hi" {}
      | "Howdy" {}
;

%%

int main()
{
	yyparse();
	return 0;
}
