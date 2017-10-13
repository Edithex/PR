#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#include"czytelnia.h"

pthread_mutex_t muteks = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t czytelnicy = PTHREAD_COND_INITIALIZER;
pthread_cond_t pisarze = PTHREAD_COND_INITIALIZER;
/*** Implementacja procedur interfejsu ***/

int my_read_lock_lock(czytelnia_t* czytelnia_p){
  pthread_mutex_lock(&muteks);
  
  while(czytelnia_p->ilosc_pisarzy > 0) pthread_cond_wait(&czytelnicy, &muteks);
  ++czytelnia_p->ilosc_czytelnikow;
  printf("czytelnik odwiedzil czytelnie\n\tczytelnikow %d, pisarzy %d\n", czytelnia_p->ilosc_czytelnikow, czytelnia_p->ilosc_pisarzy);
  pthread_cond_signal(&czytelnicy);
  
  pthread_mutex_unlock(&muteks);
}


int my_read_lock_unlock(czytelnia_t* czytelnia_p){
   pthread_mutex_lock(&muteks);
   
   --czytelnia_p->ilosc_czytelnikow;
   printf("czytelnik opuscil czytelnie\n\tczytelnikow %d, pisarzy %d\n", czytelnia_p->ilosc_czytelnikow, czytelnia_p->ilosc_pisarzy);
   if(czytelnia_p->ilosc_pisarzy = 0) pthread_cond_signal(&pisarze);
   
   pthread_mutex_unlock(&muteks);
}


int my_write_lock_lock(czytelnia_t* czytelnia_p){
   pthread_mutex_lock(&muteks);
   
   if(czytelnia_p->ilosc_czytelnikow + czytelnia_p->ilosc_pisarzy > 0) pthread_cond_wait(&pisarze, &muteks);

   ++czytelnia_p->ilosc_pisarzy;
   printf("pisarz odwiedzil czytelnie\n\tczytelnikow %d, pisarzy %d\n", czytelnia_p->ilosc_czytelnikow, czytelnia_p->ilosc_pisarzy);
   
   pthread_mutex_unlock(&muteks);
}


int my_write_lock_unlock(czytelnia_t* czytelnia_p){
    pthread_mutex_lock(&muteks);
    
    --czytelnia_p->ilosc_pisarzy;
    printf("pisarz opuscil czytelnie\n\tczytelnikow %d, pisarzy %d\n", czytelnia_p->ilosc_czytelnikow, czytelnia_p->ilosc_pisarzy);
    pthread_cond_signal(&pisarze);
    pthread_cond_signal(&czytelnicy);
    
    pthread_mutex_unlock(&muteks);
}

void inicjuj(czytelnia_t* czytelnia_p){
	czytelnia_p->ilosc_czytelnikow = 0;
	czytelnia_p->ilosc_pisarzy = 0;
}

void czytam(czytelnia_t* czytelnia_p){
    usleep(rand()%1000000);
}

void pisze(czytelnia_t* czytelnia_p){
    usleep(rand()%1000000);
}
