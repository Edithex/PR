#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<pthread.h>

#include"pomiar_czasu.h"

#define ROZMIAR 10000000
#define LICZBA_W 5

pthread_mutex_t muteks; 
pthread_t watki[LICZBA_W];
double global_array_of_local_sums[LICZBA_W];

struct przedzial{ 
double a; 	// przedział całkowania
double b;
};	
struct przedzial global_ranges[LICZBA_W];

double f(double); // funkcja całkowania
void *integral_struct_ranges( void* arg_wsk);
void *integral_with_global_array(void* arg_wsk);

double a,b;
double dx;
double suma=0; 
double PI=3.141592653589793;

int main( int argc, char *argv[] )
{
  	a =-PI,b=PI;
  	dx = (b-a) / ROZMIAR;
  	int i; 

  	double t1;

  	int indeksy[LICZBA_W]; 
  	for(i = 0; i < LICZBA_W; i++) 
		indeksy[i]=i;

  	pthread_mutex_init( &muteks, NULL);
  
  	double length = (b-a) / LICZBA_W;
  	double x1 = a;
  	double x2;

  	for(i = 0; i < LICZBA_W; ++i)
	{
	  	x2 = x1 + length;
	  	global_ranges[i].a = x1;
	  	global_ranges[i].b = x2;
	  	x1 = x2;
	} 
	
  	// calka blokowa
  	t1 = czas_zegara();
  
  	for(i = 0; i < LICZBA_W; i++) 
 		pthread_create(&watki[i], NULL, integral_struct_ranges, (void *) &global_ranges[i]);

  	for(i = 0; i < LICZBA_W; i++) 
		pthread_join(watki[i], NULL);
  
  	t1 = czas_zegara() - t1;
  	printf("\n(a,b) = (%lf,%lf)\n\n", a,b);
  	printf("Blokowo = %.12lf\n", suma);
  	printf("Czas= %lf\n\n", t1);
 
  
	// calka sekwencyjna
	double DX = (b-a) / ROZMIAR;
	double x = a;
	double SUMA = 0.0;
	
	t1 = czas_zegara();
	double f_x = f(a);

	for(i = 0; i < ROZMIAR; ++i)
	{
		SUMA += f_x;
		x += DX;
		f_x = f(x);
		SUMA += f_x;
	}

	SUMA *= 0.5 * dx;

	t1 = czas_zegara() - t1;
	printf("Sekwencyjnie = %.12lf\n", SUMA);
	printf("Czas = %lf\n", t1);	
}

double f(double x)
{
	return sin(x);
}

void *integral_struct_ranges(void* arg_wsk)
{
	struct przedzial r;
	r = *((struct przedzial*) arg_wsk);
	int iterations = ROZMIAR / LICZBA_W;

	double dx = (r.b-r.a) / iterations;
	double x = r.a;
	double lokalna_suma = 0.0;
	double f_x = f(r.a);
	int i;

	for(i = 0; i < iterations; ++i)
	{
		lokalna_suma += f_x;
		x += dx;
		f_x = f(x);
		lokalna_suma += f_x;
	}

	lokalna_suma *= 0.5 * dx;
	
	pthread_mutex_lock( &muteks );
	suma += lokalna_suma;
	pthread_mutex_unlock( &muteks );

	pthread_exit( (void *)0);
}

void *integral_with_global_array(void* arg_wsk)
{
	int moj_id = *( (int *) arg_wsk ); 
	double  X1,X2;
	double suma = 0.0;
	int i;

	for(i = moj_id; i < ROZMIAR; i += LICZBA_W)
	{
		X1 = a + i*dx;
		X2 = X1 + dx;
		suma += f(X1) + f(X2);
	}

	suma *= 0.5 * dx;
	global_array_of_local_sums[moj_id] = suma;
	pthread_exit( (void *)0);
}
