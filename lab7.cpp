#include <iostream>
#include <unistd.h>
#include <fstream>
#include <math.h>
#include <sstream>
#include <stdio.h>

using namespace std;

void read(int address, char buf[10]);
void write(int address, char buf[10]);

int main(){

	char byte[10];

	cout << "reading block 3, offset 4, should read 00011000: " ;
	read(304, byte);		
	string value(byte);
	cout << value << endl;

	cout << "writing block 3, offset 4, to 11111111" << endl;
	char toWrite[10] = "11111111\n";
	write(304, toWrite);

	cout << "reading block 3, offset 4, should read 11111111: ";
	read(304, byte);		
	string value2(byte);
	cout << value2 << endl;

	//comment out this section to check the memory file to make sure it was updated
	cout << "writing block 3, offset 4, back to 00011000: " << endl;
	char original[10] = "00011000\n";
	write(304, original);

	cout << "reading block 3, offset 4, should read 00011000: ";
	read(304, byte);		
	string value3(byte);
	cout << value3 << endl;

	return 0;
}

//format is page as the hundred/thousands digit, offset as the tens/ones digits
void read(int address, char buf[10]){
		FILE *pFile;

		char	line[10], //10 to accomodate \n and \0
					block[10][10];

		//compute the page
		int page = floor(address/100);

		//compute the offset
		int offset = address%100;

		pFile = fopen("memory.txt", "r");
		if(pFile == NULL){cout << "error" << endl; return ;}

		//get to the block
		fseek(pFile, 9*(page-1)*10, SEEK_SET);

		//save the block to ram
		for(int y=0;y<10;y++){
			fgets(line, 10, pFile);
			strncpy(block[y], line, 10);
		}

		fclose(pFile);

		//return the byte based on offset
		strncpy(buf, block[offset-1], 8);
		return;
}


void write(int address, char buf[10]){
		FILE *pFile;

		char	line[10], //10 to accomodate \n and \0
					block[10][10];

		//compute the page
		int page = floor(address/100);

		//compute the offset
		int offset = address%100;

		pFile = fopen("memory.txt", "r+");
		if(pFile == NULL){cout << "error" << endl; return ;}

		//get to the block
		fseek(pFile, 9*(page-1)*10, SEEK_SET);

		//save the block to ram
		for(int y=0;y<10;y++){
			fgets(line, 10, pFile);
			strncpy(block[y], line, 10);
		}

		fclose(pFile);

		//copy the information to be written to the block
		strncpy(block[offset-1], buf, 10);

		//open the file again to write
		pFile = fopen("memory.txt", "r+");
		//get to the block
		fseek(pFile, 9*(page-1)*10, SEEK_SET);
		//write block back to disk
		for(int i=0;i<10;i++){
			fputs(block[i], pFile);
		}
		
		fclose(pFile);

		return;
}
