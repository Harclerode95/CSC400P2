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

int pageinmem(int * mem, int page)
{
  int i;

  for (i=0;i<PFRAME; i++)
    if (mem[i] == page) return 1;
  return 0;
}
void load(int * mem, int page)
{
  int i;

  for (i=0;i<PFRAME; i++)
    if (mem[i] == -1) {
	mem[i]=page;
	return;
    }
}
void listmemory(int * mem)
{
  int i;

  for (i=0;i<PFRAME; i++)
    if (mem[i]!=-1) printf("[%c]", mem[i]);
    else printf("[-1]");
  printf("\n");
  return;
}

int main(int argc, char * argv[])
{
  int memory[PFRAME];
//  char pagereference[21]="ABCDEFGHIJKLMNOPQRST";
  char pagereference[21]="ABCDEEDBCFJKMCBFFCMA";


  int i, page, toreplace, pagefault=0, totalpage=0;


    for (i=0;i<PFRAME; i++) memory[i] = -1;
    for (i=0;i<20; i++) {
	page=pagereference[i]; //everytime read a page 

	printf("%c", page);
	  if (!pageinmem(memory, page)) {
		pagefault++;
		if (memory[PFRAME-1] != -1) {//memory is full since pages are allocated from left to right
		  toreplace=(int) ((float)random()/RAND_MAX*PFRAME);
		  printf("(M)   ->%d   ",toreplace+1);
		  //replace
		  memory[toreplace]=page;
		}
		else 
		  load(memory, page);
		listmemory(memory);
	  }
	  else
		printf("(H)\n");	
    }
    printf("\n Total page fault rate is %f\n",(float)pagefault/20);

  return 1;

}
