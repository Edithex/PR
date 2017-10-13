#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#include"czytelnia.h"


/*** Implementacja procedur interfejsu ***/

int my_read_lock_lock(czytelnia_t* czytelnia_p){
while(czytelnia_p->liczba_pisz>0) pthread_cond_wait(czytelnia_p->czytelnicy);
czytelnia_p->liczba_czyt++;
pthread_cond_signal(czytelnia_p->czytelnicy);


}


int my_read_lock_unlock(czytelnia_t* czytelnia_p){
czytelnia_p.liczba_czyt--;
if(czytelnia_p.liczba_czyt==0) pthread_cond_signal(czytelnia_p.pisarze);
}


int my_write_lock_lock(czytelnia_t* czytelnia_p){
  if(czytelnia_p.liczba_czyt+liczba_pisz>0) pthread_cond_wait(czytelnia_p.czytelnicy);
czytelnia_p.liczba_pisz++;
}


int my_write_lock_unlock(czytelnia_t* czytelnia_p){
   czytelnia_p.liczba_pisz--;
if(czytelnia_p.czytelnicy) pthread_cond_signal(czytelnia_p.czytelnicy);
else pthread_cond_signal(czytelnia_p.pisarze);
}

void inicjuj(czytelnia_t* czytelnia_p){

}

void czytam(czytelnia_t* czytelnia_p){
    usleep(rand()%1000000);
}

void pisze(czytelnia_t* czytelnia_p){
    usleep(rand()%1000000);
}


