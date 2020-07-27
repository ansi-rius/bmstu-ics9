public class Lab4 {
    private static double countY (double s) {
        return (Math.exp(3*s)+Math.exp(4*s) + 5/12);
    }
    private static double[] solve_matrix(int n, double[] a, double[] b, double[] c, double[] d) {
        double[] diag_a = b; double[] diag_b = c; double[] diag_c = a; double[] free_d = d;
        double[] alpha = new double[n]; double[] beta = new double[n]; double [] x = new double[n];
        if (diag_a[0] != 0) {
            alpha[0] = - diag_b[0]/diag_a[0];
        } else {
            System.out.println("a[0] = 0 error"); return null;
        }
        beta[0] = free_d[0] / diag_a[0];
        for (int i=1; i<n-1; i++) {
            alpha[i] = -(diag_b[i])/(alpha[i-1]*diag_c[i-1] + diag_a[i]);
            beta[i] = (free_d[i]-diag_c[i-1]*beta[i-1])/(alpha[i-1]*diag_c[i-1] + diag_a[i]);
        }
        beta[n-1] = (free_d[n-1]-diag_c[n-2]*beta[n-2])/(alpha[n-2]*diag_c[n-2]
                + diag_a[n-1]);
        x[n-1] = beta[n-1];
        for (int i=n-2; i>=0; i--) {
            x[i] = alpha[i]*x[i+1] + beta[i];
        }
        return x;
    }

    public static void main(String[] args) {
        int N = 10;
        double a = 0, b = 1;
        double h = (b-a)/(float)N;
        N++;
        double[] x = new double[N];
        for (int i = 0; i < N; i++) {
            x[i] = i / 10.0;
        }
        double A = countY(a), B = countY(b);

        double[] a1 = new double[N-1];
        double[] b1 = new double[N];
        double[] c = new double[N-1];
        double[] d = new double[N];

        b1[0] = 1;
        c[0] = 0;
        d[0] = A;

        for (int i = 0; i < N-2; i++) {
            a1[i] = (1 + 1.0 / 10);
        }
        a1[N-2] = 0;

        for (int i = 1; i<N-1; i++) {
            b1[i] = 2.0/100-2;
            c[i] = 1 - 1.0/10;
            d[i] = 2*x[i]/100;
        }
        b1[N-1] = 1;
        d[N-1] = B;
        double[] solution = solve_matrix(N, a1, b1, c, d);
        for (int i = 0; i < N; i++) {
            System.out.println(x[i] + "   " + countY(x[i])+ " "+
                    solution[i]+ "   "+ Math.abs(countY(x[i]) - solution[i])); }
    }
}
