public class Test1 {                                    // ----- 53 вариант ------
    public static void main(String[] args) {
        Fractions[] fract = new Fractions[4];

        //fract[0] = new Fractions(1, 0);
        fract[0] = new Fractions();
        fract[1] = new Fractions(2);
        fract[2] = new Fractions(12, 20);
        fract[3] = new Fractions(4, 5);

        for (int i=0; i<fract.length; i++) {
            System.out.println("// The floating value of " +fract[i]+ " is " + fract[i].evaluate());
        }

        System.out.println("add = " + (fract[0].add(fract[1])).evaluate() +
                " (" + "fraction = " + (fract[0].add(fract[1])) + ")");

        //System.out.println("add = " + (fract[0].add(fract[1])));

        System.out.println("multiplication = " + (fract[1].multiplication(fract[2])).evaluate() +
                " (" + "fraction = " + (fract[1].multiplication(fract[2])) + ")");

        //System.out.println("multi = " + (fract[1].multi(fract[2])));

        System.out.println("add = " + (fract[2].add(fract[3])).evaluate() +
                " (" + "fraction = " + (fract[2].add(fract[3])) + ")");

        System.out.println("multiplication = " + (fract[3].add(fract[1])).evaluate() +
                " (" + "fraction = " + (fract[3].add(fract[1])) + ")");

        System.out.println("toString " + fract[0].toString());

        //System.out.println("Gcd of 2 and 10 is " + gcd(2,10));
    }
}
