public class Lab4 {
    //Методы Рунге-Кутта численного решения задачи Коши...

    public static void main(String[] args) {
        double x0, y0, y1, y0_1, z1;
        double k1, k2, k4, k3;
        double p, q, h, n, a, b;

        x0 = 0;
        y0 = 1;
        y0_1 = 2; //y'

        a = 0.0;
        b = 1.0;
        n = 10;

        h = (b - a)/n; // шаг

        //2 вариант p = -7; q = 12
        p = -7;
        q = 12;

        System.out.println("\t   X\t\t   Y\t\t   Y'");
        for (; x0 < b-h; x0 += h) {

            k1 = h * f(x0, y0, y0_1, p, q);

            k2 = h * f(x0 + h/2.0, y0 + (h * y0_1)/2.0, y0_1 + k1/2.0, p, q);

            k3 = h * f(x0 + h / 2.0, y0 + (h * (y0_1 + k1 / 2.0)) / 2.0, y0_1 + k2 / 2.0, p, q);

            k4 = h * f(x0 + h, y0 + (h * (y0_1 + k2 / 2.0)), y0_1 + k3, p, q);

            z1 = y0_1 + (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;
            y1 = y0 + ((h * y0_1) + 2.0 * (h * (y0_1 + k1 / 2.0)) + 2.0 * (h * (y0_1 + k2 / 2.0))+ (h * (y0_1 + k3))) / 6.0;

            System.out.printf("\t %.4f \t %.4f \t %.4f \n", (x0+h), y1, z1);
            y0 = y1;
            y0_1 = z1;
        }

    }

    //2 вариант f(x) = 5
    public static double f(double x, double y, double z, double p, double q) {
        return (5 - p*z - q*y);
    }

}