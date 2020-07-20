#include"lrparser.tab.h"
#include"ast.h"

int main()
{
  if(!(yyin=fopen("test.txt","r")))
      printf("open fail\n");
  else
  yyparse();
  return 0;
}