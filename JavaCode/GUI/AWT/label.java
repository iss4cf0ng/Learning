import java.awt.*;

public class label {

    static Frame frm = new Frame("label test");
    static Label lab = new Label("Here is the test", Label.CENTER);
    public static void main(String[] args) {
        frm.setSize(300, 200);
        frm.setBackground(Color.yellow);
        lab.setForeground(Color.black);
        frm.add(lab);
        frm.setVisible(true);
    }
}
