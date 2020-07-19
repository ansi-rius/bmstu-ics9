import java.math.BigInteger;
import java.util.Scanner;

public class FastFib {

    public static BigInteger multi(BigInteger a, BigInteger b) {
        return a.multiply(b);
    }

    public static BigInteger ad(BigInteger a, BigInteger b) {
        return a.add(b);
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        
        BigInteger[][] m = {
                {BigInteger.valueOf(1), BigInteger.valueOf(1)},
                {BigInteger.valueOf(1), BigInteger.valueOf(0)},
        };
        BigInteger[][] res = {
                {BigInteger.valueOf(0), BigInteger.valueOf(0)},
                {BigInteger.valueOf(0), BigInteger.valueOf(0)},
        };

        BigInteger a = BigInteger.valueOf(1);
        BigInteger b = BigInteger.valueOf(0);

        if (n < 3) {
            System.out.println(1);
        } else {
            while (n > 0) {
                if ((n % 2) != 0) {
                    res[0][0] = ad(multi(a,m[0][0]), multi(b, m[1][0]));

                    res[0][1] = ad(multi(a, m[0][1]), multi(b, m[1][1]));

                    a = res[0][0];
                    b = res[0][1];
                }
                res[0][0] = ad(multi(m[0][0], m[0][0]), multi(m[0][1], m[1][0]));

                res[0][1] = ad(multi(m[0][0], m[0][1]), multi(m[0][1], m[1][1]));

                res[1][0] = ad(multi(m[1][0], m[0][0]), multi(m[1][1], m[1][0]));

                res[1][1] = ad(multi(m[1][0], m[0][1]), multi(m[1][1], m[1][1]));
                //m1 = res;

                m[0][0] = res[0][0];
                m[0][1] = res[0][1];
                m[1][0] = res[1][0];
                m[1][1] = res[1][1];

                n /= 2;
            }
            System.out.println(b);
        }
    }
}