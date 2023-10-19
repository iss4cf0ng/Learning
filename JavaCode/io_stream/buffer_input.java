import java.io.*;

public class buffer_input {
    public static void main(String[] args) {
        try {
            FileInputStream obj = new FileInputStream("test.txt");
            BufferedInputStream buffer = new BufferedInputStream(obj);
            int b;
            while ((b = buffer.read()) != -1) {
                System.out.print((char)b);
            }
            buffer.close();
            obj.close();
            System.out.println("\nBufferedInputStream successed.");
        }
        catch (Exception e) {
            System.out.println(e);
        }
    }
}
