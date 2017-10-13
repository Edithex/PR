/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package prlab8;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Simple_executor_test {

    private static final int NTHREADS= 30;
 
    public static void main(String[] args) {
           		Calka_callable calka;
                        double suma=0;
		try {
       
                        double a=-3.14;
                        double b=3.14;
                     
                        double krok=(b-a)/NTHREADS;
                                
			for (double i = 0; i <NTHREADS; i++) {
                              double aa=a+(i*krok);
                        double bb=a+(i+1)*krok;
				calka = new Calka_callable(aa,bb,0.0000001);
				suma+=calka.call();
			}
			//System.out.println("Wynik: "+suma);
                        

	} catch (Exception e) {
			e.printStackTrace();
		}

	Counter counter = new Counter();
	ExecutorService executor = Executors.newFixedThreadPool(NTHREADS);

	for (int i = 0; i < 50; i++) {
	    Runnable worker = new CounterPlus(counter);
	    executor.execute(worker);
	}

	// This will make the executor accept no new threads
	// and finish all existing threads in the queue
	executor.shutdown();

	// Wait until all threads finish
	while (!executor.isTerminated()) {}

	System.out.println("Finished all threads");
	System.out.format("\nCounter_1: %d, Counter_2 %d\n\n", 
			  counter.get_c1(), counter.get_c2());
    }
} 
