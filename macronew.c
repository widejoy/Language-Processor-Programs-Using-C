#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct 
{
    char name[50];
    int start;
    int end;
    int actstart;
    char params[10][50];
} Namtab;
int nam_ptr = 0;
Namtab namtab[10];
void addnamtab(char* na, int start, int end, char params[10][50], int act){
    strcpy(namtab[nam_ptr].name, na);
    namtab[nam_ptr].start = start;
    namtab[nam_ptr].end = end;
    namtab[nam_ptr].actstart = act;
    for (int i = 0; i < 10; i++) {
        if (strlen(params[i]) > 0) {  
            strcpy(namtab[nam_ptr].params[i], params[i]);
        } else {
            namtab[nam_ptr].params[i][0] = '\0';  
        }
    }
    nam_ptr++;
}
void getparams(char line[], char params[10][50]) {
    char buffer[50];
    int j = 0, k = 0;
    for (int i = 0; i <= strlen(line); i++) {
        if (line[i] == ',' || line[i] == '\n' || line[i] == '\0') {
            buffer[j] = '\0';  
            strcpy(params[k], buffer);  
            k++;   
            j = 0;  
        } else {
            buffer[j] = line[i];   
            j++;
        }
    }
}
void main(){
    FILE *fp = fopen("macro.txt","r");
    FILE *fp1 = fopen("macro.txt","r");
    int parts,s,e,ptr=0,t=0;
    char macro[1000], output[1000] = {0};
    size_t len = fread(macro, 1, 1000, fp);
    rewind(fp);
    char line[200],com[50],mac[50],param[50],name[50],Deftab[1000] = {0},params[10][50] = {0},temp1[100],dummy[200];
    while(fgets(line,200,fp)){
        parts = sscanf(line,"%s %s %s",com,mac,param);
        if(parts == 3 && strcmp(mac,"MACRO")==0){
            strcpy(name,com);
            getparams(param,params);
            s=ptr;
            fp1 = fp;
            ptr += strlen(line);
            int temp = ptr;
            strcat(Deftab,line);
            while (fgets(dummy, 200, fp1)) {
                strcat(Deftab, dummy);
                if (strstr(dummy, "MEND") != NULL) {
                    e = temp;
                    break;
                }
                temp += strlen(dummy)-1;
            }
            addnamtab(name,s,e,params,ptr);
            
        }
        else if(parts==2){
            char args[10][50] = {0},buffer[200];
            int i;
            for(i = 0;i<nam_ptr;i++){
                if(strcmp(com,namtab[i].name)==0){
                    getparams(mac,args);
                    break;
                }
            }
            for(int k = namtab[i].actstart;k<=namtab[i].end;k++){
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
                            if(strcmp(tempbuffer,namtab[i].params[t])==0){
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
            ptr += strlen(line);
        }
 
            
        else{
            ptr += strlen(line);
        }
        
    }
    printf("%s",Deftab);
for (int k = 0; k < nam_ptr; k++) {
    printf("Macro #%d:\n", k + 1);
    printf("Name: %s\n", namtab[k].name);
    printf("Start: %d\n", namtab[k].start);
    printf("End: %d\n", namtab[k].end);
    printf("Actual Start: %d\n", namtab[k].actstart);
    
    printf("Parameters:\n");
    for (int i = 0; i < 10; i++) {
        if (strlen(namtab[k].params[i]) > 0) {
            printf("  Param %d: %s\n", i + 1, namtab[k].params[i]);
        }
    }
    printf("\n");
    printf("output\n");
    printf("%s",output);
}
}