#include<stdio.h>
#include<stdlib.h>
#include <string.h>

void substring( char* str , char* substr, int start , int length){
   if (start < 0 || start >= strlen(str)) {
        substr[0] = '\0'; 
        return;
   }
   strncpy(substr, str + start, length);
   substr[length] = '\0';
   return ;
}

int stringbreak( char* str , char* substr1 ,  char* substr2 , int idx ){
    int length = strlen(str) ; 
       if (idx < 0 || idx >= length) {
        substr1[0] = '\0'; 
        substr2[0] = '\0'; 
        return 0;
       } 
       strncpy(substr1, str + 0, idx+1);
       strncpy(substr2, str + idx+1, length-idx-1);
       substr1[idx+1] = '\0';
       substr2[length-idx-1] = '\0';
       return 1;
}


int ValidNaturalNumber(char str[]){
     int length = strlen(str) ; 
     if(str[0] == 48 || length > 3 || length == 0){
      return 0 ;
     }
     for( int i = 0 ; i < length ; i++){   
          if( str[i] < 48 || str[i] > 57 ){    //0=48 9=57 
                  return 0 ;
          }
     }
     return 1 ;
}

int ValidWholeNumber(char str[]){
     int length = strlen(str) ; 
     if(length == 1 && str[0] == 48){
      return 1 ;
     }
     else if(str[0] == 48 ||  length == 0){
      return 0 ;
     }
    
     for( int i = 0 ; i < length ; i++){   
          if( str[i] < 48 || str[i] > 57 ){    //0=48 9=57 
                  return 0 ;
          }
     }
     return 1 ;
}


int ValidCapString(char str[]){
    int length = strlen(str) ; 
    if(length > 3 || length == 0){
      return 0 ;
    }
    for( int i = 0 ; i < length ; i++){   
          if( str[i] < 65 || str[i] > 90 ){    // A=65 Z=90
                  return 0 ;
          }
    }
    return 1 ;
}

int ValidCell(char str[] , char* sub1 , char* sub2){
   int length = strlen(str) ; 
   if( length < 2 || length > 6 ){
      return 0 ;
   }
    
   int idx = 0 ;
   while( idx < length ){
       if(str[idx] >= 48 && str[idx] <= 57){
          break ;
       }
       idx++ ;
   }
  
   if( idx > 0 && idx < length ){
     
       
       
       strncpy(sub2, str + idx, length-idx+1);
       strncpy(sub1, str + 0, idx);
         
       sub1[idx] = '\0';
       sub2[length-idx] = '\0';
 
        if( ValidCapString(sub1)*ValidNaturalNumber(sub2)){
              return 1 ;
        }
   }
   sub1 = "";
   sub2 = "";
   return 0 ;    

}


int ValidCell2(char str[]){
   int length = strlen(str) ; 
   if( length < 2 || length > 6 ){
      return 0 ;
   }
    
   int idx = 0 ;
   while( idx < length ){
       if(str[idx] >= 48 && str[idx] <= 57){
          break ;
       }
       idx++ ;
   }
  
   if( idx > 0 && idx < length ){
     
    
        char sub1[4] ;
        char sub2[4] ;
       strncpy(sub2, str + idx, length-idx+1);
       strncpy(sub1, str + 0, idx);
         
       sub1[idx] = '\0';
       sub2[length-idx] = '\0';
   
        if( ValidCapString(sub1)*ValidNaturalNumber(sub2)){
              return 1 ;
        }
   }
  
   return 0 ;    

}

int ValidFunction(char str[]  ){
  
   if(  strcmp(str, "MIN") == 0){
     return 1 ;
   }else if( strcmp(str,  "MAX")==0){
    return 2 ;
   }else if( strcmp(str,  "AVG")==0){
       return 3 ; 
   }else if( strcmp(str,  "SUM")==0){
       return 4 ;
   }else if( strcmp(str, "STDEV")==0){
       return 5 ;
   }else if( strcmp(str,  "SLEEP")==0){
     
       return 6 ;
   }
   return 0 ;
}

int ValidComp(char r1[] , char r2[] , char s1[] , char s2[]){
     if(strlen(r1) > strlen(s1)){
          return 0 ;
     }else if(strlen(r1) == strlen(s1)){
          if (strcmp(s1,r1)+1){
              if(atoi(s2) >= atoi(r2)){
                  return 1;
              }
          }
     }else{
          if(atoi(s2) >= atoi(r2)){
                  return 1;
              } 
     }
     return 0 ;

}
int ValidRange(char str[] , char* EqualExpr , char* PostExpr){
    int length = strlen(str) ;
    if( length > 4){
         int idx = 0 ;
         while( idx < length ){
            if(str[idx] == ':'){
               break ;
            }
            idx++ ;
         }
         if(idx == length){
            return 0 ;
         }
         if(idx > 6 || idx == length || idx < 2){
               return 0 ;
            }
         // char EqualExpr[idx+1] ;     
         strncpy(EqualExpr, str + 0, idx);
         EqualExpr[idx] = '\0';    
         char r1[7];
         char r2[7]; 
         int Bool1 = ValidCell(EqualExpr,r1,r2) ;
         if( Bool1 ){

               length = length-idx-1 ;           
               if(length > 0 && length < 7){
                  // char PostExpr[length+1] ;
                  strncpy(PostExpr, str + idx+1,length);
                  PostExpr[length] = '\0';
                   char s1[7];
                   char s2[7];
                  int A = ValidCell(PostExpr,s1,s2);
                  
                  if(A ){
                     if(ValidComp(r1,r2,s1,s2)){
                     return 1 ;
                     }
                  }
               }
    }
   
}
 return 0 ;
}

int ValidPostExpr(char str[] , char* EqualExpr , char* PostExpr){
   
    int length = strlen(str) ;
   //   printf("%d",length )  ; 
    if( length > 2){
       
         int idx = 0 ;
         while( idx < length ){
            if(str[idx] == '*' || str[idx] == '-' || str[idx] == '+' || str[idx] == '/' ){
               break ;
            }
            idx++ ;
         }
         if(idx == length|| idx < 1){
            return 0 ;
         }
      
         // char EqualExpr[idx+1] ; 
       
         strncpy(EqualExpr, str + 0, idx);
         EqualExpr[idx] = '\0';    
            
         if( ValidCell2(EqualExpr)||ValidWholeNumber(EqualExpr)){

               length = length-idx-1 ;           
               if(length > 0 ){
                  // char PostExpr[length+1] ;
                  strncpy(PostExpr, str + idx+1,length);
                  PostExpr[length] = '\0';
                  int A = ValidCell2(PostExpr);
                  
                  if(A || ValidWholeNumber(PostExpr)){
                    
                     return 1 ;
                  }
               }
    }
   
}
 return 0 ;
}

int RetValues(char C){
    if(C=='+'){
      return 3 ;
    }else if( C=='-'){
       return 4 ;
    }else if( C=='*'){
       return 5 ;
    }else if(C=='/'){
       return 6 ;
    }
    return 0 ;
}

int ParseFunc(char str[] ,char EqualExpr[] , char Exp1[] ,char Exp2[]){
        
        int length = strlen(str) ;
                  
                  int count = 0 ;
                  char Operator ;
                  
                  while( count < length ){
                     if(str[count] == '('  ){
                        Operator = str[count] ;
                        break ;
                     }
                     count++ ;
                  }
                 if(count == length){
                    return 0 ;
                 } 
                
                  // printf("%d", count) ;

                 if( str[count] == '(' ){
                         
                        if( str[length-1] == ')' && length - count > 2){
                              
                              char Function[count+1] ;
                            
                              strncpy(Function, str + 0, count);
                              Function[count] = '\0';
                              
                              int func = ValidFunction(Function) ;
                              
                              if(func){
                                 
                                    length = length-count-2 ;
                                    char Range[length+1] ;
                                    strncpy(Range, str + count+1,length);
                                    Range[length] = '\0'; 

                                    if( func == 6){
                                         if(ValidWholeNumber(Range)||ValidCell2(Range)){
                                          //   Eq = EqualExpr;
                                             int len1 = strlen(Function);

                                             strncpy(EqualExpr, str + 0, len1);
                                             EqualExpr[len1] = '\0';    
       
                                             int len2 = strlen(Range);
                                            
                                             int k = strlen(EqualExpr) + 1  ; 
                                           
                                             strncpy(Exp1, str + k,len2);
                                              Exp1[len2] = '\0';
                                              
                                            return func + 6 ;
                                         } 

                                    }else{
                                        
                                         char str1[7];
                                         char str2[7];
                                       //   printf("%s\n" ,Range);
                                        if( ValidRange(Range,Exp1,Exp2)){
                                             // Eq = EqualExpr;
                                            

                                             int len1 = strlen(Function);

                                             strncpy(EqualExpr, str + 0, len1);
                                             EqualExpr[len1] = '\0'; 
                                            return func + 6;
                                        }
                                    }
                              }

                        }
                          
                       return 0 ;  

                  }
  

 

}
// Value: 
// ○ Constant. Example: 23, 41. 1
// ○ Cell. Example: C1, Z22.  2
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

int Parser(char str[] , char*  EqualExpr , char* Exp1 , char* Exp2 ,char* Exp3 ){
    
    int length = strlen(str) ;
    int FlagEqual = 0 ;
    int idx = 0 ;
    while( idx < length ){
       if(str[idx] == '=' ){
          break ;
       }
       idx++ ;
    }
    
    if(idx > 6 || idx == length || idx < 2){
      return 0 ;
    }
    
   //  char EqualExpr[idx+1] ;
   
        
    strncpy(EqualExpr, str + 0, idx);
    EqualExpr[idx] = '\0';    
        
    if( ValidCell2(EqualExpr)){
         
          length = length-idx-1 ;
          if(length > 0){
          char PostExpr[length+1] ;
          strncpy(PostExpr, str + idx +1,length);
          PostExpr[length] = '\0';
           
                  int count = 0 ;
                  char Operator ;
                  
                  while( count < length ){
                     if( PostExpr[count] == '*' || PostExpr[count] == '-' || PostExpr[count] == '+' || PostExpr[count] == '/' || PostExpr[count] == '(' ){
                        Operator = PostExpr[count] ;
                        break ;
                     }
                     count++ ;
                  }
                     //  printf("%c", Operator) ;
                  // printf("%d", count) ;
                  if( count == length){
                     
                    if( ValidWholeNumber(PostExpr)){
                         
                          strncpy(Exp1, str + idx + 1,length);
                          Exp1[length] = '\0';
                        
                          return 1 ;
                    }
                    if( ValidCell2(PostExpr )){
                          
                          strncpy(Exp1, str + idx + 1,length);
                          Exp1[length] = '\0';
                        
                          return 2 ;
                    }
                  }else if(Operator == '('){
                            
                          int ret =   ParseFunc(PostExpr, Exp1 , Exp2 , Exp3);
                        return ret ;  
                  }
                  else{
                     int ret = RetValues(Operator);
                     char str1[20];
                     char str2[20];
                     // printf(PostExpr);
                     // printf(" %d ", strlen(PostExpr));
                     if(ValidPostExpr(PostExpr ,Exp1 ,Exp2)){
                       
                        return ret; 
                     } 
                  }
          } 
       
        
    }
 
 
   
    return 0 ;
}

int main(){
      

   char str[] = "A5=MIN(A1:B1)";
   char Exp1[20] ;
   char Exp2[20] ;
   char Exp3[20] ;
   char Exp4[20] ;
   
   int a = Parser(str , Exp1 , Exp2 ,Exp3, Exp4);
   printf("%d " ,a) ;
  
    printf( "%s ",Exp1) ;
    printf( "%s ",Exp2) ;
    printf( "%s ",Exp3) ;
     printf( "%s ",Exp4) ;
   
      
return 0;
}