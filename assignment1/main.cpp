#include <pthread.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>



using namespace std;
string theArray[9][9];

void makeGridFrmFile(string file);
void print();
bool findMissing(string s);
void *checkVertical(void *);
void* checkHorizontal(void *);
void* checkSub(void *);
void * checksub(void *);
int stringToInt(string s);

int main(int argc, char* argv[])
{
  //check if file was inputted
  if(argc < 2)
  {
    cout<<"No file given. EXIT" <<endl;
    exit(0);
  }
  else{
    //go to file inputted
    string inFile  = argv[1];
    makeGridFrmFile(inFile);
    pthread_t theThread[3];
    for(int i=0;i<3;++i)
    {
      switch(i)
      {
        case 0:
        pthread_create(&theThread[0], NULL, checkVertical, NULL);
        case 1:
        pthread_create(&theThread[1],NULL, checkHorizontal, NULL);
        case 2:
        pthread_create(&theThread[2],NULL,checksub,NULL);
        break;
      }
    }
    for(int i=0;i<3;++i)
    {
      pthread_join(theThread[i],NULL);
    }
  /*  pthread_t threadCol;
    pthread_t threadRow;
    pthread_t threadSub;
    pthread_create(&threadCol, NULL, checkVertical, NULL);
    pthread_create(&threadRow,NULL, checkHorizontal, NULL);
    pthread_create(&threadSub,NULL,checksub,NULL);
  /*  switch(i) {
      case 0:
        pthread_create(theThreads[0], NULL, vScan, NULL);
        break;
      case 1:
        pthread_create(&theThreads[1], NULL, hScan, NULL);
        break;
      case 2:
        pthread_create(&rheThreads[2], NULL, sScan, NULL);
        break;
        for(int i = 0; i < 3; ++i)
        {
        pthread_join(theThreads[i], NULL);
        }
    }
    pthread_join(threadCol, NULL);
    pthread_join(threadRow,NULL);
    pthread_join(threadSub,NULL);*/
  }
}

void print()
{
  for(int x=0; x<9; x++)
  {
    for(int y=0;y<9;y++)
    {
      cout<<theArray[x][y];
    }
  }
}

void makeGridFrmFile(string file)
{
  ifstream inFile(file.c_str());
  string values;
  int row =0;
  string line;
  while (row <9 &&getline(inFile,line))
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

int stringToInt(string s)
{
  int num  = atoi(s.c_str());
  return num;
}


void *checkVertical(void *)
{
  int dupArray[9];
  int counter=0;
  for (int i=0; i<10;++i)
  {
    dupArray[i] = i;
  }
  for(int y=0; y<9;++y)
  {
    for(int x=0;x<9;++x)
    {
      counter=0;
      for(int j=0;j<9;++j)
      {
        if(stringToInt(theArray[j][x])==dupArray[y]){
          counter++;
      }
      if(counter>=2)
        {
        cout<<endl<<"Error at row:"<<j+1<<" | column:"<<x+1<<endl;
        cout<<"Vertical Duplicated value:"<<theArray[j][x]<<endl;
        int sum=0;
        int dup=0;
        int temp=0;
        int missing=0;
        for(int k=0;k<9;k++)
        {
          sum+=stringToInt(theArray[x][k]);
        }
        dup = stringToInt(theArray[j][x]);
        temp = sum-dup;
        missing  = 45-temp;
        cout<<"Missing Value:"<<missing<<endl;
        counter=0;
        }
      }
    }
  }
}


void* checkHorizontal(void *)
{
  int dupArray[9];
  int counter=0;
  for (int i=0; i<10;++i)
  {
    dupArray[i] = i;
  }
  for(int y=0; y<9;++y)
  {
    for(int x=0;x<9;++x)
    {
      counter=0;
      for(int j=0;j<9;++j)
      {
        if(stringToInt(theArray[x][j])==dupArray[y]){
          counter++;
      }
      if(counter>=2)
        {
        cout<<endl<<"Error at row:"<<x+1<<"| column:"<<j+1<<endl;
        cout<<"Horizontal Duplicated value:"<<theArray[x][j]<<endl;
        int sum=0;
        int dup=0;
        int missing=0;
        int temp=0;
        for(int k=0;k<9;k++)
        {
          sum+=stringToInt(theArray[x][k]);
        }
        dup = stringToInt(theArray[x][j]);
        temp = sum-dup;
        missing  = 45-temp;
        cout<<"Missing Value:"<<missing<<endl;
        counter=0;
        }
      }
    }
  }
}

bool findMissing(string s)
{
  int num = atoi(s.c_str());
  cout<<num<<endl;
  return true;
}

void*  checksub(void *)
{
  int dupArray[9];
  int counter=0;
  for (int i=0; i<10;++i)
  {
    dupArray[i] = i;
  }

  for(int i=0; i<9; i+=3)
  {
    for(int j=0; j<9;j+=3)
    {
      int block = (((i/3)*3)+(j/3));
      int subgrid[3][3];
      int newRow=0;
      for(int k=i;k<(i+3);k++)
      {
        int newCol =0;
        cout<<endl;
        //counter=0;
        for(int l=j;l<(j+3);l++)
        {
          subgrid[newRow][newCol] = stringToInt(theArray[k][l]);
        }

      }

      newRow++;
      cout<<endl;
    }
  }

}
void* checkSub(void *)
{
  int dupArray[9];
  int counter=0;
  for (int i=0; i<10;++i)
  {
    dupArray[i] = i;

  }
  for(int i=6;i>=0;i-=3)
  {
    for(int j=6;j>=0;j-=3)
    {
      string subgrid[9];
      int n=0;
      counter=0;
      cout<<endl;
      for(int x=i; x<i+3;++x)
      {
        for(int y=j;y<j+3;++y){
          subgrid[n]= theArray[x][y];
          cout<<subgrid[n];
          ++n;
        }
      }
      for(int m=0;m<9;m++)
      {
        if(stringToInt(subgrid[m])==dupArray[m])
        {
          cout<<subgrid[m];
          cout<<"("<<i<<i<<")";
          counter++;
        }
      }
      if(counter>=2)
      {
       cout<<endl<<"Error in range("<<i<<","<<i<<")"<<
       "to ("<<j<<","<<j<<")"<<endl;
      //  cout<<endl<<"Error at row:"<<j<<"| column:"<<i<<endl;
        cout<<"Subgrid Duplicated value:"<<theArray[j][i]<<endl;
      /*  int sum=0;
        int dup=0;
        int missing=0;
        int temp=0;
        for(int k=0;k<9;k++)
        {
          sum+=stringToInt(theArray[x][k]);
        }
        dup = stringToInt(theArray[x][j]);
        temp = sum-dup;
        missing  = 45-temp;*/
        //cout<<"Missing Value:"<<missing<<endl;
        //counter=0;
      }
    }

  }
}
