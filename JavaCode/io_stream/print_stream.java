import java.io.*;

public class print_stream {
    public static void main(String[] args) throws IOException {
        FileOutputStream fo = new FileOutputStream("test3.txt");
        PrintStream ps = new PrintStream(fo);
        String str = "Hello";
        ps.println(str);
        ps.println("Here is the test");
        ps.println("ISSAC");
        int x = 4000;
        ps.println(x);
        ps.close();
        fo.close();
        System.out.println("Write successfully.");
    }
}
