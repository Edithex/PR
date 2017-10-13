import java.util.Random;

public class Czytelnik implements Runnable {
    private Czytelnia czytelnia = new Czytelnia();

    public Czytelnik(Czytelnia czytelnia) {
        this.czytelnia = czytelnia;
    }

    @Override
    public void run() {
        Thread t = Thread.currentThread();
        Random random = new Random();

        while(true){
            System.out.println("Czytelnik " + t.getId() + " chce wejść.");
            czytelnia.chceCzytac();
            System.out.println("Czytelnik " + t.getId() + " czytam...");
            try {
                Thread.sleep(random.nextInt(1000));
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("Czytelnik " + t.getId() + " skonczyłem czytać.");
            czytelnia.koniecCzytania();
            System.out.println("Czytelnik " + t.getId() + " wyszedł.");
        }
    }
}