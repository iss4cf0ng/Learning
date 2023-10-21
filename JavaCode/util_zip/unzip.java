import java.io.*;
import java.util.zip.*;

public class unzip {
    public static void main(String[] args) throws IOException {
        File my_dir = new File("mydir");
        if (my_dir.mkdir())
            System.out.println(my_dir.getName());
        else
            System.out.println("Directory existed.");
        
        byte[] buffer = new byte[1024];
        FileInputStream src_file = new FileInputStream("folder.zip");
        ZipInputStream src = new ZipInputStream(src_file);
        ZipEntry zip_entry = src.getNextEntry();
        while (zip_entry != null) {
            String f_name = zip_entry.getName();
            FileOutputStream dst = new FileOutputStream(my_dir + "/" + f_name);
            int length;
            while ((length = src.read(buffer)) > 0) {
                dst.write(buffer, 0, length);
            }
            dst.close();
            zip_entry = src.getNextEntry();
        }
        src.close();
    }
}
