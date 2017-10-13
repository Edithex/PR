#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>

int zmienna_globalna=0;

#define ROZMIAR_STOSU 1024*64


int funkcja_watku( void* argument )
{
int zmienna_lokalna;
int *z= (int*)argument;
printf("%d\n",(*z));
int i;
for(i=0;i<100;i++)
{
  zmienna_lokalna++;
 zmienna_globalna++;
}

printf("Zmienna lokalna: %d  ",zmienna_lokalna);
printf("Zmienna globalna: %d  ",zmienna_globalna);
  int wynik; 
  wynik=execv("./program",NULL); 
  if(wynik==-1) 
   printf("Proces potomny nie wykonal programu\n");

  return 0;
}

main()
{

  void *stos;
void *stos2;
  pid_t pid;
  pid_t pid2;
  int i; 
  
  stos = malloc( ROZMIAR_STOSU );
stos2 = malloc (ROZMIAR_STOSU );
  if (stos == 0) {
    printf("Proces nadrzędny - blad alokacji stosu\n");
    exit( 1 );
  }
inicjuj_czas();
  //for(i=0;i<10000;i++){
int z=0;
    pid = clone( &funkcja_watku, (void *) stos+ROZMIAR_STOSU, 
		 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, (void*)&z );
    pid2 = clone( &funkcja_watku, (void *) stos2+ROZMIAR_STOSU, 
		 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, (void*)&z );
    waitpid(pid, NULL, __WCLONE);

 // }
drukuj_czas();
  free( stos );
}
