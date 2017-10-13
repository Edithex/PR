#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

void * watek_klient (void * arg);
int l_kr, i;
int l_kl = 5;
int l_kf = 3;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
main(){

  pthread_t *tab_klient;
  int *tab_klient_id;
  //printf("\nLiczba klientow: "); scanf("%d", &l_kl);

  //printf("Liczba kufli: "); scanf("%d", &l_kf);

  //printf("\nLiczba kranow: "); scanf("%d", &l_kr);
  l_kr = 1;

  tab_klient = (pthread_t *) malloc(l_kl*sizeof(pthread_t));
  tab_klient_id = (int *) malloc(l_kl*sizeof(int));
  for(i=0;i<l_kl;i++) tab_klient_id[i]=i;


  printf("Otwieramy pub (simple)!\n");
  printf("Liczba wolnych kufli %d\n", l_kf); 

  for(i=0;i<l_kl;i++){
    pthread_create(&tab_klient[i], NULL, watek_klient, &tab_klient_id[i]); 
  }
  for(i=0;i<l_kl;i++){
    pthread_join( tab_klient[i], NULL);
  }
  printf("Zamykamy pub!\n");
printf("Liczba wolnych kufli %d\n", l_kf);
}


void * watek_klient (void * arg_wsk){

  int moj_id = * ((int *)arg_wsk);
  int pobrano_kufel = 0;
  int i, j, kufel, result;
  int ile_musze_wypic = 2;

  printf("Klient %d, wchodzę do pubu\n", moj_id); 
    
  for(i=0; i<ile_musze_wypic; i++){
//    do{
	if(pthread_mutex_trylock(&mutex) == 0){
	    printf("\nKufel zablokowany\n", moj_id); 
	    if(l_kf>0){
		    printf("\nSą wolne kufle\n", moj_id); 
		    l_kf--;
		    pobrano_kufel = 1;
		    printf("\nPodaję piwo w kuflu.\n", moj_id); 
	    }
	    pthread_mutex_unlock(&mutex);}
	else {
	    printf("\nNie ma kufli\n", moj_id); 
	}
  //  }while(pobrano_kufel == 0);
    printf("Klient %d, wybieram kufel\n", moj_id); 

    j=0;
    printf("Klient %d, nalewam z kranu %d\n", moj_id, j); 
    usleep(300);
    
    printf("Klient %d, pije\n", moj_id); 
    nanosleep((struct timespec[]){{0, 500000000L}}, NULL);
    
    printf("Klient %d, odkladam kufel\n", moj_id); 
    if(pobrano_kufel == 1){
	pthread_mutex_lock(&mutex);
	pobrano_kufel = 0;
	l_kf++;
	printf("Klient %d zwrocił kufel. Liczba kufli: %d\n", moj_id, l_kf); 
	pthread_mutex_unlock(&mutex);
    }
  }

  printf("Klient %d, wychodzę z pubu\n", moj_id); 
    
  return(NULL);
} 

//test - ilośc kufli powinna sie zawsze zgadzać
//zmienne warunkowe
//"tajlock"
