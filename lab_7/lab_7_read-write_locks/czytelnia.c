#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#include"czytelnia.h"


/*** Implementacja procedur interfejsu ***/

int my_read_lock_lock(czytelnia_t* czytelnia_p){
	/*if( liczba_pisz > 0  lub  ~empty(pisarze)) 
	wait(czytelnicy);
	liczba_czyt ++;
	signal(czytelnicy);*/
}


int my_read_lock_unlock(czytelnia_t* czytelnia_p){
	/*liczba_czyt --;
	if(liczba_czyt = 0)  signal(pisarze);*/
}


int my_write_lock_lock(czytelnia_t* czytelnia_p){
  	/*if( liczba_czyt+liczba_pisz > 0) wait(pisarze);
	liczba_pisz ++;*/
}


int my_write_lock_unlock(czytelnia_t* czytelnia_p){
	/* liczba_pisz --;
	if( ~empty(czytelnicy)) signal(czytelnicy);
	WPP  signal(pisarze);*/
}

void inicjuj(czytelnia_t* czytelnia_p){
	
}

void czytam(czytelnia_t* czytelnia_p){
    usleep(rand()%1000000);
}

void pisze(czytelnia_t* czytelnia_p){
    usleep(rand()%1000000);
}


