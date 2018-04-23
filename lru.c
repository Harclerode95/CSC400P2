// Catriona Reynolds  rey9672@calu.edu
// Tyler Harclerode   har9688@calu.edu
// CSC 400 - Operating Systems
// Least-Recently-Used Programming Assignment 2
// Last Updated: 4/22/2018
// Compilation Instruction:	gcc lru.c -o lru
// Execution Instruction:	./lru samplefile.txt
// Note: samplefile.txt must exhist in current directory

#include "stdio.h"
#include "unistd.h"
#include "time.h"
#include "stdlib.h" //required for random()
#include <sys/ipc.h> 
#include <sys/msg.h> 

#define PFRAME 10 // 10 pages per frame


void Error(char * msg){
  printf("%s \n", msg);
  exit(0);
}

// Check if page is in memory ( 1 = yes, 0 = no )
int pageinmem(int * mem, int * intu, int page){
	int i;
	for (i=0; i<PFRAME; i++)
		if (mem[i] == page){
/*If already in memory reset Intuition*/
			intu[i] = 0;
/**************************************/
			return 1;
		}
	return 0;
}

// Load page into memory
void load(int * mem, int * intu, int page){
	int i;

	for (i=0; i<PFRAME; i++)
		// Is current memory slot holding page?
		if (mem[i] == -1) {
			// If not, store this page
			mem[i]=page;
/*********Set intution*********/
			intu[i]=0;
/******************************/
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

//Update intuition array
void update(int * intu){
	int i;
	
	for(i=0;i<PFRAME;i++)
		//increment intuition array
		intu[i] += 1;
	return;
}

int lru_replace(int * mem, int * intu){
	int i;
	//Initialize maximum element
	int max = intu[0];
	//Initialize max value location
	int location = 0;
	
	for(i=1;i<PFRAME;i++)
		if(intu[i] > max){
			max = intu[i];
			location = i;
		}
	
	//Return the location of the page with the greatest Intuition
	return location;
	
}
	
int main(int argc, char * argv[]){
	int i, toreplace, pagefault = 0, totalpage = 0;
	int memory[PFRAME];
/*added intuition array parallel to memory*/
	int intuition[PFRAME];
/******************************************/
	char page, pagereference;
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
    for (i=0;i<PFRAME; i++) memory[i] = -1; 

   // Reset total pages
    totalpage = 0;

   // Read the first char
    pagereference = fgetc(fptr);
	
	
    while (pagereference != '\n' && pagereference != EOF) {
	  // Transfer page
		page = pagereference;  
		printf("%c", page);

	  //Call update for intuition queue
	       update(intuition);
		
	  // Is the page in memory?
		if (!pageinmem(memory, intuition, page)) {
		  // If not, update pagefault (number of faults)
			pagefault++;
			
		  // Is memory full?
			if (memory[PFRAME - 1] != -1) {
/*Call fn() to find page to replace*/
				toreplace = lru_replace(memory, intuition);
/***********************************/
				printf("(M));
			  // Replace:
				memory[toreplace] = page;
/***Reset intuition for new page***/
				intuition[toreplace] = 0;
/**********************************/
			}
			
			else {
				printf("(M)");
				load(memory, intuition, page);
				
		}
	  // Page exists
		else	
			printf("(H)");

	 // List the memory
	       listmemory(memory);
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
	printf("\n Page Faults = %d , total pages = %d",pagefault,totalpage);    
	printf("\n Total page fault rate is %f\n\n",(float)pagefault/totalpage);
    }
  }	
	
	fclose(fptr);
	return 1;

}
