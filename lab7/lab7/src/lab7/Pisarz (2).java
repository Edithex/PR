package lab7;
public class Pisarz extends Thread {
	private static Integer idCounter = 0;
	private Integer id;
	private Czytelnia biblioteka;
	
	Pisarz(Czytelnia b){biblioteka = b; id=idCounter++;}

	public void run() {
		for(int i=0;; i++){
			System.out.println("Pisarz "+id+" czeka.");
			try {
				biblioteka.pisarz_wejscie();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			System.out.println("Pisarz "+id+" pisze.");
			try {
				Thread.sleep(500);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			biblioteka.pisarz_wyjscie();
		}
	}
	 
}
