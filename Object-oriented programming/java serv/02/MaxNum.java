import java.util.Scanner;
import java.util.Arrays;

public class MaxNum {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        //System.out.println(n);
        int a[] = new int[n];
        for (int i=0; i<n; i++) {
            a[i] = input.nextInt();
            //System.out.println("a["+i+"]= "+a[i]);
        }

        Arrays.sort(a);

        /*for (int i=n-1; i>=0; i--) {
            //a[i] = input.nextInt();
            System.out.println("a["+i+"]= "+a[i]);
        }*/

        long max;
        int k = 0;
        for (int i=0; i<n; i++) {
            max = a[0];
            for (int j=0; j<n; j++) {
                if ((a[j] != 0) && ((Integer.valueOf(String.valueOf(max) + String.valueOf(a[j])) <= Integer.valueOf(String.valueOf(a[j]) + String.valueOf(max))))) {
                    max = a[j];
                    k = j;
                }
            }
            a[k] = 0;
            System.out.print(max);
        }
        //System.out.println(max);
    }
}
