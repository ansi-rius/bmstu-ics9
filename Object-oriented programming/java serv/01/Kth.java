import java.util.Scanner;

public class Kth {

        public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        long k =in.nextLong();
        
        int n = 1;
        long p = 1;
        long s = 9, sp = 0;
        
        while (s<k){
            n++;
            p*=10;
            sp = s;
            s+=9*p*n;
        }
        //System.out.println(n);
        s = k - sp;
        //System.out.println(s);
        long c = p + s / n;
        
        //System.out.println(c);
        
        n = (int) (s % n);
        //System.out.println(n);

        //System.out.println(n);

        System.out.println((c+"").charAt(n));   
    }
}
