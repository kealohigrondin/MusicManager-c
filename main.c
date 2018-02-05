/*
Kealohi Grondin
PA 2 - music player pt 1
January 29 2018

wait function found on quora from user "Jagdishsinh Jadeja"
*/
#include "pa2.h"


int main(void)
{
	int menuOption = 0, success = 0, option = 0;
	Node *pHead = NULL;
	FILE * infile = fopen("playlist.csv", "r");		
	FILE * outfile = fopen("playlist.csv", "w");
	Record newRecord[9] = { NULL };
	char line[100] = { '\0' }, artist[30] = { '\0' };
	while (menuOption != 11)
	{
		displayMenu();
		menuOption = getMenuOption();
		switch (menuOption)
		{
		case 1://load
			printf("Loading songs...");
			wait(4);
			for (int i = 0; i < 9; i++)
			{
				fgets(line, 100, infile);
				newRecord[i] = *makeSong(line);
				insertAtFront(&pHead, newRecord[i]);
			}
			break;
		case 2://store
			printf("Storing songs...");
			storeRecords(pHead, outfile);
			wait(4);
			break;
		case 3://display
			printf("Do you want to display all songs? (1 for yes, 0 for no)");
			scanf("%d", &option);
			if (option == 0)
			{
				printf("Enter artist you want to display:");
				gets(artist);
				//scanf("%s", &artist);
			}
			displayRecord(pHead, option, artist);
			break;
		case 4://insert
			printf("Insert\n");
			break;
		case 5://delete
			printf("Delete\n");
			break;
		case 6://edit
			printf("Enter artist you want to edit:");
			scanf("%s", &artist);
			editRecord(&pHead, artist);
		case 7://sort
			printf("Sort\n");
			break;
		case 8://rate
			printf("Enter artist you want to re-rate:");
			scanf("%s", &artist);
			rateSong(&pHead, artist);
		case 9://play
			printf("Enter artist you want to play:");
			scanf("%s", &artist);
			playSong(pHead, artist);
		case 10://shuffle
			printf("Shuffle\n");
			break;
		case 11://exit
			menuOption = 11;
			break;
		default:
			printf("\n\nswitch defaulted\n\n");
		}//end switch
	}//end while

	fclose(infile);
	fclose(outfile);
}