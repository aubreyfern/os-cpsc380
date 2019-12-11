/*
Author:Aubrey Fernando
Email: ferna190@mail.chapman.edu
g++ -std=c++11 -pthread assgin3.cpp -o a.out
 * */
#include <iostream>
#include <pthread.h>
#include <sched.h>
#include <vector>
#include <mutex>
#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>

using namespace std;

int board[10][10];

//initialize semaphores
sem_t sme1;
sem_t sme2;
sem_t sme3;
sem_t sme4;

//initialize thread counters
int counter1=0;
int counter2=0;
int counter3=0;
int counter4=0;

//initialize thread overruns
int overrun1=0;
int overrun2=0;
int overrun3=0;
int overrun4=0;

//initialize boolean if running
bool running1 = false;
bool running2 = false;
bool running3 = false;
bool running4 = false;

void doWork();
void print();

//initialize thread functions
void *scheduler(void *);
void *thread1(void *);
void *thread2(void *);
void *thread3(void *);
void *thread4(void *);


 int main()
 {
   //initialize semaphores
  sem_init(&sme1, 0, 0);
  sem_init(&sme2, 0, 0);
  sem_init(&sme3, 0, 0);
  sem_init(&sme4, 0, 0);

//initialize threads
  pthread_t thread_1;
  pthread_t thread_2;
  pthread_t thread_3;
  pthread_t thread_4;
  pthread_t thread_5;

//professor cpuAffinity
  cpu_set_t mask;
  int cpuAffinity = 1;

  CPU_ZERO(&mask);
  CPU_SET(cpuAffinity, &mask);

//create threads
  pthread_create(&thread_1, NULL, thread1, NULL);
  pthread_setaffinity_np(thread_1, sizeof(mask), &mask);


  pthread_create(&thread_2, NULL, thread2, NULL);
  pthread_setaffinity_np(thread_2, sizeof(mask), &mask);

  pthread_create(&thread_3, NULL, thread3, NULL);
  pthread_setaffinity_np(thread_3, sizeof(mask), &mask);

  pthread_create(&thread_4, NULL, thread4, NULL);
  pthread_setaffinity_np(thread_4, sizeof(mask), &mask);

  //create thread scheduler
  pthread_create(&thread_5,NULL, scheduler, NULL);
  pthread_setaffinity_np(thread_5, sizeof(mask), &mask);

//join threads
  pthread_join(thread_1,NULL);
  pthread_join(thread_2,NULL);
  pthread_join(thread_3,NULL);
  pthread_join(thread_4,NULL);
  pthread_join(thread_5,NULL);

 }

//do work function
void doWork(){
  //make board
  int board[10][10];
  for(int x=0; x<9;++x){
    for(int y=0;y<=9;++y){
      board[x][y]=1;
      }
  }
  //board product
  int product =1;
  int cols[]={0, 5, 1, 6, 2, 7, 3, 8, 4, 9};
  for(int x=0; x<=9; x++){
    for(int y=0; y<=9; y++){
      product *=board[cols[x]][y];
    }
  }
}

//scheduler
void *scheduler(void *)
{
  for(int x=0; x<160;++x){
  //T1  - 1 unit
    if(running1){
      overrun1++;
    }
//semaphore signal & not running
    sem_post(&sme1);
    running1 = false;

//tT2 - 2 units
    if(x%2==0)
    {
      if(running2){
        overrun2++;
      }
      sem_post(&sme2);
      running2=false;
    }
//T3- 4 units
    if(x%4==0)
    {
      if(running3){
        overrun3;
      }
      sem_post(&sme3);
      running3 = false;
    }
//T4 - 16 units
    if(x%16==0)
    {
      if(running4)
      {
        overrun4;
      }
      sem_post(&sme4);
      running4 = false;
    }
  }

  //print results at end
      cout <<endl<< "THREAD ONE"<<endl<<"Ran: "<<counter1<<" | Overrun:"<<overrun1<<endl;
      cout <<endl<< "THREAD TWO"<<endl<<"Ran: "<<counter2<<" | Overrun:"<<overrun2<<endl;
      cout <<endl<< "THREAD THREE"<<endl<<" Ran: "<<counter3<<" | Overrun:"<<overrun3<<endl;
      cout <<endl<< "THREAD FOUR"<<endl<<"Ran: "<<counter4<<" | Overrun:"<<overrun4<<endl;
      exit(0);


}

//thread1
void *thread1(void *)
{
  while(true)
  {
    running1 = false;
    sem_wait(&sme1);
    running1 = true;
    doWork();
    counter1++;
  }
}

//thread2
void *thread2(void *)
{
  while(true)
  {
    sem_wait(&sme2);
    running2 = true;
    doWork();
    counter2++;
  }
}

//thread3
void *thread3(void *)
{
  while(true){
    sem_wait(&sme3);
    running3 = true;
    doWork();
    counter3++;
  }
}

void  *thread4(void *)
{
  while(true){
    sem_wait(&sme4);
    running4 = true;
    doWork();
    counter4++;
  }
}

//thread4
 void print()
 {
   for(int x=0; x<9; x++)
   {
     for(int y=0;y<9;y++)
     {
       cout<<board[x][y]<<" ";
     }
     cout<<endl;
   }
 }
