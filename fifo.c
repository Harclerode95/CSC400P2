// Catriona Reynolds  rey9672@calu.edu
// Tyler Harclerode   har9688@calu.edu
// CSC 400 - Operating Systems
// First-In-First-Out Programming Assignment 2
// Last Updated: 4/22/2018
// Compilation Instruction:	gcc fifo.c -o fifo
// Execution Instruction:	./fifo samplefile.txt
// Note: samplefile.txt must exhist in current directory

#include "stdio.h"
#include "unistd.h"
#include "time.h"
#include <stdlib.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 

#define PFRAME 10
#define MAXPAGES 1000
//Assume that the program will be assigned 5 page frames

void Error(char * msg){
  printf("%s \n", msg);
  exit(0);
}

// Check if page is in memory ( 1 = yes, 0 = no )
int pageinmem(int * mem, int page){
	int i;
	for (i=0; i<PFRAME; i++)
		if (mem[i] == page) return 1;
  
	return 0;
}

// Load page into memory
void load(int * mem, int page){
	int i;

	for (i=0; i<PFRAME; i++)
		// Is current memory slot holding page?
		if (mem[i] == -1) {
			// If not, store this page
			mem[i]=page;
			return;
		}	
}

// List the memory
void listmemory(int * mem){
	int i;

	for (i=0;i<PFRAME; i++)
		// If page is in memory slot, print it
		if (mem[i]!=-1) printf("[%c]", mem[i]);
		// Otherwise, print -1 (no page in memory slot)
		else printf("[-1]");
  
	printf("\n");
	return;
}

// First in First out page replacement
void fifo_replace(int * mem, int page){
	int i;
	
	for (i=0; i<PFRAME-1; i++){
		mem[i] = mem[i+1];
	}
	
	// Newest page always placed in end
	mem[PFRAME-1] = page;
}

/* Get pagereferences from txt file 
char* get_pages_from_file(char * filename, char buff[]){
	//buff = malloc(sizeof(char) * 1000);
	FILE *page_file;
	if ((page_file = fopen(filename,"r")) == NULL){
		printf("Error opening file");
	}
	fscanf(page_file, "%s", buff[]);
	return buff;
}
*/
	
	
int main(int argc, char * argv[]){
	int i, pagefault = 0, pagefault = 0, totalpage = 0;
	int memory[PFRAME];

	char page;
	int eof = 0;
	FILE *fptr;
	
// Open file
	fptr = fopen(argv[1],"r");
	if(fptr == NULL) {
	   perror("ERROR opening file");
	   return(-1);
	}

	
// While not the end of file
	while(pagereference != EOF){

		
		// Memory starts out as list of -1
		for (i=0;i<PFRAME;i++) memory[i] = -1;
		
 		// Reset total pages
    		totalpage = 0;

   		// Read the first char
    		pagereference = fgetc(fptr);
	
	
    		while (pagereference != '\n' && pagereference != EOF) {
	  		// Transfer page
			page = pagereference;  
			printf("%c", page);

			
			// Is the page in memory?
			if (!pageinmem(memory, page)) {
				// If not, update pagefault (number of faults)
				printf("(_)");
				pagefault++;
			
				// Is memory full?
				if (memory[PFRAME - 1] != -1)
					fifo_replace(memory, page);
				else{ 
					load(memory, page);	
					listmemory(memory);
				}
			}	
			// Page exists
			else printf("(+)");
			
	 		// Increment total page
			totalpage += 1;	    	

	 		// Get next char
	    		pagereference = fgetc(fptr);
		}
	
   	   // Check for end of file		
    	   if(pagereference == EOF){
		eof = 1;
		printf("\nEnd of file found\n");
    	   }
    	   else{
    		printf("\n Total page fault rate is %f\n\n",(float)pagefault/totalpage);
	   }	
	}
	
	fclose(fptr);
	return 1;

}
