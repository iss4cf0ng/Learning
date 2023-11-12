import java.awt.*;

public class font {
    static Frame frm = new Frame("Font");
    static Label lab = new Label("Java");
    public static void main(String[] args) {
        frm.setLayout(null);
        frm.setSize(300, 200);
        frm.setBackground(Color.yellow);
        frm.setForeground(Color.blue);
        lab.setForeground(Color.blue);
        lab.setBackground(Color.pink);
        lab.setAlignment(Label.CENTER);
        lab.setLocation(50, 80);
        lab.setSize(150, 50);
        lab.setFont(new Font("Serief", Font.BOLD+Font.ITALIC, 18));
        frm.add(lab);
        frm.setVisible(true);
    }
}
