import java.awt.*;

public class gridLayout {
    static Frame frm = new Frame("GridLayout");
    public static void main(String[] args) {
        GridLayout obj = new GridLayout(2, 3);
        frm.setLayout(obj);
        frm.setSize(300, 200);
        frm.add(new Button("1"));
        frm.add(new Button("2"));
        frm.add(new Button("3"));
        frm.add(new Button("4"));
        frm.add(new Button("5"));
        frm.add(new Button("6"));
        frm.add(new Button("7"));
        frm.setVisible(true);
    }
}
