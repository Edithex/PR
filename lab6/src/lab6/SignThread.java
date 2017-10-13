/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lab6;

/**
 *
 * @author jkolacz
 */
public class SignThread extends Thread {
    
       private char sign;
    private Obraz obraz;
    private int ID;

    public SignThread(char sign, Obraz obraz, int ID) {
        this.sign = sign;
        this.obraz = obraz;
        this.ID = ID;
    }
     @Override
    public synchronized void start() {
        super.start();
        int signCout = 0;
        for(int n = 0; n<obraz.size_n; ++n){
            for(int m = 0; m<obraz.size_m; ++m){
                if (obraz.tab[n][m] == sign) ++signCout;
            }
        }
        System.out.print("Thread ID: " + this.ID + " " + sign + ": " + signCout+" " );
        for(int i=0;i<signCout;i++)
        {
            System.out.print("=");
        }
        
        System.out.println();

    }
    
}
