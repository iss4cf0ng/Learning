import java.awt.*;

public class layoutManagers {
    static Frame frm = new Frame("LayoutManagers");
    public static void main(String[] args) {
        BorderLayout obj = new BorderLayout(4, 2);
        frm.setLayout(obj);
        frm.setSize(300, 200);
        frm.add(new Button("East"), obj.EAST);
        frm.add(new Button("West"), obj.WEST);
        frm.add(new Button("South"), obj.SOUTH);
        //frm.add(new Button("North"), obj.NORTH);
        //frm.add(new Button("Center"), obj.CENTER);

        frm.setVisible(true);
    }
}
