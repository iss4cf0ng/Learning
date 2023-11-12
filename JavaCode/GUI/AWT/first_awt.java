import java.awt.*;

public class first_awt {
    public static void main(String[] args) {
        Frame frm = new Frame("My first AWT Windows application");
        frm.setSize(200, 150);
        frm.setBackground(Color.yellow);
        frm.setLocation(200, 100);
        frm.setVisible(true);
        frm.setName("MyWindows");

        System.out.println("Windows x coord : " + frm.getX());
        System.out.println("Windows y coord : " + frm.getY());
        System.out.println("Windows height : " + frm.getHeight());
        System.out.println("Windows width : " + frm.getWidth());
        System.out.println("Windows name : " + frm.getName());
        System.out.println("Background color : " + frm.getBackground());
    }
}