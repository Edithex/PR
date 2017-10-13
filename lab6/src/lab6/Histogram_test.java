/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lab6;

import java.util.Scanner;


class Histogram_test {
    
    public static void main(String[] args) {

	Scanner scanner = new Scanner(System.in);
	int totalSigns=94;
        int ilosc_watkow=3;
	System.out.println("Set image size: n (#rows), m(#kolumns)");
	int n = scanner.nextInt();
	int m = scanner.nextInt();
	Obraz obraz_1 = new Obraz(n, m);

	obraz_1.calculate_histogram();
	obraz_1.print_histogram();
        int ilosc_iteracji=totalSigns/ilosc_watkow;
        System.out.println("blokowo");
          Thread[] threads1 = new Thread[ilosc_watkow];
        for(int i = 0; i < ilosc_watkow; ++i){
            (threads1[i]=new Thread(new BlockThread(ilosc_iteracji*i,ilosc_iteracji*(i+1),obraz_1, i))).start();
        }
        
        for(int i = 0; i< ilosc_watkow; ++i)
            try {
                threads1[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        
obraz_1.print_histogram();
  
                System.out.println("Watek dla kazdego znaku ");
        SignThread[] threads = new SignThread[totalSigns];
        for(int i = 0; i < totalSigns; ++i){
            (threads[i]=new SignThread((char)(33 + i), obraz_1, i)).start();
        }

        for(int i = 0; i < totalSigns; ++i)
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
    

    }

}
