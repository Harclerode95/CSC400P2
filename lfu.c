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
int pageinmem(int * mem, int * intu, int page){
	int i;
	for (i=0; i<PFRAME; i++)
		if (mem[i] == page){
/*If already in memory inc Intuition*/
			intu[i] += 1;
/**************************************/
      return 1;
    }
  
	return 0;
}

// Load page into memory
void load(int * mem, int * intu int page){
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

int lfu_replace(int * mem, int * intu){
	int i;
	//Initialize minimum element
	int min = intu[0];
	//Initialize min value location
	int location = 0;
	
	for(i=1;i<PFRAME;i++)
		if(intu[i] < min){
			min = intu[i];
			location = i;
		}
	
	//Return the location of the page with the greatest Intuition
return location;
  
  return location;
}

int main(int argc, char * argv[]){
	int i, page, toreplace, pagefault = 0, totalpage = 0;
	int memory[PFRAME];
/*added intuition array parallel to memory*/
	int intuition[PFRAME];
/******************************************/
	char pagereference[21]="ABCDEEDBCFJKMCBFFCMA";
	//  char pagereference[21]="ABCDEFGHIJKLMNOPQRST";
	
   // Memory starts out as list of -1
    for (i=0;i<PFRAME; i++) memory[i] = -1;
	
    for (i=0;i<20; i++) {
	  // Everytime read a page
		page = pagereference[i];  
		printf("%c", page);
		
	  // Is the page in memory?
		if (!pageinmem(memory, intuition, page)) {
		  // If not, update pagefault (number of faults)
			pagefault++;
			
		  // Is memory full?
			if (memory[PFRAME - 1] != -1) {	
/*Call fn() to find page to replace*/        
				toreplace = lfu_replace(memory, intuition);
/***********************************/
				printf("(M)   ->%d   ", toreplace + 1);
			  // Replace:
				memory[toreplace] = page;
/***Reset intuition for new page***/
				intuition[toreplace] = 0;
/**********************************/
			}
			
			else 
				load(memory, intuition, page);
				listmemory(memory);
		}
	  // Page exists
		else printf("(H)\n");	
		}
	
    printf("\n Total page fault rate is %f\n",(float)pagefault/20);

	return 1;

}
