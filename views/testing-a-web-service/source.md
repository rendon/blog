<p>I've been working with Web services these days for some college projects. Here are some interesting ways to test your web service.</p>

<p>Supponse this is our Web service:</p>

Embed: `web-service.php`

![Our web service](/testing-a-web-service/testws_myservice.png)

<p>Now, How to test if our Web service is working as expected? Let' see.</p>

## SoapUI

<p>This is a greate tool. Given a Web service location, SoapUI generates the needed SOAP messages to send requests to our Web service. Here I show how to test our previous Web service.</p>

![SoapUI new project](/testing-a-web-service/testws_soapui_new.png)


![Calling our Web service using SoapUI](/testing-a-web-service/testws_soapui_request.png)

## Command line

<p>Using the command line always let us understand better how the stuffs works :). </p>

<p>Put the following request message in a file called <em>request.xml</em>:</p>

Embed: `request.xml`

### Using Wget

<p>Issue the following command to test our Web service:</p>

Embed: `wget.sh`

<p>The content the file <em>response.xml</em> should be something like this:</p>

Embed: `wget-output.xml`

<p>This is the same response shown in picture , unindented though.</p>

### Using cURL

<p>Here is the curl version:</p>

Embed: `curl.sh`

<p>The content of the <em>out.xml</em> file must be the same as the previous example.</p>

### Using telnet

<p>Here I show you how you can send an HTTP POST request to our WS using telnet:</p>

Embed: `telnet.sh`

<p>DON'T FORGET to specify the content length!</p>

## Using Java

<p>Well, this is useful too, specially if you are developing a Java application.</p>

Embed: `testws.java`

## Using C++ with Qt

<p>I used this too:</p>

Embed: `testws-qt.cpp`

<p>The methods <em>testService()</em> and <em>testFinished()</em> are <a href="http://qt-project.org/doc/qt-5.0/qtcore/signalsandslots.html">SLOTS</a>.</p>

## What's next?

<p>So far we have seen only how to test the connection to the Web service, the next step would be to extract the information we need from the response message, is not that hard, search for XML parser for your language, for Qt I've used <a href="http://doc.qt.io/qt-5/qxmlstreamreader.html" target="_blank">QXmlStreamReader</a>.</p>

<p>I hope this be helpful.</p>
