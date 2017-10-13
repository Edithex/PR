package lab7;

public class BibliotekaTest {
	private static Integer liczbaCzytelnikow = 10;
	private static Integer liczbaPisarzy = 1;
	public static void main(String[] args) {
		Czytelnia b= new Czytelnia();
		for(int i=0; i<liczbaCzytelnikow || i<liczbaPisarzy; i++){
			if(i<liczbaPisarzy) 
				new Pisarz(b).start();
			if(i<liczbaCzytelnikow)
				new Czytelnik(b).start();
		}
	}
}