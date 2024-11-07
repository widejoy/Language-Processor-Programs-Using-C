#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct{
    char operand[50];
    char label[50];
    char opcode[50];
    int address;

} Instructions;

typedef struct{
    char name[50];
    int address;
} Symtab;
int ins_ptr = 0;
int sym_ptr = 0;

Symtab symtabs[10];
Instructions instructions[10];
void addtosymtab(char label[100],int add){
    strcpy(symtabs[sym_ptr].name,label);
    symtabs[sym_ptr].address = add;
    sym_ptr++;
}
void main(){
    char line[200], label[50], operand[50], opcode[50];
    int parts,start_adr,counter,t;
    FILE *fp = fopen("pass1.txt","r");
    while(fgets(line,200,fp)){
        parts = sscanf(line,"%s %s %s",label,opcode,operand);
        if(parts==2){
            strcpy(operand,opcode);
            strcpy(opcode,label);
            strcpy(label,"");
        }
        else if(parts==1){
            strcpy(opcode,label);
            strcpy(operand,"");
            strcpy(label,"");
        }
        if(strcmp("START",opcode)==0){
            t = (int)strtol(operand,NULL,16);
            start_adr = t;
            counter = start_adr;
            continue;
        }
        strcpy(instructions[ins_ptr].operand, operand);
        strcpy(instructions[ins_ptr].opcode, opcode);
        strcpy(instructions[ins_ptr].label, label);
        ins_ptr++;  
    }
    for(int i = 0;i<ins_ptr;i++){        
        instructions[i].address = counter;
        if(instructions[i].label[0]!='\0'){
        addtosymtab(instructions[i].label,counter);
    }
        if(strcmp(instructions[i].opcode,"RESW")==0){
            t = (int)strtol(instructions[i].operand,NULL,16);
            counter =counter +t*3;
        }
        else if(strcmp(instructions[i].opcode,"RESB")==0){
            t = (int)strtol(instructions[i].operand,NULL,16);
            counter+=t;
        }
        else if(strcmp(instructions[i].opcode,"BYTE")==0){
            int len = 0;
            len+=strlen(instructions[i].operand)-3;
            if(instructions[i].operand[0]=='C'){
                counter+=len;
            }
            else{
                counter+=len/2;
            }
        }

        else{
            counter+=3;
        }

    }
    printf("Symbol Table:\n");
    printf("Name\tAddress\n");
    for (int i = 0; i < sym_ptr; i++) {
        printf("%s\t%x\n", symtabs[i].name, symtabs[i].address);
    }
    printf("\nInstructions:\n");
    printf("Address\tLabel\tOpcode\tOperand\n");
    for (int i = 0; i < ins_ptr; i++) {
        printf("%04x\t%s\t%s\t%s\n", instructions[i].address, instructions[i].label, instructions[i].opcode, instructions[i].operand);
    }

     
}