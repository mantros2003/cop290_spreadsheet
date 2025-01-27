#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
void print_array(int** arr,int rows,int cols){
    printf("   ");
    for(int i=1;i<=cols;i++){
        printf("%s    ",convertAlpha(i));
    }
    printf("\n");
    for(int i=0;i<rows;i++){
        printf("%d  ",i);
        for(int j=0;j<cols;j++){
            printf("%d    ",arr[i][j]);
        }
        printf("\n");
    }
}
int main(){
    int x;
    int y;
    scanf("%d %d",&x,&y);
    int** arr=create_array(x,y);
    print_array(arr,x,y);
    return 0;
}