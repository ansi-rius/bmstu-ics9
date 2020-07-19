import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.Scanner;
import java.util.Queue;

class Vertex {
    int index;
    int key;
    int value;
    int x;
    ArrayList<Integer> vertexes;
    ArrayList<Integer> lens;


    public Vertex(int x) {
        this.x = x;
        vertexes = new ArrayList<>();
        lens = new ArrayList<>();

    }
}

class InitQueue { // все по очереди с приоритетами
    Vertex[] heap;
    int cap;
    int count = 0;
    public InitQueue(int n){
        heap = new Vertex[n];
        cap = n;
    }

    public static void Insert(Vertex[] g, InitQueue q, int ptr){ //3 модуль 1 сем 10+ стр
        int i = q.count;
        q.count = i+1;
        q.heap[i] = g[ptr];
        while((i>0) && (q.heap[(i-1)/2].key > q.heap[i].key)){
            Vertex tmp = q.heap[(i-1)/2];
            q.heap[(i-1)/2] = q.heap[i];
            q.heap[i] = tmp;
            q.heap[i].index = i;
            i = (i-1)/2;
        }
        q.heap[i].index = i;
    }

    public static void DecreaseKey(InitQueue priorityqueue, Vertex ptr, int a, int n) {
        int i = ptr.index;
        ptr.key = a;
        while ((i>0) && (priorityqueue.heap[(i-1)/2]).key > a) {
            Vertex tmp = priorityqueue.heap[(i-1)/2];
            priorityqueue.heap[(i-1)/2] = priorityqueue.heap[i];
            priorityqueue.heap[i] = tmp;
            priorityqueue.heap[i].index = i;
            i = (i-1)/2;
        }
        ptr.index = i;
    }

    public static boolean QueueEmpty(InitQueue q) {
        int empty = 0;
        //if (q.count == empty)
            return (q.count == empty) ? true : false;
    }

    public static Vertex ExtractMin(Vertex[] g, InitQueue q) {
        Vertex ptr = q.heap[0];
        q.count = q.count - 1;
        if (q.count > 0) {
            q.heap[0] = q.heap[q.count];
            q.heap[0].index = 0;
            Heapify(0, q.count, q.heap);
        }
        return ptr;
    }

    public static void Heapify(int i, int n, Vertex[] p) { //2 модуль 1 сема стр 61
        for(;;) {
            int l = 2*i+1;
            int r = l+1;
            int j = i;
            if ((l<n) && (p[i].key > p[l].key))
                i = l;
            if ((r<n) && (p[i].key > p[r].key))
                i = r;
            if (p[i] == p[j])
                break;
            Vertex tmp = p[i];
            p[i] = p[j];
            p[j] = tmp;
            p[i].index = i;
            p[j].index = j;
        }
    }
}

public class Prim {


    private static int MST_Prim(Vertex[] g, int n) {
        for (int v=0; v<g.length; v++) {
            g[v].index = -1;
        }
        int count = 0;
        InitQueue priorityqueue = new InitQueue(n);
        Vertex v = g[0];
        for(;;) {
            v.index = -2;
            for(int i=0; i < g[v.x].vertexes.size(); i++) {
                Vertex u = g[g[v.x].vertexes.get(i)];
                if (u.index == -1) {
                    u.key = g[v.x].lens.get(i); //длину в ключ
                    u.value = v.x; //в значение номер вершины
                    InitQueue.Insert(g, priorityqueue, u.x); //закидываю в очередь
                } else if ((u.index != -2) && (g[v.x].lens.get(i) < u.key)) {
                    u.value = v.x;
                    InitQueue.DecreaseKey(priorityqueue, u, g[v.x].lens.get(i), n);
                } //чем меньше длина - тем больше приоритет
            }
            if (InitQueue.QueueEmpty(priorityqueue)) break;
            v = InitQueue.ExtractMin(g, priorityqueue);
            count += v.key;
        }
        return count;
    }

    public static void main(String[] args) {
         int N, M, u, v, len;

         Scanner in = new Scanner(System.in);
         N = in.nextInt();
         M = in.nextInt();

        Vertex[] g = new Vertex[N];
        for (int i = 0; i < N; i++)
            g[i] = new Vertex(i);

        for (int i = 0; i < M; i++) {
            v = in.nextInt();
            u = in.nextInt();
            len = in.nextInt();
            g[u].vertexes.add(v);
            g[v].vertexes.add(u);
            g[v].lens.add(len);
            g[u].lens.add(len);
        }

        System.out.println(MST_Prim(g, N));
    }
}
