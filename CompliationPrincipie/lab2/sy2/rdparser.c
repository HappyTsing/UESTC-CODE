
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
typedef struct _ast ast;
typedef struct _ast* past;
struct _ast {
	int ivalue;       //保存整数信息
	char* svalue;     //保存字符串信息
	char* nodeType;   //结点类型
	past left;        //指向左子树
	past right;       //指向右子树
};

extern int yylex();
extern int yylval;
extern char* yytext;
extern FILE* yyin;
int tok;

void advance();
bool match(int);


past program();
past external_declaration();
past decl_or_stmt();
past declarator_list();
past intstr_list();
past initializer();
past declarator();
past parameter_list();
past parameter();
past type();
past statement();
past statement_list();
past expression_statement();
past expr();
past cmp_expr();
past add_expr();
past mul_expr();
past primary_expr();
past expr_list();
past id_list();

void advance()
{
	tok = yylex();
	printf("tokval: %s\n", yytext);
}
bool match(int terminal_symbol)
{
	if (tok == terminal_symbol)
		return true;
	else
		return false;
}

past newAstNode();
void showAst(past node, int nest);
past newList_nofinal(past);
past newList_final(past);
past setnull(past);


//创建一个空树结点
past newAstNode()
{
	past node = (past)malloc(sizeof(ast));
	if (node == NULL)
	{
		printf("run out of memory.\n");
		exit(0);
	}
	memset(node, 0, sizeof(ast));
	//memset()函数原型是extern void *memset(void *buffer, int c, int count)  
	//buffer：为指针或是数组
	//c：是赋给buffer的值
	//count：是buffer的长度.
	//这个函数在socket中多用于清空数组.如:原型是memset(buffer, 0, sizeof(buffer))
	return node;
}

//输出树
void showAst(past l,int j)												
{
	int a=1;
	if(l->nodeType)
	{
		int i = 0;
		a=0;
		for(i; i<j; i++)
		{
			printf(" ");
		}
		if(strcmp(l->nodeType, "intValue") == 0)
		{
			printf("%s  %d\n", l->nodeType, l->ivalue);
		}

	
	    else if(strcmp(l->nodeType, "strValue") == 0)
		{
			printf("%s  %s\n", l->nodeType, l->svalue);
		}
		
	
	    else if(strcmp(l->nodeType, "idValue") == 0)
		{
			printf("%s  %s\n", l->nodeType, l->svalue);
		}
		
	
		else if(strcmp(l->nodeType, "finalValue") == 0)
		{
			printf("%s  %d\n", l->nodeType, l->ivalue);	
		}
		else
		{
			printf("%s\n",l->nodeType);
		}

	
       
		
	}
	if(l->left)
	{
		showAst(l->left,j+1-a);
	}
	if(l->right)
	{
		showAst(l->right,j+1-a);
	}
		return ;
}

past setnull(past buf)//将叶子结点的后续指针赋空值 
{
	buf->left = NULL;
	buf->right = NULL;
	return buf;
}
past newList_nofinal(past l)
{
	l->right = newAstNode();
	l = l->right;
	return l;
}
past newList_final(past l)
{
	l->left = newAstNode();
	l->left->nodeType = (char*)malloc(20);
	strcpy(l->left->nodeType, yytext);
	if (match(NUMBER))
	{
		strcpy(l->left->nodeType, "intValue");
		l->left->ivalue = yylval;
	}
	if (match(STRING))
	{
	    strcpy(l->left->nodeType, "strValue");
		l->left->svalue = (char*)malloc(50);
		strcpy(l->left->svalue, yytext);
	}
	if(match(ID))
	{
		strcpy(l->left->nodeType, "idValue");
		l->left->svalue = (char*)malloc(50);
		strcpy(l->left->svalue, yytext);
	}
	if(match(CMP)||match(ASSIGN)||match('+')||match('-')||match('*')||match('/')||match('%')||match(';')||match(',')||match('{')||match('}')||match('(')||match(')')||match('[')||match(']')||match('='))
	{
		strcpy(l->left->nodeType, "finalValue");
		   l->left->ivalue = tok;
	}
	return newList_nofinal(l);
}


past program()
{
	past l = newAstNode();
	past buf = l;  
    //buf指向l所指向的，l始终指向第一个结点，操作则对buf进行
	l->nodeType = "program";
	while (!match(FEND))
	{
		buf->left = external_declaration();
		buf=newList_nofinal(buf);
	}
    buf = setnull(buf);
	return l;
}
past external_declaration()
{
	past l = newAstNode();
	past buf = l;
	buf->nodeType = "external_declaration";
	buf->left= type();
	buf = newList_nofinal(buf);
	buf->left = declarator();
	buf = newList_nofinal(buf);
	buf->left = decl_or_stmt();
	buf = newList_nofinal(buf);
	buf = setnull(buf);
	return l;
}

past decl_or_stmt()
{
	past l = newAstNode();
	past buf = l;
	buf->nodeType = "decl_or_stmt";
	if (match('{'))
	{
		buf = newList_final(buf);
		advance();
		if (match('}'))
		{
			buf = newList_final(buf);
			advance();
		}
		else
		{
			buf->left = statement_list();
			buf = newList_nofinal(buf);
			if (match('}'))
			{
				buf = newList_final(buf);
				advance();
			}
			else
			{
				printf(" ERROR:decl_or_stmt()");
			}
		}
	}
	else if (match(','))
	{
		buf = newList_final(buf);
		advance();

		buf->left =declarator_list();
		buf = newList_nofinal(buf);
		if (match(';'))
		{
			buf = newList_final(buf);
			advance();
		}
		else
		{
			printf(" ERROR:decl_or_stmt()");
		}
	}
	else if (match(';'))
	{
		buf = newList_final(buf);
		advance();
	}
	else
	{
		printf(" ERROR:decl_or_stmt()");
	}
	buf = setnull(buf);
	return l;
}
past declarator_list()
{
	past l = newAstNode();
	past buf = l;
	buf->nodeType = "declarator_list";
	buf->left = declarator();
	buf = newList_nofinal(buf);
	while (match(','))
	{
		buf = newList_final(buf);
		advance();
		buf->left = declarator_list();
		buf = newList_nofinal(buf);
	}
	buf = setnull(buf);
	return l;
}
past intstr_list()
{
	past l = newAstNode();
	past buf = l;
	buf->nodeType = "intstr_list";
	buf->left = initializer();
	buf = newList_nofinal(buf);
	while (match(','))
	{
		buf = newList_final(buf);
		advance();
		buf->left = intstr_list();
		buf = newList_nofinal(buf);
	}
	buf = setnull(buf);
	return l;
}
past initializer()
{
	past l = newAstNode();
	past buf = l;
	buf->nodeType = "initializer";
	if (!match(NUMBER)&&!match(STRING))
	{
		printf("Error:initializer():expect NUMBER or STRING\n");
	}
	buf = newList_final(buf);
	buf = setnull(buf);
	advance();
	return l;
}
past declarator()
{
	past l = newAstNode();
	past buf = l;
	buf->nodeType = "declarator";
	if (!match(ID))
	{
		printf("Error:declarator():expect ID\n");
	}
	buf = newList_final(buf);
	advance();
	if (match('='))
	{
		buf = newList_final(buf);
		advance();
		buf->left = expr();
		buf = newList_nofinal(buf);
	}
	else if (match('('))
	{
		buf = newList_final(buf);
		advance();
		if (match(')'))
		{
			buf = newList_final(buf);
			advance();
		}
		else
		{
			buf->left = parameter_list();
			buf = newList_nofinal(buf);
			if (!match(')'))
			{
				printf("Error:declarator():expect )\n");
			}
			buf = newList_final(buf);
			advance();
		}
	}
	else if (match('['))
	{
		buf = newList_final(buf);
		advance();
		if (match(']'))
		{
			buf = newList_final(buf);
			advance();
		}
		else
		{
			buf->left = expr();
			buf = newList_nofinal(buf);
			if (!match(']'))
			{
				printf("Error:declarator():expect ]\n");
			}
			buf = newList_final(buf);
			advance();
		}
		if (match('='))
		{
			buf = newList_final(buf);
			advance();
			if (!match('{'))
			{
				printf("Error:declarator():expect {\n");
			}
			buf = newList_final(buf);
			advance();
			buf->left = intstr_list();
			buf = newList_nofinal(buf);
			if (!match('}'))
			{
				printf("Error:declarator():expect }\n");
			}
			buf = newList_final(buf);
			advance();
		}
	}
	buf = setnull(buf);
	return l;
}
past parameter_list()
{
	past l = newAstNode();
	past buf = l;
	buf->nodeType = "parameter_list";
	buf->left = parameter();
	buf = newList_nofinal(buf);
	while (match(','))
	{
		buf = newList_final(buf);
		advance();
		buf->left = parameter_list();
		buf = newList_nofinal(buf);
	}
	buf = setnull(buf);
	return l;
}
past parameter()
{
	past l = newAstNode();
	past buf = l;
	buf->nodeType = "parameter";
	buf->left = type();
	buf = newList_nofinal(buf);
	if (!match(ID))
	{
		printf("Error:parameter():expect ID\n");
	}
	buf = newList_final(buf);
	advance();
	buf = setnull(buf);
	return l;
}
past type()
{
	past l = newAstNode();
	past buf = l;
	l->nodeType = "type";
	if (!match(INT)&& !match(STR)&&!match(VOID))
	{
		printf("Error:type():expect int or str or past\n");
	}
	buf = newList_final(buf);
	advance();
	buf = setnull(buf);
	return l;
}
past statement()
{
	past l = newAstNode();
	past buf = l;
	buf->nodeType = "statement";
	if (match(SCAN))
	{
		buf = newList_final(buf);
		advance();
		buf->left = id_list();
		buf = newList_nofinal(buf);
		if (!match(';'))
		{
			printf("Error,expect ;\n");
		}
		buf = newList_final(buf);
		advance();
	}
	else if (match(PRINT))
	{
		buf = newList_final(buf);
		advance();
		if (match(';'))
		{
			buf = newList_final(buf);
			advance();
		}
		else
		{
			buf->left = expr_list();
			buf = newList_nofinal(buf);
			if (!match(';'))
			{
				printf("Error,expect ;\n");
			}
			buf = newList_final(buf);
			advance();
		}
	}
	else if (match(RETURN))
	{
		buf = newList_final(buf);
		advance();
		if (match(';'))
		{
			buf = newList_final(buf);
			advance();
		}
		else
		{
			buf->left = expr();
			buf = newList_nofinal(buf);
			if (!match(';'))
			{
				printf("Error,expect ;\n");
			}
			buf = newList_final(buf);
			advance();
		}
	}
	else if (match(WHILE))
	{
		buf = newList_final(buf);
		advance();
		if (!match('('))
		{
			printf("Error,expect (\n");
		}
		buf = newList_final(buf);
		advance();
		buf->left = expr();
		buf = newList_nofinal(buf);
		if (!match(')'))
		{
			printf("Error,expect )\n");
		}
		buf = newList_final(buf);
		advance();
		buf->left = statement();
		buf = newList_nofinal(buf);
	}
	else if (match(IF))
	{
		buf = newList_final(buf);
		advance();
		if (!match('('))
		{
			printf("Error,expect (\n");
		}
		buf = newList_final(buf);
		advance();
		buf->left = expr();
		buf = newList_nofinal(buf);
		if (!match(')'))
		{
			printf("Error,expect )");
		}
		buf = newList_final(buf);
		advance();
		buf->left = statement();
		buf = newList_nofinal(buf);
		if (match(ELSE))
		{
			buf = newList_final(buf);
			advance();
			buf->left = statement();
			buf = newList_nofinal(buf);
		}
	}
	else if (match('{'))
	{
		buf = newList_final(buf);
		advance();
		buf->left = statement_list();
		buf = newList_nofinal(buf);
		if (!match('}'))
		{
			printf("Error,expect }\n");
		}
		buf = newList_final(buf);
		advance();
	}
	else if (match(VOID)||match(STR)||match(INT))
    {
        buf = newList_final(buf);
		advance();
		buf->left = declarator_list();
		buf = newList_nofinal(buf);
		if (!match(';'))
		{
			printf("Error,expect ;\n");
		}
		buf = newList_final(buf);
		advance();
	}
	else if(match(';') || match('-') || match(ID) || match(NUMBER) || match(STRING))
	{
		buf->left = expression_statement();
		buf = newList_nofinal(buf);
	}
	buf = setnull(buf);
	return l;
}
past statement_list()
{
	past l = newAstNode();
	past buf = l;
	buf->nodeType = "statement_list";
	while(match(SCAN) || match(PRINT) || match(WHILE) || match(RETURN) || match(IF) || match('{') || match(VOID) || match(STR) || match(INT) || match(';') || match('(') || match(ID) || match(STRING) || match(NUMBER) || match('-'))
	{
		buf->left = statement();
		buf = newList_nofinal(buf);
	}
	buf = setnull(buf);
	return l;
}
past expression_statement()
{
	past l = newAstNode();
	past buf = l;
	buf->nodeType = "expression_statement";
	if (match(';'))
	{
		buf = newList_final(buf);
		advance();
	}
	else
	{
		buf->left = expr();
		buf = newList_nofinal(buf);
		if (!match(';'))
		{
			printf("Error,expect ;\n");
		}
		buf = newList_final(buf);
		advance();
	}
	buf = setnull(buf);
	return l;
}
past expr()
{
	past l = newAstNode();
	past buf = l;
	buf->nodeType = "expr";
	buf->left = cmp_expr();
	buf = newList_nofinal(buf);
	buf = setnull(buf);
	return l;
}
past cmp_expr()
{
	past l = newAstNode();
	past buf = l;
	buf->nodeType = "cmp_expr";
	buf->left = add_expr();
	buf = newList_nofinal(buf);
	while (match(CMP))
	{
		buf = newList_final(buf);
		advance();
		buf->left = cmp_expr();
		buf = newList_nofinal(buf);
	}
	buf = setnull(buf);
	return l;
}
past add_expr()
{
	past l = newAstNode();
	past buf = l;
	buf->nodeType = "add_expr";
	buf->left = mul_expr();
	buf = newList_nofinal(buf);
	while (match('+')||match('-'))
	{
		buf = newList_final(buf);
		advance();
		buf->left = add_expr();
		buf = newList_nofinal(buf);
	}
	buf = setnull(buf);
	return l;
}
past mul_expr()
{
	past l = newAstNode();
	past buf = l;
	buf->nodeType = "mul_expr";
	if (match('-'))
	{
		buf = newList_final(buf);
		advance();
		buf->left = mul_expr();
		buf = newList_nofinal(buf);
	}
    else
	{
		buf->left = primary_expr();
		buf = newList_nofinal(buf);
		while (match('*')|| match('/') || match('%')) 
		{
			buf = newList_final(buf);
			advance();
			buf->left = mul_expr();
			buf = newList_nofinal(buf);
		}
	}
	buf = setnull(buf);
	return l;
}
past primary_expr()
{
	past l = newAstNode();
	past buf = l;
	buf->nodeType = "primary_expr";
	if (match(ID))
	{
		buf = newList_final(buf);
	    advance();
		if (match('['))
		{
			buf = newList_final(buf);
			advance();
			buf->left = expr();
			buf = newList_nofinal(buf);
			if (!match(']'))
			{
				printf("Error,expect ]\n");
			}
			buf = newList_final(buf);
			advance();
			if (match('='))
			{
				buf = newList_final(buf);
				advance();
				buf->left = expr();
				buf = newList_nofinal(buf);
			}
		}
		else if (match('='))
		{
			buf = newList_final(buf);
			advance();
			buf->left = expr();
			buf = newList_nofinal(buf);
		}
		else if (match('('))
		{
			buf = newList_final(buf);
			advance();
			if (match(')'))
			{
				buf = newList_final(buf);
				advance();
			}
			else
			{
				buf->left = expr_list();
				buf = newList_nofinal(buf);
				if (!match(')'))
				{
					printf("Error,expect )\n");
				}
				buf = newList_final(buf);
				advance();
			}
		}
		else if (match(ASSIGN))
		{
			buf = newList_final(buf);
			advance();
			buf->left = expr();
			buf = newList_nofinal(buf);
		}
	}
	else if (match('('))
	{
		buf = newList_final(buf);
		advance();
		buf->left = expr();
		buf = newList_nofinal(buf);
		if (!match(')'))
		{
			printf("Error,expect )\n");
		}
		buf = newList_final(buf);
		advance();
	}
	else
	{
		if (!match(NUMBER)&&!match(STRING))
		{
			printf("Error,expect  NUMBER or STRING \n");
		}
		buf = newList_final(buf);
		advance();
	}
	buf = setnull(buf);
	return l;
}
past expr_list()
{
	past l = newAstNode();
	past buf = l;
	buf->nodeType = "expr_list";
	buf->left = expr();
	buf = newList_nofinal(buf);
	while (match(','))
	{
		buf = newList_final(buf);
		advance();
		buf->left = expr_list();
		buf = newList_nofinal(buf);
	}
	buf = setnull(buf);
	return l;
}
past id_list()
{
	past l = newAstNode();
	past buf = l;
	buf->nodeType = "id_list";
	if (!match(ID))
	{
		printf("Error,expect ID\n");
	}
	buf = newList_final(buf);
	advance();
	while(match(','))
	{
		buf = newList_final(buf);
		advance();
		buf->left = id_list();
		buf = newList_nofinal(buf);
	}
	buf = setnull(buf);
	return l;
}

int main(int argc, char*argv[])
{


	setbuf(stdout, NULL);
	if(argc < 2 )
	{
		printf("input file is needed.\n");
		exit(0);
    }
    yyin = fopen(argv[1],"r");
	advance();
	past program_tree=program();
	showAst(program_tree, 0);
	printf("rdparser succeed!\n");
	fclose(yyin);
	return 0;
}

