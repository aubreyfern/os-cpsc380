#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

class fileIO{

public:
  void readFile(string inFile);
  void print();
  string *getArray(size_of s);
private:
  string theArray[9][9];
};
