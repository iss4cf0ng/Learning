import java.io.*;

public class reader {
    public static void main(String[] args) {
        int i;
        try {
            FileReader reader = new FileReader("test.txt");
            while((i = reader.read()) != -1) {
                char ch = (char)i;
                System.out.print(ch);
            }
            reader.close();
            System.out.println("\nRead successfully.");
        }
        catch (IOException e) {
            System.out.println(e);
        }
    }
}
