/*******************************************************************
*   main.cpp
*   Poornima ByreGowda
*   Programming Assignment  demonstrating the usage of The Hashing Function
*   
*   This program is entirely my own work
*******************************************************************/


#pragma once
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <string.h>
#include "Hashing.h"
#define TABLESIZE     95
#define KEYSIZE       4
#define EMPTYKEY      "----"
#define DATAFILE      "P4DATA.TXT"
int  hashIndex, probeDec;
using namespace std;

void InitTable(HashStruct hashT[], int TableSize)
      {
          int i;
	
          for(i=0; i<TableSize; i++)
          {
              strcpy_s(hashT[i].key, EMPTYKEY);
              hashT[i].data = 0;
          }
      }

int Hash_1(char *Key)
{
	int hashIndex = (Key[0] + Key[1] + Key[2] + Key[3])% TABLESIZE;
	  //cout<< " hashIndex1 "<< hashIndex;
     return hashIndex;
}
int Hash_2(char *Key)
{
	int hashIndex= ((Key[0] * Key[1]) + (Key[2] * Key[3])) % TABLESIZE;
	//cout<<" hashIndex2  "<<hashIndex;
	return hashIndex;
}
int Hash_3(char *Key)
{
	int hashIndex = (Key[1]+Key[2]) % TABLESIZE;
	//cout<<" hashIndex3 "<<hashIndex;
	return hashIndex;
}

int ProbeDec_1(char *Key)
{
	//cout<< "  ProbeDec_1 "<< "1";
	return 1;
	
}
int ProbeDec_2(char *Key)
{  
	
	int ProbeDec_2 = ( Key[0]+ Key[1]+Key[3]+Key[4]) / TABLESIZE;
	//cout<< "ProbeDec_2  " <<ProbeDec_2;
	return ProbeDec_2;
	
}
int ProbeDec_3(char *Key)
{
	int ProbeDec_3 =  (Key[0] * Key[1]) / TABLESIZE;
	//cout<< "ProbeDec_3  " <<ProbeDec_3;
	return ProbeDec_3;

}
int HashInsert(HashStruct T[], char *key, int data, int hNum, int dhNum)
      {
            int  testNum = (hNum * 3) + dhNum;
            int  colCount = 0;
            

            switch(testNum)
            {
                  case 0 :  // Hash function 1 -- Double hash 1 (linear probing) 
                            hashIndex = Hash_1(key);
                            probeDec = ProbeDec_1(key); // Function just returns 1 
                            break;
                  case 1 :  // Hash function 1 -- Double hash 2  
                            hashIndex = Hash_1(key);
                            probeDec = ProbeDec_2(key);
                            break;
                  case 2 :  // Hash function 1 -- Double hash 3  
                            hashIndex = Hash_1(key);
                            probeDec = ProbeDec_3(key);
                            break;
                  case 3 :  // Hash function 2 -- Double hash 1 (linear probing)  
                            hashIndex = Hash_2(key);
                            probeDec = ProbeDec_1(key); // Function just returns 1
                            break;
                  case 4 :  // Hash function 2 -- Double hash 2  
                            hashIndex = Hash_2(key);
                            probeDec = ProbeDec_2(key);
                            break;
                  case 5 :  // Hash function 2 -- Double hash 3  
                            hashIndex = Hash_2(key);
                            probeDec = ProbeDec_3(key);
                            break;
                  case 6 :  // Hash function 3 -- Double hash 1 (linear probing)  
                            hashIndex = Hash_3(key);
                            probeDec = ProbeDec_1(key); // Function just returns 1
                            break;
                  case 7 :  // Hash function 3 -- Double hash 2  
                            hashIndex = Hash_3(key);
                            probeDec = ProbeDec_2(key);
                            break;
                  case 8 :  // Hash function 3 -- Double hash 3  
                            hashIndex = Hash_3(key);
                            probeDec = ProbeDec_3(key);
                            break;
    }

			// Find a place to insert into the table
            while(strcmp(T[hashIndex].key, EMPTYKEY) != 0)
            {
                  colCount++;
                  hashIndex -= probeDec;  // Decrementing was chosen you could also choose to
                  if(hashIndex < 0)    //  increment and wrap back to the beginning of the table.
                       hashIndex = hashIndex + TABLESIZE;
            }
			strcpy(T[hashIndex].key,key);
			T[hashIndex].data = data;
			//cout << "\n"<< T[hashIndex].key<< "\t" << T[hashIndex].data<< "\t";
			return colCount;
}



void main()
{

	 ofstream myfile;
     myfile.open ("P4Results.txt"); 

	
     int  i, hashNum, dHashNum, count;
     ifstream     *inFile;
     HashStruct   T[100];   // Hash table srray of 100 data structures
     char         line[64]; // Array to hold lines read from file
     char         key[5];   // Array to hold 4-character keysHashInsert
     int          data;    // Integer data
	 char filename[100];

	 strcpy(filename,DATAFILE);
	 myfile<< " The Programming4 assignment output is as follows"; 


//==============================================================================
      /* --- Snippet 2: The following code can be used to perform the 9 tests. Use 
                        hashNum to increment a loop for each of 3 hash functions and 
                        dHashNum to increment a nested loop for each of 3 double 
                        hash functions. --- */
				
      // For each of three hash functions//
      for(hashNum = 0; hashNum < 3; hashNum++)
      {
         // For each of three double hash functions
         for(dHashNum = 0; dHashNum < 3; dHashNum++)
         {
            InitTable(T, TABLESIZE);               // Call function to initialize table to empty
            inFile = new ifstream();
            inFile->open(filename, ifstream::in);   // Open data file for this test
            if(!inFile->is_open())
            {
               cout << "Unable to open data file. Program terminating\n";
               return;
            }
            count = 0;     // Initialize collision counter
            for(i = 0; i < 50; i++)
            {
                 inFile->getline(line, 64, '\n');
                 sscanf(line, "%s %d", key, &data);
                 count += HashInsert(T, key, data, hashNum, dHashNum);
				 //cout << " count " << count;
                 // Note: The HashInsert() function uses the indices of hashNum and
                 // dHashNum to know which hash function and double hash function to call
                 // in this test.
            }

			//==============================================================================
       /* --- Snippet 3: This code shows how to create a diagram of the results of a single
          test using one hash function and one double hash function.  The resulting
          diagram looks similar to the sample below with '|' representing a slot where
          a key hashed or double hashed to and '-' representing an empty slot:
          ||-||||---|||-|-||||||||-----||-|-||---||||--|-|||...etc.  --- */
	  
      myfile<<"\n";
      cout << "\nTesting hash function " << hashNum << " using double hash " << dHashNum << ".\n";
      cout << "Total collisions = " << count << ".\n";
	  myfile << "\nTesting hash function " << hashNum << " using double hash " << dHashNum << ".\n";
      myfile << "Total collisions = " << count << ".\n";
      // Show the form of the array
      for(int i=0; i < 100; i++)
          if(strcmp(T[i].key, EMPTYKEY)) // strcmp gives a non-zero (true) result if Key is NOT the EMPTYKEY
		  {
			  cout << "|";     // Indicate an entry at this location
	          myfile << "|";
		  }
       else
           {
			   cout << "-";     // Indicate no entry at this location
	          myfile << "-";
		  }
      cout << "\n\n";

            inFile->close();		/* Close the text file */
            delete inFile;
         }
      }
	  myfile<<endl;
	  getchar();
	  myfile.close();
}