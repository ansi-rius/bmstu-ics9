import java.util.AbstractSet;
import java.util.ArrayList;
import java.util.Iterator;

public class SparseSet<T extends Hintable> extends AbstractSet<T> {
    private int n;
    //private T[] dense;
    private ArrayList<T> dense;

    SparseSet() {
        n = 0;
        dense = new ArrayList<T>();
    }

    @Override
    public Iterator<T> iterator() {
        return new HintsIterator();
    }

    private class HintsIterator implements Iterator<T> {
        private int pos = 0;

        public boolean hasNext() {
            return pos < n;
        }

        public T next() {
            if (hasNext())
                return dense.get(pos++);
            throw new IllegalArgumentException("End");
        }

        public void remove() {
            SparseSet.this.remove(dense.get(pos-1));
        }
    }

    public boolean contains(Object o) {
        T z = (T) o;
        //int c = (int) o;
        //if ((z.hint()>=0) && (z.hint()<n) && (dense[z.hint()] == z)) return true;
        if ((z.hint()>=0) && (z.hint()<n) && (dense.get(z.hint()) == z)) return true;

        else return false;
    }

    public boolean add(T x) {
        if (!contains(x)) {
            //dense[n] = x;
            dense.add(x);
            x.setHint(n);
            n++;
            return true;
        }else return false;
    }

    public boolean remove(Object h){ //z=2 low= 2
        T z = (T) h;
        if (contains(z)) {

            dense.set(z.hint() , dense.get(n-1));
            dense.get(n-1).setHint(z.hint());

            n--;
            return true;
        }
        return false;
    }
    
    public int size() {
        return n;
    }

    public void clear() {
        n=0;
    }
}