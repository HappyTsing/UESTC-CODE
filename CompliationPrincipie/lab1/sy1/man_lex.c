#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>
#include <string.h> 
#include<stdbool.h>
int charClass;
#define MAX_LEN 1500
char lexeme[MAX_LEN];//now character token array
char nextChar;
char next2Char;
int lexLen;
int token;
int nextToken;
bool flag;      //true¡êofloat false:int
FILE *inFile;

#define LETTER 0  //letter
#define DIGIT 1   //digit
#define UNKNOWN 999  //unknown
#define DIAN 46	//'.'
#define XX 47  //  /
#define XH 42  //  *
#define XHX 95 // the ch is '_'
#define DOLLAR 36 // $
#define DYH 39 //'
#define SYH  34 //"

enum { INT=500, FLOAT,STRING, CHAR,ID, EQU, GEQU, LEQU, UNEQU, DLY,DLH,ERROR };   //DLY:&&  DLH:||
char* keywords[] = {
	"abstract","assert","boolean","break","byte","case",
	"catch","char","class","const","continue","default",
	"do","double","else","enum","extends","final","finally",
	"float","for","goto","if","implements","import",
	"instanceof","int","interface","long","native","new",
	"package","private","protected","public","return","strictfp",
	"short","static","super","switch","synchronized","this",
	"throw","throws","transient","try","void","volatile","while"
};

void addChar();
void getChar();
void getNonBlack();
void checkKeywords(char* pword);
int checkSymbol(char ch, char nextCh);
int lexer();

void addChar() {
	if (lexLen <= MAX_LEN) {
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = 0;
	}
	else {
		printf("ERROR: the lexeme is too long. \n");
	}
}
void getChar() { //to get "charclass"
	static int firstRun = 1;
	if (firstRun) {
		nextChar = getc(inFile);
		next2Char = getc(inFile);
		firstRun = 0;
	}
	else {
		nextChar = next2Char;
		next2Char = getc(inFile);
	}

	if (nextChar == EOF) {
		charClass = EOF;
	}
	else {
		if (isalpha(nextChar)) {
			charClass = LETTER;
		}
		else if (isdigit(nextChar)) {
			charClass = DIGIT;
		}
		else {
			charClass = UNKNOWN;
		}
	}
}
void getNonBlack() {
	while (isspace(nextChar)) {
		getChar();
	}
}

int checkSymbol(char ch, char nextCh) { //to get "nextToken"
	switch (ch) {
	case '?':
	case '-':
	case '+':
	case '(':
	case ')':
	case '{':
	case '}':
	case ':':
	case ';':
	case ',':
	case '[':
	case ']':
	case '@':
	case '%':
	case '^':
	case '\a':
	case '\b':
	case '\n':
	case '\f':
	case '\r':
	case '\v':
	case '\t':
	case '\0':
	//??
	case '#':             //#
	
	case 32:              //the ASC_number of " " is 32
		addChar();
		nextToken = ch;
		break;

	case '=':
		addChar();
		nextToken = ch;
		if (nextCh == '=') {
			getChar();
			addChar();
			nextToken = EQU;
		}
		break;
	case '>':
		addChar();
		nextToken = ch;
		if (nextCh == '=') {
			getChar();
			addChar();
			nextToken = GEQU;
		}
		break;
	case '<':
		addChar();
		nextToken = ch;
		if (nextCh == '=') {
			getChar();
			addChar();
			nextToken = LEQU;
		}
		break;
	case '!':
		addChar();
		nextToken = ch;
		if (nextCh == '=') {
			getChar();
			addChar();
			nextToken = UNEQU;
		}
		break;
	case'&':
		addChar();
		nextToken = ch;
		if (nextCh == '&') {
			getChar();
			addChar();
			nextToken = DLY;
		}
		break;
	case'|':
		addChar();
		nextToken = ch;
		if (nextCh == '|') {
			getChar();
			addChar();
			nextToken = DLH;
		}
		break;
	case 39:              //'
		addChar();
		nextToken = DYH; //'
		break;
	case '"':
		addChar();
		nextToken = SYH;  //"
		break;
	case '.':
		addChar();
		nextToken = DIAN;  //.
		break;
	case '/':
		addChar();
		nextToken = XX;    // /
		break;
	case '*':
		addChar();
		nextToken = XH;    // *
		break;
	case '_':
		addChar();
		nextToken = XHX;    // _
		break;
	case '$':
		addChar();
		nextToken = DOLLAR;  //$
		break;
	case EOF:
		addChar();
		nextToken = EOF;
		break;
	default:
		printf("ERROR:unknown character %c  \n", ch);
		nextToken = ERROR;
	}
	return nextToken;
}
void checkKeywords(char* pword) {
	int i = 0;
	while (keywords[i] != 0) {
		char* pkeywords = keywords[i];
		if (strcmp(pword, pkeywords) == 0) {
			nextToken = 1000 + i;
			return;
		}
		i++;
	}
}
//getChar() already,and get charclass
int lexer() {
	lexLen = 0;
	getNonBlack();
	flag = false;
	switch (charClass) {
	case LETTER:
		addChar();  //add nextchar
		getChar();  //geta new char
		while (charClass == LETTER || charClass == DIGIT) {
			addChar();
			getChar();
		}
		nextToken = ID;
		//check is or not keywords
		checkKeywords(lexeme);
		break;
	case DIGIT:
		addChar();
		getChar();
		if (charClass == UNKNOWN)
		{
			checkSymbol(nextChar, next2Char);
			lexeme[--lexLen] = '\0';
		}
		if (charClass == LETTER)
		{
			if ((nextChar == 'L' | nextChar == 'l') && flag == false)
			{
				addChar();
				getChar();
			}
			else if ((nextChar == 'F' | nextChar == 'f') && flag == true)
			{
				addChar();
				getChar();
			}
			else
				break;
		}
		while (charClass == DIGIT || nextToken == DIAN)
		{
			if (nextToken == DIAN)
				flag = true;
			addChar();
			getChar();
			if (charClass == UNKNOWN)
			{
				if (flag == true)         //There's already a decimal point, and the next sign exits the loop
					break;
				else
				{
					checkSymbol(nextChar, next2Char);
					lexeme[--lexLen] = '\0';    
					//Addchar will be called at the same time as the check, which will repeat. For example, output 1.. 3. Therefore, delete the result after add in check
				}
			
			}
			if (charClass == LETTER)
			{
				if ((nextChar == 'L' | nextChar == 'l') && flag == false)
				{
					addChar();
					getChar();
				}
				else if ((nextChar == 'F' | nextChar == 'f') && flag == true)
				{
					addChar();
					getChar();
				}
				else
					break;
			}
				
		}
		if (flag == false)
			nextToken = INT;
		else
		{
			flag = false; //reset to false after used
			nextToken = FLOAT; 
		}
		break;

	case UNKNOWN:
		checkSymbol(nextChar, next2Char);  //addchar will be down when you check
		if (nextToken == SYH)
		{
			getChar();
			if (charClass == UNKNOWN)
				checkSymbol(nextChar, next2Char);
			else
				addChar();
			while (charClass==DIGIT||charClass==LETTER|| (charClass==UNKNOWN&&nextToken != SYH))
			{
				getChar();
				if (charClass == UNKNOWN)
					checkSymbol(nextChar, next2Char);
				else
					addChar();
			}

			if (nextToken == SYH)
			{
				nextToken = STRING;
			}
			else
			{
				nextToken = ERROR;
			}

		}
		if (nextToken == DYH)  //'
		{
			//Gets the value between single quotes
			getChar();
			addChar();   
			getChar();
			checkSymbol(nextChar, next2Char);
			if (nextToken == DYH)
			{
				nextToken = CHAR;
			}
			else
			{
				nextToken = ERROR;
			}

		}
		//if it is /* */ or // or /** */ Comment, return directly, no output
		if (nextToken == XX)
		{
			getChar();
			if (charClass == UNKNOWN)
			{
				checkSymbol(nextChar, next2Char);
				if (nextToken == XX)
				{
					getChar();
					while (nextChar != '\n') {
						getChar();
					}
					return nextToken;
				}
				else if (nextToken == XH)
				{
					while (1)
					{
						getChar();
						if (charClass == UNKNOWN)
							checkSymbol(nextChar, next2Char);
						if (nextToken == XH)
						{
							getChar();
							if (charClass == UNKNOWN)
								checkSymbol(nextChar, next2Char);
							if (nextToken == XX)
							{
								getChar();
								return nextToken;
							}
							
						}

					}

				}

			}
			// If the input is 3/10, the output/needs to keep 1, so return directly, otherwise the following getchar will overwrite 1
			printf("<%6d,	%s	>\n", nextToken, lexeme);
			return nextToken;
		}
				
		
		//Now determine the id starting with _ or $
		//A single '$' can be used as the variable name id, but a single '_' cannot
		if (nextToken == XHX )
		{
			getChar();
			if (charClass == UNKNOWN)
			{
				checkSymbol(nextChar, next2Char);
				lexeme[--lexLen] = '\0';
			}		
			while (charClass == LETTER || charClass == DIGIT|| nextToken == XHX || nextToken == DOLLAR) {
				if (flag == false)   
                 //The first time you run the loop, note that '_'is followed by a character that can be used as id.
					flag = true;
				addChar();
				getChar();
				if (charClass == UNKNOWN)
				{
					checkSymbol(nextChar, next2Char);
					lexeme[--lexLen] = '\0';
				}

			}


			if (flag == true)
			{
				flag = false;   //set to false after using
				nextToken = ID;
			}
			printf("<%6d,	%s >\n", nextToken, lexeme);
			//The reason I'm printing and returning here is because I've already got a char and I'm not using it
			//And then at the bottom it's going to get a char again, so I'm going to repeat it, so I'm going to return it.
			return nextToken;

		} 
		else if (nextToken == DOLLAR) //The dollar sign '$' alone can also be 'id'
		{
			getChar();
			if (charClass == UNKNOWN)
			{
				checkSymbol(nextChar, next2Char);
				lexeme[--lexLen] = '\0';
			}

			while (charClass == LETTER || charClass == DIGIT || nextToken == XHX || nextToken == DOLLAR) {
				addChar();
				getChar();
				if (charClass == UNKNOWN)
				{
					checkSymbol(nextChar, next2Char);
					lexeme[--lexLen] = '\0';
				}

			}
			nextToken = ID;
			printf("<%6d,	%s	>\n", nextToken, lexeme);
			return nextToken;
		}
		getChar();
		break;
	case EOF:
		nextToken = EOF;
		lexeme[0] = 'E';
		lexeme[1] = 'O';
		lexeme[2] = 'F';
		lexeme[3] = 0;
		break;
	}

	printf("<%6d,	%s	>\n", nextToken, lexeme);
	return nextToken;
}

int main(int argc, char*argv[]) {
	if(argc<2){
		   printf("ERROR:input file name is needed.\n");
		   exit(0);
		}
	inFile = fopen(argv[1], "r");
	if (inFile == NULL) {
		printf("ERROR:can not open file.\n");
		exit(0);
	}
	getChar();
	while (nextToken != EOF) {
		lexer();
	}
	fclose(inFile);
	return 0;
}
