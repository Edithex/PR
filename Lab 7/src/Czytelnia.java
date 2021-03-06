package lab7;
import java.util.concurrent.locks.*;

public class Czytelnia {
	private Integer licznik;
	private Integer licznikPisarzy;
private Lock biblioteka = new ReentrantLock();
private Condition pisarze = biblioteka.newCondition();
private Condition czytelnicy = biblioteka.newCondition();

Czytelnia(){licznik = 0;licznikPisarzy=0;}

void czytelnik_wejscie() throws InterruptedException{
	biblioteka.lock();
	
	try{
		if(licznik == -1 || licznikPisarzy!=0) czytelnicy.await();
		licznik++;
		czytelnicy.signal();
	}finally{
		biblioteka.unlock();
	}
}
void czytelnik_wyjscie(){
	biblioteka.lock();
	licznik--;
	if(licznik==0) pisarze.signal();
	biblioteka.unlock();
}

void pisarz_wejscie() throws InterruptedException{
	biblioteka.lock();
	try{
		
		licznikPisarzy++;
		if(licznik != 0) pisarze.await();
		licznik = -1;
		licznikPisarzy--;
	}finally{
		biblioteka.unlock();
	}
}
void pisarz_wyjscie(){

	biblioteka.lock();
	System.out.println("Pisarz wychodzi.");
	licznik = 0;
	if(czytelnicy != null) czytelnicy.signal();
	else pisarze.signal();
	biblioteka.unlock();
}
}
