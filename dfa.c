#include<stdio.h>
#include<string.h>

int i=0, s =0;
char str[1000];
void q1(char c);
void q0(char c);
void q2(char c);
void q3(char c);
void main(){
    printf("ENTER STRING: \n");
    scanf("%s",str);
    q0(str[0]);
    if(s){
        printf("ACCEPTED");
    }
    else{
        printf("NOT ACCEPTED");
    }

}

void q0(char c){
    if(i==strlen(str)){
        return;
    }
    i++;
    if(c=='a'){
        q1(str[i]);
    }
    else{
        q3(str[i]);
    }
}
void q1(char c){
    if(i==strlen(str)){
        return;
    }
    i++;
    if(c=='a'){
        q3(str[i]);
    }
    else{
        q2(str[i]);
    }
}
void q2(char c){
    if(i==strlen(str)){
        return;
    }
    i++;
    if(c=='a'){
        q1(str[i]);
    }
    else{
        q3(str[i]);
    }
}

void q3(char c)
{
    if(i==strlen(str)){
        s = 1;
        return;
    }
    i++;
    q3(str[i]);
}