import java.awt.*;

public class textArea {
    static Frame frm = new Frame("TestArea");
    static TextArea txt = new TextArea("TextArea", 2, 20, TextArea.SCROLLBARS_VERTICAL_ONLY);

    public static void main(String[] args) {
        frm.setLayout(null);
        frm.setSize(300, 200);
        frm.setBackground(Color.yellow);
        txt.setBounds(30, 40, 150, 50);
        frm.add(txt);
        frm.setVisible(true);
    }
}
