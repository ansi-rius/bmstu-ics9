import static java.lang.Math.*;

public class OptimizationMethods {
    public static void main(String[] args) {
        double a = 0;
        double b = PI/4;
        double eps = 0.03;
        dihotomy_method(a,b,eps);
        gold_method(a,b,eps);
        parabola_method(a,b,eps);
    }

    public static void dihotomy_method(double a, double b, double e) {
        double x1, x2 = 0;
        double x = 0;

        while (b-a > 2*e) {
            x = (a+b)/2;
            x1 = x - e;
            x2 = x + e;
            if (f(x1) <= f(x2))
                b = x1;
            else if (f(x1) > f(x2)) {
                a = x2;
            }

        }
        double res = x;
        System.out.println("dihonomy_method: "+res+" "+f(res)*180/PI);
    }

    public static double f(double x) {
        return (Math.tan(x) - 2*Math.sin(x))*PI/180;
    }

    public static void gold_method(double a, double b, double e) {
        double x1, x2 = 0;
        double x = 0;
        double f1,f2 = 0;

        x = (a+b)/2;
        x1 = a+(3-sqrt(5))*(b-a)/2;
        x2 = a+(sqrt(5)-1)*(b-a)/2;
        f1 = f(x1);
        f2 = f(x2);
        while (b-a > 2*e) {

            if (f1 < f2) {
                b = x2;
                x2 = x1;
                f2 = f1;
                x1 = a + (3 - sqrt(5)) * (b - a) / 2;
                f1 = f(x1);
            }
            else {
                a = x1;
                x1 = x2;
                f1 = f2;
                x2 = a+(sqrt(5)-1)*(b-a)/2;
                f2 = f(x2);
            }
        }
        double res = (x1+x2)/2;
        System.out.println("golden_method: "+res+" "+f(res)*180/PI);
    }

    public static void parabola_method(double a, double b, double e) {
        double x1, x2 = 0;
        double x = 0;

        x = (a+b)/2;
        x1 = x - df(x)/ddf(x);

        while (x1 - x > e) {
            x = x1;
            x1 = x - df(x)/ddf(x);

        }
        double res = x1;
        System.out.println("parabola_method: "+res+" "+f(res)*180/PI);
    }

    public static double df(double x) {
        return -2*cos(x)+ 1/(cos(x)*cos(x));
    }

    public static double ddf(double x) {
        return 2*sin(x)+ 2*sin(x)/(cos(x)*cos(x));
    }

    public static double t(double x, double xk) {
        return f(x) + df(xk)*(x-xk) + ddf(xk)/2 * (x-xk)*(x-xk);
    }
}
