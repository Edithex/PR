import com.sun.org.apache.xpath.internal.SourceTree;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Czytelnia {
    final private ReentrantLock lock = new ReentrantLock();
    final private Condition pisarze = lock.newCondition(),
                            czytelnicy = lock.newCondition();
    private int iloscCzytelnikow = 0, iloscPisarzy = 0;

    public void chceCzytac(){
        lock.lock();
        try{
            if(iloscPisarzy > 0 || lock.hasWaiters(pisarze)) try {
                czytelnicy.await();
            } catch (InterruptedException e) {e.printStackTrace();}
            ++iloscCzytelnikow;
            System.out.println("    Czytelnik dodany - Czytelnicy " + iloscCzytelnikow + " Pisarze " + iloscPisarzy);
            czytelnicy.signal();
        } finally {{lock.unlock();}}
    }

    public void koniecCzytania(){
        lock.lock();
        try{
                --iloscCzytelnikow;
                System.out.println("    Czytelnik usunięty - Czytelnicy " + iloscCzytelnikow + " Pisarze " + iloscPisarzy);
                if(iloscCzytelnikow == 0) pisarze.signal();
             } finally {{lock.unlock();}}
    }

    public void chcePisac() {
        lock.lock();
        try{
            if(iloscPisarzy + iloscCzytelnikow > 0) try {
                pisarze.await();
            } catch (InterruptedException e) {e.printStackTrace();}
            ++iloscPisarzy;
            System.out.println("    Pisarz dodany - Czytelnicy " + iloscCzytelnikow + " Pisarze " + iloscPisarzy);
        } finally {{lock.unlock();}}
    }

    public void koniecPisania(){
        lock.lock();
        try{
            --iloscPisarzy;
            System.out.println("    Pisarz usunięty - Czytelnicy " + iloscCzytelnikow + " Pisarze " + iloscPisarzy);
            if(lock.hasWaiters(czytelnicy)) {
                System.out.println("    Czytelnicy w kolejce do czytelni");
                czytelnicy.signal(); }
            else {
                System.out.println("    Sygnał dla pisarzy");
                pisarze.signal(); }
        } finally {{lock.unlock();}}
    }
}
