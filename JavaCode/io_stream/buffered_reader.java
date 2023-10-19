import java.io.*;

public class buffered_reader {
    public static void main(String[] args) throws IOException {
        InputStreamReader ir = new InputStreamReader(System.in);
        BufferedReader br = new BufferedReader(ir);
        System.out.print("Enter name : ");
        String name = br.readLine();
        System.out.println("Welcome : " + name);
    }
}
