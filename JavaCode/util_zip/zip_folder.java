import java.io.*;
import java.util.zip.*;

public class zip_folder {
    public static void main(String[] args) throws IOException {
        File file2zip = new File("zip23"); //Class is "File" but also can use int folder.
        FileOutputStream zip2save = new FileOutputStream("folder.zip");
        ZipOutputStream dst = new ZipOutputStream(zip2save);
        zipFile(file2zip, file2zip.getName(), dst);
        dst.close();
    }

    //Recursive function
    private static void zipFile(File file2zip, String filename, ZipOutputStream dst) throws IOException {
        //Do not compresss if file is hidden
        if (file2zip.isHidden()) {
            return;
        }

        //Do recursion
        if (file2zip.isDirectory()) {
            File[] files = file2zip.listFiles();
            for (File file:files) {
                zipFile(file, filename + "/" + file.getName(), dst);
            }
            return;
        }

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
}
