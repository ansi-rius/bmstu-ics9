import java.util.Scanner;

public class Econom {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String s = scanner.nextLine();
        int k = 0;
        while (s.indexOf(')') > 0) {
            s = s.replace(s.substring(s.indexOf(')') - 4, s.indexOf(')') + 1),"ß");
            k++;
        }
        System.out.println(k);
    }
}