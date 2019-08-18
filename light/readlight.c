#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
int data[200], i, tmp, swap;
FILE *fp;
if(argc != 2) {
	printf("Usage: %s <filename>\n", argv[0]);
	exit(0);
}
fp = fopen(argv[1], "r");
fread(data, 200, sizeof(int), fp);
for(i=0;i<200;i++) printf("%d ", data[i]);
printf("\n");
while(1){
swap = 0;
for(i=0;i<199;i++) if(data[i] > data[i+1]){
	swap = 1;
	tmp = data[i+1];
	data[i+1] = data[i];
	data[i] = tmp;
}
if(swap == 0) break;
}
printf("The sorted array is: ");
for(i=0;i<200;i++) printf("%d ", data[i]);
printf("\n");
}
