#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "_parser.h"

void print_resp(response r) {
   printf("%d ",r.status);
	printf("%d ",r.func);
	printf("%d ",r.target);
	printf("%d ",r.arg1);
	printf("%d ",r.arg2);
	printf("%d ",r.arg_type);
   printf("\n");
}

//Substring function
void substring(char * str, char * substr, int start, int length) {
  if (start < 0 || (unsigned int)start >= strlen(str)) {
    substr[0] = '\0';
    return;
  }
  strncpy(substr, str + start, length);
  substr[length] = '\0';
  return;
}

//Valid Row (1 to 999)
int ValidRow(char str[]) {
   int length = strlen(str);
   if (length > 3 || length == 0) {
     return 0;
   }
   if (length > 1 && str[0] == '0') {
     return 0;
   }
   for (int i = 0; i < length; i++) {
     if (str[i] < 48 || str[i] > 57) { //0=48 9=57 
       return 0;
     }
   }
   return 1;
}

int ValidRow2(char str[]) {
	int length = strlen(str);
	if (length > 3 || length == 0) {
		return 0;
	}
	if (length > 1 && str[0] == '0') {
		return 0;
	}
	for (int i = 0; i < length; i++) {
		if (str[i] < 48 || str[i] > 57) { //0=48 9=57
			return 0;
		}
	}
	return atoi(str);
}

//Valid Row (A to ZZZ)
int ValidColumn(char str[]) {
	int length = strlen(str) ;
	if(length > 3 || length == 0) {
		return 0 ;
	}
	for( int i = 0 ; i < length ; i++) {
		if(str[i] < 65 || str[i] > 90 ) {   // A=65 Z=90
			return 0 ;
		}
	}
	return 1 ;
}

int ValidColumn2(char str[]) {
	int length = strlen(str) ;
	if(length > 3 || length == 0) {
		return 0 ;
	}
	int ans = 0 ;
	for( int i = 0 ; i < length ; i++) {
		if(str[i] < 65 || str[i] > 90 ) {   // A=65 Z=90
			return 0 ;
		}
		ans = 26*ans + str[i] - 'A'+1  ;

	}
	return ans ;
}

//Valid Integer
int ValidInteger(char str[]) {
	int length = strlen(str) ;
	if(length == 0) {
		return 0;
	}
	if(str[0] == '-' || str[0] == '+') {
		if(length == 1) {
			return 0;
		}
		if(length == 2 && str[1] == 48) {
			return 1;
		}
		else if(str[1] == 48) {
			return 0 ;
		}
		for(int i = 1; i < length; i++) {
			if( str[i] < 48 || str[i] > 57 ) {   //0=48 9=57
				return 0 ;
			}
		}
		return 1 ;
	} else {
		if(length == 1 && str[0] == 48) {
			return 1 ;
		}
		else if(str[0] == 48 ) {
			return 0 ;
		}

		for( int i = 0 ; i < length ; i++) {
			if( str[i] < 48 || str[i] > 57 ) {   //0=48 9=57
				return 0 ;
			}
		}
		return 1 ;
	}
}

//Valid cell representation returns args
int ValidCell(char str[], char* sub1, char* sub2) {
	int length = strlen(str) ;
	if( length < 2 || length > 6 ) {
		return 0 ;
	}
	int idx = 0 ;
	while( idx < length ) {
		if(str[idx] >= 48 && str[idx] <= 57) {
			break ;
		}
		idx++ ;
	}
	if( idx > 0 && idx < length ) {
		strncpy(sub2, str + idx, length-idx);
		strncpy(sub1, str + 0, idx);
		sub1[idx] = '\0';
		sub2[length-idx] = '\0';
		if( ValidColumn(sub1)*ValidRow(sub2)) {
			return 1 ;
		}
	}
	sub1[0] = '\0';
	sub2[0] = '\0';
	return 0 ;
}

//Valid cell representation check
int ValidCell2(char str[]) {
	int length = strlen(str) ;
	if(length < 2 || length > 6) {
		return 0 ;
	}
	int idx = 0 ;
	while(idx < length) {
		if(str[idx] >= 48 && str[idx] <= 57) {
			break ;
		}
		idx++ ;
	}
	if (idx > 0 && idx < length) {
		char sub1[4] ;
		char sub2[4] ;
		strncpy(sub2, str + idx, length-idx);
		strncpy(sub1, str + 0, idx);
		sub1[idx] = '\0';
		sub2[length-idx] = '\0';
		if(ValidColumn(sub1)*ValidRow(sub2)) {
			return 1 ;
		}
	}
	return 0 ;
}

int ValidCell3(char str[]) {
	int length = strlen(str) ;
	if( length < 2 || length > 6 ) {
		return 0 ;
	}
	int idx = 0 ;
	while( idx < length ) {
		if(str[idx] >= 48 && str[idx] <= 57) {
			break ;
		}
		idx++ ;
	}
	if( idx > 0 && idx < length ) {
		char sub1[4] ;
		char sub2[4] ;
		strncpy(sub2, str + idx, length-idx);
		strncpy(sub1, str + 0, idx);
		sub1[idx] = '\0';
		sub2[length-idx] = '\0';
		int col = ValidColumn2(sub1) ;
		int row = ValidRow2(sub2)    ;

		if( col > 0 && row > 0) {
			return 1000*col + row ;
		}
	}
	return 0;
}

//Valid function ie. MIN , MAX , AVG etc
int ValidFunction(char str[]) {
	if (strcmp(str, "MIN") == 0) {
		return 1;
	} else if (strcmp(str, "MAX")==0) {
		return 2;
	} else if (strcmp(str, "AVG")==0) {
		return 3;
	} else if (strcmp(str, "SUM")==0) {
		return 4;
	} else if (strcmp(str, "STDEV")==0) {
		return 5;
	} else if (strcmp(str, "SLEEP")==0) {
		return 6;
	}

	return 0 ;
}

//Valid Column comparision  ie. AA4 Z19 etc
int ValidComp(char r1[], char r2[], char s1[], char s2[]) {
	if(strlen(r1) > strlen(s1)) {
		return 0;
	} else if(strlen(r1) == strlen(s1)) {
		if (strcmp(s1,r1)>=0) {
			if(atoi(s2) >= atoi(r2)) {
				return 1;
			}
		}
	} else {
		if(atoi(s2) >= atoi(r2)) {
			return 1;
		}
	}
	return 0;
}

// Valid range
int ValidRange(char str[], char* EqualExpr, char* PostExpr) {
	int length = strlen(str) ;
	if( length > 4) {
		int idx = 0 ;
		while( idx < length ) {
			if(str[idx] == ':') {
				break ;
			}
			idx++ ;
		}
		if(idx == length) {
			return 0 ;
		}
		if(idx > 6 || idx == length || idx < 2) {
			return 0 ;
		}
		strncpy(EqualExpr, str + 0, idx);
		EqualExpr[idx] = '\0';
		char r1[7];
		char r2[7];
		int Bool1 = ValidCell(EqualExpr,r1,r2) ;
		if( Bool1 ) {
			length = length-idx-1 ;
			if(length > 0 && length < 7) {
				strncpy(PostExpr, str + idx+1,length);
				PostExpr[length] = '\0';
				char s1[7];
				char s2[7];
				int Bool2 = ValidCell(PostExpr,s1,s2);
				if(Bool2) {
					if(ValidComp(r1,r2,s1,s2)) {
						return 1 ;
					} else {
						return 2 ;
					}
				}
			}
		}
	}
	return 0 ;
}

//A map from arithmatic operations to their return values
int RetValues(char C) {
	if(C=='+') {
		return 3 ;
	} else if( C=='-') {
		return 4 ;
	} else if( C=='*') {
		return 5 ;
	} else if(C=='/') {
		return 6 ;
	}
	return 0 ;
}

//Valiid Post Expr for arithmatic Expre
int ValidPostExpr(char str[], char* EqualExpr, char* PostExpr) {
	int length = strlen(str) ;
	if( length > 2) {
		int idx = 0 ;
		if(str[0] == '-' || str[0] == '+') {
			idx = 1 ;
		}
		while( idx < length ) {
			if(str[idx] == '*' || str[idx] == '-' || str[idx] == '+' || str[idx] == '/' ) {
				break ;
			}
			idx++ ;
		}
		if(idx >= length-1|| idx < 1) {
			return 0 ;
		}
		strncpy(EqualExpr, str + 0, idx);
		EqualExpr[idx] = '\0';
		int A = ValidCell2(EqualExpr);
		int B = ValidInteger(EqualExpr) ;
		int sum = 0;
		if( A||B) {
			if(A) {
				sum += 2;
			}
			int postlength = length-idx-1 ;
			strncpy(PostExpr, str + idx+1,postlength);
			PostExpr[postlength] = '\0';
			int C = ValidCell2(PostExpr);
			int D = ValidInteger(PostExpr);
			if(C || D) {
				if(C) {
					sum += 1;
				}
				return 1+sum ;
			}
		}
	}
	return 0 ;
}

//Valiid Post Expr for function Expre
int ParseFunc(char str[],char EqualExpr[], char Exp1[],char Exp2[]) {
	int length = strlen(str) ;
	if (length < 4 || str[0] == '\0') {
		return 0;
	}
	int count = 0 ;
	// char Operator = '\0';
	while( count < length ) {
		if(str[count] == '('  ) {
			// Operator = str[count] ;
			break;
		}
		count++ ;
	}
	if(count == length || str[length - 1] != ')') {
		return 0;
	}
	if( length - count <= 2) {
		return 0;
	}
	char Function[count+1] ;
	strncpy(Function, str + 0, count);
	Function[count] = '\0';
	int func = ValidFunction(Function) ;
	if (!func) {
		return 0;
	}
	length = length-count-2 ;
	char Range[length+1] ;
	strncpy(Range, str + count+1,length);
	Range[length] = '\0';
	if( func == 6) {
		if(ValidInteger(Range)||ValidCell2(Range)) {
			int len1 = strlen(Function);
			strncpy(EqualExpr, str + 0, len1);
			EqualExpr[len1] = '\0';
			int len2 = strlen(Range);
			int k = strlen(EqualExpr) + 1  ;
			strncpy(Exp1, str + k,len2);
			Exp1[len2] = '\0';
			return func + 6 ;
		}
	} else {
		// char str1[7];
		// char str2[7];
		int ans = ValidRange(Range,Exp1,Exp2) ;
		if( ans ==  1) {
			int len1 = strlen(Function);
			strncpy(EqualExpr, str + 0, len1);
			EqualExpr[len1] = '\0';
			return func + 6;
		} else if(ans == 2) {
			return 1;
		}
	}

	return 0;
}


// Value: 
// ○ Constant. Example: 23, 41.   1 
// ○ Cell. Example: C1, Z22.   2 
// ● Arithmetic expressions:  
// ○ Value+Value 3
// ○ Value-Value 4
// ○ Value*Value 5
// ○ Value/Value 6
// ● Function: 

// ○ MIN(Range) 7
// ○ MAX(Range) 8
// ○ AVG(Range) 9
// ○ SUM(Range) 10
// ○ STDEV(Range) 11
// ○ SLEEP(Value) 12
// ● w for up 13,  
// ● d for right 14,  
// ● a for left 15,  
// ● s for down 16,  
// ● q: exit the program 17 ,
// disable_output 18
// enable_output 19
// scroll_to <CELL> 20


//Errors : 
//random user input not expected by the program  (unrecognized cmd)
 //(Invalid range) 

 //Argtype :
 //0 -- 00 (Value Oper Value)
 //1 -- 01 (Value Oper Cell)
 //2 -- 10 (Cell Oper Value)
 //3 -- 11 (Cell Oper Cell)

 //Status Codes
 //Totally(unrecognized cmd) 0
 //OK 1
 //Empty string 2 
 //Invalid Range 3


response parse(char str[]) {
	response Returns = {0};
	int length = strlen(str) ;
	if( length == 0 ) {
		Returns.status = 2;
		return Returns ;
	}
	if(length == 1) {
		if( str[0] == 'w') {
		   Returns.status = 0;
			Returns.func = 13;
			return Returns;
		} else if( str[0] == 'd' ) {
			Returns.status = 0;
			Returns.func = 14 ;
			return Returns ;
		} else if( str[0] == 'a' ) {
			Returns.status = 0;
			Returns.func = 15 ;
			return Returns ;
		} else if( str[0] == 's' ) {
			Returns.status = 0;
			Returns.func = 16 ;
			return Returns ;
		} else if( str[0] == 'q' ) {
			Returns.status = 0;
			Returns.func = 17 ;
			return Returns ;
		}
	}
	if( strcmp(str, "disable_output") == 0) {
		Returns.status = 0;
		Returns.func = 18 ;
		return Returns ;
	}
	if( strcmp(str, "enable_output") == 0 ) {
		Returns.status = 0;
		Returns.func = 19 ;
		return Returns ;
	}
	if( length > 10 ) {
		char scroll[11] ;
		strncpy(scroll, str + 0,10);
		scroll[10] = '\0';
		if(strcmp(scroll, "scroll_to ")==0) {
			char cell[length-10+1] ;
			strncpy(cell, str + 10,length-10);
			cell[length-10] = '\0';
			int ans  = ValidCell3(cell) ;
			if(ans) {
				Returns.status = 0;
				Returns.func = 20;
				Returns.target = ans;
				Returns.arg_type = 2;
				return Returns;
			}
		}
	}
	int idx = 0 ;
	while(idx < length) {
		if(str[idx] == '=' ) {
			break ;
		}
		idx++ ;
	}
	if(idx > 6 || idx == length || idx < 2) {
		Returns.status = 1;        // Error code
		return Returns;
	}
	char EqualExpr[idx+1] ;
	strncpy(EqualExpr, str + 0, idx);
	EqualExpr[idx] = '\0';
	int Dest01 = ValidCell3(EqualExpr) ;
	if( Dest01) {
		Returns.target = Dest01 ;
		length = length-idx-1 ;
		if(length > 0) {
			char PostExpr[length+1] ;
			strncpy(PostExpr, str + idx +1,length);
			PostExpr[length] = '\0';
			int count = 0 ;
			char Operator = '\0';
			if(PostExpr[0] == '-' || PostExpr[0] == '+' ) {
				count = 1 ;
			}
			while( count < length ) {
				if( PostExpr[count] == '*' || PostExpr[count] == '-' || PostExpr[count] == '+' || PostExpr[count] == '/' || PostExpr[count] == '(' ) {
					Operator = PostExpr[count] ;
					break ;
				}
				count++ ;
			}
			if( count == length) {
				if( ValidInteger(PostExpr)) {
					Returns.status = 0;
					Returns.func = 1;
					Returns.arg1 = atoi(PostExpr);
					Returns.arg_type = 0;
					return Returns;
				}
				int Arg01  =  ValidCell3(PostExpr ) ;
				if(Arg01) {
					Returns.status = 0;
					Returns.func = 2 ;
					Returns.arg1 =  Arg01 ;
					Returns.arg_type = 2 ;
					return Returns ;
				}
			} else if(Operator == '(') {
				char Ret1[20] ;
				char Ret2[20] ;
				char Ret3[20] ;
				int ret =   ParseFunc(PostExpr, Ret1, Ret2, Ret3);
				if(ret == 12 ) {
					Returns.status = 0;
					Returns.func = 12 ;
					if( ValidInteger(Ret2)) {     // What if not valid integer
						Returns.arg1 = atoi(Ret2) ;
						Returns.arg_type = 0 ;
					}
					int Arg01  =  ValidCell3(Ret2) ;
					if(Arg01) {
						Returns.arg1 =  Arg01 ;
						Returns.arg_type = 2 ;
					}
					return Returns ;
				} else if( ret > 6 && ret  < 12 ) {
					int Arg01 = ValidCell3(Ret2);
					int Arg02 = ValidCell3(Ret3);
					Returns.status = 0;
					Returns.func = ret ;
					Returns.arg1 =  Arg01 ;
					Returns.arg2 =  Arg02 ;
					Returns.arg_type = 3 ;
					return Returns ;
				} else if( ret == 1 ) {
					Returns.status = 1;        // Error code
					return Returns ;
				}

			}
			else {
				int ret = RetValues(Operator);
				char Ret2[20] ;
				char Ret3[20] ;
				int Argtp = ValidPostExpr(PostExpr,Ret2,Ret3) ;
				if( Argtp) {
					Argtp = Argtp - 1 ;
					int Arg01 = 0;
					int Arg02 = 0;
					if(Argtp == 0 || Argtp == 1) {
						Arg01 = atoi(Ret2);
					} else if( Argtp == 2 ||Argtp == 3 ) {
						Arg01 = ValidCell3(Ret2);
					}
					if(Argtp == 0 || Argtp == 2) {
						Arg02 = atoi(Ret3);
					} else if( Argtp == 1 ||Argtp == 3 ) {
						Arg02 = ValidCell3(Ret3);
					}
					Returns.status = 0;
					Returns.func = ret ;
					Returns.arg1 =  Arg01 ;
					Returns.arg2 =  Arg02 ;
					Returns.arg_type = Argtp ;
					return Returns ;
				}
			}
		}
	}
	Returns.status = 1;
	return Returns;
}

// int main() {
// 	char str[] = "ZZZ999=123+456";
// 	response Ret = parse(str);
// 	printf("%d ",Ret.status);
// 	printf("%d ",Ret.func);
// 	printf("%d ",Ret.target);
// 	printf("%d ",Ret.arg1);
// 	printf("%d ",Ret.arg2);
// 	printf("%d ",Ret.arg_type);

// 	return 0;
// }