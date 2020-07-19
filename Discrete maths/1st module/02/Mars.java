import java.util.Scanner;

public class Mars {

        static Scanner in = new Scanner(System.in);
    
    static char m[][];
    static int a[][];
    static boolean b[];

    static boolean search(int N, int next, int i){
        boolean answer = false;
        if (i==0){
            //
            // b->m [true,false]
            //
            if (correct()){
                int tmp[][] = new int[a.length+1][];
                for (int k = 0; k < a.length; k++){
                    tmp[k] = new int[a[k].length];
                    for (int j = 0; j < a[k].length; j++){
                        tmp[k][j] = a[k][j];
                    }
                }
                int k = 0;
                for (int j = 0; j < b.length; j++) {
                    k += (b[j]?1:0);
                }
                tmp[a.length] = new int[k];
                k = 0;
                for(int j = 0; j < b.length; j++) {
                    if (b[j]) {
                        tmp[a.length][k++] = j;
                    }
                }
                a = tmp;
                
                answer = true;
                
                //
                //for(int j=0; j<a[a.length-1].length; j++){
                //  System.out.print((a[a.length-1][j]+1)+" ");
                //}
                //System.out.println(correct(m));
                //
            }
        } else {
            
            for(int j = next; j < N; j++) {
                if (!b[j]){
                    if (corrb(j)){
                        b[j]=true;

                        answer = search(N, j+1, i-1);

                        if (answer) break;

                        b[j]=false;
                    }
                }
            }
        }
        return answer;
    }
    
    static boolean corrb(int j){
        boolean res = true;
        for (int i = 0; i < b.length; i++){
            if (b[i]){
                if (m[i][j] == '+'){
                    res = false;
                    break;
                }
            }
        }
        return res;
    }
    
    static boolean correct() {
        boolean res = true;
        int mi, mj;
        fnexti: for (int i = 0; i < b.length; i++){
            if (!b[i]){
                mi = i;
                for (int j = i + 1; j < b.length; j++){
                    if (!b[j]){
                        mj = j;
                        if (m[mi][mj] == '+'){
                            res = false;
                            break fnexti;
                        }
                    }
                }
            }
        }
        return res;
    }
    
    public static void main(String[] args) {
        // TODO Auto-generated method stub
        int N = in.nextInt();
        m = new char[N][N];
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                m[i][j] = in.next().charAt(0);
            }
        }
        
        for (int i = N / 2; i >= 1; i--){
            a = new int[0][];
            b = new boolean[N];
            
            if (search(N, 0, i)){
                break;
            }
        }
        
        if (a.length > 0) {
            //for(int i=0; i<a.length; i++){
            //  System.out.printf("%2d: ",(i+1));
            //  for(int j=0; j<a[i].length; j++){
            //      System.out.print((a[i][j]+1)+" ");
            //  }
            //  System.out.println();
            //}

            if (a.length > 0) {
                int i = 0;
                for(int j = 0; j < a[i].length; j++) {
                    System.out.print((a[i][j]+1)+" ");
                }
            }
        } else {
            System.out.println("No solution");
        }
        
        in.close();
    }

}
