#include<stdio.h>
#include<string.h>
#include<ctype.h>
void main(){
    char sourceCode[1000];
    FILE *fp = fopen("input.txt","r");
    size_t len = fread(sourceCode,1,1000,fp);
    int i=0,j=0;
    char buffer[40];
    int iskeyword = 0;
    char keywords[10][10] = {
        "while","for","if","else","do","char","int","string","void"
    };
    do{
        if(sourceCode[i]=='#'){
            j = 0;
            while(sourceCode[i]!='\n'){
                buffer[j] = sourceCode[i];
                i++;
                j++;
            }
            buffer[j] = '\0';
            printf("TOKEN PREPROCESSOR BUFFER: %s \n",buffer);
        }
        else if(isalpha(sourceCode[i]))
        {
            j = 0;
            while(isalpha(sourceCode[i]) || sourceCode[i] == '_'){
                buffer[j] = sourceCode[i];
                i++;
                j++;
            }
            buffer[j] = '\0';
            for(int k=0;k<9;k++){
                if(strcmp(buffer,keywords[k])==0){
                    iskeyword = 1;
                }
            }
            if(iskeyword){
                printf("TOKEN KEYWORD: %s \n",buffer);
            }
            else{
                printf("TOKEN IDENTIFIER: %s \n",buffer);
            }
            iskeyword = 0;
        }
        else if(sourceCode[i] == '"'){
            j = 0;
            i++;
            while(sourceCode[i]!='"'){
                buffer[j] = sourceCode[i];
                i++;
                j++;
            }
            buffer[j] = '\0';
            printf("TOKEN STRING: %s \n",buffer);

        }
        else if(sourceCode[i] == '{'){
            printf("PARA OPEN \n");
            i++;
        }
        else if(sourceCode[i]=='}'){
            printf("PARA CLOSE \n");
            i++;
        }
        i++;
    }while(i<len);
}


