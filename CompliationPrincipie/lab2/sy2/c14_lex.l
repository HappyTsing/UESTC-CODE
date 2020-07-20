%{
enum yytokentype{
        NUMBER=258,STRING,ID,       
		INT,STR,VOID,IF,ELSE,WHILE,RETURN,PRINT,SCAN,
		CMP,
		ASSIGN,
		FEND
};

int yylval;

%}
%x comment string

%%
\/\/.+        {}      
[ \t\n\r\f\v]+    {}
"#".+ {}



"int"      {return INT;}
"str"	   {return STR;}
"void"     {return VOID;}
"if"       {return IF;}
"else"     {return ELSE;}
"while"    {return WHILE;}
"return"   {return RETURN;}
"print"    {return PRINT;}
"scan"     {return SCAN;}



"=="|"!="|">="|"<="|"<"|">"      {return CMP;}

"+="|"-="|"*="|"/="|"%="      {return ASSIGN;}



\+	{return '+';}
\-  {return '-';}
\*	{return '*';}
\/  {return '/';}
"%"	{return '%';}
";" {return ';';}
","	{return ',';}
"{" {return '{';}
"}"	{return '}';}
"(" {return '(';}
")" {return ')';}
"["	{return '[';}
"]"	{return ']';}
"=" {return '=';}
<<EOF>>  {return FEND;}    

[0-9]*		 {yylval = atoi(yytext);return NUMBER;}

"/*"         BEGIN(comment);

<comment>[^*]*        {}
<comment>"*"+[^*/]*   {}          
<comment>\*\/       BEGIN(INITIAL);

\"        BEGIN(string);
<string>[^"]* {return STRING;}
<string>\"   BEGIN(INITIAL);

([_a-zA-Z][a-z_A-Z0-9]*)   {return ID;}


%%



int yyerror(char *s)
{
	fprintf(stderr, "error: %s\n", s);
	return 0;
}

int yywrap()
{
	return 1;
}


