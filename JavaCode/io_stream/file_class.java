import java.io.*;

public class file_class {
    public static void main(String[] args) throws IOException {
        File f = new File("hello1.txt");
        Boolean file_exited = f.exists();
        System.out.println("File existed : " + file_exited);
        if (!file_exited) {
            if (f.createNewFile()) {
                //System.out.println();
                System.out.println("File create successfully.");
                System.out.println("File existed : " + f.exists());
                System.out.println("Filename : " + f.getName());
                System.out.println("Parent path : " + f.getParent());
                System.out.println("Absolute path : " + f.getAbsolutePath());
                System.out.println("Is file : " + f.isFile());
                System.out.println("Is directory : " + f.isDirectory());
                System.out.println("Is absoulte : " + f.isAbsolute());
                System.out.println("Readable : " + f.canRead());
                System.out.println("Writable : " + f.canWrite());
                System.out.println("Set readonly : " + f.setReadOnly());
                System.out.println("Writable : " + f.canWrite());
                System.out.println("Set writable : " + f.setWritable(true));
                System.out.println("Writable : " + f.canWrite());
            }
        }
        else {
            System.out.println("File existed!");
        }
    }
}
