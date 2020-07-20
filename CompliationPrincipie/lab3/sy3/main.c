#include"lrparser.tab.h"
#include"ast.h"

int main(int argc ,char*argv[])
{

    setbuf(stdout, NULL);
    if(argc < 2 )
    {
        printf("input file is needed.\n");
        exit(0);
    }
    yyin = fopen(argv[1],"r");
	yyparse();
    fclose(yyin);
    return 0;
   
}