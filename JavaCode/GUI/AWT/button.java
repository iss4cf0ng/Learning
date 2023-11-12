import java.awt.*;

public class button {
    static Frame frm  = new Frame("Button");
    static Button btn = new Button("Click me");
    public static void main(String[] args) {
        frm.setLayout(null);
        frm.setSize(300, 200);
        frm.setBackground(Color.yellow);
        frm.setBounds(100, 80, 100, 50);
        frm.add(btn);
        frm.setVisible(true);
    }
}
