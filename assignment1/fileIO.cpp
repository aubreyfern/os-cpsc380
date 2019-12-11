#include "fileIO.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

void fileIO::readFile(string inFile)
{
  //if file doesn't exist
  if(!ifstream(inFile.c_str()))
  {
    cout<<"Invalid File. EXITING"<<endl;
    exit(0);
  }
  else{
    string lines;
    ifstream file(inFile.c_str());
   //ifstream file(inFile);
    char delim = ',';
    string values;
    int row =0;
    string line;
    while (row <9 &&getline(file,line))
    {
      stringstream iss(line);
      int cols=0;
      string value;

      while(cols <9 && getline(iss,value,','))
      {
        theArray[row][cols]=value;
        cols++;
      }
      row++;
    }
    print();
  }
}

void fileIO::print()
{
  for(int x=0; x<9; x++)
  {
    for(int y=0;y<9;y++)
    {
      cout<<theArray[x][y];
    }
  }
}

string fileIO::*getArray(size_of s)
{
	return ret;
}
