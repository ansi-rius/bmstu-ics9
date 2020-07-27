import java.util.Scanner;

import static java.lang.Math.*;

public class MethodOfSquares {

    static class Pair {
        double a;
        double b;
        Pair(double a, double b) {
            this.a = a;
            this.b = b;
        }
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);


        int n = 11;

        double[] array_x = new double[n];
        double[] array_y = new double[n];

        array_x[0] = 1;    array_x[5] = 1.85;
        array_x[1] = 1.5;  array_x[6] = 1.86;
        array_x[2]= 1.7;   array_x[7] = 1.88;
        array_x[3] = 1.75; array_x[8] = 1.89;
        array_x[4] = 1.8;  array_x[9] = 1.9;
        array_x[10] = 2.0;

        array_y[0] = 10;    array_y[5] = 23.5;
        array_y[1] = 16.5;  array_y[6] = 24;
        array_y[2]= 20.0;   array_y[7] = 24.5;
        array_y[3] = 21.5;  array_y[8] = 25;
        array_y[4] = 22;    array_y[9] = 25.5;
        array_y[10] = 27.0;

        Pair koef_z1;
        koef_z1 = minimum_squares(array_x, array_y);
        System.out.println("a=" + koef_z1.a + "; b=" + koef_z1.b);

        double[] array_lny = new double[n];

        for (int i=0; i<n; i++) {
            array_lny[i] = log(array_y[i]);
        }
        Pair koef_z3;
        koef_z3 = minimum_squares(array_x, array_lny);
        double aa, bb;
        bb = koef_z3.a;
        aa = exp(koef_z3.b);
        System.out.println("a=" + aa+ "; b=" + bb);


        double a_del;
        double b_del;

        a_del = Math.exp(bb);
        b_del = aa;

        System.out.println("a_del=" + a_del + "; b_del=" + b_del);

        double y_g;
        y_g = sqrt(array_y[0]*array_y[n-1]);

        double x_a;
        x_a = (array_x[0]+array_x[n-1])/2;

        double array_z3;
        array_z3 = a_del*Math.exp(b_del * x_a);


        double delta3;

        delta3 = abs(array_z3 - y_g);
        System.out.println("delta3=" + delta3);

        double delta1;
        delta1 = abs(koef_z1.a*x_a + koef_z1.b);
        System.out.println("delta1=" + delta1);

        //System.out.println("new_a=" + new_a + "; new_b=" + new_b);

    }

    private static Pair minimum_squares(double[] array_x, double[] array_y) {
        double D = 0;
        double C = 0;
        double B = 0;
        double A = 0;

        int n = array_x.length;

        for (int i=0; i<n; i++) {
            B += array_x[i]; //B
            C += array_x[i]*array_y[i]; //C
            D += (array_y[i]); //D
            A += array_x[i]*array_x[i]; //A
        }

        //a = ( sum_xy - sum_x * sum_y)/(n*sum_x2 - sum_x*sum_x);
        //b = (sum_y - a*sum_x)/(n+1);

        //a = ((sum_xy - sum_y*sum_x)/(n+1))/(sum_x2 - sum_x*sum_x/(n+1));
        //b = (sum_y - a*sum_x)/(n+1);

        double a = (C-D*B/(n+1))/(A-B*B/(n+1));
        double b = (D - a*B)/(n+1);



        return new Pair(a, b);
    }
}
