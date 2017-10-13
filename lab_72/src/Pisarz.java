import java.util.Random;


public class Pisarz implements Runnable{
    private Czytelnia czytelnia = new Czytelnia();

    public Pisarz(Czytelnia czytelnia) {
        this.czytelnia = czytelnia;
    }

    @Override
    public void run() {
        Thread t = Thread.currentThread();
        Random random = new Random();

        while(true){
            System.out.println("Pisarz " + t.getId() + " chce wejść.");
            czytelnia.chcePisac();
            System.out.println("Pisarz " + t.getId() + " piszę...");
            try {
                Thread.sleep(random.nextInt(1000));
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("Pisarz " + t.getId() + " skonczyłem pisać.");
            czytelnia.koniecPisania();
            System.out.println("Pisarz " + t.getId() + " wyszedł.");
        }
    }
}
