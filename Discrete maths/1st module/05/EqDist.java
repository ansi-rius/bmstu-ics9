import java.util.*;

class Vertex {
    boolean mark;

    ArrayList<Integer> data_about_vertexes;
    public Vertex() {
        data_about_vertexes = new ArrayList<>();
    }
}

public class EqDist {

    private void BFS(int k, int[][] distances_between_u_v, int v_help, Vertex[] g){ //лекции стр 51
        for (int q=0; q<g.length; q++)
            g[q].mark = false;
        ArrayDeque<Integer> queue = new ArrayDeque();
        for (int w=0; w<g.length; w++) {
            if (!g[w].mark) {
                g[v_help].mark = true;
                queue.add(v_help);
                distances_between_u_v[k][v_help] = 0;
                while (!queue.isEmpty()) {
                    int q = queue.pop();
                    for (int i = 0; i < g[q].data_about_vertexes.size(); i++) {
                        int y = g[q].data_about_vertexes.get(i);
                        if (!g[y].mark) {
                            g[y].mark = true;
                            queue.add(y);
                            distances_between_u_v[k][y] = distances_between_u_v[k][q] + 1;
                        }
                    }
                }
            }
        }
    }

    public static void main(String[] args) {

        int N, M, K, v, u, v_help;

        //ArrayList<Integer> list = new ArrayList();
        int[] list = new int[100000];

        Scanner in = new Scanner(System.in);
        N = in.nextInt();
        M = in.nextInt();

        Vertex[] g = new Vertex[N];
        for (int i = 0; i < N; i++)
            g[i] = new Vertex();

        for (int i = 0; i < M; i++) {
            v = in.nextInt();
            u = in.nextInt();
            g[u].data_about_vertexes.add(v);
            g[v].data_about_vertexes.add(u);
        }

        EqDist eq = new EqDist();
        K = in.nextInt();
        int[][] distances_between_u_v = new int[K][N];
        int ind = 0;

        for (int i = 0; i < K; i++) {
            for (int j = 0; j < N; j++)
                distances_between_u_v[i][j] = 666;
            v_help = in.nextInt();
            eq.BFS(i, distances_between_u_v, v_help, g);
        }


        for (int i = 0; i < N; i++) {
            //int res = 1;
            boolean res = true;
            for (int j = 1; j < K; j++) {
                if ((distances_between_u_v[j][i] == 666) || (distances_between_u_v[j-1][i] != distances_between_u_v[j][i]))
                    res = false;
            }

            if (res) {
                list[ind] = i;
                //System.out.println("list["+ind+"] ="+list[ind]);
                ind++;
                //System.out.println("i= "+i);
            }
            //System.out.println("i= "+i);
        }

        //Arrays.sort(list); сортировка не нужна в блоке if выше всегда будет
        //System.out.println("ind ="+ind);       расстанавливаться по возрастанию
        if (ind == 0)
            System.out.println("-");
        else
            for(int i = 0; i < ind; i++)
                System.out.print(list[i] + " ");
    }
}