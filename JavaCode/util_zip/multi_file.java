import java.io.*;
import java.util.zip.*;

public class multi_file {
    public static void main(String[] args) throws IOException {
        String[] src_files = {"test.txt", "test1.txt"};
        
        FileOutputStream zip2save = new FileOutputStream("multi.zip");
        ZipOutputStream dst = new ZipOutputStream(zip2save);
        for (String src_file : src_files) {
            File file2zip = new File(src_file);
            FileInputStream src = new FileInputStream(file2zip);
            ZipEntry zip_entry = new ZipEntry(file2zip.getName());
            dst.putNextEntry(zip_entry);
            byte[] bytes = new byte[1024];
            int length;
            while ((length = src.read(bytes)) >= 0) {
                dst.write(bytes, 0, length);
            }
            src.close();
        }
        dst.close();
    }
}
