#include <iostream>
#include <unistd.h>
#include <fstream>
#include <math.h>
#include <sstream>
#include <stdio.h>

using namespace std;

void readPage(int block, char buf[11]);
void writePage(int block, char buf[11]);



struct virtualMemory{
	int pageTable[10]; //form pb where p is page frame and b is present bit
	char pages[3][11];
	int currentFrame;
} virtualMem;

char pageTableLookup(int address, virtualMemory *vm);

int main(){

//	int pageTable[] = {0,0,0,0,0,0,0,0,0,0};

	for(int i =0;i<9;i++)
		virtualMem.pageTable[i] = -1;

	virtualMem.currentFrame = 0;

	virtualMemory *vmp = &virtualMem;

	char byte;
	for(int i=0;i<100;i++){
		printf("%c",pageTableLookup(i, &virtualMem));
		//pageTableLookup(i, &virtualMem);
	}

	//char page[11];
//	readPage(1, page);
//	string value(page);
	//cout << value << endl;

	// printf("\n");

//	char page[11];
//
//	cout << "reading page 3: " ;
//	readPage(3, page);
//	string value(page);
//	cout << value << endl;
//
//	cout << "writing page 3: " ;
//	char newPage[11] = "cccccccccc";
//	writePage(3, newPage);
//
//	cout << "reading page 3: " ;
//	readPage(3, page);
//	string value3(page);
//	cout << value3 << endl;

	return 0;
}

void readPage(int pageNum, char buf[11]){
		FILE *pFile;

		char page[11];

		pFile = fopen("memory.txt", "r");
		if(pFile == NULL){cout << "error" << endl; return ;}

		//get to the block
		fseek(pFile, 10*(pageNum-1), SEEK_SET);

		//save the page to ram
		fgets(page, 11, pFile);

		fclose(pFile);

		//return the page
		strncpy(buf, page, 11);
		return;
}


void writePage(int pageNumber, char buf[11]){
		FILE *pFile;

		pFile = fopen("memory.txt", "r+");
		if(pFile == NULL){cout << "error" << endl; return ;}

		//get to the page
		fseek(pFile, 10*(pageNumber-1), SEEK_SET);

		//write page to disk
		fputs(buf, pFile);

		fclose(pFile);

		return;
}




char pageTableLookup(int address, virtualMemory *vm){
	int page = floor(address/10);
	int offset = address % 10;

	int pageTableEntry = vm->pageTable[page];

	if(pageTableEntry >= 0)
		return vm->pages[page][offset];

	int currentPageFrame = vm->currentFrame%3;

	readPage(page+1, vm->pages[currentPageFrame]);

	vm->pageTable[page] = currentPageFrame;

	for(int i =0 ;i<10;i++){
		int pf = vm->pageTable[i];
		if(pf == currentPageFrame){
			vm->pageTable[i] = -1;
		}
	}

	vm->currentFrame ++;

	return vm->pages[currentPageFrame][offset];

}
