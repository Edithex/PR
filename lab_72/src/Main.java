
public class Main {

    public static void main(String[] args) {
        Thread[] pisarze = new Thread[2];
        Thread[] czytelnicy = new Thread[4];
        Czytelnia czytelnia = new Czytelnia();

        for(int i = 0; i < pisarze.length; ++i)
            (pisarze[i] = new Thread(new Pisarz(czytelnia))).start();

        for(int i = 0; i < czytelnicy.length; ++i)
            (czytelnicy[i] = new Thread(new Czytelnik(czytelnia))).start();
    }
}
