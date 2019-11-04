#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *get_token(char *s, char *token)
{
int i, j;

i = 0; j = 0;
while(s[i] == ' ') i = i + 1;
while(s[i] != ' ' && s[i] != 0 && s[i] != '\n'){
token[j] = s[i];
i = i + 1;
j = j + 1;
}
token[j] = 0;
return s+i;
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
char buf[100];
if(argc != 1) {
printf("Usage: %s \n", argv[0]);
exit(0);
}

fgets(buf, 100, stdin);
printf("The string is %s\n", buf);
printf("The length of the string is %ld\n", strlen(buf));
char num1[100], num2[100], op[100], *p;
p = get_token(buf, num1);
if(is_number(num1)==0) {
	printf("Wrong number: %s\n", num1);
	exit(0);
}
p = get_token(p, op);
if(is_operator(op)==0) {
	printf("Wrong operator: %s\n", op);
	exit(0);
}
p = get_token(p, num2);
if(is_number(num2)==0) {
	printf("Wrong number: %s\n", num2);
	exit(0);
}

int n1, n2, r;
n1 = atoi(num1);
n2 = atoi(num2);
char c;
c = op[0];
if(c=='+') {
r = addition(n1, n2);
printf("The result is %d\n", r);
}
if(c=='*') {
r = multiply(n1, n2);
printf("The multiplication is %d\n", r);
}
if(c=='-'){
r = subtract(n1, n2);
printf("The subtraction is %d\n", r);
}
}

