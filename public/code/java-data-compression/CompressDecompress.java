import java.io.IOException;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.util.zip.Deflater;
import java.util.zip.ZipInputStream;
import java.util.zip.ZipOutputStream;
import java.util.zip.ZipEntry;

public class CompressDecompress {
    public static byte[] decompress(byte[] input) throws IOException {
        if (input == null) {
            throw new IOException("Input must not be null");
        }
        byte[] buffer = new byte[2048];
        ZipInputStream zip = new ZipInputStream(new ByteArrayInputStream(input));
        ByteArrayOutputStream output = new ByteArrayOutputStream();
        ZipEntry entry = zip.getNextEntry();
        if (entry == null) {
            throw new IOException("No entry found");
        }
        int len;
        while ((len = zip.read(buffer)) > 0) {
            output.write(buffer, 0, len);
        }
        zip.close();
        output.close();
        return output.toByteArray();
    }

    public static byte[] compress(byte[] input) throws IOException {
        if (input == null) {
            throw new IOException("Input must not be null");
        }
        ByteArrayOutputStream output = new ByteArrayOutputStream();
        ZipOutputStream zip = new ZipOutputStream(output);
        zip.setMethod(Deflater.DEFLATED);
        zip.setLevel(Deflater.BEST_SPEED);

        ZipEntry entry = new ZipEntry("data");
        entry.setSize(input.length);
        zip.putNextEntry(entry);
        zip.write(input);
        zip.closeEntry();
        zip.close();
        return output.toByteArray();
    }
}
