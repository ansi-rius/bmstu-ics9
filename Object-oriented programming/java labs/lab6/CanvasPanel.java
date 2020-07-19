import javax.swing.*;
import java.awt.*;

public class CanvasPanel extends JPanel {
    private int v = 70;
    private int gr = 20;
    private int a = 30;

    public void setValues(int sp, int al, int gra /*,int ress*/) {
        gr = gra;
        a = al;
        v = sp;
        repaint();
    }

    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        //g.setColor(Color.RED);
        //g.drawOval(10, 10, radius, radius);

        double d = (a*Math.PI)/180;
        int res = (int) ((v*v) * (Math.sin(d)*Math.sin(d)))/(2*gr);
        //int res = (int) paint.getRes();

        g.drawLine(20, 300-res, 25, 300-res);
        //g.drawString( res+""+"м" , 30, 300-res); //сколько метров

        //* убрать пунктир?
        g.drawLine(40, 300-res, 45, 300-res);
        g.drawLine(60, 300-res, 65, 300-res);
        g.drawLine(80, 300-res, 85, 300-res);
        g.drawLine(100, 300-res, 105, 300-res);
        g.drawString( res+""+"м" , 30, 297-res); //сколько метров
        // */

        //все по осям
        g.drawLine(20, 10, 20, 350); //Y
        g.drawLine(20, 350, 350, 350); //X
        g.drawString("Y", 25, 15);
        g.drawString("X", 350, 346);
        g.drawString("0", 7, 360);
        g.drawOval(17,348,5,5);
        g.fillOval(17,348,5,5);
        //верхняя точка траектории
        g.drawOval(120,297-res,5,5);
        g.fillOval(120,297-res,5,5);
        //чёртов овал
        g.drawArc(20, 300-res, 200,  100+2*res, 0, 180);
    }
}
