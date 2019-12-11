/*
Author:Aubrey Fernando
Email: ferna190@mail.chapman.edu
Program that uses two threads & two semaphores to simulate a see saw
g++ -std=c++11 -pthread assgin2.cpp -o a.out
 * */
#include <iostream>
#include <thread>
#include <stdio.h>
#include <unistd.h>
#include <mutex>
#include <pthread.h>
#include <condition_variable>

using namespace std;
//mutex lock as binary semaphores
mutex mtxFred;
mutex mtxWilma;
condition_variable cv;

//starting fred & wilma heights
double fredHeight =1;
double wilmaHeight = 7;

//counter time
int curr=0;

void *fredSee(void *);
void *wilmaSaw(void *);

int main(){
  mtxWilma.lock();
  pthread_t thread1;
  pthread_t thread2;
  //sleep(1);
  //create threads
  pthread_create(&thread1, NULL, fredSee, NULL);
  pthread_create(&thread2, NULL, wilmaSaw, NULL);
  //join threads
  pthread_join(thread1,NULL);
  pthread_join(thread2, NULL);
  return 0;
}


//fred see saw actions
void *fredSee(void *){
  int counter =0;
  //up & down 10 times
  while(counter<10){
    ++counter;
    //acquire fred
    mtxFred.lock();
    while(fredHeight < 7){
      curr++;
      cout<<endl;
      fredHeight+=1;
      wilmaHeight-=1;
      cout<<"TIME:"<<curr<<endl;
      cout << "Fred's Height: " << fredHeight << endl;
      cout << "Wilma's Height: " << wilmaHeight << endl;
      cv.notify_all();
      sleep(1);
    }
    //wilma release
  mtxWilma.unlock();
  cout<<"DOWN"<<endl;;
  }
}

//wilma thread
void *wilmaSaw(void *){
  int counter=0;
  while(counter<10)
  {
    ++counter;
    //acquire wilma
    mtxWilma.lock();
    while(wilmaHeight <7)
    {
      curr++;
      fredHeight-=1.5;
      wilmaHeight+=1.5;
      cout<<endl;
      cout<<"TIME:"<<curr<<endl;
      cout << "Fred's Height: " << fredHeight << endl;
      cout << "Wilma's Height: " << wilmaHeight << endl;
      cv.notify_all();
      sleep(1);
    }
    //fred relase
    mtxFred.unlock();
    cout<<"UP"<<endl;
  }
}
