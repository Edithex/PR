package lab7;

public class Czytelnik extends Thread{
	private static Integer idCounter = 0;
	private Integer id;
	private Czytelnia biblioteka;
	
	Czytelnik(Czytelnia b){biblioteka = b; id=idCounter++;}

	@Override
	public void run() {
		for(int i=0;; i++){
			System.out.println("Czytelnik "+id+" czeka.");
			try {
				biblioteka.czytelnik_wejscie();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				//e.printStackTrace();
			}
			System.out.println("Czytelnik "+id+" czyta.");
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				//e.printStackTrace();
			}
			System.out.println("Czytelnik "+id+" wychodzi.");
			biblioteka.czytelnik_wyjscie();
		}
	}
	
}
