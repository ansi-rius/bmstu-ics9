import javax.swing.*;   //45
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class paint {
    private JPanel mainPanel;
    private JSpinner speedSpinner;
    private JTextField areaField;
    private CanvasPanel canvasPanel;
    private JSpinner alphaSpinner;
    private JSpinner gSpinner;

    int V, a, g;
    static double area;

    public paint() {
        speedSpinner.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                V = (int) speedSpinner.getValue();
                a = (int) alphaSpinner.getValue();
                g = (int) gSpinner.getValue();

                canvasPanel.setValues(V,a,g);
                double d = (a*Math.PI)/180;

                area = ((V*V) * (Math.sin(d)*Math.sin(d)))/(2*g);
                areaField.setText(String.format("%.2f", area));
            }
        });
        alphaSpinner.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                V = (int) speedSpinner.getValue();
                a = (int) alphaSpinner.getValue();
                g = (int) gSpinner.getValue();

                canvasPanel.setValues(V,a,g);
                double d = (a*Math.PI)/180;

                area = ((V*V) * (Math.sin(d)*Math.sin(d)))/(2*g);

                areaField.setText(String.format("%.2f", area));
            }
        });
        gSpinner.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                V = (int) speedSpinner.getValue();
                a = (int) alphaSpinner.getValue();
                g = (int) gSpinner.getValue();

                canvasPanel.setValues(V,a,g);
                double d = (a*Math.PI)/180;

                area = ((V*V) * (Math.sin(d)*Math.sin(d)))/(2*g);

                areaField.setText(String.format("%.2f", area));
            }
        });
        alphaSpinner.setValue(30);
        gSpinner.setValue(20);
        speedSpinner.setValue(70);
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Окружность");
        frame.setContentPane(new paint().mainPanel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);
    }
}