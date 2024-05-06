import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.HttpURLConnection;
 
public class TestWS {
    public static void main(String[] args) throws Exception {
        TestWS test = new TestWS();
        test.test();
    }
 
    private void test() throws Exception {
 
        String ws = "http://localhost/ws/index.php";
        URL url = new URL(ws);
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
 
        conn.setRequestMethod("POST");
        conn.setRequestProperty("Content-Type:", "text/xml");
        //conn.setRequestProperty("Header", "SOAPAction: 'Hello'");
 
        String message = "<soapenv:Envelope xmlns:soapenv='http://schemas.xmlsoap.org/soap/envelope/' xmlns:mys='MyService'> <soapenv:Header/> <soapenv:Body> <mys:Hello> <name>Rafael</name> </mys:Hello> </soapenv:Body> </soapenv:Envelope>";

        conn.setDoOutput(true);
        DataOutputStream out = new DataOutputStream(conn.getOutputStream());
        out.writeBytes(message);
        out.flush();
        out.close();
 
        BufferedReader in = new BufferedReader(
                    new InputStreamReader(conn.getInputStream())
                );

        String line, response = "";
        while ((line = in.readLine()) != null)
            response += line;

        in.close();
        System.out.println(response);
    }
}
