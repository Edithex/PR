/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lab6;

import  java.util.Random;


class Obraz {
    
    public int size_n;
    public int size_m;
    public char[][] tab;
    public int[] histogram;
    public int[] id_watku;
    

    Obraz(int n, int m) {
        this.size_n = n;
	this.size_m = m;
	tab = new char[n][m];
	
	final Random random = new Random();
	
	for(int i=0;i<n;i++) {
	    for(int j=0;j<m;j++) {	
		tab[i][j] = (char)(random.nextInt(94)+33);  // ascii 33-127
		System.out.print(tab[i][j]+" ");
	    }
	    System.out.print("\n");
	}
	System.out.print("\n\n");

	histogram = new int[94];
        id_watku = new int[94];
   	clear_histogram();}
    
    public void clear_histogram(){

	for(int i=0;i<94;i++) histogram[i]=0;

    }

    public void calculate_histogram(){

	for(int i=0;i<size_n;i++) {
	    for(int j=0;j<size_m;j++) {
	
		for(int k=0;k<94;k++) {
		    if(tab[i][j] == (char)(k+33)) histogram[k]++;	    
		}

	    }
	}

    }

    public void print_histogram(){
	
	for(int i=0;i<94;i++) {
	    System.out.print("ID watku"+id_watku[i]+" "+(char)(i+33)+" "+histogram[i]+" ");
            for(int j=0;j<histogram[i];j++)
            {
             System.out.print("=");
            }
            System.out.println();
	}

    }
    public void update_histogram(int x,int signCout,int ID)
    {
        histogram[x]=signCout;
        id_watku[x]=ID;
    }
     

}