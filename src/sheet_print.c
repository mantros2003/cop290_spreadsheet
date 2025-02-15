#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "cell.h"
#include "column.h"
#include "hashset.h"
#include "nodes_ll.h"
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
    return 0;
}
