#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    char name[50];
    int start;
    int end;
    char params[10][50];
} Namtab;

Namtab namtab[10];
int nam_ptr = 0;

void addnamtab(char* na, int start, int end, char params[10][50]){
    strcpy(namtab[nam_ptr].name, na);
    namtab[nam_ptr].start = start;
    namtab[nam_ptr].end = end;
    for (int i = 0; i < 10; i++) {
        if (strlen(params[i]) > 0) {  
            strcpy(namtab[nam_ptr].params[i], params[i]);
        } else {
            namtab[nam_ptr].params[i][0] = '\0';  
        }
    }
    nam_ptr++;
}

int checkmacro(char line[]){
    char temp[10];
    int j = 0;
    for(int i = 0; i < strlen(line); i++){
        if(line[i] == ' '){
            if(strcmp(temp, "MACRO") == 0){
                return 1;
            }
            memset(temp, '\0', strlen(temp));
            j = 0;
        } else {
            temp[j] = line[i];
            j++;
        }
    }
    return 0;
}

void getmacroparams(char line[], char params[][50]){
    char buff[10];
    int j = 0, k = 0;
    for(int i = 0; i < strlen(line); i++){
        if (line[i] == '&'){
            buff[j] = '&';
            j++;
            i++;
            while(isalnum(line[i]) || line[i] == '_'){
                buff[j] = line[i];
                i++;
                j++;
            }
            buff[j] = '\0';
            j = 0;
            strcpy(params[k], buff);
            k++;
        }
    }
}

char* getfirstword(char line[]){
    static char temp[10];
    int i = 0;
    while(line[i] != ' '){
        temp[i] = line[i];
        i++;
    }
    temp[i] = '\0';
    return temp;
}

int checkcall(char line[]){
    char* word = getfirstword(line);
    for(int i = 0; i <= nam_ptr; i++){
        if(strcmp(word, namtab[i].name) == 0){
            return i;
        }
    }
    return -1;
}

void main(){
    char macro[1000];
    char deftab[1000] = {0};
    char output[1000] = {0};
    FILE *fp = fopen("macro.txt", "r");
    size_t len = fread(macro, 1, 1000, fp);
    char params[10][50] = {0};  
    char buffer[35];
    char name[50];
    int i = 0, j = 0, start = 0, ismacro = 0, a;

    while(i < len){
        if(macro[i] == '\n'){
            buffer[j] = '\0';
            a = checkcall(buffer);
            if(a != -1){
                char args[10][50];
                getmacroparams(buffer,args);
                for(int k = namtab[a].start;k<=namtab[a].end;k++){
                    if(macro[k]=='&'){
                        int ptr = 1;
                        char tempbuffer[50]= {'&'};
                        k++;
                         while(isalnum(macro[k])||macro[k]=='_'){
                            tempbuffer[ptr] = macro[k];
                            ptr++;
                            k++;
                        }
                        tempbuffer[ptr] = '\0';
                        k--;
                        for(int t=0;t<sizeof(args);t++){
                            if(strcmp(tempbuffer,namtab[a].params[t])==0){
                                 strcat(output,args[t]); 
                                ptr=0;
                                break;
                            }
                        }
                    }
                    else{
                        strncat(output, &macro[k], 1);
                    }
                }
            }
            if(ismacro){
                if(strcmp(buffer, "MEND") == 0){
                    addnamtab(name, start, i,params);
                    ismacro--;
                }
                
                strcat(deftab, buffer);
                strcat(deftab, "\n"); 
                
            }
            if(checkmacro(buffer)){
                strcpy(name, getfirstword(buffer));
                getmacroparams(buffer,params);
                start = i;
                ismacro++;
                strcat(deftab, buffer);
                strcat(deftab, "\n"); 
            }

            j = 0;
        } else {
            buffer[j] = macro[i];
            j++;
        }
        i++;
    }

    printf("Name Table:\n");
    for (int i = 0; i < nam_ptr; i++) {
         printf("Macro Name: %s, Start: %d, End: %d\n", namtab[i].name, namtab[i].start, namtab[i].end);
                 printf("Parameters:\n");
        for (int j = 0; j < 10; j++) {
            if (strlen(namtab[i].params[j]) > 0) {
                printf("  Param %d: %s\n", j + 1, namtab[i].params[j]);
            }
        }
    }
    printf("\nDefinition Table:\n%s", deftab);
    printf("\nOutput Table:\n%s", output);
}
