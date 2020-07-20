#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum yytokentype {
	NUMBER = 258, STRING, ID,
	INT, STR, VOID, IF, ELSE, WHILE, RETURN, PRINT, SCAN,
	CMP, //< > = >= <= !=
	ASSIGN, //+= -= *= /=
	FEND  //end of file
};
// if match(),then advance()

extern int yylex();
extern int yylval;
extern char* yytext;
extern FILE* yyin;

int tok;

void advance();
bool match(int);

int program();
int external_declaration();
int decl_or_stmt();
int declarator_list();
int intstr_list();
int initializer();
int declarator();
int parameter_list();
int parameter();
int type();
int statement();
int statement_list();
int expression_statement();
int expr();
int cmp_expr();
int add_expr();
int mul_expr();
int primary_expr();
int expr_list();
int id_list();

void advance()
{
	tok = yylex();
	printf("tok: %s\n", yytext);
}
bool match(int terminal_symbol)
{
	if (tok == terminal_symbol)
		return true;
	else
		return false;
}
int program()
{

	external_declaration();
	while (tok != FEND) {
		external_declaration();
	}
	return 1;
}

int external_declaration()
{
	if (match(INT) || match(STR) || match(VOID)) //FIRST
		type();
	else
	{
		printf("ERROR:external_declaration()\n");
		return 0;
	}
	if (match(ID))
		declarator();
	else 
	{
		printf("ERROR:external_declaration()\n");
		return 0;
	}
	
    if (match('{') || match(',') || match(';'))
		decl_or_stmt();
	else
	{
		printf("ERROR:external_declaration()\n");
		return 0;
	}
	return 1;
}
int decl_or_stmt()
{
	if (match('{'))
	{
		advance();
		if (match('}'))
		{
			advance();
			return 1;
		}        //statement' first
		else if(match(SCAN)||match(PRINT)||match(RETURN)||match(WHILE)||match(IF)||match('{')||match(VOID)||match(STR)||match(INT)||match(';')||match('(')||match(ID)||match(STRING)||match(NUMBER)||match('-'))
		{
			statement_list();
			if (!match('}'))
			{
				printf("ERROR:decl_or_stmt()1\n");
				return 0;
			}
			advance();
			return 1;
		}
		else
		{
			printf("ERROR:decl_or_stmt()2\n");
			return 0;
		}
	}
	else if (match(','))
	{
		advance();
		if (match(ID))
		{
			declarator_list();
			if (!match(';'))
			{
				printf("ERROR:decl_or_stmt()3\n");
				return 0;
			}
			advance();
			return 1;
		}
		else
		{
			printf("ERROR:decl_or_stmt()4\n");
			return 0;
		}

	}
	else if (match(';'))
	{
		advance();
		return 1;
	}
	else
	{
		printf("ERROR:decl_or_stmt5\n");
		return 0;
	}
}
int  declarator_list()
{
	if (match(ID))
	{
		declarator();
		while (match(','))
		{
			advance();
			if (match(ID))
			{
				declarator();
			}
			else
			{
				printf("ERROR: declarator_list()\n");
				return 0;
			}

		}
		return 1;
	}
	else
	{
		printf("ERROR: declarator_list()\n");
		return 0;
	}

}
int  intstr_list()
{
	if (match(NUMBER)||match(STRING))
	{
		initializer();
		while (match(','))
		{
			advance();
			if (match(NUMBER) || match(STRING))
			{
				initializer();
			}
			else
			{
				printf("ERROR: intstr_list()\n");
				return 0;
			}

		}
		return 1;
	}
	else
	{
		printf("ERROR: intstr_list()\n");
		return 0;
	}
}
int  initializer()
{
	if (match(NUMBER))
	{
		advance();
		return 1;
	}
	else if (match(STRING))
	{
		advance();
		return 1;
	}
	else
	{
		printf("ERROR:False Match initializer:Expect NUMBER or STRING\n");
		return 0;
	}
}
int  declarator()
{
	if (!match(ID))
	{
		printf("ERROR:False Match declarator:Expect ID\n");
		return 0;
	}
	else
	{
		advance();
		if (match('='))
		{
			advance();
			if (match(ID) || match('(') || match(NUMBER) || match(STRING) || match('-'))
			{
				expr();
				return 1;
			}
			else
			{
				printf("ERROR:declarator()\n");
				return 0;
			}

		}
		else if (match('('))
		{
			advance();
			if (match(')'))
			{
				advance();
				return 1;
			}
			else if(match(INT)||match(STR)||match(VOID))
			{
				parameter_list();
				if (match(')'))
				{
					advance();
					return 1;
				}
				else
				{
					printf("ERROR:declarator()\n");
					return 0;
				}

			}
			else
			{
				printf("ERROR:declarator()\n");
				return 0;
			}
		}
		else if (match('['))
		{
			advance();
			if (match(']'))
			{
				advance();
				if (match('='))
				{
					advance();
					if (match('{'))
					{
						advance();
						if (match(NUMBER) || match(STRING))
						{
							intstr_list();
							if (match('}'))
							{
								advance();
								return 1;
							}
							else
							{
								printf("ERROR:declarator()\n");
								return 0;
							}
						}
						else
						{
							printf("ERROR:declarator()\n");
							return 0;
						}
					}
					else
					{
						printf("ERROR:declarator()\n");
						return 0;
					}
				}
				return 1;  //没匹配到=，说明是匹配了语句 ID'[' ']'
			}
			else if (match(ID) || match('(') || match(NUMBER) || match(STRING) || match('-'))
			{
				expr();
				if (match(']'))
				{
					advance();
					if (match('='))
					{
						advance();
						if (match('{'))
						{
							advance();
							if (match(NUMBER) || match(STRING))
							{
								intstr_list();
								if (match('}'))
								{
									advance();
									return 1;
								}
								else
								{
									printf("ERROR:declarator()\n");
									return 0;
								}
							}
							else
							{
								printf("ERROR:declarator()\n");
								return 0;
							}
						}
						else
						{
							printf("ERROR:declarator()\n");
							return 0;
						}
					}
					return 1;  //没匹配到=，说明是匹配了语句 ID'['expr() ']'
				}
				else
				{

					printf("ERROR:declarator()\n");
					return 0;
				}
			}
			else
			{

				printf("ERROR:declarator()\n");
				return 0;
			}
		}
		else
		{
			return 1;
			//表示只匹配了ID
		}
	}
}
int  parameter_list()
{
	if (match(INT) || match(STR)||match(VOID))
	{
		parameter();
		while (match(','))
		{
			advance();
			if (match(INT) || match(STR) || match(VOID))
			{
				parameter();
			}
			else
			{
				printf("ERROR:parameter_list()\n");
				return 0;
			}

		}
		return 1;
	}
	else
	{
		printf("ERROR:parameter_list())\n");
		return 0;
	}
}
int  parameter()
{
	if (match(INT) || match(STR) || match(VOID))
	{
		type();
		if (!match(ID))
		{
			printf("ERROR:parameter()\n");
			return 0;
		}
		advance();
		return 1;
	}
	else
	{
		printf("ERROR:parameter()\n");
		return 0;
	}

}
int  type()
{
	if (match(INT))
	{
		advance();
		return 1;
	}
	else if (match(STR))
	{
		advance();
		return 1;
	}
	else if (match(VOID))
	{
		advance();
		return 1;
	}
	else
	{
		printf("ERROR:type():Expect INT or STR or VOID\n");
		return 0;
	}
}
int  statement()
{
	if (match(INT) || match(STR) || match(VOID))
	{
		type();
		if (match(ID))
		{
			declarator_list();
			if (match(';'))
			{
				advance();
				return 1;
			}
			else
			{
				printf("ERROR:statement()1\n");
				return 0;
			}
		}
		else
		{
			printf("ERROR:statement()2\n");
			return 0;
		}
	}
	else if (match('{'))
	{
		advance();
		if (match(SCAN) || match(PRINT) || match(RETURN) || match(WHILE)||match(IF) || match('{') || match(VOID) || match(STR) || match(INT) || match(';') || match('(') || match(ID) || match(STRING) || match(NUMBER) || match('-'))
		{
			statement_list();
			if (match('}'))
			{
				advance();
				return 1;
			}
			else
			{
				printf("ERROR:statement()3\n");
				return 0;
			}
		}
		else
		{
			printf("ERROR:statement()4\n");
			return 0;
		}
	}
	else if (match(';') || match('-') || match(ID) || match(NUMBER) || match(STRING))
	{
		expression_statement();
		return 1;
	}
	else if (match(IF))
	{
		advance();
		if (match('('))
		{
			advance();
			if (match('-') || match(ID) || match(NUMBER) || match(STRING)||match('('))
			{
				expr();
				if (match(')'))
				{
					advance();
					if (match(SCAN) || match(PRINT) || match(RETURN)||match(WHILE) || match(IF) || match('{') || match(VOID) || match(STR) || match(INT) || match(';') || match('(') || match(ID) || match(STRING) || match(NUMBER) || match('-'))
					{
						statement();
						if (match(ELSE))
						{
							advance();
						if (match(SCAN) || match(PRINT) || match(RETURN) ||match(WHILE)|| match(IF) || match('{') || match(VOID) || match(STR) || match(INT) || match(';') || match('(') || match(ID) || match(STRING) || match(NUMBER) || match('-'))
							{
								statement();
								return 1;
							}
							else
							{
								printf("ERROR:statement()5\n");
								return 0;
							}
						}
						else
						{
							return 1; //IF '(' expr ')' statement
						}
					}
					else
					{
						printf("ERROR:statement()6\n");
						return 0;
					}
				}
				else
				{
					printf("ERROR:statement()7\n");
					return 0;
				}
			}
			else
			{
				printf("ERROR:statement()8\n");
				return 0;
			}

		}
		else
		{
			printf("ERROR:statement()9\n");
			return 0;
		}
	}
	else if (match(WHILE))
	{
	advance();
		if (match('('))
		{
			advance();
			if (match('-') || match(ID) || match(NUMBER) || match(STRING)||match('('))
			{
				printf("3\n");
				expr();
				if (match(')'))
				{
					advance();
					if (match(SCAN) || match(PRINT) || match(RETURN) ||match(WHILE)|| match(IF) || match('{') || match(VOID) || match(STR) || match(INT) || match(';') || match('(') || match(ID) || match(STRING) || match(NUMBER) || match('-'))
					{
						statement();
						return 1;
					}
					else
					{
						printf("ERROR:statement()10\n");
						return 0;
					}
				}
				else
				{
					printf("ERROR:statement()11\n");
					return 0;
				}
			}
			else
			{
				printf("ERROR:statement()12\n");
				return 0;
			}
		}
		else
		{
			printf("ERROR:statement()13\n");
			return 0;
		}
	

	}
	else if (match(RETURN))
	{
	advance();
	if (match(';'))
	{
		advance();
		return 1;
	}
	else if (match('-') || match(ID) || match(NUMBER) || match(STRING)|| match('('))
	{
		expr();
		if (match(';'))
		{
			advance();
			return 1;
		}
		else
		{
			printf("ERROR:statement()14\n");
			return 0;
		}
	}
	else

	{
		printf("ERROR:statement()15\n");
		return 0;
	}

     }
	else if (match(PRINT))
	{
	advance();
	if (match(';'))
	{
		advance();
		return 1;
	}
	else if (match('-') || match(ID) || match(NUMBER) || match(STRING) || match('('))
	{
		expr_list();
		
		if (match(';'))
		{
			advance();
			return 1;
		}
		else
		{
			
			printf("ERROR:statement()16\n");
			return 0;
		}

	}
	else

	{
		printf("ERROR:statement()17\n");
		return 0;
	}

	 }
	else if (match(SCAN))
	{
	advance();
	if (match(ID))
	{
		id_list();
		if (match(';'))
		{
			advance();
			return 1;
		}
		else
		{
			printf("ERROR:statement()18\n");
			return 0;
		}
	}
	else
	{
		printf("ERROR:statement()19\n");
		return 0;
	}


	
 }
	else
	{
	printf("ERROR:statement()20\n");
	return 0;

 }
 }

int  statement_list()
{
	if (match(SCAN) || match(PRINT)|| match(WHILE)|| match(RETURN) || match(IF) || match('{') || match(VOID) || match(STR) || match(INT) || match(';') || match('(') || match(ID) || match(STRING) || match(NUMBER) || match('-'))
	{
		
		statement();
		while (match(SCAN) || match(PRINT) || match(RETURN) ||match(WHILE)|| match(IF) || match('{') || match(VOID) || match(STR) || match(INT) || match(';') || match('(') || match(ID) || match(STRING) || match(NUMBER) || match('-'))
		{
			statement();
		}
		return 1;
	}
	else
	{
		printf("ERROR statement_list()\n");
		return 0;

	}
	

}
int  expression_statement()
{
	if (match(';'))
	{
		advance();
		return 1;
	}
	else if (match('-') || match(ID) || match(NUMBER) || match(STRING) || match('('))
	{
		expr();
		if (match(';'))
		{	advance();
		    return 1;
		}
		else
		{
			printf("ERROR:expression_statement()1\n");
			return 0;
		}		
	}
	else
	{
		printf("ERROR:expression_statement()2\n");
		return 0;
	}
}
int  expr()
{

	if (match('-') || match(ID) || match(NUMBER) || match(STRING) || match('('))
	{
		cmp_expr();
	 }
	else
	{
		printf("ERROR:expr()\n");
		return 0;
	}
}
int  cmp_expr()
{
	if (match('-') || match(ID) || match(NUMBER) || match(STRING) || match('('))
	{
		add_expr();
		while(match(CMP))
		{
			advance();
			if (match('-') || match(ID) || match(NUMBER) || match(STRING) || match('('))
			{
				cmp_expr();
			}
		}
		return 1;

	}
	else
	{
		printf("ERROR: cmp_expr()\n");
		return 0;
	}
}
int  add_expr()
{
	if (match('-') || match(ID) || match(NUMBER) || match(STRING) || match('('))
	{
		mul_expr();
		while(match('+')||match('-'))
		{
			advance();
			if (match('-') || match(ID) || match(NUMBER) || match(STRING) || match('('))
			{
				add_expr();
			}
		}

	}
	else
	{
		printf("ERROR: add_expr()\n");
		return 0;
	}
}

int  mul_expr()
{
	if (match(ID) || match(NUMBER) || match(STRING) || match('('))
	{
		primary_expr();
		while(match('*') || match('/') || match('%'))
		{
			advance();
			if ( match(ID) || match(NUMBER) || match(STRING) || match('('))
			{
				mul_expr();
			}
		}
		return 1;
	}
	else if(match('-'))
	{
		advance();
		if (match(ID) || match(NUMBER) || match(STRING) || match('('))
		{
			return primary_expr();
			
		}
		else
		{
			printf("ERROR: mul_expr()\n");
		    return 0;
		}

	}
	else
	{
		printf("ERROR: mul_expr()\n");
		return 0;
	}
}
int  primary_expr()
{
	if (match(ID))
	{
		advance();
		if (match('('))
		{
			advance();
			if (match(')'))
			{
				advance();
				return 1;
			}
			else if (match('-') || match(ID) || match(NUMBER) || match(STRING) || match('('))
			{
				if (expr_list())
				{
					if (match(')'))
					{
						advance();
						return 1;
					}
					else
					{
						printf("ERROR:primary_expr\n");
						return 0;
					}
				}
				else
				{
					printf("ERROR:primary_expr\n");
					return 0;
				}
			
			}
			else
			{
				printf("ERROR:primary_expr\n");
				return 0;
			}
			
		}
		else if (match('['))
		{
			advance();
			if (match('-') || match(ID) || match(NUMBER) || match(STRING) || match('('))
			{
				if (expr())
				{
					if (match(']'))
					{
						advance();
						if (match('='))
						{
							advance();
							if (match('-') || match(ID) || match(NUMBER) || match(STRING) || match('('))
							{
								if (expr())
								{
									return 1;
								}
								else
								{
									printf("ERROR:primary_expr\n");
									return 0;
								}
							}
							else
							{
								printf("ERROR:primary_expr\n");
								return 0;
							}
						}
						else
						{
							return 1;
						}
					}
					else
					{
						printf("ERROR:primary_expr\n");
						return 0;
					}
				}
				else
				{
					printf("ERROR:primary_expr\n");
					return 0;
				}
			}
			else
			{
				printf("ERROR:primary_expr\n");
				return 0;
			}	
		}
		else if (match('='))
		{
			advance();
			if (match('-') || match(ID) || match(NUMBER) || match(STRING) || match('('))
			{
				if (expr())
				{
					return 1;
				}
				else
				{
					printf("ERROR:primary_expr\n");
					return 0;
				}
			}
			else
			{
				printf("ERROR:primary_expr\n");
				return 0;
			}
		}
		else if (match(ASSIGN))
		{
			advance();
			if (match('-') || match(ID) || match(NUMBER) || match(STRING) || match('('))
			{
				expr();
				return 1;
			}
			else
			{
				printf("ERROR:primary_expr\n");
				return 0;
			}
		}
		else
		{
			return 1;
		}
	
	}
	else if (match('('))
	{
	    advance();
		if (match('-') || match(ID) || match(NUMBER) || match(STRING) || match('('))
		{
			if (expr())
			{
				if (match(')'))
				{
					advance();
					return 1;
				}
				else
				{
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	else if (match(NUMBER))
	{
		advance();
		return 1;
	}
	else if (match(STRING))
	{
		advance();
		return 1;
	}
	else
	{
		printf("ERROR:primary_expr\n");
		return 0;
	}
}
int  expr_list()
{
	if (match('-') || match(ID) || match(NUMBER) || match(STRING) || match('('))
	{
		expr();
		while (match(','))
		{
			advance();
			if (match('-') || match(ID) || match(NUMBER) || match(STRING) || match('('))
			{
				expr_list();
			}
			else
			{
				printf("ERROR:Fail Match expr_list\n");
				return 0;
			}
		}
		return 1;
	}
	else
	{
		printf("ERROR:Fail Match expr_list\n");
		return 0;
	}
}
int  id_list()    //ok
{
	if (!match(ID))
	{
		printf("ERROR:Fail Match id_list\n");
		return 0;
	}
	else
	{
		advance();
		while (match(','))
		{
			advance();
			id_list();
		}
		return 1;
	}
}

int main(int argc, char **argv)
{
	
	setbuf(stdout, NULL);
	if(argc < 2 )
	{
		printf("input file is needed.\n");
		exit(0);
    }
    yyin = fopen(argv[1],"r");
	advance();
	program();
    printf("rdcheck succeed!\n");
	fclose(yyin);
	return 0;
}