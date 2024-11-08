#include<stdio.h>
#include <stdlib.h>
#include<string.h>

char* addzero(char inp[10]){
    static char result[10];
    int j = 0;
    int padding = 6 - strlen(inp);   
    for (j = 0; j < padding; j++) {
            result[j] = '0';
    }
    result[j] = '\0';
    strcat(result, inp);

    return result; 
}

char * getsymtabadd(char inp[50]){
    static char result[50];
    FILE *symp = fopen("symtab.txt","r");
    char line[100];
    char label[50],add[50];
    while(fgets(line,100,symp)){
        sscanf(line,"%s %s",label,add);
        if(strcmp(inp,label)==0){
            strcpy(result,add);
            addzero(result);
            return result;
        }
    }
     fclose(symp);
}
char * getoptabadd(char inp[50]){
    static char result[50];
    FILE *symp = fopen("optab.txt","r");
    char line[100];
    char label[50],add[50];
    while(fgets(line,100,symp)){
        sscanf(line,"%s %s",label,add);
        if(strcmp(inp,label)==0){
            strcpy(result,add);
            return result;
        }
    }
     fclose(symp);
}
void main(){ 
    FILE *fp = fopen("outputpass1.txt","r");
    FILE *fp1 = fopen("header.txt","w");
    FILE *fp2 = fopen("length.txt","r");
    FILE *fp3 = fopen("text.txt","w");
    FILE *fp4 = fopen("end.txt","w");
    char firstline[100], programname[50], start_adr_str[50], dummy[50], length[10];
    char start[100],opcode[100],label[100], last[10],operand[50], output[1000] = {0}, line[100];
    int t;
    fgets(firstline, 200, fp);
    fread(length,1,10,fp2);
    sscanf(firstline,"%s %s %s",programname,dummy,start_adr_str);
    strcpy(length,addzero(length));
    fprintf(fp1,"H^%s %s^%s",programname,addzero(start_adr_str),length);
    fgets(firstline,200,fp);
    sscanf(firstline,"%s %s %s",start,opcode,label);
    strcpy(last,getsymtabadd(label));
    fprintf(fp3, "T^%s^%s^", addzero(start_adr_str), &last[strlen(last) - 2]);
    do{
        t = sscanf(firstline,"%s %s %s %s",start,opcode,label,operand);
        strcpy(line,"");
        if(strcmp("END",opcode)==0){
            fprintf(fp4,"E^%s",addzero(start_adr_str));
            strcat(output,"END\t");
            strcat(output,start_adr_str);
            break;
        }
        if (t!=4){
            if(getoptabadd(opcode)){
                fprintf(fp3,"%s%s^",getoptabadd(opcode),getsymtabadd(label));
                strcat(line,getoptabadd(opcode));
                strcat(line,getsymtabadd(label));
                strcat(line,"\t");
             }
        }
        else{
            if(strcmp(label,"WORD")==0){
                fprintf(fp3,"%s^",addzero(operand));
                strcat(line,addzero(operand));
                strcat(line,"\t");
            }
            else if (strcmp(label,"BYTE")==0){
                for(int k = 2;k<strlen(operand)-1;k++){
                    fprintf(fp3,"%x",operand[k]);
                    
                }
                fprintf(fp3,"^");
            }
        }
        strcat(line,firstline);
        strcat(output,line);

    }
    while(fgets(firstline,200,fp));
    printf("%s", output);
}