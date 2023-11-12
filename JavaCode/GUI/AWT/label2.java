import java.awt.*;

public class label2 {
    static Frame frm = new Frame("Label2");
    static Label lab1 = new Label();
    static Label lab2 = new Label();
    public static void main(String[] args) {
        frm.setLayout(null);
        frm.setSize(300, 200);
        frm.setBackground(Color.yellow);
        lab1.setText("Java");
        lab1.setForeground(Color.blue);
        lab1.setBounds(50, 50, 100, 30);
        lab2.setText("Python");
        lab2.setForeground(Color.green);
        lab2.setBounds(50, 100, 100, 30);
        frm.add(lab1);
        frm.add(lab2);
        frm.setVisible(true);
    }
}
