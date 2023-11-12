import java.awt.*;

public class getAllFonts {
    public static void main(String[] args) {
        GraphicsEnvironment graphicsEnv = GraphicsEnvironment.getLocalGraphicsEnvironment();
        String[] fontFamilyNames = graphicsEnv.getAvailableFontFamilyNames();
        for (String name : fontFamilyNames) {
            System.out.println(name);
        }
        System.out.println("------------------------------------");
        Font[] fonts = graphicsEnv.getAllFonts();
        for (Font font : fonts) {
            System.out.println(font);
        }
    }
}
