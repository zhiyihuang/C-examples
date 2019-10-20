#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *get_token(char *s)
{
int i;
char *token;
token = malloc(100);
i = 0;
while(s[i] != ' ' && s[i] != 0){
token[i] = s[i];
i = i + 1;
}
token[i] = 0;
return token;
}


int is_operator(char *s)
{
if(strlen(s) != 1) return 0;
if(s[0] == '+' || s[0] == '-' || s[0] == '*') return 1;
else return 0;
}

int is_number(char *s)
{
int i;
i = 0;
while(s[i] != 0){
    if(s[i] >= '0' && s[i] <= '9') i = i+1;
    else return 0;
}
return 1;
}

int addition(int x, int y)
{
return x+y;
}

int multiply(int x, int y)
{
return x * y;
}

int subtract(int x, int y)
{
return x-y;
}
int main(int argc, char *argv[])
{
if(argc != 2) {
printf("Usage: %s \n", argv[0]);
exit(0);
}
if(is_number(argv[1])) printf("yes %s is a number\n", argv[1]);
else printf("No, %s is not a number\n", argv[1]);

exit(0);


int num1, num2;
num1 = atoi(argv[1]);
num2 = atoi(argv[2]);
while(1){
printf("choose one of the following operations\n");
printf("a: add\n");
printf("m: multiply\n");
printf("s: subtract\n");
printf("q: quit!\n");
char c = getchar();
if(c=='q') exit(0);
getchar();
printf("input the first operand:");
scanf("%d", &num1);
printf("input the second operand:");
scanf("%d", &num2);
int r;
if(c=='a') {
r = addition(num1, num2);
printf("The result is %d\n", r);
}
if(c=='m') {
r = multiply(num1, num2);
printf("The multiplication is %d\n", r);
}
if(c=='s'){
r = subtract(num1, num2);
printf("The subtraction is %d\n", r);
}
getchar();
}
}

