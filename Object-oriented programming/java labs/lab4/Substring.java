/*      45 Последовательность строк с итератором
    по строкам, являющимся подстрокой следующей строки
        в последовательности
*/
import java.util.Iterator;
import java.util.Arrays;
import java.util.ArrayList;

public class Substring implements Iterable<String> {
    public ArrayList<String> strings = new ArrayList<>();

    Substring(String[] arr) {
        strings.addAll(Arrays.asList(arr)); //загоняю все значения массива из теста в список
    }

    public void addStr(String str) {
        strings.add(str);
    }

    public String getStr(int index) {
        return strings.get(index);
    }

    public boolean checkStr(String str) {
        return strings.contains(str);
    }

    public int getSize() {
        return strings.size();
    }

    public void deleteStrings() {
        strings.clear();
    }

    public Iterator <String> iterator() {
        return new SubstringIterator();
    }

    private class SubstringIterator implements Iterator<String> {
        private int pos;

        SubstringIterator() {
            pos = 0;
        }

    /*    public boolean hasNext() {
            //System.out.println("size= "+(strings.size() - 1));
            //System.out.println("pos= "+pos);
           if (pos < strings.size() - 1) {
                //System.out.println("size = "+strings.size());
                //System.out.println("послед индекс = "+strings.get(pos+1).lastIndexOf(strings.get(pos)));
                //System.out.println("длина слова= "+(strings.get(pos+1)).length());
            //    System.out.println("pos= "+pos);
                return ((strings.get(pos+1).lastIndexOf(strings.get(pos)) >= 0) && (pos < strings.size() - 1));
            } else {
            //    System.out.println("f");
            //    System.out.println("pos= "+pos);
                return false;
            }
        }*/

        public boolean hasNext() {
            if (strings.size() < 2){
                //System.out.println("  Need 2 or more arguments");
                throw new IllegalArgumentException("Need 2 or more arguments");
                //return false;
            }
            if (pos < strings.size() - 1) {
                while (!((pos < strings.size() - 1) && (strings.get(pos + 1).lastIndexOf(strings.get(pos)) >= 0))) {
                    if (strings.get(pos).equals("")) {
                        pos++;
                        throw new IllegalArgumentException("  You entered empty string");
                        //System.out.println("  You entered empty string");
                        //pos++;
                    }
                    if (strings.get(pos+1).equals("")) {
                        pos+=2;
                        throw new IllegalArgumentException("  You entered empty string");
                        //System.out.println("  You entered empty string");
                    }
                    pos++;
                }
                return ((strings.get(pos + 1).lastIndexOf(strings.get(pos)) >= 0) && (pos < strings.size() - 1));
            } else {
                return false;
            }
        }

        public String next() {
            if (hasNext()) {
                return strings.get(pos++);
            }
            throw new IllegalArgumentException("  End");
        }
    }
}