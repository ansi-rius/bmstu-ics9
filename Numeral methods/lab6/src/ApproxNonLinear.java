public class ApproxNonLinear {
    public static void main(String[] args) {
        //2 вариант
        // A=1 B=-3 C=0 D=3
        //f(x) = x^3 - 3x^2 +3


        divideOnHalf(-10.0, 0.0);
        divideOnHalf(0.0, 2.0);
        divideOnHalf(2.0, 10.0);

        newton(-1.0, 0.0);
        newton(1.0, 1.5);
        newton(2.0, 3.0);

    }

    static void divideOnHalf(double a, double b){
        double x = 0;
        double a1 = a;
        double b1 = b;
        double e = 0.001;
        double k=0;
        while (b1-a1 > 2*e) {
            x = (a1+ b1)/2;
            if (f(a) * f(x) < 0) {
                b1 = x;
            } else {
                a1 = x;
            }
            k++;
        }
        System.out.println("Divide method: "+(a1+b1)/2);
        System.out.println("Num of steps: "+k);
    }

    public static double sgn(double x) {
        if (x>0) return 1;
        else if (x==0) return 0;
        else return -1;
    }

    static void newton(double a, double b) {
        double x0 = 0;
        double x1 = 0;
        double e = 0.001;

        if (f(a)*f_derivative2(a) > 0){
            x0 = a;
        }else{
            x0 = b;
        }
        int k = 0;
        while (true) {
            x1 = x0 -f(x0)/f_derivative(x0);
            k++;
            if ((f(x1)*f(x1 + sgn(x1-x0)*e))<0){
                break;
            }
            x0 = x1;

        }
        System.out.println("Newton method: "+x1);
        System.out.println("Num of steps: "+k);
    }

    static double f(double x) { return (1)*x*x*x + (-3)*x*x + (0)*x + (3); }

    static double f_derivative(double x) { return 3*x*x + (-6)*x; }

    static double f_derivative2(double x) {
        return 6*x - 6;
    }
}
