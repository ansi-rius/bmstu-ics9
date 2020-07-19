import java.util.Scanner;
import java.util.Stack;

class Vertex {
        int n;
    int T1;
    int T2;
    int low;
    int comp;
    Vertex(int n){
        this.n = n;
        T1 = 0;
        T2 = 0;
        low = 0;
        comp = 0;
    }
}

class Edge {
    int u;
    int v;
}

class Graph {
    Vertex[] V;
    Edge[] E;
    Graph(int N, int M, Edge[] E){
        V = new Vertex[N];
        for(int i=0; i<N; i++)
        {
            V[i] = new Vertex(i);
        }
        this.E = E;
    }
    void OutE(){
        for(Vertex v: V){
            System.out.printf("v = %d, comp = %d, low = %d, T1 = %d\n", v.n, v.comp, v.low, v.T1);
        }
        for(Edge e: E){
            System.out.printf("u = %d, v = %d\n", e.u, e.v);
        }
    }
}

public class GraphBase {
    
    public static int time = 1;
    public static int count = 1;

    public static void VisitVertex_Tarjan(Graph G, Vertex v, Stack<Vertex> s) {
        v.T1 = v.low = time; time = time + 1;
        s.push(v);
        for(int i = 0; i<G.E.length; i++){
            if(G.V[G.E[i].u].T1 == 0){
                VisitVertex_Tarjan(G, G.V[G.E[i].u], s);
            }
            if(G.V[G.E[i].u].comp == 0 && G.V[G.E[i].v].low > G.V[G.E[i].u].low){
                G.V[G.E[i].v].low = G.V[G.E[i].u].low;
            }
        }
        if( v.T1 == v.low ){
            Vertex u;
            do {
                u = s.pop();
                u.comp = count;
            } while (u.n != v.n);
            count = count + 1;
        }
    }

    public static void Tarjan(Graph G){
        for(int i=0; i<G.V.length; i++){
            G.V[i].T1 = G.V[i].comp = 0;
        }
        Stack<Vertex> s = new Stack<>();
        for(int i=0; i<G.V.length; i++){
            if(G.V[i].T1 == 0){
                VisitVertex_Tarjan(G, G.V[i], s);
            }
        }
    }

    public static void main(String[] args) {
        // TODO Auto-generated method stub
        Scanner in = new Scanner(System.in);
        int N = in.nextInt();
        int M = in.nextInt();
        Edge[] E = new Edge[M];
        for(int i=0; i<M; i++){
            E[i] = new Edge();
            E[i].u = in.nextInt();
            E[i].v = in.nextInt();
        }
        Graph G = new Graph(N,M,E);
        Tarjan(G);
        //System.out.printf("%d\n", count);
        //G.OutE();
        boolean out = false;
        for(Vertex v: G.V){
            //if(v.low == v.T1 && v.low != 1){
            if(v.low == v.T1){
                
                int c = v.comp;
                int qc = 0;
                for(Vertex vc: G.V){
                    if(vc.comp == c) qc++;
                }
                
                int l = v.low;
                int ql = 0;
                for(Vertex vc: G.V){
                    if(vc.low == l) ql++;
                }
                
                
                int u = -1;
                boolean f = false;
                for(Edge e: G.E){
                    if(e.v == v.n) {
                        f = true;
                        u = e.u;
                        break;
                    }
                }
                
                boolean g = false;
                if(f){
                    for(Edge e: G.E){
                        if(e.v == u && e.u == v.n && v.n !=0) {
                            g = true;
                            break;
                        }
                    }
                }

                //if(qc>1 && ql == 1){
                if( !f || g && (qc>1 && ql > 1)){
                    out = true;
                    System.out.printf("%d ", v.n);
                }
            }
        }
        if(!out){
            System.out.printf("%d ", 0);
        }
        in.close();
    }

}
