%option noyywrap yylineno

%{
    #include"ast.h"
    #include"lrparser.tab.h"
%}
%x comment string
%%

"while"             {return WHILE;}
"int"               {return INT;}
"str"               {return STR;}
"void"              {return VOID;}
"if"                {return IF;} 
"else"              {return ELSE;}
"return"            {return RETURN;}
"print"             {return PRINT;}
"scan"              {return SCAN;}
"<" |
">" |
">=" |
"<=" |
"=="                {yylval.save_yytext=strdup(yytext);return CMP;}
":=" |
"+=" |
"/=" |
"-=" |
"*="                {yylval.save_yytext=strdup(yytext);return ASSIGN;}
"+" |
"-" |
"*" |
"/" |
"%" |
"," |
";" |
"=" |
"[" |
"]" |
"(" |
")" |
"{" |
"}"                  {yylval.save_yytext=strdup(yytext);return yytext[0];}
[0-9]+               {yylval.save_yytext=strdup(yytext);return NUMBER;}
[a-zA-Z][a-zA-Z0-9_]* {yylval.save_yytext=strdup(yytext);return ID;}

"/*"         BEGIN(comment);

<comment>[^*]*        {}
<comment>"*"+[^*/]*   {}          
<comment>\*\/       BEGIN(INITIAL);

\"        BEGIN(string);
<string>[^"]* {yylval.save_yytext=strdup(yytext);return STRING;}
<string>\"   BEGIN(INITIAL);


\/\/.+        {}      
[ \t\n\r\f\v]+    {}         
<<EOF>>             {return EOP;} //EOF:End OF Programme
%%

int yyerror(char *text){
    fprintf(stderr,"error:%s\nline:%d\nyytext:%s",text,yylineno,yytext);
    return 0;
}