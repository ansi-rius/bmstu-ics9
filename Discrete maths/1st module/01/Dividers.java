import java.util.Scanner;
import static java.lang.Math.sqrt;
public class Dividers {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        long number = input.nextLong();
        int length = (int) Math.sqrt(number) *2;
        long array[] = new long[length];

        int k = 1;
        int end;
        int c = 0;

        array[0] = number;

        if (number > 10000) {
            end = (int) Math.sqrt(number)  - 1;
            for (int i = 1; i < (int) Math.sqrt(number); i++) {
                if (number % i == 0 && number/i != 1 && i != 1) {
                    array[end] = i;
                    k++;
                    array[k] = number/i;
                    end--;
                }
            }
        } else {
            end = (int) number;
            array[0] = number;
            for (int i = end-1; i > 1; --i) {
                if (number % i == 0) {
                    array[k] = i;
                    k++;
                }
            }
        }


        if (number > 10000) {
            length = 2*end;
        }


        boolean var;
        
        System.out.println("graph {");
        for (int i = 0; i < length; i++) {
            if (array[i] != 0) {
                array[c] = array[i];
                System.out.println("    "+array[c]);
                c++;
            }
        }

        array[c] = 1;
        System.out.println("    " + array[c]);

        for (int i = 0; i < c+1; i++) {
            for (int j = 0; j < c+1; j++) {
                if ((array[i] != 0) && (array[j] != 0) && (array[i] != array[j]) && (i != j) && (array[i] % array[j] == 0)) {
                    var = true;
                    for (int d = i; d < j; d++) {
                        if ((d != i) && (array[d] != 0) && (array[i] != 0) && (array[j] != 0)  && (array[i] % array[d] == 0) && (array[d] % array[j] == 0) ) {
                            var = false;
                            break;
                        }
                    }
                    if (var) {
                        System.out.println("    " + array[i] + " -- " + array[j]);
                    }
                }
            }
        }

        System.out.println("}");
    }
}

