#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	//get user input and store it to a character array
	printf("Enter the password you would like to crack: \n");
	struct timeval stop, start;

	char b[10];
    	int i,j;
    	while( (b[i++]=getchar()) != '\n' && i < 10) /* take input from user until it's a newline or equal to 10 */
        ;
     	b[i] = '\0';
     	i = 0;
     	while(b[i] != '\0')
        printf("%c",b[i++]);
        printf("\n");
	//printf("runs to here");
	//input from file the library and store it in a character array
	 FILE *ptr_file;
  	char wordlist[100000][20];
  	ptr_file = fopen("100000Passwords.txt","r");
  	if(!ptr_file)
      		return 1;


  	for(i=0; fgets(wordlist[i], 100000, ptr_file)!= NULL;i++)
        	;
  	fclose(ptr_file);
    	printf("\n");

  	// Compare the given password with the wordlist

    int boolContinue = 1;
    int passCount = 0;
    int currentWordCount = 0;

    int lenPass = strlen(b);
    lenPass = lenPass - 1;
    //printf("%d\n", lenPass);
    int lenWord = 0;

	gettimeofday(&start, NULL);
	for (i = 0; i < 100000; i++)
	{
        lenWord = strlen(wordlist[i]) - 1;
		while (boolContinue == 1)
		{
		    //printf("%d ", lenWord);
		    //printf("%d\n", sizeof(wordlist[i]));
			if (lenPass == lenWord)
			{
				for (j = 0; j < lenPass; j++)
				{
					if (wordlist[i][j] != b[j])
					{
						boolContinue = 0;
						break;
					}
				}
				if (boolContinue == 0) { break; }
				printf("\nYour library match was : ");
				printf("%s",wordlist[i]);
			}
			boolContinue = 0;
		}
		boolContinue = 1;
	}

    gettimeofday(&stop, NULL);
    printf("took %lu milliseconds\n", stop.tv_usec - start.tv_usec);
    printf("\n");

	return(0);
}