import java.io.*;

public class buffered_write {
    public static void main(String[] args) throws IOException {
        FileWriter writer = new FileWriter("test1.txt");
        BufferedWriter buffer_w = new BufferedWriter(writer);
        String str = "Hello here is the test";
        buffer_w.write(str, 0, 6);
        buffer_w.newLine();
        buffer_w.write(str, 6, str.length() - 6);
        buffer_w.close();
        writer.close();
        System.out.println("Writre successfully.");
    }
}
