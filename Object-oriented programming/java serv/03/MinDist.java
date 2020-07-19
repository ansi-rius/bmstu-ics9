import java.util.Scanner;

public class MinDist {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String s = in.nextLine();
        char x = in.next().charAt(0), y = in.next().charAt(0);
        // from server ^^^ don't touch!

/*        //my tests
        System.out.println("in = "+s);
        System.out.println("x = "+x);
        System.out.println("y = "+y);
        *///

        int ras = 0;
        //int len = s.length();
        int min = 100000000;
        for (int i=0; i<s.length(); i++) {
            if (s.charAt(i) == x) {
                for (int j=0; j<s.length(); j++) {
                    if (s.charAt(j) == y) {
                        //System.out.println("i = "+i);
                        //System.out.println("j = "+ j);
                        ras = Math.abs(j-i)-1;
                        if (ras < min) {
                            min = ras;
                        }
                        //System.out.println(ras);
                    }
                }
                //System.out.println("Hoi");
            }
        }
        System.out.println(min);
    }
}
