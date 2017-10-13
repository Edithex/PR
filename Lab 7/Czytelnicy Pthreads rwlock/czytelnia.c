#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#include"czytelnia.h"


/*** Implementacja procedur interfejsu ***/
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

int my_read_lock_lock(czytelnia_t* czytelnia_p){
	pthread_rwlock_rdlock(&rwlock);
  
	++czytelnia_p->ilosc_czytelnikow;
	printf("czytelnik odwiedzil czytelnie\n\tczytelnikow %d, pisarzy %d\n", czytelnia_p->ilosc_czytelnikow, czytelnia_p->ilosc_pisarzy);
}


int my_read_lock_unlock(czytelnia_t* czytelnia_p){   
   --czytelnia_p->ilosc_czytelnikow;
   printf("czytelnik opuscil czytelnie\n\tczytelnikow %d, pisarzy %d\n", czytelnia_p->ilosc_czytelnikow, czytelnia_p->ilosc_pisarzy);
   
   pthread_rwlock_unlock(&rwlock);
}


int my_write_lock_lock(czytelnia_t* czytelnia_p){
   pthread_rwlock_wrlock(&rwlock);
   
   ++czytelnia_p->ilosc_pisarzy;
   printf("pisarz odwiedzil czytelnie\n\tczytelnikow %d, pisarzy %d\n", czytelnia_p->ilosc_czytelnikow, czytelnia_p->ilosc_pisarzy);
}


int my_write_lock_unlock(czytelnia_t* czytelnia_p){   
    --czytelnia_p->ilosc_pisarzy;
    printf("pisarz opuscil czytelnie\n\tczytelnikow %d, pisarzy %d\n", czytelnia_p->ilosc_czytelnikow, czytelnia_p->ilosc_pisarzy);
    
    pthread_rwlock_unlock(&rwlock);
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
