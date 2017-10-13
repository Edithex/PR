/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package prlab8;

public class Counter {
    private long c1 = 0; private long c2 = 0;


    private Object lock1 = new Object(); 
    private Object lock2 = new Object();


    public void inc1() {
    	synchronized(lock1) {
    	    try {
    		c1++;
    		Thread.sleep(1); 
    	    } catch (InterruptedException e) {
		// some code
    	    }
    	}
    }
	
    public void inc2() {
    	synchronized(lock2) {
    	    try{
    		c2++;
    		Thread.sleep(1);
    	    } catch (InterruptedException e) {
		// some code
    	    }  
    	} 
    }

    public long get_c1() {
	return(c1);
    }

    public long get_c2() {
	return(c2);
    }
}






