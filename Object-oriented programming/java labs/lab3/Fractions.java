public class Fractions {
    private int numerator, denominator;

     Fractions(int n, int d) {
        if(d == 0) {
            throw new IllegalArgumentException("denominator is zero"); //check if denom = 0;
        }
        numerator = n;
        denominator = d;

         int thisGcd = gcd(numerator, denominator);

         numerator = numerator/thisGcd;
         denominator = denominator/thisGcd;
     }

    public Fractions(int n) {
        this(n,1);
    }

    public Fractions() {
        numerator = 0;
        denominator = 1;
    }

    public String toString() {
        int thisGcd = gcd(numerator, denominator);

        return (numerator/thisGcd + "/" + denominator/thisGcd);
    }
     private static int gcd (int n, int d) {
         if (d==0)
             return n;
         return gcd(d,n%d);
     }

    public double evaluate() {  // like 'eval'
        double n = numerator;
        double d = denominator;
        return (n / d);
    }

    public Fractions add (Fractions fract2) {
        Fractions res = new Fractions((numerator * fract2.denominator) + (fract2.numerator * denominator),
                                    (denominator * fract2.denominator));
        return res;
    }

    public Fractions multiplication (Fractions fract2) {
        Fractions res = new Fractions((numerator * fract2.numerator),
                (fract2.denominator * denominator));
        return res;
    }
}