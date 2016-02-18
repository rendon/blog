"=========== Meta ============
"StrID : 883
"Title : Testing a Web service
"Slug  : testing-a-web-service
"Cats  : Sin categoría
"Tags  : 
"=============================
"EditType   : post
"EditFormat : Markdown
"TextAttach : wpid1602-vimpress_52817244_mkd.txt
"========== Content ==========
I've been working with Web services these days for some college projects. Here are some interesting ways to test your web service.

Supponse this is our Web service:

<pre lang="php">
<?php
require_once 'lib/nusoap.php';

function Hello($name)
{
    return "Hello " . $name . "!";
}

$server = new soap_server();
$server->configureWSDL("MyService", "urn:MyService");
$server->soap_defencoding = 'utf-8';


$server->register('Hello',
    array('name' => 'xsd:string'),
    array('response' => 'xsd:string'),
    'MyService',
    false,
    'rpc',
    'literal',
    'Test method.'
);

if (isset($HTTP_RAW_POST_DATA)) {
    $server->service($HTTP_RAW_POST_DATA);
} else {
    $server->service("php://input");
}

?>
</pre>

[php]
figure('testws_myservice', 'Our web service', 'testws_myservice', 'png', 'EN');
[/php]

Now, How to test if our Web service is working as expected? Let' see.

[php]section("SoapUI");[/php]

This is a greate tool. Given a Web service location, SoapUI generates the needed SOAP messages to send requests to our Web service. Here I show how to test our previous Web service.

[php]
figure('testws_soapui_new', 'SoapUI new project', 'testws_soapui_new','png', 'EN');
[/php]


[php]
figure('testws_soapui_request', 'Calling our Web service using SoapUI', 'testws_soapui_request', 'png', 'EN');
[/php]

[php]section("Command line");[/php]

Using the command line always let us understand better how the stuffs works :). 

Put the following request message in a file called _request.xml_:

<pre lang="xml">
<soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/" xmlns:mys="MyService">
   <soapenv:Header/>
   <soapenv:Body>
      <mys:Hello>
         <name>Rafael</name>
      </mys:Hello>
   </soapenv:Body>
</soapenv:Envelope>
</pre>

[php]subsection("Using Wget");[/php]

Issue the following command to test our Web service:

<pre theme="slate">
wget --post-file=request.xml --header="Content-Type: text/xml" --header="SOAPAction: 'Hello'" http://localhost/ws/index.php?wsdl -O response.xml
</pre>

The content the file _response.xml_ should be something like this:

<pre lang="xml">
<?xml version="1.0" encoding="utf-8"?><SOAP-ENV:Envelope xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:SOAP-ENC="http://schemas.xmlsoap.org/soap/encoding/"><SOAP-ENV:Body><ns1:HelloResponse xmlns:ns1="MyService"><response>Hello Rafael!</response></ns1:HelloResponse></SOAP-ENV:Body></SOAP-ENV:Envelope>
</pre>

This is the same response shown in picture [php]ref('testws_soapui_request');[/php], unindented though.

[php]subsection("Using cURL");[/php]

Here is the curl version:

<pre theme="slate">
curl --header "Content-Type: text/xml; charset=utf-8" --data @request.xml http://localhost/ws/index.php > out.xml
</pre>

The content of the _out.xml_ file must be the same as the previous example.

[php]subsection("Using telnet");[/php]

Here I show you how you can send an HTTP POST request to our WS using telnet:

<pre theme="slate">
[10:29:57]ddc@intel~$ telnet localhost 80
Trying ::1...
Connected to localhost.
Escape character is '^]'.
POST /ws/index.php HTTP/1.0
Content-Type: text/xml; charset=utf-8
Content-Length: 212

<soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/" xmlns:mys="MyService"> <soapenv:Header/> <soapenv:Body> <mys:Hello> <name>Rafael</name> </mys:Hello> </soapenv:Body> </soapenv:Envelope>
HTTP/1.1 200 OK
Date: Wed, 20 Nov 2013 16:29:59 GMT
Server: Apache/2.2.22 (Debian)
X-Powered-By: PHP/5.4.4-14+deb7u4
X-SOAP-Server: NuSOAP/0.9.5 (1.123)
Content-Length: 420
Vary: Accept-Encoding
Connection: close
Content-Type: text/xml; charset=utf-8

<?xml version="1.0" encoding="utf-8"?><SOAP-ENV:Envelope xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:SOAP-ENC="http://schemas.xmlsoap.org/soap/encoding/"><SOAP-ENV:Body><ns1:HelloResponse xmlns:ns1="MyService"><response>Hello Rafael!</response></ns1:HelloResponse></SOAP-ENV:Body></SOAP-ENV:Envelope>Connection closed by foreign host.
</pre>

DON'T FORGET to specify the content length!

[php]section("Using Java");[/php]

Well, this is useful too, specially if you are developing a Java application.

<pre lang="java">
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
</pre>

[php]section("Using C++ with Qt");[/php]

I used this too:

<pre lang="cpp">
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QVBoxLayout *layout = new QVBoxLayout();
    QPushButton *testButton = new QPushButton("Test service");
    connect(testButton, SIGNAL(clicked()), this, SLOT(testService()));
    layout->addWidget(testButton);
    QWidget *widget = new QWidget(this);
    widget->setLayout(layout);
    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::testService()
{
    QString message("<soapenv:Envelope xmlns:soapenv='http://schemas.xmlsoap.org/soap/envelope/' xmlns:mys='MyService'> <soapenv:Header/> <soapenv:Body> <mys:Hello> <name>Rafael</name> </mys:Hello> </soapenv:Body> </soapenv:Envelope>");

    QUrl url("http://localhost/ws/index.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/xml");
    QNetworkAccessManager *nm = new QNetworkAccessManager(this);
    QObject::connect(nm, SIGNAL(finished(QNetworkReply *)), this, SLOT(testFinished(QNetworkReply*)));
    nm->post(request, message.toAscii());
}

void MainWindow::testFinished(QNetworkReply *reply)
{
    QByteArray ans = reply->readAll();
    QString response(ans.data());

    // Process your response message
    qDebug() << response << endl;
}
</pre>

The methods _testService()_ and _testFinished()_ are <a href="http://qt-project.org/doc/qt-5.0/qtcore/signalsandslots.html">SLOTS</a>.

[php]section("What's next?");[/php]

So far we have seen only how to test the connection to the Web service, the next step would be to extract the information we need from the response message, is not that hard, search for XML parser for your language, for Qt I've used <a href="https://qt-project.org/doc/qt-4.8/qxmlstreamreader.html" target="_blank">QXmlStreamReader</a>.

I hope this be helpful.


