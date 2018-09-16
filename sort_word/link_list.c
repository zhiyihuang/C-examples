#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define word_len 1024

struct link {
char word[word_len];
int count;
struct link *next;
};

void insert(struct link *head, char word[])
{
	struct link *tail, *ptr;

	tail = head;
	if(strcmp(tail->word, word) == 0) {
	    tail->count ++;
	    return;
	}
	while (tail->next != NULL) {
		tail = tail->next;
		if(strcmp(tail->word, word) == 0) {
		    tail->count ++;
		    return;
		}
	}
	ptr = malloc(sizeof(struct link));
	strcpy(ptr->word, word);
	ptr->count = 1;
	ptr->next = NULL;

	tail->next = ptr;
	return;

}

