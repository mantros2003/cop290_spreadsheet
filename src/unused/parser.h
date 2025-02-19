#ifndef PARSER_H_
#define PARSER_H_

typedef struct ParseReturn{
   char Status ;
   char Oper ;
   int  Dest ;
   int  Arg1 ;
   int  Arg2 ;
   char Argtype ;
}ParseReturn ;

void substring( char* str , char* substr, int start , int length);
int ValidRow(char str[]);
int ValidRow2(char str[]);
int ValidColumn(char str[]);
int ValidColumn2(char str[]);
int ValidInteger(char str[]);
int ValidCell(char str[] , char* sub1 , char* sub2);
int ValidCell2(char str[]);
int ValidCell3(char str[]);
int ValidFunction(char str[]);
int ValidComp(char r1[] , char r2[] , char s1[] , char s2[]);
int ValidRange(char str[] , char* EqualExpr , char* PostExpr);
int RetValues(char C);
int ValidPostExpr(char str[] , char* EqualExpr , char* PostExpr);
int ParseFunc(char str[] ,char EqualExpr[] , char Exp1[] ,char Exp2[]);
ParseReturn Parser(char str[]);

#endif
