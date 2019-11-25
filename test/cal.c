#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int larger_number(char *s)
{
char largest_number[12] = "1073741824";
char buf[100];
int i, j;

i = j = 0;
while(s[i] == '0') i = i + 1;
while(s[i] != 0) buf[j++] = s[i++];
buf[j] = 0; s = buf;
if(strlen(s) == strlen(largest_number)){
     if(strcmp(s, largest_number) > 0) return 1;
  else return 0;
} else {
  if(strlen(s) > strlen(largest_number)) return 1;
  else return 0;
}
}

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
if(strlen(s)==0) return 2;
i = 0;
while(s[i] != 0){
    if(s[i] >= '0' && s[i] <= '9') i = i+1;
    else return 0;
}
return 1;
}

long long addition(int x, int y)
{
return (long long)x+y;
}

long long multiply(int x, int y)
{
return (long long)x * (long long)y;
}

long long subtract(int x, int y)
{
return (long long)x-y;
}
int main(int argc, char *argv[])
{
char buf[100];
if(argc != 1) {
printf("Usage: %s \n", argv[0]);
exit(0);
}

while(1){
printf("input your expression: ");
fgets(buf, 100, stdin);
if(buf[0] == 'q') exit(0);
printf("The string is %s\n", buf);
printf("The length of the string is %d\n", strlen(buf));
char num1[100], num2[100], op[100], *p;
p = get_token(buf, num1);
if(is_operator(num1) == 1) {
	printf("Missing num1\n");
	continue;
}
if(is_number(num1)!=1) {
	if(is_number(num1)==0)printf("Wrong number: %s\n", num1);
	else printf("Missing num1\n");
	continue;
}
if(larger_number(num1) == 1) {
	printf("The number %s is too large\n", num1);
	continue;
}
p = get_token(p, op);
if(is_operator(op)==0) {
	printf("Wrong operator: %s\n", op);
	continue;
}
p = get_token(p, num2);
if(is_number(num2)!=1) {
	if(is_number(num2)==0)printf("Wrong number: %s\n", num2);
	else printf("Missing num2\n");
	continue;
}
if(larger_number(num2) == 1) {
        printf("The number %s is too large\n", num2);
        continue;
} 
int n1, n2;
long long r;
n1 = atoi(num1);
n2 = atoi(num2);
char c;
c = op[0];
if(c=='+') {
r = addition(n1, n2);
printf("The result is %lld\n", r);
}
if(c=='*') {
r = multiply(n1, n2);
printf("The multiplication is %lld\n", r);
}
if(c=='-'){
r = subtract(n1, n2);
printf("The subtraction is %lld\n", r);
}
}
}
