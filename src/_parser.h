#ifndef PARSER_H_
#define PARSER_H_

typedef struct response {
   char status;
   char func;
   int  target;
   int  arg1;
   int  arg2;
   char arg_type;
} response;

void print_resp(response r);
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
response parse(char str[]);

#endif