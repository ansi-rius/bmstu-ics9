/*      45 Последовательность строк с итератором
    по строкам, являющимся подстрокой следующей строки
        в последовательности
*/
import java.util.Iterator;
public class Test {
    public static void main(String[] args) {
        //StringBuilder b = new StringBuilder("qwerty");
        String[] b = {"pine", "pineapple", "pineapplepen", "bob", "bober"};
        Substring strs1 = new Substring(b);

        String[] a = {"igogo"};
        Substring strs2 = new Substring(a);

        String[] c ={};
        //Substring strs3 = new Substring(c);

        String[] d ={"no", "no"};
        Substring strs4 = new Substring(d);

        System.out.println("Test 1");
        for (String s : strs1) System.out.println(s);
        //System.out.println("Test 2");
        //for (String s : strs2) System.out.println(s);
        //System.out.println("Test 3");
        //for (String s : strs3) System.out.println(s);
        System.out.println("Test 4");
        //for (String s : strs4) System.out.println(s);
        Iterator<String> iter = strs4.iterator();
        System.out.println(iter.next());
        System.out.println(iter.next());
        System.out.println(iter.next());
        //strs2.addStr("igogola");
        //System.out.println("Test 5");
        //for (String s : strs2) System.out.println(s);

    }
}
