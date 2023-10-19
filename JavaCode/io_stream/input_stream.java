import java.io.*;

public class input_stream {
    public static void main(String[] args) {
        try {
            FileInputStream obj = new FileInputStream("hello.txt");
            int b = obj.read();
            System.out.print((char)b);

            while ((b = obj.read()) != -1) {
                System.out.print((char)b);
            }

            obj.close();
            System.out.println("Read success!");
        }
        catch (IOException e) {
            System.out.println(e);
        }
    }
}
