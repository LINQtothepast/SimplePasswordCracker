#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

//console line to compile =
//	mpicc MPIProject.c
//console line to run =
//	mpirun -n 10 ./a.out

int main(int argc, char **argv){

	int x=-1;
	int myrank,msgtag=0;
	int num_procs;
	MPI_Status status;
	char b[10];
	char wordlist[100000][20];
    	int i, j;
	int boolContinue = 1;
    	int passCount = 0;
    	int currentWordCount = 0;
	int lenPass, lenWord;
	int passwordFound = 0;
	struct timeval stop, start;

	if(MPI_Init(&argc,&argv) != MPI_SUCCESS){
		printf("MPI-INIT Failed\n");
		return 1;
	}
	
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
	MPI_Comm_size(MPI_COMM_WORLD,&num_procs);
	if (myrank == 0) 
	{
		//get user input and store it to a character array
		printf("Enter the password you would like to crack: \n");

    		while( (b[i++]=getchar()) != '\n' && i < 10) /* take input from user until it's a newline or equal to 10 */
        	;
     		b[i] = '\0';
     		i = 0;
     		while(b[i] != '\0')
        	printf("%c",b[i++]);
        	printf("\n");

		lenPass = (strlen(b)-1);
		MPI_Send(&lenPass, 1, MPI_INT, 1, msgtag, MPI_COMM_WORLD);
		MPI_Send(&b, lenPass, MPI_CHAR, 1, msgtag, MPI_COMM_WORLD);
		
		
		//input 1st half
	 	FILE *ptr_file;
  		ptr_file = fopen("100000Passwords.txt","r");
  		if(!ptr_file)
      		return 1;

		for(i=0; fgets(wordlist[i], 100000, ptr_file)!= NULL;i++)
        	;
  		fclose(ptr_file);

    		//printf("\n");
		//printf("password length is %d\n", lenPass);
		
		gettimeofday(&start, NULL);
		for (i = 0; i<50000; i++)
		{
       			lenWord = (strlen(wordlist[i])-1);
			while (boolContinue == 1)
			{
		    		//printf("%d ", (lenWord));
		    		//printf("%d\n", sizeof(wordlist[i]));
				if (lenPass == (lenWord))
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
					printf("\nYour library match found by %d was : %s\n", myrank,wordlist[i] );
					//printf("%s",wordlist[i]);
					passwordFound = 1;
				}
				boolContinue = 0;
				if (passwordFound == 1) { break; }
			}
			boolContinue = 1;
			if (passwordFound == 1) { break; }
		}

    		gettimeofday(&stop, NULL);
		
		if (passwordFound == 1)
		{
		printf("Core %d ", myrank);
		printf("took %lu milliseconds\n", stop.tv_usec - start.tv_usec);
		}
    		//printf("\n");
	}
	if (myrank != 0)
	{
		MPI_Recv(&lenPass,1,MPI_INT,0,msgtag,MPI_COMM_WORLD,&status);
		MPI_Recv(&b,lenPass,MPI_CHAR,0,msgtag,MPI_COMM_WORLD,&status);
		//printf("%s\n", b);
		
		//input 2nd half
	 	FILE *ptr_file;
  		ptr_file = fopen("100000Passwords.txt","r");
  		if(!ptr_file)
      		return 1;

		for(i=0; fgets(wordlist[i], 100000, ptr_file)!= NULL;i++)
        	;
  		fclose(ptr_file);

    		//printf("\n");
		//printf("password length is %d\n", lenPass);
		
		gettimeofday(&start, NULL);
		for (i = 50000; i<100000; i++)
		{
       			lenWord = (strlen(wordlist[i])-1);
			while (boolContinue == 1)
			{
		    		//printf("%d ", (lenWord));
		    		//printf("%d\n", sizeof(wordlist[i]));
				if (lenPass == (lenWord))
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
					printf("\nYour library match found by %d was : %s\n", myrank,wordlist[i]);
					//printf("%s",wordlist[i]);
					passwordFound = 1;
				}
				boolContinue = 0;
				if (passwordFound == 1) { break; }				
			}
			boolContinue = 1;
			if (passwordFound == 1) { break; }
		}
		
		gettimeofday(&stop, NULL);
		if (passwordFound == 1)
		{
		printf("Core %d ", myrank);
		printf("took %lu milliseconds\n", stop.tv_usec - start.tv_usec);
		}
    		//printf("\n");		
	}

	MPI_Finalize();
}
