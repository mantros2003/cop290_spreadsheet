#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define min(a,b) ((a)<(b))?(a):(b)
typedef struct {
    int numberPart;
    char* stringPart;
}int_string;
int convertInt(char x[]){
    int result=0;
    int length=strlen(x);
    int i=length-1;
    int p=0;
    while(i>=0){
        char ch=x[i];
        int req=ch-'A'+1;
        result=result+(pow(26,p)*req);
        p++;
        i--;
    }
    return result;
}
char* modify(char* x,int* cols_max_length,int col_number){
    int size=strlen(x);
    int upto=cols_max_length[col_number-1]>3?cols_max_length[col_number-1]:3;
    char* result=(char*)malloc(upto*sizeof(char));
    strcpy(result,x);
    for(int i=size;i<upto;i++){
        result[i]=' ';

    }
    return result;
}
char* int_modify(int x){
    char* result=(char*) malloc(3*sizeof(char));
    sprintf(result,"%d",x);
    int size=strlen(result);
    for(int i=size;i<3;i++){
        result[i]=' ';
    }
    return result;
}
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
int_string* segregate(char* position){
    int_string* result=(int_string*) malloc(2*sizeof(int_string));
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
int** create_array(int rows,int cols){
    int** arr;
    arr=(int** )malloc(rows*sizeof(int*));
    if(arr==NULL){
        printf("Memeory allocatoin faliled");
        return NULL;
    }
    for(int i=0;i<rows;i++){
        arr[i]=(int*) malloc(cols*sizeof(int));
    }
    return arr;
}
void print_array(int** arr,int rows,int cols,int* col_max_length){
    printf("     ");
    for(int i=1;i<=cols;i++){
        printf("%s  ",modify(convertAlpha(i),col_max_length,i));
    }
    printf("\n");
    for(int i=0;i<rows;i++){
        printf("%s  ",int_modify(i));
        for(int j=0;j<cols;j++){
            printf("%d    ",arr[i][j]);
        }
        printf("\n");
    }
}
void print_array_constrained_helper(int rowStart,int rowMax,int colStart,int colMax,int** arr,int* colMaxLength){
    int rowEnd=rowStart+10>rowMax?rowMax:rowStart+9;
    int colEnd=colStart+10>colMax?colMax:colStart+9;
    printf("     ");
    for(int colNumber=colStart;colNumber<=colEnd;colNumber++){
        printf("%s  ",modify(convertAlpha(colNumber),colMaxLength,colNumber));
    }

    printf("\n");

    for(int rowNumber=rowStart;rowNumber<=rowEnd;rowNumber++){
        printf("%s  ",int_modify(rowNumber));
        for(int colNumber=colStart;colNumber<=colEnd;colNumber++){
            printf("%d    ",arr[rowNumber-1][colNumber-1]);
        }
        printf("\n");
    }
}
void print_array_constrained(char* firstPosition,char* secondPosition,int row_max,int col_max,int** arr,int* colMaxLength){
    int_string* p1=segregate(firstPosition);
    int_string* p2=segregate(secondPosition);
    int row1=p1->numberPart;
    int row2=p2->numberPart;
    int col1=convertInt(p1->stringPart);
    int col2=convertInt(p2->stringPart);
    printf("%d %d %d %d \n",row1,row2,col1,col2);
    if(row1>row2){
        printf("First rownumber has to be small\n");
        return;
    }
    else if(col1>col2){
        printf("First colnumber has to be small\n");
        return;
    }
    else if(row2>row_max){
        printf("Rownumber exceeded the sheet\n");
        return;
    }
    else if(col2>col_max){
        printf("Colnumber exceeded the sheer\n");
        return;
    }
    col_max=min(col2,col_max);
    row_max=min(row2,row_max);
    int cur_row=row1;
    int cur_col=col1;
    char direction[10];
    print_array_constrained_helper(1,row_max,1,col_max,arr,colMaxLength);
    while(1){
        printf("%s","Enter the direction in which you want the further information:   ");
        scanf("%s",&direction);
        if(strcmp(direction,"w")==0){
            // cur_row=(cur_row-10)<0?0 : cur_row-10;
            if(cur_row<=10){
                printf("Out of sheet UP\n");
                return;
            }
            else{
                cur_row=cur_row-10;
                print_array_constrained_helper(cur_row,row_max,cur_col,col_max,arr,colMaxLength);
                }
        }
        else if(strcmp(direction,"s")==0){
            // cur_row=(cur_row+10)>row_max? break: cur_row-10;
            if((cur_row+10)>row_max){
                printf("row limit exceeded DOWN \n");
                return;
            }
            else{
                cur_row=cur_row+10;
                print_array_constrained_helper(cur_row,row_max,cur_col,col_max,arr,colMaxLength);}
        }
        else if(strcmp(direction,"a")==0){
            if(cur_col<=10){
                printf("Sheet limit exceeded LEFT\n");
                return ;
            }
            else{
                cur_col=cur_col-10;
                print_array_constrained_helper(cur_row,row_max,cur_col,col_max,arr,colMaxLength);
            }
        }
        else if(strcmp(direction,"d")==0){
            if((cur_col+10)>col_max){
                printf("Sheet limit exceeded RIGHT\n");
                return;
            }
            else{
                cur_col=cur_col+10;
                print_array_constrained_helper(cur_row,row_max,cur_col,col_max,arr,colMaxLength);
            }
        }
        else if(strcmp(direction,"q")==0){
            return;
        }
        else{
            printf("Invalid input\n");
            return;
        }
    }

}
// int main(){
//     int rows=12;
//     int cols=28;
//     int* headings=(int*) calloc(cols,sizeof(int));
//     int** arr=create_array(rows,cols);
//     int* col_maxlength=(int*)calloc(cols,sizeof(int));
//     print_array_constrained("A1","Z12",rows,cols,arr,col_maxlength);
//     return 0;
// }
