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
public class BlockThread implements Runnable {
    
     private int i,j;
    private Obraz obraz;
    private int ID;
    public BlockThread(int i,int j, Obraz obraz, int ID) {
        this.i = i;
        this.j=j;
        this.obraz = obraz;
        this.ID = ID;
    }


    @Override
    public void run() {
        for(int k=i;k<j;k++)
      {
          char sign=(char)(33+k);
        int signCout = 0;
        for(int n = 0; n<obraz.size_n; ++n){
            for(int m = 0; m<obraz.size_m; ++m){
                if (obraz.tab[n][m] ==sign ) ++signCout;
            }
        }
        
        obraz.update_histogram(k, signCout,this.ID);
         
    }
    }
    
}
