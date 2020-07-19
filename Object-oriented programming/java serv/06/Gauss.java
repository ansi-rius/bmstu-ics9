import java.util.InputMismatchException;
import java.util.Scanner;

class fraction {
        int numerator;
    int denominator;
    fraction (int numerator, int denominator) {
        this.numerator = numerator;
        this.denominator = denominator;
    }
    void prn() {
        //if (denominator == 1)
        //  System.out.print(numerator);
        //else
            System.out.print(numerator + "/" + denominator);
    }
    void add(fraction f) {
        if(f.denominator == this.denominator) {
            this.numerator += f.numerator;
        } else {
            int d = f.denominator * this.denominator; 
            this.numerator = f.denominator * this.numerator + this.denominator * f.numerator;
            this.denominator = d;
        }
        reduce();
    }
    void sub(fraction f) {
        if(f.denominator == this.denominator) {
            this.numerator -= f.numerator;
        } else {
            int d = f.denominator * this.denominator; 
            this.numerator = f.denominator * this.numerator - this.denominator * f.numerator;
            this.denominator = d;
        }
        reduce();
    }
    void mul(fraction f) {
        this.numerator *= f.numerator;
        this.denominator *= f.denominator;
        reduce();
    }
    void div(fraction f) {
        this.numerator *= f.denominator;
        this.denominator *= f.numerator;
        reduce();
    }
    void reduce(){
        int gcd = gcd(this.numerator, this.denominator);
        this.numerator /= gcd;
        this.denominator /= gcd;
        
        int sign=this.numerator*this.denominator;
        this.denominator = Math.abs(this.denominator);
        this.numerator = Math.abs(this.numerator);
        if(sign<0) this.numerator = -this.numerator;
    }
    static int gcd(int a, int b) {
        if(a==0) return b;
        a = a>0 ? a : -a;
        b = b>0 ? b : -b;
        while(a != b) {
            if (a>b) {
                a = a - b;
            } else {
                b = b - a;
            }
        }
        return a;
    }
}

public class Gauss {

    static Scanner s = new Scanner(System.in);
    
    static int enter_dimension() {
        try {
            return s.nextInt();
        } catch (Exception e) {
            return 0;
        }
    }
    
    static fraction [][] enter_matrix(int N) {
        fraction [][] m = new fraction [N][N+1];
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N+1; j++){
                try {
                    m[i][j] = new fraction(s.nextInt(),1);
                } catch (Exception e) {
                    m[i][j] = new fraction(0,1);
                }
            }
        }
        return m;
    }
    
    static void prn(fraction [][] m) {
        for(int i = 0; i < m.length; i++){
            for(int j = 0; j < m[i].length; j++){
                m[i][j].prn();
                System.out.print(" ");
            }
            System.out.println();
        }
        System.out.println();
    }

    static void PrnResult(fraction [][] m,int []order) {
        for(int i = 0; i < m.length; i++){
            int k=0;
            for(; k<order.length; k++){
                if(order[k]==i){
                    break;
                }
            }
            m[k][m[i].length-1].prn();
            System.out.println();
        }
    }
    
    static boolean GaussResult(fraction [][] m,int []order) {
        boolean solution = true;
        fraction d;
        for(int i = 0; i < m.length; i++){
            if(m[i][i].numerator == 0){
                int j = i+1;
                for(; j<m[i].length-1; j++){
                    if(m[i][j].numerator != 0){
                        break;
                    }
                }
                if(j==m[i].length-1){
                    solution = false;
                    break;
                } else {
                    fraction tmp;
                    int ord = order[i]; order[i]=order[j]; order[j]=ord;
                    for(int k = 0; k<m.length; k++){
                        tmp=m[k][i]; m[k][i]=m[k][j]; m[k][j]=tmp;
                    }
                }
            }
            d = new fraction(m[i][i].numerator,m[i][i].denominator);
            for(int j=0; j<m[i].length; j++){
                m[i][j].div(d);
            }
            for(int k = i+1; k<m.length; k++){
                d = new fraction(m[k][i].numerator,m[k][i].denominator);
                for(int j = i; j<m[i].length; j++){
                    fraction sm =new fraction(m[i][j].numerator,m[i][j].denominator);
                    sm.mul(d);
                    m[k][j].sub(sm);
                }
            }
        }
        if(solution)
        {
            for(int i = m.length-1; i > 0; i--){
                //if(m[i][i].numerator == 0){
                //  solution = false;
                //  break;
                //}
                for(int k = i-1; k>=0; k--){
                    d = new fraction(m[k][i].numerator,m[k][i].denominator);
                    for(int j = i; j<m[i].length; j++){
                        fraction sm =new fraction(m[i][j].numerator,m[i][j].denominator);
                        sm.mul(d);
                        m[k][j].sub(sm);
                    }
                }
            }
        }
        return solution;
    }

    public static void main(String[] args) {
        int N = enter_dimension();
        fraction [][] m = enter_matrix(N);

        int []order = new int [N];
        for(int i=0; i<order.length; i++){
            order[i] = i;
        }

        //prn(m);
        
        if(GaussResult(m,order)) {
            //prn(m);
            
            PrnResult(m,order);
        } else {
            System.out.print("No solution");
        }
        
        s.close();
    }

}
