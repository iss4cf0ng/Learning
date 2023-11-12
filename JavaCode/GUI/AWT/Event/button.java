import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class button {
    static Frame frm = new Frame("Button");
    static Button btn = new Button("Click me");

    static class MyListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            frm.setBackground(Color.gray);
        }
    }
    public static void main(String[] args) {
        frm.setLayout(new FlowLayout());
        frm.setSize(200, 120);
        frm.setBackground(Color.yellow);
        btn.addActionListener(new MyListener());
        frm.add(btn);
        frm.setVisible(true);
    }
}
