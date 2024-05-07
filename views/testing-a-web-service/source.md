# Testing a Web service
2016-02-18 2024-05-07 #dev #post

I've been working with Web services these days for some college projects. Here are some interesting ways to test your web service.

Supponse this is our Web service:

Embed: `web-service.php`

![Our web service](/testing-a-web-service/testws_myservice.png)

Now, how to test if our Web service is working as expected? Let' see.

## SoapUI

This is a greate tool. Given a Web service location, SoapUI generates the needed SOAP messages to send requests to our Web service. Here I show how to test our previous Web service.

![SoapUI new project](/testing-a-web-service/testws_soapui_new.png)


![Calling our Web service using SoapUI](/testing-a-web-service/testws_soapui_request.png)

## Command line

Using the command line always let us understand better how the stuffs works :). 

Put the following request message in a file called *request.xml*:

Embed: `request.xml`

### Using Wget

Issue the following command to test our Web service:

Embed: `wget.sh`

The content the file *response.xml* should be something like this:

Embed: `wget-output.xml`

This is the same response shown in picture , unindented though.

### Using cURL

Here is the curl version:

Embed: `curl.sh`

The content of the *out.xml* file must be the same as the previous example.

### Using telnet

Here I show you how you can send an HTTP POST request to our WS using telnet:

Embed: `telnet.sh`

DON'T FORGET to specify the content length!

## Using Java

Well, this is useful too, specially if you are developing a Java application.

Embed: `testws.java`

## Using C++ with Qt

I used this too:

Embed: `testws-qt.cpp`

The methods *testService()* and *testFinished()* are [SLOTS](http://qt-project.org/doc/qt-5.0/qtcore/signalsandslots.html).

## What's next?

So far we have seen only how to test the connection to the Web service, the next step would be to extract the information we need from the response message, is not that hard, search for XML parser for your language, for Qt I've used [QXmlStreamReader](http://doc.qt.io/qt-5/qxmlstreamreader.html).

I hope this be helpful.
