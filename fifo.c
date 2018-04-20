// Replace the page that has been in the system the longest

#include "stdio.h"
#include "unistd.h"
#include "time.h"
#include "stdlib.h" //required for random()
#include <sys/ipc.h> 
#include <sys/msg.h> 

#define PFRAME 5
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

// Replace the page that has been in the system the longest

#include "stdio.h"
#include "unistd.h"
#include "time.h"
#include <sys/ipc.h> 
#include <sys/msg.h> 

#define PFRAME 5
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
	mem[PFRAME-1] = page;
}

// Get pagereferences from txt file 
char* get_pages_from_file(char * filename){
	char* buff;
	FILE *page_file = fopen(filename,"r");
	fscanf(page_file, "%s", buff);
	return buff;
}

	
int main(int argc, char * argv[]){
	int i, page, toreplace, pagefault = 0, totalpage = 0;
	int memory[PFRAME];
	char* pagereference;
	//  char pagereference[21]="ABCDEEDBCFJKMCBFFCMA";
	//  char pagereference[21]="ABCDEFGHIJKLMNOPQRST";
	if (argv[1] != NULL){
		pagereference = get_pages_from_file(argv[1]);
	}
   // Memory starts out as list of -1
    for (i=0;i<PFRAME;i++) memory[i] = -1;
	
    for (i=0;i<sizeof pagereference;i++) {
	  // Every time read a page
		page = pagereference[i];  
		printf("%c", page);
		
	  // Is the page in memory?
		if (!pageinmem(memory, page)) {
		  // If not, update pagefault (number of faults)
			printf("(_)");
			pagefault++;
			
		  // Is memory full?
			if (memory[PFRAME - 1] != -1)
				fifo_replace(memory, page);
			else load(memory, page);	
		}
	  // Page exists
		else printf("(+)");	
	}
	
	// Always list memory
	listmemory(memory);
		
    printf("\n Total page fault rate is %f\n",(float)pagefault/20);

	return 1;

}
