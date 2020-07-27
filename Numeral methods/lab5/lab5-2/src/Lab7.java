import static java.lang.Math.*;

public class Lab7 {
    static double a = 1.0;
    static double b = 2.0;
    static double c = 0.0;
    static double d = 1.0;
    static double e = 0.001;

    public static double f(double x, double y) {
        return exp(y);
    }

    public static double y(double u, double v) {
        return 0+v*(1+log(u));
    }

    public static  void main(String[] args) {

        double h = sqrt(e);
        int c = 0;

        while (abs(method(h) - method(2*h))/3 > e) {
            h = h/2;
            c++;
        }
        System.out.println("s= " + method(h));
        System.out.println("num of steps= "+ c);
        System.out.println("res of int= 3.07");

    }

    public static double method(double h) {
        double s = 0;
        double xi = a;
        double v;
        while (xi < b) {
            v = c;
            while (v < d) {
                s += f(xi+h/2, y(xi,v) + h/2) * (1 + log(xi) + h/2);
                v+=h;
            }
            xi += h;
        }
        return h*h*s;
    }

}
