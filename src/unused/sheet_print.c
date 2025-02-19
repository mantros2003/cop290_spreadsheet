#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cell.h"
#include "cell.c"
#include "database.h"
#include "database.c"
#include "hashset.h"
#include "hashset.c"
#include "nodes_ll.h"
#include "nodes_ll.c"
#include <math.h>
#include <ctype.h>
/* 
 *  The following type is useful when we want segregate alphabetic string from 
 *  numeric string of cell representation.
 *  eg.AA23 Here alphabetic string is AA and nnumeric string is 23.
 */
typedef struct {
    int numberPart;
    char* stringPart;
}int_string;
/*
 * The following functoin converts the given alphanumeric form 
 * to it's numeric representation.
 */
int convertInt(char x[]){
    int result=0;
    int length=strlen(x);
    int i=length-1;
    int p=0;
    while(i>=0){
        char ch=x[i];
        int req=ch-'A'+1;
        result=result+(int)(pow(26,p)*req);
        p++;
        i--;
    }
    return result;
}
/*
 *  The following function segregates the alphabetic string part and numeric string part
 *  from the given cell representation.
 */
int_string* segregate(char* position){
    int size=strlen(position);
    int k=0;
    char* stringPart=(char*) malloc(size*sizeof(char));
    for(int i=0;i<size;i++){
        if(!isalpha(position[i]) && !isdigit(position[i])){
            printf("%s  ","You entered the wrong cell");
            return NULL;
        }
        else if(isalpha(position[i])){
            stringPart[k++]=position[i];
        }
        else if(isdigit(position[i])){
            break;
        }
    }
    int numberPart=0;
    int power=size-k-1;
    for(int i=k;i<size;i++){
        int digit=position[i]-'0';
        numberPart+=pow(10,power)*digit;
        power--;
    }
    int_string* after_segregation=(int_string*) malloc(sizeof(int_string));
    after_segregation->numberPart=numberPart;
    after_segregation->stringPart=stringPart;
    return after_segregation;
}
/*
 *  The following function return a pointer to the cell that
 *  corresponds with the given row and column numbers in the database.
 */
struct cell* get_cell_pointer(int row,int col,database* db){
    struct column_segment *column_pointer=get_column(db,col);
    return get_cell(row,&column_pointer);
}
void add_dep_range(struct cell *target, char* start,char* end, char oper,database *db){
    target->oper=oper;
    int_string* temp1=segregate(start);
    int_string* temp2=segregate(end);
    int start_row=temp1->numberPart;
    int end_row=temp2->numberPart;
    int start_col=convertInt(temp1->stringPart);
    int end_col=convertInt(temp2->stringPart);
    for(int i=start_row;i<=end_col;i++){
        for(int j=start_col;j<=end_col;j++){
            struct cell* from=get_cell_pointer(i,j,db);
            add_dep(target,from,oper);
        }
    }
    free(temp1);
    free(temp2);

}
/*
 *Converts the colNumber to corresponding Alphabatic representation and returns.
 */
char* convertAlpha(int x){
    char* ptr;
    ptr=(char*) malloc (4*(sizeof(char)));
    int ind=0;
    while(x>0){
        int rem=x%26;
        if(rem==0){
            ptr[ind++]='Z';
            x=(x-1)/26;
        }
        else{
            ptr[ind++]='A'+(rem-1);
            x=x/26;
        }
    }
    ptr[ind]='\0';
    for(int i=0;i<ind/2;i++){
        char temp=ptr[i];
        ptr[i]=ptr[ind-i-1];
        ptr[ind-i-1]=temp;
    }
    return ptr;
}
/*
 * Prints the 10x10 section of the spreadsheet from given row and column.
 * If there are fewer then 10 rows or 10 columns it prints as many as possible.
 * First column headers are printed on first line.
 * Then,values in the cells are printed if there is no error in the cell else "error" is printed.
 */
void print_sheet(database* db,int row,int col){
    int rowEnd=(row+10)<=(db->num_rows)?row+10:db->num_rows;
    int colEnd=(col+10)<=(db->num_cols)?col+10:db->num_cols;
    printf("        ");
    for(int colnumber=col;colnumber<rowEnd;colnumber++){
        printf("%-9s",convertAlpha(colnumber));
    }
    printf("\n");
    for(int rowNumber=row;rowNumber<(row+10);rowNumber++){
        printf("%-8d",rowNumber);
        for(int colNumber=col;colNumber<colEnd;colNumber++){
            if(has_error(db,colNumber,rowNumber)){
                printf("%-9s","error");
            }
            else{
            printf("%-9d",get(db,colNumber,rowNumber));}
        }
        printf("\n");
    }
}
int main(){
    // char* x=(char*)malloc(2*sizeof(char));
    // x[0]='x';
    // int* y=(int*)malloc(sizeof(int));
    // *y=2;
    // print_int(*y);
    // print_end();
    // for(int i=0;i<40;i++){
    //     printf("%s %d",x,*y);
    //     get_next(&x,y);
    //     printf("\n");
    // 
    return 0;
}
