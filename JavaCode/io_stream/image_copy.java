import java.io.*;

public class image_copy {
    public static void main(String[] args) {
        try {
            FileInputStream src = new FileInputStream("linking.png");
            FileOutputStream dst = new FileOutputStream("_linking.png");
            System.out.println("Image size : " + src.available());

            byte[] img_bytes = new byte[src.available()];
            src.read(img_bytes);
            dst.write(img_bytes);
            src.close();
            dst.close();
        }
        catch (Exception e) {
            System.out.println(e);
        }
    }
}
