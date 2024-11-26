#include<stdio.h>
#include <stdlib.h>
#include<string.h>

char* addzero(char inp[10]){
    static char result[10];
    int len = 6 - strlen(inp);
    int i =0;
    for(i=0;i<len;i++){
        result[i] = '0';
    }
    result[i] = '\0';
    strcat(result,inp);
    return result;
}
char* getsymtab(char inp[50]){
    static char result[50];
    FILE *symp = fopen("symtab.txt","r");
    char line[50],label[10],addr[10];
    int parts;
    while(fgets(line,200,symp)){
        sscanf(line,"%s %s",label,addr);
        if(strcmp(inp,label)==0){
            strcpy(result,addr);
            break;
        }
    }
    return result;
}
char* getoptab(char inp[50]){
    static char result[50];
    FILE *symp = fopen("optab.txt","r");
    char line[50],label[10],addr[10];
    int parts;
    while(fgets(line,200,symp)){
        sscanf(line,"%s %s",label,addr);
        if(strcmp(inp,label)==0){
            strcpy(result,addr);
            break;
        }
    }
    return result;
}
void main(){
    FILE *fp = fopen("outputpass1.txt","r");
    FILE *fp1 = fopen("length.txt","r");
    char line[200],firstline[200],programname[100],dummy[100],startingaddr[100],output[1000] = {0};
    char padded_startingaddr[10], padded_length[10];
    char length[10],address[50],label[50],opcode[50],operand[50];
    int parts;
    fgets(length,200,fp1);
    fgets(line,200,fp);
    sscanf(line,"%s %s %s",programname,dummy,startingaddr);
    strcpy(padded_startingaddr,addzero(startingaddr));
    strcpy(padded_length,addzero(length));
    printf("HEAD RECORD: H^%s %s^%s\n",programname,padded_startingaddr,padded_length);
    printf("END RECORD: E^%s\n",padded_startingaddr);
    printf("TEXT RECORD:\n");
    printf("T^%s^%s^",padded_startingaddr,length);
    while(fgets(line,200,fp)){
        parts = sscanf(line,"%s %s %s %s",address,label,opcode,operand);
        if(parts==3){
            strcpy(operand,opcode);
            strcpy(opcode,label);
        }
        if(strcmp(label,"END")==0){
            break;
        }
        if(strcmp(opcode,"RESW")==0 || strcmp(opcode,"RESB")==0){}
        else if(strcmp(opcode,"BYTE")==0){
            for(int k =2;k<strlen(operand)-1;k++){
                printf("%x",operand[k]);
            }
            printf("^");
        }
        else if(strcmp(opcode,"WORD")==0){
            printf("%s^",addzero(operand));
        }
        else{
            printf("%s%s^",getoptab(opcode),getsymtab(operand));
        }
    }
}   