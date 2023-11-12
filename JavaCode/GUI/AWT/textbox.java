import java.awt.*;

public class textbox {
    static Frame frm = new Frame("TextField");
    static TextField txt1 = new TextField("Editable");
    static TextField txt2 = new TextField("unEditable");
    static TextField txt3 = new TextField("marked by symbol");
    public static void main(String[] args) {
        frm.setLayout(null);
        frm.setSize(300, 200);
        frm.setBackground(Color.yellow);
        txt1.setBounds(30, 40, 150, 20);
        txt2.setBounds(30, 80, 150, 20);
        txt3.setBounds(30, 120, 150, 20);
        txt2.setEditable(false);
        txt3.setEchoChar('*');
        frm.add(txt1);
        frm.add(txt2);
        frm.add(txt3);
        frm.setVisible(true);
    }
}
