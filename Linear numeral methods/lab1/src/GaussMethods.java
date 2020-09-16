import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Vector;

public class GaussMethods {
    public static void main(String[] args) {

        int vec1_size, vec2_size;

        List<String> lines = new ArrayList<>();
        int line_num = 0;

        try (BufferedReader br = new BufferedReader(new FileReader("/Users/anemone/Desktop/bmstu-ics9/numeral_methods_linear/lab1-1/src/test.txt"))) {

            while (br.ready()) {
                lines.add(br.readLine());
            }
        } catch (IOException e) {
            System.out.println((e.getMessage()));
        }
        vec1_size = Integer.parseInt(lines.get(line_num++));
        vec2_size = Integer.parseInt(lines.get(line_num++));

        double[] vector1 = new double[vec1_size];
        double[] vector2 = new double[vec2_size];

        String[] line = lines.get(line_num++).split(" ");
        for (int i=0; i<vec1_size; i++) {
            vector1[i] = Double.parseDouble(line[i]);
        }
        line = lines.get(line_num++). split(" ");
        for (int i=0; i<vec2_size; i++) {
            vector2[i] = Double.parseDouble(line[i]);
        }
        double res = scalar_product(vector1, vector2);
        System.out.println("Res = "+res);

        int matrix1_width, matrix1_height;
        line_num++;
        line = lines.get(line_num++).split(" ");
        matrix1_width = Integer.parseInt(line[0]);
        matrix1_height = Integer.parseInt(line[1]);

        double[][] matrix1 = new double[matrix1_height][matrix1_width];

        for (int i=0; i<matrix1_height; i++) {
             line = lines.get(line_num++).split(" ");
             for (int k=0; k<matrix1_width; k++) {
                 matrix1[i][k] = Double.parseDouble(line[k]);
             }
        }

        int vec3_size;
        line_num++; //9
        vec3_size = Integer.parseInt(lines.get(line_num++));
        double[] vector3 = new double[vec3_size];

        line = lines.get(line_num++). split(" ");
        for (int i=0; i<vec3_size; i++) {
            vector3[i] = Double.parseDouble(line[i]);
        }

        double[] vres = matrix_vector_product(matrix1, vector3);
        printArray(vres);

        int matrix2_width, matrix2_height;
        line_num++;
        line = lines.get(line_num++).split(" ");
        matrix2_width = Integer.parseInt(line[0]);
        matrix2_height = Integer.parseInt(line[1]);

        double[][] matrix2 = new double[matrix2_height][matrix2_width];

        for (int i=0; i<matrix2_height; i++) {
            line = lines.get(line_num++).split(" ");
            for (int k=0; k<matrix2_width; k++) {
                matrix2[i][k] = Double.parseDouble(line[k]);
            }
        }

        int matrix3_width, matrix3_height;
        line_num++;
        line = lines.get(line_num++).split(" ");
        matrix3_width = Integer.parseInt(line[0]);
        matrix3_height = Integer.parseInt(line[1]);

        double[][] matrix3 = new double[matrix3_height][matrix3_width];

        for (int i=0; i<matrix3_height; i++) {
            line = lines.get(line_num++).split(" ");
            for (int k=0; k<matrix3_width; k++) {
                matrix3[i][k] = Double.parseDouble(line[k]);
            }
        }

        double[][] mres = matrix_product(matrix2, matrix3);
        printMatrix(mres);

        int matrix4_width, matrix4_height;
        line_num++;
        line = lines.get(line_num++).split(" ");
        matrix4_width = Integer.parseInt(line[0]);
        matrix4_height = Integer.parseInt(line[1]);

        double[][] matrix4 = new double[matrix4_height][matrix4_width];
        double[][] matrix4_copy = new double[matrix4_height][matrix4_width];

        for (int i=0; i<matrix4_height; i++) {
            line = lines.get(line_num++).split(" ");
            for (int k=0; k<matrix4_width; k++) {
                matrix4[i][k] = Double.parseDouble(line[k]);
                matrix4_copy[i][k] = Double.parseDouble(line[k]);
            }
        }


        int vec4_size;
        line_num++; //9
        vec4_size = Integer.parseInt(lines.get(line_num++));
        double[] vector4 = new double[vec4_size];

        line = lines.get(line_num++). split(" ");
        for (int i=0; i<vec4_size; i++) {
            vector4[i] = Double.parseDouble(line[i]);
        }

        double[] gres = gauss_method(matrix4, vector4);
        printArray(gres);


        double[] checkRes = matrix_vector_product(matrix4_copy, gres);
        printArray(checkRes);
    }

    public static double scalar_product(double[] a, double[] b) {
        if (a.length != b.length) {
            System.out.println("Wrong lens");
            return -1;
        } else {
            double sum = 0;
            for (int i=0; i<a.length; i++) {
                sum += a[i] *b[i];
            }
            //System.out.println("res of scalar = "+sum);
            return sum;
        }
    }

    public static void printArray(double[] arr) {
        System.out.println("Arr print started:");
        for (int i=0; i<arr.length; i++) {
            System.out.println("    "+arr[i]);
        }
        System.out.println("Arr print ended.");
    }

    public static void printMatrix(double[][] matr) {
        System.out.println("Matr print started:");
        for (int i=0; i<matr.length; i++) {
            System.out.print("    ");
            for (int j=0; j<matr[0].length; j++) {
                System.out.print(matr[i][j]+"  ");
            }
            System.out.println();
        }
        System.out.println("Matr print ended.");
    }

    public static double[] matrix_vector_product(double[][] A, double[] b) {
        if (A[0].length != b.length) {
            System.out.println("Wrong lens");
            System.out.println(A[0].length+"   "+b.length);
            return null;
        } else {
            double[] res = new double[b.length];
            for (int i=0; i<A[0].length; i++) {
                //System.out.println("i= "+i);
                //System.out.println(A.get(i));
                res[i] = scalar_product(A[i], b);
            }
            return res;
        }
    }

    public static double[][] matrix_product(double[][] A, double[][] B) {
        if (A[0].length != B.length) {
            System.out.println("Wrong lens");
            System.out.println(A[0].length+"  "+B.length);
            return null;
        } else {
            double[][] res = new double[B.length][B.length];

                for (int i = 0; i < A[0].length; i++) {
                    double[] column = new double[B.length];
                    for (int j = 0; j < B.length; j++) {
                        column[j] = B[j][i];
                    }
                    for (int k=0; k<A.length; k++) {
                        res[k][i] = scalar_product(A[k], column);
                    }
                }

            return res;
        }
    }

    public static double[] gauss_method(double[][] A, double[] y) {
        double[] x = new double[A.length];
        int k=0;
        int n = A.length;
        while (k<n) {
            // Поиск строки с максимальным a[i][k] -- подъем строки с наибольшим элементом, чтобы под главной диагональю были нули
            double max = Math.abs(A[k][k]); //чтобы на главной диагонали не было нулевых элементов
            int index = k;
            for (int i = k + 1; i < n; i++) {
                if (Math.abs(A[i][k]) > max) {
                    max = Math.abs(A[i][k]);
                    index = i;
                }
            }
            for (int j = 0; j < n; j++)
            {
                double temp = A[k][j];
                A[k][j] = A[index][j];
                A[index][j] = temp;
            }
            double temp = y[k]; //свобод вектор
            y[k] = y[index];
            y[index] = temp;
            // Нормализация уравнений
            for (int i = k; i < n; i++)
            {
                temp = A[i][k];
                for (int j = 0; j < n; j++)
                    A[i][j] = A[i][j] / temp;
                y[i] = y[i] / temp; //свобод вектор
                if (i == k)  continue; // уравнение не вычитать само из себя
                for (int j = 0; j < n; j++)
                    A[i][j] = A[i][j] - A[k][j];
                y[i] = y[i] - y[k];
            }
            k++;
        }
        // обратная подстановка
        for (k = n - 1; k >= 0; k--)
        {
            x[k] = y[k];
            for (int i = 0; i < k; i++)
                y[i] = y[i] - A[i][k] * x[k];
        }
        return x;
    }

}
