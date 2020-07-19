import java.util.ArrayList;
import java.util.Scanner;

class Vertex {
    int u, v;
    ArrayList<Integer> lists;
    public Vertex() {
        lists = new ArrayList<>();
    }
}
public class BridgeNum {

    public static int bridges, timer;
    public static Vertex[] g;
    public static Boolean[] oldtrash;
    public static Integer[] inG;
    public static Integer[] fup;

    public static void dfs(int v, int p){
        inG[v] = fup[v] = timer++;
        oldtrash[v] = true; //вместо окрашивания пройденных вершин черным/серым цветом,
        for (int i = 0; i<g[v].lists.size(); ++i) { //использую булеан и массив используемых
            int where = g[v].lists.get(i);            //"oldtrash"
            if (where == p) continue;
            if (oldtrash[where]) {
                fup[v] = min(fup[v], inG[where]);
            } else {
                dfs(where, v);
                fup[v] = min(fup[v], fup[where]);
                if (fup[where] > inG[v])
                    bridges++;
            }
        }
    }

    public static int min(int a, int b) {
        return (a < b) ? a:b;
    }

    public static void FindBridges(int N){
        timer = 0;
        for (int i = 0; i < N; ++i)
            oldtrash[i] = false;
        for (int i = 0; i < N; ++i)
            if (!oldtrash[i])
                dfs(i, -1);
    }

    public static void main(String[] args) {
        int N, M, v, u;


        Scanner in = new Scanner(System.in);
        N = in.nextInt();
        M = in.nextInt();

        g = new Vertex[N];
        oldtrash = new Boolean[N];
        inG = new Integer[N];
        fup = new Integer[N];

        for (int i = 0; i < N; i++)
            g[i] = new Vertex();

        for (int i=0; i<M; i++) {
            v = in.nextInt();
            u = in.nextInt();
            g[u].lists.add(v);
            g[v].lists.add(u);
        }

        FindBridges(N);

        System.out.println(bridges);
    }
}
