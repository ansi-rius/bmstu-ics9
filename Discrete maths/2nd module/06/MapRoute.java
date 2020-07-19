import java.util.Map;
import java.util.PriorityQueue;
import java.util.Scanner;

class Vertex implements Comparable<Vertex> {
    public int mark;  //метка - по началу там беск. число, потом при проходе верш
    public int x;     //номер вершины                   //меняем на длину пути
    public int ii,jj; //координаты в матрице
    public boolean used; //проходили ли эту верш
    public Vertex(int x, int ii, int jj) {
        this.x=x;
        this.ii =ii;
        this.jj=jj;
        this.used=false;
        this.mark=66666;
    }
    public int compareTo(Vertex o) {
        return this.mark-o.mark;
    }
}

public class MapRoute {
    public static boolean Relax(Vertex v, Vertex u) { //релаксирование
        return (v.mark > (u.mark+v.x));
    }

    public static void DecreaseKey(PriorityQueue<Vertex> qu, Vertex v, Vertex u) {
        v.mark = u.mark + v.x;
        qu.add(v);
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n, x, i, j, north, south, east, west;
        n = in.nextInt();
        PriorityQueue<Vertex> qu = new PriorityQueue<>();

        Vertex[][] m = new Vertex[n][n];

        for (i=0; i<n; i++) {
            for (j = 0; j<n; j++) {
                x = in.nextInt();
                m[i][j] = new Vertex(x,i,j);
            }
        }
        in.close();
        m[0][0].mark = 0; // задаём начало, ответ должен накопиться в mark m[n][n]
        Vertex v=m[0][0];
        for (int t=0;t<n*n; t++) {
            i=v.ii; j=v.jj;
            north = i+1; east = j+1;  //шаги по матрице: север, восток
            south = i-1; west = j-1;  //                 юг,    запад
            if(south>=0 && !m[south][j].used && Relax(m[south][j],m[i][j]))
                DecreaseKey(qu, m[south][j], m[i][j]);
            if(north<n && !m[north][j].used && Relax(m[north][j],m[i][j]))
                DecreaseKey(qu, m[north][j], m[i][j]);
            if(west>=0 && !m[i][west].used && Relax(m[i][west],m[i][j]))
                DecreaseKey(qu, m[i][west], m[i][j]);
            if(east<n && !m[i][east].used && Relax(m[i][east],m[i][j]))
                DecreaseKey(qu, m[i][east], m[i][j]);

            m[i][j].used=true;
            if(!qu.isEmpty())
                v=qu.remove();
        }
        m[n-1][n-1].mark += m[0][0].x;
        System.out.print(m[n-1][n-1].mark);
    }
}