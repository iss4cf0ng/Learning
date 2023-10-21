import java.io.*;
import java.util.zip.*;

public class file2zip {
    public static void main(String[] args) throws IOException {
        /*
         * Compress single file.
         * 1 Create FileInputStream object.
         * 1.1 Create directly or create File object in beginning and create FileInputStream.
         * 2 Create zip archive destination FileOutputStream object and ZipOutStream object.
         * 3 Create zip entry in zip archive.
         * 4 read byte from FileInputStream and write byte as zip format into zip destination object.
         */

        //Construct File object
        File file2zip = new File("test.txt");
        FileInputStream src = new FileInputStream(file2zip);

        //Construct compressed destination object
        FileOutputStream zip2save = new FileOutputStream("test.zip", false);
        ZipOutputStream dst = new ZipOutputStream(zip2save);

        //Create zip compress entry in zip file.
        ZipEntry zip_entry = new ZipEntry(file2zip.getName());
        dst.putNextEntry(zip_entry);

        //Read src as byte, write zip format bytes into dst stream.
        byte[] bytes = new byte[1024];
        int length;
        while ((length = src.read(bytes)) >= 0) {
            dst.write(bytes, 0, length);
        }
        dst.close();
        src.close();
    }
}
