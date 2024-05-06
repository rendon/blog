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
