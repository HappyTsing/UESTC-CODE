#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum type{ID = 258 ,NUMBER, STRING, CMP, };                                       	
                                                                                                                           
extern FILE * yyin;                                                             	
extern int advance();                                                                	
extern char* yytext;                                                            	                                    
extern int Tok;                                                                		                                         
                                                                                
typedef struct _ast ast;                                                        
typedef struct _ast *past;
struct _ast															 
{
	char* ivalue;														
	char* nodeType;													 
	past left;														
	past right;														

void showAst(past l,int j);												
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
past newAstNode();														
past newList_final(past buf);													
past newList_nofinal(past buf);													
past setnull(past buf);													 
past l;


void showAst(past l,int j)												
{
	int a = 1;
	if(l->nodeType)
	{
		a = 0;
		int i = 0;
		for(i; i<j; i++)
		{
			printf("  ");
		}
		if(l->ivalue && strcmp(l->ivalue,"int") == 0)									
		{
			printf("%s\t%s\n",l->ivalue,l->nodeType);
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
past program()
{
	past l = newAstNode();
	past buf = l;
	l->nodeType = "program";												 
	advance(); 															
	while(Tok != 0)
	{
		buf->left = external_declaration();
		buf = newList_nofinal(buf);
	}
	buf = setnull(buf);
	return l;
}
past external_declaration()
{
	past l = newAstNode();
	past buf = l;
	l->nodeType = "external_declaration";
	buf->left = type();
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
	buf->nodeType="decl_or_stmt";
	if(strcmp(yytext,"{") == 0)//如果当前字符串成功匹配期望的终结符，则生成叶子节点 
	{
		buf = newList_final(buf);												 
		advance();
		if(strcmp(yytext,"}") == 0)
		{
			buf = newList_final(buf);
			advance();
		}
		else
		{
			buf->left=statement_list();
			buf = newList_nofinal(buf);
			if(strcmp(yytext,"}") != 0)
			{
				printf("error,expect }\n");
			}
			buf = newList_final(buf);
			advance();
		}
	}
	else if(strcmp(yytext,",") == 0)
	{
		buf = newList_final(buf);
		advance();
		buf->left=declarator_list();
		buf = newList_nofinal(buf);
		if(strcmp(yytext,";") != 0)
		{
			printf("error,expect ;\n");
		}
		buf = newList_final(buf);
		advance();
	}
	else
	{
		if(strcmp(yytext,";") != 0)
		{
			printf("error,expect ;\n");
		}
		buf = newList_final(buf);
		advance();
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
	while(strcmp(yytext,",") == 0)
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
	while(strcmp(yytext,",") == 0)
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
	if(Tok != NUMBER && Tok != STRING)
	{
		printf("error,expect NUMBER or STRING\n");
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
	if(Tok != ID)
	{
		printf("error,expect ID\n");
	}
 	buf = newList_final(buf);
 	advance();
	if(strcmp(yytext,"=") == 0)
	{
		buf = newList_final(buf);
		advance();
		buf->left = expr();
		buf = newList_nofinal(buf);
	}
	else if(strcmp(yytext,"(") == 0)
	{
		buf = newList_final(buf);
		advance();
		if(strcmp(yytext,")") == 0)
		{
			buf = newList_final(buf);		
			advance();
		}
		else
		{
			buf->left = parameter_list();
			buf = newList_nofinal(buf);
			if(strcmp(yytext,")") != 0)
			{
				printf("error,expect )\n");
			}
			buf = newList_final(buf);		
			advance();
		}
	}
	else if(strcmp(yytext,"[") == 0)
	{
		buf = newList_final(buf);				
		advance();
		if(strcmp(yytext,"]") == 0)
		{
			buf = newList_final(buf);
			advance();
		}
		else
		{
			buf->left = expr();
			buf = newList_nofinal(buf);
			if(strcmp(yytext,"]") != 0)
			{
				printf("error,expect ]\n");
			}
			buf = newList_final(buf);
			advance();
		}
		if(strcmp(yytext,"=") == 0)
		{
			buf = newList_final(buf);		
			advance();
			if(strcmp(yytext,"{") != 0)
			{
				printf("error,expect {\n");
			}
			buf = newList_final(buf);		
			advance();
			buf->left = intstr_list();
			buf = newList_nofinal(buf);
			if(strcmp(yytext,"}") != 0)
			{
				printf("error,expect }\n");
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
	while(strcmp(yytext,",") == 0)
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
	if(Tok != ID)
	{
		printf("error,expect ID\n");
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
	if(strcmp(yytext,"int") != 0 && strcmp(yytext,"str") != 0 && strcmp(yytext,"past") && 0)
	{
		printf("error,expect int or str or past\n");
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
	if(strcmp(yytext,"scan") == 0)
	{
		buf = newList_final(buf);
		advance();
		buf->left = id_list();
		buf = newList_nofinal(buf);
		if(strcmp(yytext,";") != 0)
		{
			printf("error,expect ;\n");
		}
		buf = newList_final(buf);
		advance();
	}
	else if(strcmp(yytext,"print") == 0)
	{
		buf = newList_final(buf);
		advance();
		if(strcmp(yytext,";") == 0)
		{
			buf = newList_final(buf);
			advance();
		}
		else
		{
			buf->left = expr_list();
			buf = newList_nofinal(buf);
			if(strcmp(yytext,";") != 0)
			{
				printf("error,expect ;\n");
			}
			buf = newList_final(buf);
			advance();
		}
	}
	else if(strcmp(yytext,"return") == 0)
	{
		buf = newList_final(buf);
		advance();
		if(strcmp(yytext,";") == 0)
		{
			buf = newList_final(buf);
			advance();
		}
		else
		{
			buf->left = expr();
			buf = newList_nofinal(buf);
			if(strcmp(yytext,";") != 0)
			{
				printf("error,expect ;\n");
			}
			buf = newList_final(buf);
			advance();
		}
	}
	else if(strcmp(yytext,"while") == 0)
	{
		buf = newList_final(buf);
		advance();
		if(strcmp(yytext,"(") != 0)
		{
			printf("error,expect (\n");
		}
		buf = newList_final(buf);
		advance();
		buf->left = expr();
		buf = newList_nofinal(buf);
		if(strcmp(yytext,")") != 0)
		{
			printf("error,expect )\n");
		}
		buf = newList_final(buf);
		advance();
		buf->left = statement();
		buf = newList_nofinal(buf);
	}
	else if(strcmp(yytext,"if") == 0)
	{
		buf = newList_final(buf);
		advance();
		if(strcmp(yytext,"(") != 0)
		{
			printf("error,expect (\n");
		}
		buf = newList_final(buf);
		advance();
		buf->left = expr();
		buf = newList_nofinal(buf);
		if(strcmp(yytext,")") != 0)
		{
			printf("error,expect )");
		}
		buf = newList_final(buf);
		advance();
		buf->left = statement();
		buf = newList_nofinal(buf);
		if(strcmp(yytext,"else") == 0)
		{
			buf = newList_final(buf);
			advance();
			buf->left = statement();
			buf = newList_nofinal(buf);
		}
	}
	else if(strcmp(yytext,"{") == 0)
	{
		buf = newList_final(buf);
		advance();
		buf->left = statement_list();
		buf = newList_nofinal(buf);
		if(strcmp(yytext,"}") != 0)
		{
			printf("error,expect }\n");
		}
		buf = newList_final(buf);
		advance();
	}
	else if(strcmp(yytext,"int") == 0 || strcmp(yytext,"str") == 0 || strcmp(yytext,"past") == 0)
	{
		buf = newList_final(buf);
		advance();
		buf->left = declarator_list();
		buf = newList_nofinal(buf);
		if(strcmp(yytext,";") != 0)
		{
			printf("error,expect ;\n");
		}
		buf = newList_final(buf);
		advance();
	}	
	else    
	{       
		buf->left = expression_statement();
		buf = newList_final(buf);
	}
	buf = setnull(buf);
	return l;  
}        
past statement_list()
{  
	past l = newAstNode();
	past buf = l;      
	buf->nodeType = "statement_list";
	while(Tok != 0)
	{
		buf->left = statement();
		buf = newList_nofinal(buf);
		if(strcmp(yytext,"}") == 0)
		{
			break;
		}
	}
	buf = setnull(buf);
	return l;
}  
past expression_statement()
{
	past l = newAstNode();
	past buf = l;
	buf->nodeType = "expression_statement";
	if(strcmp(yytext,";") == 0)
	{
		buf = newList_final(buf);
		advance();                         
	}                              
	else                           
	{    
		buf->left = expr(); 
		buf = newList_nofinal(buf);                  
		if(strcmp(yytext,";") != 0)   
		{                             
			printf("error,expect ;\n");  
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
	while(Tok == CMP)
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
	while(strcmp(yytext,"+") == 0 || strcmp(yytext,"-") == 0)
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
	if(strcmp(yytext,"-") == 0)
	{
		buf = newList_final(buf);
		advance();
	}
	else
	{
		buf->left = primary_expr();
		buf = newList_nofinal(buf);
		while(strcmp(yytext,"*") == 0 || strcmp(yytext,"/") == 0 || strcmp(yytext,"%") == 0)
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
	if(Tok == ID)
	{
		buf = newList_final(buf);
		advance();
		if(strcmp(yytext,"[") == 0)
		{
			buf = newList_final(buf);
			advance();
			buf->left = expr();
			buf = newList_nofinal(buf);
			if(strcmp(yytext,"]") != 0)
			{
				printf("error,expect ]\n");
			}
			buf = newList_final(buf);
			advance();
			if(strcmp(yytext,"=") == 0)
			{
				buf = newList_final(buf);
				advance();
				buf->left = expr();
				buf = newList_nofinal(buf);
			}
		}
		else if(strcmp(yytext,"=") == 0)
		{
			buf = newList_final(buf);
			advance();
			buf->left = expr();
			buf = newList_nofinal(buf);
		}
		else if(strcmp(yytext,"(") == 0)
		{
			buf = newList_final(buf);
			advance();
			if(strcmp(yytext,")") == 0)
			{
				buf = newList_final(buf);
				advance();
			}
			else 
			{
				buf->left = expr_list();
				buf = newList_nofinal(buf);
				if(strcmp(yytext,")") != 0)
				{
					printf("error,expect )\n");
				}
				buf = newList_final(buf);
				advance();
			}
		}
		else if(Tok == (int)'-')
		{
			buf = newList_final(buf);
			advance();
			buf->left = expr();
			buf = newList_nofinal(buf);
		}
	}
	else if(strcmp(yytext,"(") == 0)
	{
		buf = newList_final(buf);
		advance();
		buf->left = expr();
		buf = newList_nofinal(buf);
		if(strcmp(yytext,"(") != 0)
		{
			printf("error,expect (\n");
		}
		buf = newList_final(buf);
		advance();
	}
	else
	{
		if(Tok != NUMBER && Tok != STRING)
		{
			printf("error,expect return l; NUMBER or STRING or ( or ID\n");
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
	while(strcmp(yytext,",") == 0)
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
	if(Tok != ID)
	{
		printf("error,expect ID\n");
	}
	buf = newList_final(buf);
	advance();
	while(strcmp(yytext,",") == 0)
	{
		buf = newList_final(buf);
		advance();
		buf->left = id_list();
		buf = newList_nofinal(buf);
	}
	buf = setnull(buf);
	return l;
}

past newAstNode()														//生成新的节点 
{
	past new;
	new = (past)malloc(sizeof(ast));
	if(new == NULL)
	{
		printf("error!");
		exit(0);
	}
	new->ivalue = 0;
	new->nodeType = NULL;
	new->ivalue = NULL;
	return new;
}
past newList_final(past buf)													//匹配终结符成功后，生成一个新的叶子节点 
{
	buf->left = newAstNode();
	buf->left->nodeType = (char*)malloc(10);
	strcpy(buf->left->nodeType,yytext);
	if(Tok == 260)
	{
		buf->left->ivalue = (char*)malloc(4);
		buf->left->ivalue = "int";
	}
	buf->left->left = NULL;
	buf->left->right = NULL;
	buf->right = newAstNode();
	buf = buf->right;
	
	return buf;
}
past newList_nofinal(past buf)//调用非终结符的文法匹配函数后，生成新的非叶子节点 
{
	buf->right = newAstNode();
	buf = buf->right;
	return buf;
}
past setnull(past buf)//将叶子结点的后续指针赋空值 
{
	buf->left = NULL;
	buf->right = NULL;
	return buf;
}
int main(int argc, char *argv[]) {
	l = newAstNode();
	l = program();
	showAst(l, 0);
	return 0;
}
