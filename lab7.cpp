#include <iostream>
#include <unistd.h>
#include <fstream>
#include <math.h>
#include <sstream>
#include <stdio.h>

using namespace std;

void readPage(int block, char buf[11]);
void writePage(int block, char buf[11]);

struct pageTableEntry {
	int pageNumber;	
	int address;
};

int main(){

	char page[11];

	cout << "reading page 3: " ;
	readPage(3, page);		
	string value(page);
	cout << value << endl;

	cout << "writing page 3: " ;
	char newPage[11] = "cccccccccc";
	writePage(3, newPage);		

	cout << "reading page 3: " ;
	readPage(3, page);		
	string value3(page);
	cout << value3 << endl;

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
