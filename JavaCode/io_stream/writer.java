import java.io.*;

public class writer {
    public static void main(String[] args) {
        try {
            FileWriter fw = new FileWriter("test.txt", true);
            fw.write("\n");
            String str = "Hello here is the test.";
            fw.write(str);
            fw.close();
            System.out.println("Write successfully.");
        }
        catch (IOException e) {
            System.out.println(e);
        }
    }
}
