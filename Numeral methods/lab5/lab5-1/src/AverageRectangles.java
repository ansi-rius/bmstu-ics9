import static java.lang.Math.abs;
import static java.lang.Math.sqrt;

public class AverageRectangles {
    static double a = 0.0;
    static double b = 3.0;
    public static  void main(String[] args) {

        double n = 2;
        double e = 0.001;
        double res = 57;

        while (abs(method(n) - method(2*n))/3 > e) {
            n *= 2;
        }
        System.out.println("s= " + method(n));
        System.out.println("num of steps= "+ n);
        System.out.println("res of int= 57");
    }

    public static double f(double x) {
        return x*sqrt(x*x)+16;
    }

    public static double method(double n) {
        double h = (b-a)/n;
        double sum = 0;
        for (int i=0; i<n; i++) {
            sum += f(a + i*h + h/2);
        }
        return sum*h;
    }

}
