
/*integer*/
DINT ([0-9]*)([lL]?)

/*floating number*/
DFLOAT [0-9]*\.[0-9]*[fF]?

/*character string*/
DSTRING \"(.*?)\"

/*characters*/
DCHAR \'.\'   


 /*keywords*/
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

/*Identifier :'_' beginning, must be followed by something, the rest of the beginning can be a separate identifier*/
ID ([a-z$A-Z][a-z_$A-Z0-9]*)|(_[a-z_$A-Z0-9]+) 

/*annotation*/
COMMENT (\/\/.+)|(\/\*(.|\n)*?\*\/)



/*blank character*/
WHITESPACE [ \t\n\r\f\v]+


 /*operator*/
 /*arithmetic operator*/
ADD  \+
SUB  \-
MUL  \*
QUO  \/
REM  %
INC    \+\+
DEC    \-\-
 /*assigning operator*/
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
 /*Bitwise operators*/
AND      &
OR       \|
XOR      \^
SHL      <<
SHR      >>
AND_NOT  ~
 /*logical operator*/
LAND   &&
LOR    \|\|
NOT    \!
 /*relational operator*/
EQL     ==
LSS     <
GTR     >
NEQ       !=
LEQ       <=
GEQ       >=
QUA   \?
 /*punctuation*/
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
DQUA       \"
SQUA       \'
 /*else*/

QQQ @
%%

 /*keywords*/
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

 /*Skip whitespace and comments*/
{WHITESPACE} {}
{COMMENT} {printf("Comments:  %s\n",yytext);}


 /*operator*/
 /*arithmetic operator*/
{ADD} {printf("Operator:  %s\n",yytext);}
{SUB} {printf("Operator:  %s\n",yytext);}
{MUL} {printf("Operator:  %s\n",yytext);}
{QUO} {printf("Operator:  %s\n",yytext);}
{REM} {printf("Operator:  %s\n",yytext);}
{INC} {printf("Operator:  %s\n",yytext);}
{DEC} {printf("Operator:  %s\n",yytext);}
 /*logical operator*/
{LAND} {printf("Operator:  %s\n",yytext);}
{LOR} {printf("Operator:  %s\n",yytext);}
{NOT} {printf("Operator:  %s\n",yytext);}
 /*assigning operator*/
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
 /*Bitwise operators*/
{AND} {printf("Operator:  %s\n",yytext);}
{OR} {printf("Operator:  %s\n",yytext);}
{XOR} {printf("Operator:  %s\n",yytext);}
{SHL} {printf("Operator:  %s\n",yytext);}
{SHR} {printf("Operator:  %s\n",yytext);}
{AND_NOT} {printf("Operator:  %s\n",yytext);}
 /*relational operator*/
{EQL} {printf("Operator:  %s\n",yytext);}
{LSS} {printf("Operator:  %s\n",yytext);}
{GTR} {printf("Operator:  %s\n",yytext);}
{NEQ} {printf("Operator:  %s\n",yytext);}
{LEQ} {printf("Operator:  %s\n",yytext);}
{GEQ} {printf("Operator:  %s\n",yytext);}
{QUA} {printf("Operator:  %s\n",yytext);}
 /*punctuation*/
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
{DQUA} {printf("Punctuation:  %s\n",yytext);}
{SQUA} {printf("Punctuation:  %s\n",yytext);}
{QQQ}  {printf("Punctuation  %s\n",yytext);}




 /*Integer, floating point, string, character, identifier*/

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