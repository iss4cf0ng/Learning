import java.io.*;

public class write_byte {
    public static void main(String[] args) {
        try {
            FileOutputStream obj = new FileOutputStream(".\\hello.txt");
            obj.write(70);
            
            String str = "Hello here is the test.";
            byte[] str_byteArray = str.getBytes();
            obj.write(str_byteArray);
            obj.close();

            System.out.println("Done!");
        }
        catch (IOException e) {
            System.out.println(e);
        }
    }
}
