#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

int zmienna_wspolna=0;
#define WYMIAR 1000
#define ROZMIAR WYMIAR*WYMIAR
double a[ROZMIAR],b[ROZMIAR],c[ROZMIAR];


void * zadanie_watku (void * arg_wsk)
{
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,
    NULL);
long unsigned int a = pthread_self();
    printf("\twatek potomny id systemowe: %lu\n", a);
    printf("\twatek potomny id iteracji: %d\n", arg_wsk);

    return(NULL);
}
int main()
{
    pthread_t tid;
    pthread_attr_t attr;
    void *wynik;
    int i;
    printf("watek glowny: tworzenie watku potomnego nr 1\n");
    for(i=0; i<10; i++){
	pthread_create (&tid, NULL, zadanie_watku, i);
	sleep(2);
    }

    for(i = 0; i<10; i++){
	pthread_join(tid, &wynik);
    }
    
    pthread_exit(NULL);
}
