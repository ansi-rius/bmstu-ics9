import java.util.AbstractSet;
import java.util.Iterator;

public class IntSparseSet extends AbstractSet<Integer> {
    private int[] sparse; //числа
    private int[] dense; //их индексы
    private int n;
    private int low, high;

    public IntSparseSet(int low, int high) {
        n=0;
        this.low=low;
        this.high = high;
        dense=new int[high-low];
        sparse=new int[high-low];
    }

    public Iterator<Integer> iterator() {
        return new IntIterator();
    }

    private class IntIterator implements  Iterator<Integer> {
        private int pos = 0;

        public boolean hasNext() {
            return pos < n;
        }

        public Integer next() {
            if (hasNext())
                return dense[pos++];
            throw new IllegalArgumentException("End");
        }

        public void remove() {
            IntSparseSet.this.remove(dense[pos-1]);
        }
    }

    public int size() {
        return n;
    }

    public boolean contains(Object o) {
        int z = (int) o;
        if ((z < high && z >= low) && (sparse[z-low]>=0) && (sparse[z-low]<n) && (dense[sparse[z-low]] == z)) return true;
        else return false;
    }

    public boolean add(Integer elem) {
        if (elem<high && elem>=low && !contains(elem)) {
            dense[n]=elem;
            sparse[elem-low]=n;
            n++;
            return true;
        }else return false;
    }

    public boolean remove(Object h){ //z=2 low= 2
        int z = (int) h;
        if (contains(z)) {
            dense[sparse[z-low]] = dense[n-1];
            sparse[dense[n-1] - low] = sparse[z-low];
            //dense[n-1] = 0;
            //sparse[z] = 0;
            n--;
            return true;
        }
        return false;
    }

    public void clear() {
        n=0;
    }
}