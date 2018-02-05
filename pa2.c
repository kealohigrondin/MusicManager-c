#include "pa2.h"



void displayMenu()
{
	printf("MAIN MENU:\n\n(1) Load\n(2) Store\n(3) Display\n(4) Insert\n(5) Delete\n"
		"(6) Edit\n(7) Sort\n(8) Rate\n(9) Play\n(10) Shuffle\n(11) Exit\n");
}

int getMenuOption()
{
	int option = 0;
	printf("ENTER OPTION: ");
	scanf("%d", &option);
	if (option != 1 && option != 2 && option != 3 && option != 4 && option != 5 &&
		option != 6 && option != 7 && option != 8 && option != 9 && option != 10 && option != 11)
	{
		printf("ERROR: Enter valid value\n");
		option = getMenuOption();
	}
	return option;
}

Node *makeNode(Record newRecord)
{
	Node *pMem = NULL;
	pMem = (Node *)malloc(sizeof(Node)); //allocates space for a Node
	
	if (pMem != NULL) //malloc functioned properly and allocated memory for pMem
	{
		pMem->pNext = NULL;
		pMem->pPrev = NULL;
		pMem->song = newRecord;
	}
	return pMem;
}

Record *makeSong(char *line)
{
	Record *song = NULL;
	char *length = NULL, lengthMin = NULL;
	song = (Record*)malloc(sizeof(Record));
	strncpy(song->artist, strtok(line, ","), 30);
	strncpy(song->album, strtok(NULL, ","), 30);
	strncpy(song->title, strtok(NULL, ","), 30);
	strncpy(song->genre, strtok(NULL, ","), 30);
	length = strtok(NULL, ",");
	song->plays = atoi(strtok(NULL, ","));
	song->rating = atoi(strtok(NULL, ","));
	lengthMin = length[0];
	song->length.min = atoi(&lengthMin);
	length = &length[2];
	song->length.sec = atoi(length);

	return song;
}

void printRecord(Node *pMem)
{
	printf("SONG NAME: %s\n", pMem->song.title);
	printf("   ARTIST: %s\n", pMem->song.artist);
	printf("    ALBUM: %s\n", pMem->song.album);
	printf("    GENRE: %s\n", pMem->song.genre);
	printf(" DURATION: %d:%d\n", pMem->song.length.min, pMem->song.length.sec);
	printf("    PLAYS: %d\n", pMem->song.plays);
	printf("   RATING: %d\n\n", pMem->song.rating);
}

int insertAtFront(Node **pList, Record newRecord) //list operation
{
	Node *pMem = NULL;
	int success = 0;
	
	pMem = makeNode(newRecord);

	if (pMem != NULL)//space allocated
	{
		//connect new node/container to the list
		if (*pList != NULL) //not empty list
		{
			pMem->pNext = *pList;
			(*pList)->pPrev = pMem;
			*pList = pMem;
		}
		else //empty list
			*pList = pMem;
		success = 1;
	}
	return success;
}

void storeRecords(Node *pList, FILE* outfile)
{
	while (pList->pNext != NULL)
	{
		fprintf("playlist.csv", "%s,%s,%s,%s,%d!%d,%d,%d\n", 
			pList->song.artist, pList->song.album, pList->song.title,
			pList->song.genre, pList->song.length.min, pList->song.length.sec,
			pList->song.plays, pList->song.rating);
	}
}

void displayRecord(Node *pList, int type, char *name)
{
	Node *pMem = NULL;
	pMem = pList;
	switch (type)
	{
	case 1://print all records
		while (pMem != NULL)
		{
			printRecord(pMem);
			pMem = pMem->pNext;
		}
		break;
	case 2://print one record that matches an artist
		while (pMem != NULL)
		{
			if (strcmp(pMem->song.artist, name) == 0 )
				printRecord(pMem);
			pMem = pMem->pNext;
		}
		break;
	default:
		printf("\n\ndisplayRecord defaulted\n\n");
		break;
	}
}

void editRecord(Node** pList, char *artist)//might be complete?
{
	Node *pMem = NULL;
	pMem = *pList;
	int option = 0, fieldOp = 0;
	while (pMem->pNext != NULL)//gets matching songs
	{
		if (strcmp(pMem->song.artist, artist) == 0)//matching artist found
		{
			printRecord(pMem);
			printf("Do you want to edit this song?(0 for no, 1 for yes)");			
			scanf("%d", &option);
			if (option == 1)//edits song
			{
				printf("\nWhat field do you want to edit?\n");
				printf("(1)Title\n(2)Artist\n(3)Album\n(4)Genre\n(5)Length\n(6)Plays\n(7)Rating\n");
				scanf("%d", &fieldOp);
				switch (fieldOp)
				{
				case 1:
					printf("Enter new title:");
					scanf("%s", &pMem->song.title);
					break;
				case 2:
					printf("Enter new artist:");
					scanf("%s", &pMem->song.artist);
					break;
				case 3:
					printf("Enter new album name:");
					scanf("%s", &pMem->song.album);
					break;
				case 4:
					printf("Enter new genre:");
					scanf("%s", &pMem->song.artist);
					break;
				case 5:
					printf("Enter new song MINUTE length:");
					scanf("%d", &pMem->song.length.min);
					printf("Enter new song SECOND length:");
					scanf("%d", &pMem->song.length.sec);
					break;
				case 6:
					printf("Enter new number of plays:");
					scanf("%d", &pMem->song.plays);
					break;
				case 7:
					printf("Enter new song rating:");
					scanf("%d", &pMem->song.rating);
					break;
				default:
					printf("\n\nswitch in editRecord defaulted\n\n");
					break;
				}//end switch
			}//end yes/no if
		}//end strcmp if
		pMem = pMem->pNext;//moves to the next song
	}//end while
}

void rateSong(Node** pList, char* artist)
{
	Node *pMem = NULL;
	pMem = *pList;
	int i = 0, option = 0, newRating = 0;
	while (pMem->pNext != NULL)//gets matching songs
	{
		if (strcmp(pMem->song.artist, artist) == 0)//matching artist found
		{
			printf("Do you want to edit this song's rating?(0 for no, 1 for yes)");
			scanf("%d", &option);
			if (option == 1)//edits song
			{
				while (newRating > 5 || newRating < 1)//keeps going until it gets a valid rating
				{
					printf("Enter new rating: ");
					scanf("%d", &newRating);
					pMem->song.rating = newRating;
					if (newRating > 5 || newRating < 1)
						printf("ERROR: invalid rating, must be 1-5\n");
				}
			}
		}
		pMem = pMem->pNext;//moves to the next song
	}
}

void playSong(Node *pList, char *name)
{
	Node* pMem = NULL;
	while (pList != NULL)//gets start of music to play
	{
		if (strcmp(pList->song.artist, name) == 0)
		{
			pMem = pList;
			break;
		}
		pList = pList->pNext;
	}
	while (pMem != NULL)
	{
		printf("NOW PLAYING:\n");
		printRecord(pMem);
		pMem = pMem->pNext;
		wait(2);//2 seconds
	}
}

void wait(int seconds)
{
	clock_t endwait;
	endwait = clock() + seconds*CLOCKS_PER_SEC;
	while (clock() < endwait);
}


