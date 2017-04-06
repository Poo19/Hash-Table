/*******************************************************************
*   Hsshing.cpp
*   Poornima ByreGowda
*   Programming Assignment 4 demonstrating the usage of the Hash Function
*   
*   This program is entirely my own work
*******************************************************************/



#pragma once
#include <iostream>
#include <fstream>
#include <stdlib.h>

// Define the structure for use in the hash table
struct HashStruct
{
     char key[5];
     int data;
};