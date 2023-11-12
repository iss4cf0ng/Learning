import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class button_anonClass {
    static Frame frm = new Frame("Anonymous class");
    static Button btn = new Button("Click me");
    public static void main(String[] args) {
        frm.setLayout(new FlowLayout());
        frm.setSize(200, 120);;
        frm.setBackground(Color.yellow);
        btn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                frm.setBackground(Color.gray);
            }
        });
        frm.add(btn);
        frm.setVisible(true);
    }
}
