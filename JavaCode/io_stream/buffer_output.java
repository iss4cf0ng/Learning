import java.io.*;

public class buffer_output {
    public static void main(String[] args) {
        try {
            FileOutputStream obj = new FileOutputStream("test.txt");
            BufferedOutputStream buffer = new BufferedOutputStream(obj);
            String str = "Hello here is the test";
            byte[] b_array = str.getBytes();
            buffer.write(b_array);
            buffer.flush();
            buffer.close();
            obj.close();
            System.out.println("Output success");
        }
        catch (Exception e) {
            System.out.println(e);
        }
    }
}
