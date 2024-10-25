#include<stdio.h>
#include<string.h>
typedef struct{
    char name[50];
    int start;
    int end;
} Namtab;

Namtab namtab[10];
int nam_ptr = 0;

void addnamtab(char* na, int start,int end){
    strcpy(namtab[nam_ptr].name,na);
    namtab[nam_ptr].start = start;
    namtab[nam_ptr].end = end;
    nam_ptr++;
}

int checkmacro(char line[]){
    char temp[10];
    int j = 0;
    for(int i =0;i<strlen(line);i++){
        if(line[i]==' '){
            if(strcmp(temp,"MACRO")==0){
                return 1;
            }
            memset(temp, '\0', strlen(temp)); 
            j = 0;
        }
        else{
            temp[j] = line[i];
            j++;
        }
    }
    return 0;
}

char* getfirstword(char line[]){
    static char temp[10];
    int i =0;
    while(line[i]!=' '){
        temp[i] = line[i];
        i++;
    }
    temp[i] = '\0';
    return temp;
}
int checkcall(char line[]){
    char word[10] = getfirstword(line);
    for(int i=0;i<nam_ptr;i++){
        if(strcmp(word,namtab[i].name)==0){
            return 1;
        }
    }
    return 0;

}
void main(){
    char macro[1000];
    char deftab[1000];
    FILE *fp = fopen("macro.txt","r");
    size_t len = fread(macro,1,1000,fp);
    char buffer[35];
    char* name;
    int i = 0,j=0,start = 0,ismacro = 0;
    while(i<len){
        if(macro[i]=='\n'){
            buffer[j] = '\0';
            if(checkcall(buffer)){}
            if(ismacro){
                if(strcmp(buffer,"MEND")==0){
                    addnamtab(name,start,i);
                    ismacro--;
                }
                
                strcat(deftab,buffer);
                strcat(deftab, "\n"); 
                
            }
            if(checkmacro(buffer)){
                name = getfirstword(buffer);
                start = i;
                ismacro++;
                strcat(deftab,buffer);
                strcat(deftab, "\n"); 
            }

            j = 0;
        }
        else{
            buffer[j] = macro[i];
            j++;
        }
        i++;
    }
    printf("Name Table:\n");
    for (int i = 0; i < nam_ptr; i++) {
        printf("Macro Name: %s, Start: %d, End: %d\n", namtab[i].name, namtab[i].start, namtab[i].end);
    }
    printf("\nDefinition Table:\n%s", deftab);
}