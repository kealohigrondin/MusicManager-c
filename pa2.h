#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

typedef struct duration
{
	int min;
	int sec;
}Duration;

typedef struct record
{
	char artist[20];
	char album[20];
	char title[20];
	char genre[20];
	Duration length;
	int plays;
	int rating;
}Record;

typedef struct node
{
	Record song;
	struct node *pPrev;
	struct node *pNext;
}Node;

void displayMenu();
int getMenuOption();
Node *makeNode(Record newRecord);
Record *makeSong(char *line);
void printRecord(Node *pMem);
int insertAtFront(Node **pList, Record newRecord);
void storeRecords(Node *pList, FILE* outfile);
void displayRecord(Node *pList, int type, char *name);
void editRecord(Node** pList, char *artist);
void rateSong(Node** pList, char* artist);
void playSong(Node *pList, char *name);
void wait(int seconds);

