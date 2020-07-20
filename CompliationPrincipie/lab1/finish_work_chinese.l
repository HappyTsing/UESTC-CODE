
/*整数*/
DINT ([0-9]*)([lL]?)

/*浮点数*/
DFLOAT [0-9]*\.[0-9]*[fF]?

/*字符串*/
DSTRING \"(.*?)\"

/*字符*/
DCHAR \'.\'   


 /*关键字*/
ABSTRACT abstract
ASSERT assert
BOOLEAN boolean
BREAK break
BYTE byte
CASE case
CATCH catch
CHAR char
CLASS class
CONST const
CONTINUE continue
DEFAULT default
DO do	
DOUBLE double	
ELSE else
ENUM enum	
EXTENDS extends	
FINAL final	
FINALLY finally	
FLOAT float
FOR for	
FALSE false
GOTO goto	
IF if	
IMPLEMENTS implements	
IMPORT import
INSTANCEOF instanceof	
INT int	
INTERFACE interface	
LONG long	
NATIVE native
NEW	new	
NULL null
PACKAGE	package	
PRIVATE	private	
PROTECTED protected	
PUBLIC public
RETURN return	
STRICTFP strictfp	
SHORT short	
STATIC static	
SUPER super
SWITCH switch	
SYNCHRONIZED synchronized	
THIS this	
THROW throw	
THROWS throws
TRANSIENT transient	
TRY try	
TRUE true
VOID void	
VOLATILE volatile	
WHILE while

/*标识符:_开头，后面必须跟东西，其余开头可单独作为标识符*/
ID ([a-z$A-Z][a-z_$A-Z0-9]*)|(_[a-z_$A-Z0-9]+) 

/*注释*/
COMMENT (\/\/.+)|(\/\*(.|\n)*\*\/)



/*空白符*/
WHITESPACE [ \t\n\r\f\v]+


 /*运算符*/
 /*算术运算符*/
ADD  \+
SUB  \-
MUL  \*
QUO  \/
REM  %
INC    \+\+
DEC    \-\-
 /*赋值运算符*/
ASSIGN  =
ADD_ASSIGN  \+=
SUB_ASSIGN  \-=
MUL_ASSIGN  \*=
QUO_ASSIGN  \/=
REM_ASSIGN  %=
AND_ASSIGN  \&=
OR_ASSIGN  \|=
XOR_ASSIGN  \^=
SHL_ASSIGN  <<=
SHR_ASSIGN  >>=
AND_NOT_ASSIGN  ~=
 /*位运算符*/
AND      &
OR       \|
XOR      \^
SHL      <<
SHR      >>
AND_NOT  ~
 /*逻辑运算符*/
LAND   &&
LOR    \|\|
NOT    \!
 /*关系运算符*/
EQL     ==
LSS     <
GTR     >
NEQ       !=
LEQ       <=
GEQ       >=
 /*标点符号*/
LPAREN  \(
RPAREN  \)
LBRACK  \[
LBRACE  \{
COMMA   ,
PERIOD  \.
RBRACK     \]
RBRACE     \}
SEMICOLON  ;
COLON      :
POT         \->
DQUA       \"
SQUA       \'
 /*其他*/
QUA   \?
QQQ @
%%

 /*关键字*/
{FALSE} {printf("Key Word:  %s\n",yytext);}
{TRUE} {printf("Key Word:  %s\n",yytext);}
{NULL} {printf("Key Word:  %s\n",yytext);}
{ABSTRACT} {printf("Key Word:  %s\n",yytext);}
{ASSERT} {printf("Key Word:  %s\n",yytext);}
{BOOLEAN} {printf("Key Word:  %s\n",yytext);}
{BREAK} {printf("Key Word:  %s\n",yytext);}
{BYTE} {printf("Key Word:  %s\n",yytext);}
{CASE} {printf("Key Word:  %s\n",yytext);}
{CATCH} {printf("Key Word:  %s\n",yytext);}
{CHAR} {printf("Key Word:  %s\n",yytext);}
{CLASS} {printf("Key Word:  %s\n",yytext);}
{CONST} {printf("Key Word:  %s\n",yytext);}
{CONTINUE} {printf("Key Word:  %s\n",yytext);}
{DEFAULT} {printf("Key Word:  %s\n",yytext);}
{DO} {printf("Key Word:  %s\n",yytext);}
{DOUBLE} {printf("Key Word:  %s\n",yytext);}
{ELSE} {printf("Key Word:  %s\n",yytext);}
{ENUM} {printf("Key Word:  %s\n",yytext);}
{EXTENDS} {printf("Key Word:  %s\n",yytext);}
{FINAL} {printf("Key Word:  %s\n",yytext);}
{FINALLY} {printf("Key Word:  %s\n",yytext);}
{FLOAT} {printf("Key Word:  %s\n",yytext);}
{FOR} {printf("Key Word:  %s\n",yytext);}
{GOTO} {printf("Key Word:  %s\n",yytext);}
{IF} {printf("Key Word:  %s\n",yytext);}
{IMPLEMENTS} {printf("Key Word:  %s\n",yytext);}
{IMPORT} {printf("Key Word:  %s\n",yytext);}
{INSTANCEOF} {printf("Key Word:  %s\n",yytext);}
{INT} {printf("Key Word:  %s\n",yytext);}
{INTERFACE} {printf("Key Word:  %s\n",yytext);}
{LONG} {printf("Key Word:  %s\n",yytext);}
{NATIVE} {printf("Key Word:  %s\n",yytext);}
{NEW} {printf("Key Word:  %s\n",yytext);}
{PACKAGE} {printf("Key Word:  %s\n",yytext);}
{PRIVATE} {printf("Key Word:  %s\n",yytext);}
{PROTECTED} {printf("Key Word:  %s\n",yytext);}
{PUBLIC} {printf("Key Word:  %s\n",yytext);}
{RETURN} {printf("Key Word:  %s\n",yytext);}
{STRICTFP} {printf("Key Word:  %s\n",yytext);}
{SHORT} {printf("Key Word:  %s\n",yytext);}
{STATIC} {printf("Key Word:  %s\n",yytext);}
{SUPER} {printf("Key Word:  %s\n",yytext);}
{SWITCH} {printf("Key Word:  %s\n",yytext);}
{SYNCHRONIZED} {printf("Key Word:  %s\n",yytext);}
{THIS} {printf("Key Word:  %s\n",yytext);}
{THROW} {printf("Key Word:  %s\n",yytext);}
{THROWS} {printf("Key Word:  %s\n",yytext);}
{TRANSIENT} {printf("Key Word:  %s\n",yytext);}
{TRY} {printf("Key Word:  %s\n",yytext);}
{VOID} {printf("Key Word:  %s\n",yytext);}
{VOLATILE} {printf("Key Word:  %s\n",yytext);}
{WHILE} {printf("Key Word:  %s\n",yytext);}

 /*跳过空白和注释*/
{WHITESPACE} {}
{COMMENT} {printf("Comments:  %s\n",yytext);}


 /*运算符*/
 /*算术运算符*/
{ADD} {printf("Operator:  %s\n",yytext);}
{SUB} {printf("Operator:  %s\n",yytext);}
{MUL} {printf("Operator:  %s\n",yytext);}
{QUO} {printf("Operator:  %s\n",yytext);}
{REM} {printf("Operator:  %s\n",yytext);}
{INC} {printf("Operator:  %s\n",yytext);}
{DEC} {printf("Operator:  %s\n",yytext);}
 /*逻辑运算符*/
{LAND} {printf("Operator:  %s\n",yytext);}
{LOR} {printf("Operator:  %s\n",yytext);}
{NOT} {printf("Operator:  %s\n",yytext);}
 /*赋值运算符*/
{ASSIGN} {printf("Operator:  %s\n",yytext);}
{ADD_ASSIGN} {printf("Operator:  %s\n",yytext);}
{SUB_ASSIGN} {printf("Operator:  %s\n",yytext);}
{MUL_ASSIGN} {printf("Operator:  %s\n",yytext);}
{QUO_ASSIGN} {printf("Operator:  %s\n",yytext);}
{REM_ASSIGN} {printf("Operator:  %s\n",yytext);}
{AND_ASSIGN} {printf("Operator:  %s\n",yytext);}
{OR_ASSIGN} {printf("Operator:  %s\n",yytext);}
{XOR_ASSIGN} {printf("Operator:  %s\n",yytext);}
{SHL_ASSIGN} {printf("Operator:  %s\n",yytext);}
{SHR_ASSIGN} {printf("Operator:  %s\n",yytext);}
{AND_NOT_ASSIGN} {printf("Operator:  %s\n",yytext);}
 /*位运算符*/
{AND} {printf("Operator:  %s\n",yytext);}
{OR} {printf("Operator:  %s\n",yytext);}
{XOR} {printf("Operator:  %s\n",yytext);}
{SHL} {printf("Operator:  %s\n",yytext);}
{SHR} {printf("Operator:  %s\n",yytext);}
{AND_NOT} {printf("Operator:  %s\n",yytext);}
 /*关系运算符*/
{EQL} {printf("Operator:  %s\n",yytext);}
{LSS} {printf("Operator:  %s\n",yytext);}
{GTR} {printf("Operator:  %s\n",yytext);}
{NEQ} {printf("Operator:  %s\n",yytext);}
{LEQ} {printf("Operator:  %s\n",yytext);}
{GEQ} {printf("Operator:  %s\n",yytext);}
 /*标点符号*/
{LPAREN} {printf("Punctuation:  %s\n",yytext);}
{RPAREN} {printf("Punctuation:  %s\n",yytext);}
{LBRACK} {printf("Punctuation:  %s\n",yytext);}
{LBRACE} {printf("Punctuation:  %s\n",yytext);}
{COMMA}  {printf("Punctuation:  %s\n",yytext);}
{PERIOD} {printf("Punctuation:  %s\n",yytext);}
{RBRACK} {printf("Punctuation:  %s\n",yytext);}
{RBRACE} {printf("Punctuation:  %s\n",yytext);}
{SEMICOLON} {printf("Punctuation:  %s\n",yytext);}
{COLON} {printf("Punctuation:  %s\n",yytext);}
{POT} {printf("Punctuation:  %s\n",yytext);}
{DQUA} {printf("Punctuation:  %s\n",yytext);}
{SQUA} {printf("Punctuation:  %s\n",yytext);}
{QUA}  {printf("Punctuation  %s\n",yytext);}
{QQQ}  {printf("Punctuation  %s\n",yytext);}




 /*整型、浮点型、字符串、字符、标识符*/

{DFLOAT} {printf("float:  %s\n",yytext);}
{DINT} {printf("int:  %s\n",yytext);}

{DSTRING} {printf("String:  %s\n",yytext);}
{DCHAR} {printf("char:  %s\n",yytext);}
{ID} {printf("ID:  %s\n",yytext);}

%%
int main(int argc,char **argv)
{
        yylex();
        return 0;
}
int yywarp(){
        return 1;
}