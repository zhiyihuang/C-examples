#include <stdio.h>
#include <stdlib.h>
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
if(argc != 3) {
printf("Usage: %s num1 num2\n", argv[0]);
exit(0);
}
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

