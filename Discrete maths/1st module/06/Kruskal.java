import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

class Vertex{
    int x;
    int y;
    int depth = 0;
    Vertex parent;

    public Vertex (int x, int y) {
        this.x = x;
        this.y = y;
        parent = this;
    }
}

class Length implements Comparable<Length> {

    int u;
    int v;
    int len;

    Length(int u, int v, int len) {
        this.len = len;
        this.u = u;
        this.v = v;
    }

    public int compareTo(Length obj) {
        return this.len - obj.len;
    }
}



public class Kruskal {

    public static Vertex Find(Vertex x) { //НЕ наивный find 3 модуль стр 113
        Vertex root;
        if (x.parent == x)
            root = x;
        else {
            x.parent = Find(x.parent);
            root = x.parent;
        }
        return root;
    }

    public static void Union(Vertex x, Vertex y) { //НЕ наивный юнион 3 модуль стр 112
        Vertex root_x = Find(x);
        Vertex root_y = Find(y);
        if (root_x.depth < root_y.depth)
            root_x.parent = root_y;
        else {
            root_y.parent = root_x;
            if ((root_x.depth == root_y.depth) && (root_x != root_y))
                root_x.depth++;
        }
    }

    public static double SpanningTree(Vertex[] g, List<Length> len, int N) {
        double E = 0;
        short i =0; short e = 0;
        int u,v;
        int size = N*(N-1)/2;
        while (i < size && e < N-1) {
            u = len.get(i).u;
            v = len.get(i).v;
            if (Find(g[u]) != Find(g[v])) {
                E = E + Math.sqrt(len.get(i).len);
                Union(g[u], g[v]);
                e++;
            }
            i++;
        }
        return E;
    }

    public static void main(String[] args) {
        int N;
        int x, y;
        Scanner in = new Scanner(System.in);
        N = in.nextInt();

        Vertex[] g = new Vertex[N];

        ArrayList<Length> len = new ArrayList<>();
        for (int i = 0; i < N; i++) {
            x = in.nextInt();
            y = in.nextInt();
            g[i] = new Vertex(x, y);
        }

        int length;
        for ( int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                length = (g[i].x - g[j].x)*(g[i].x - g[j].x) + (g[i].y - g[j].y)*(g[i].y - g[j].y);
                len.add(new Length(i, j, length));
            }
        }
        Collections.sort(len);
        System.out.printf("%.2f", SpanningTree(g, len, N));
    }
}
