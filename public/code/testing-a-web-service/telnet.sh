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
