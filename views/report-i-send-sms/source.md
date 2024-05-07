<!-- vim: set spelllang=es_mx: -->

# Reporte I: Enviar mensajes SMS
2016-03-05 2024-05-06 #dev #android #post

Con éste documento doy inicio a una serie de reportes correspondientes al desarrollo de los proyectos de la asignatura **Desarrollo de Aplicaciones para Tecnologías Móviles**.

## Definición del problema

En esta ocasión toca el turno al primer proyecto, que podríamos denominar "Envío de mensajes SMS desde la PC". A continuación una breve descripción.

<blockquote>Desarrollar una aplicación de escritorio que permita a sus usuarios enviar y recibir mensajes de texto (SMS) desde la PC, usando un dispositivo celular o smartphone que funja como emisor y receptor.</blockquote>

## Propuesta de solución

La solución que vamos a tratar en este reporte consiste en lo siguiente. No vamos a crear 1 programa sino 2, un servidor en el dispositivo móvil y un cliente en la PC. El siguiente diagrama puede ayudar a entender mejor la solución.

![Diagrama de la solución](/report-i-send-sms/sms_01.png)


### Servidor

Se encargará de las siguientes actividades:

<ul>
  <li>Enviar los mensajes que el cliente le solicite y almacenarlos en una base de datos.</li>
  <li>Recibir los mensajes entrantes y almacenarlos en la base de datos.</li>
  <li>Servir la libreta de contactos del dispositivo móvil.</li>
  <li>Servir la lista de mensajes enviados.</li>
  <li>Servir la lista de mensajes recibidos.</li>
  <li>Resolver si existe un nuevo mensaje.</li>
  <li>Servir el último mensaje recibido.</li>
</li>


### Cliente

Éste se comunicará con el servidor y proporcionará una interfaz gráfica al usuario con los siguientes servicios.

<ul>
  <li>Enviar mensaje SMS.</li>
  <li>Mostrar la lista de contactos.</li>
  <li>Visualizar los mensajes recibidos.</li>
  <li>Actualizar la bandeja de entrada cuando lleguen nuevos mensajes.</li>
  <li>Visualizar los mensajes enviados.</li>
</ul>

## Requisitos

Para poder seguir este tutorial necesitas contar con los siguientes requisitos:

<ul>
  <li>Un dispositivo móvil con sistema operativo Android 2.3 (probablemente funcione con versiones posteriores)</li>
  <li>[El SDK de Java configurado](/setup-jdk).</li>
  <li>[El SDK de Android configurado](/setup-android-sdk).</li>
  <li>Opcional: IntelliJ IDEA 12 Comunity Edition, `http://www.jetbrains.com/idea/`.</li>
  <li>Conocimientos intermedios de Java.</li>
  <li>Un sistema operativo GNU/Linux Debian, utilizaremos la versión 7, denominada Wheezy.</li>
</ul>


### Notas

<ul>
  <li>Es necesario aclarar que no vamos a explicar los programas línea por línea, sino más bien, una explicación de las partes más importantes que les ayude a comprenderlos, en caso de necesitar una explicación más detallada pueden consultar las referencias que se proporcionan al final del documento.</li>
  <li>Acostumbro codificar en Ingles puesto que considero es más homogéneo, permite exponer mi código a una audiencia más amplia, y me ayuda a mejorar mi comprensión del idioma. Aunque por ser un trabajo para la escuela la interfaz forzosamente tiene que ser en Español.</li>
</ul>

## El servidor

El servidor es una aplicación para Android. Es un servidor HTTP que recibe peticiones mediante el método GET, quizás no lo más adecuado pero si lo más sencillo. Para no empezar desde cero vamos a hacer uso de NanoHTTPD (_http://nanohttpd.com/_), que como su nombre lo indica es un servidor HTTP muy pequeño, ideal para un sistema embebido.

Con el fin de aprender a utilizar el SDK de Android he optado por no utilizar un IDE para esta parte, únicamente las herramientas que incluye el SDK y la línea de comandos, nada de que preocuparse. 


### Crear el proyecto

En la línea de comandos teclee los siguiente:


```sh
mkdir SMSServer
android create project --target android-10 -n SMSServer -k com.inforscience.server -a SMSServer -p ./SMSServer

```

Así debe lucir la estructura del proyecto:


```txt
SMSServer/
├── AndroidManifest.xml
├── ant.properties
├── bin
├── build.xml
├── libs
├── local.properties
├── proguard-project.txt
├── project.properties
├── res
│   ├── layout
│   │   └── main.xml
│   └── values
│       └── strings.xml
└── src
    └── com
        └── inforscience
            └── server
                └── SMSServer.java

9 directories, 9 files

```

Por el momento en el archivo _SMSServer.java_ hay solo un método, _onCreate()_, que lo único que hace es imprimir un mensaje en de bienvenida. Primero veamos cómo implementar el servidor, dentro del archivo _SMSServer.java_ creamos una clase privada _HelloServer_ que herede de _NanoHTTPD_, un constructor y  el método _serve()_, es éste último es donde se concentra la mayor parte de la acción. El código es bastante simple por lo que no creo que halla necesidad de entrar mucho detalle.


```java
private class HelloServer extends NanoHTTPD {
    public HelloServer()
    {
        super(8080);
    }

    @Override
    public Response serve(String uri, Method method,
                          Map<String, String> header,
                          Map<String, String> parameters,
                          Map<String, String> files) {

        boolean checkForNewMsg = false;
        String answer = "";
        String command = parameters.get("command");
        if (command != null) {
            if (command.equals(COMMAND_GET_CONTACTS)) {
                log("GET: Lista de contactos...");

                answer = "";
                for (int i = 0; i < contactList.size(); i++) {
                    String name = contactList.get(i).getName();
                    String number = contactList.get(i).getNumber();
                    answer += name + FIELD_SEPARATOR + number;
                    answer += RECORD_SEPARATOR;
                }
                logln(LOG_SERVED);

            } else if (command.equals(COMMAND_SEND_MESSAGE)) {
                String number = parameters.get("number");
                String text = parameters.get("text");

                logln("GET: Enviar mensaje:");
                logln("Para: " + number);
                logln("Mensaje: \"" + text + "\"");

                if (number.matches("[+]?\\d{10,}")) {
                    sendSMS(number, text);
                    logln(LOG_SERVED);

                    long id = SmsDB.insertSentMessage(number, text);
                    // Test
                    //logln("Guardado con id " + id);
                    answer = STATUS_OK;
                } else {
                    logln(LOG_FAIL + " (Verifique el número)");
                    answer = STATUS_FAIL;
                }

            } else if (command.equals(COMMAND_GET_SENT_MESSAGES)) {
                log("GET: Mensajes enviados...");
                Cursor c = SmsDB.getAllSentMessages();
                if (c.moveToFirst()) {
                    do {
                        //answer += c.getString(0) + FIELD_SEPARATOR;
                        answer += c.getString(1) + FIELD_SEPARATOR;
                        answer += c.getString(2);
                        answer += RECORD_SEPARATOR;
                    } while (c.moveToNext());
                }
                logln(LOG_SERVED);

            } else if (command.equals(COMMAND_GET_RECEIVED_MESSAGES)) {
                log("GET: Mensajes recibidos...");
                Cursor c = SmsDB.getAllReceivedMessages();
                if (c.moveToFirst()) {
                    do {
                        //answer += c.getString(0) + FIELD_SEPARATOR;
                        answer += c.getString(1) + FIELD_SEPARATOR;
                        answer += c.getString(2);
                        answer += RECORD_SEPARATOR;
                    } while (c.moveToNext());
                }
                logln(LOG_SERVED);

            } else if (command.equals(COMMAND_CHECK_FOR_NEW_MESSAGE)) {
                if (newMessage) {
                    newMessage = false;
                    answer = CODE_TRUE;
                } else {
                    answer = CODE_FALSE;
                }

                checkForNewMsg = true;
            } else if (command.equals(COMMAND_GET_LAST_MESSAGE)) {
                answer = lastMessageNumber +
                         FIELD_SEPARATOR +
                         lastMessageText;
            }
        }


        if (!checkForNewMsg)
            logln(LOG_WAITING);
        return new NanoHTTPD.Response(answer);
    }

}

```


La forma de enviar datos con el método GET tiene el siguiente formato:


```txt
http://servidor[:puerto]/?parametro1=valor1&parametro2=valor2&parametroN=valorN

```

Un signo de interrogación seguido por una lista de parámetros con formato clave=valor, separados por ampersands (&). NanoHTTPD se encarga de extraer dichos parámetros y se los pasa al método _serve()_ en la variable _parameters_, el cliente siempre enviará como primer parámetro la cadena "command" y su valor va a determinar la acción que el cliente esta solicitando. Los posibles comandos son:

<ul>
  <li>**COMMAND_GET_CONTACTS** para solicitar la lista de contactos.</li>
  <li>**COMMAND_SEND_MESSAGE** para enviar un mensaje.</li>
  <li>**COMMAND_GET_SENT_MESSAGES** para solicitar todos los mensajes enviados.</li>
  <li>**COMMAND_GET_RECEIVED_MESSAGES** para solicitar todos los mensajes recibidos.</li>
  <li>**COMMAND_CHECK_FOR_NEW_MESSAGE** para preguntar al servidor si hay un mensaje nuevo.</li>
  <li>**COMMAND_GET_LAST_MESSAGE** para recuperar el nuevo nuevo mensaje en caso de haberlo.</li>
</ul>


Todas éstas constantes se definen tanto en el cliente como en el servidor. 

### Agregando acción al método onCreate()

Éste método es el primero que se ejecuta al iniciar la aplicación y en el vamos a incluir algunas acciones, como son, iniciar el servidor, recuperar la lista de contactos del dispositivo y cargar la base de datos. En caso de que la base de datos no exista ésta deberá ser creada, las bases de datos SQLite se almacenan en archivos. 


```java
@Override
public void onCreate(Bundle savedInstanceState)
{
    super.onCreate(savedInstanceState);
    setContentView(R.layout.main);
    logScrollView = (ScrollView) findViewById(R.id.logScrollView);
    logTextView = (TextView) findViewById(R.id.logTextView);

    logTextView.setMovementMethod(new ScrollingMovementMethod());
    log("Iniciando el servidor...");
    smsServer = new HelloServer();
    try {
        smsServer.start();
        logln(LOG_OK);
    } catch (IOException ioe) {
        logln(LOG_FAIL);
    }

    log("Cargando lista de contactos...");
    Cursor phones = getContentResolver().query(
            ContactsContract.CommonDataKinds.Phone.CONTENT_URI, null,
            null, null, null
    );

    String nc = ContactsContract.CommonDataKinds.Phone.DISPLAY_NAME;
    String nuc = ContactsContract.CommonDataKinds.Phone.NUMBER;
    String contacts = "";
    contactList = new Vector<Contact>();
    while (phones.moveToNext()) {
        String name = phones.getString(phones.getColumnIndex(nc));
        String phoneNumber = phones.getString(phones.getColumnIndex(nuc));
        contactList.add(new Contact(name, phoneNumber));
    }

    logln(LOG_OK);

    log("Inicializando la base de datos...");
    database = openOrCreateDatabase(DBManager.DB_NAME,
                                    Context.MODE_PRIVATE,
                                    null);
    logln(LOG_OK);
    logln(LOG_WAITING);
    newMessage = false;
}

```

### Servir la lista de contactos

En el método _onCreate()_ cargamos la libreta de contactos en _contactList_, ésta lista es la que le enviaremos al cliente cuando la solicite.



```java
public String getContacts()
{
    String ans = "";
    for (int i = 0; i < contactList.size(); i++) {
        String name = contactList.get(i).getName();
        String number = contactList.get(i).getNumber();
        ans += name + FIELD_SEPARATOR + number;
        ans += RECORD_SEPARATOR;
    }

    return ans;
}

    return ans;
}

```


### Servir la lista de mensajes enviados


```java
public String getReceivedMessages()
{
    String ans = "";
    Cursor c = SmsDB.getAllReceivedMessages();
    if (c.moveToFirst()) {
        do {
            ans += c.getString(1) + FIELD_SEPARATOR;
            ans += c.getString(2);
            ans += RECORD_SEPARATOR;
        } while (c.moveToNext());
    }

    return ans;
}

```

### Enviar SMS

El método _sendSMS()_ es el que se encarga de enviar los mensajes SMS:


```java
public int sendSMS(final String number, final String text)
{
    final Activity activity = this;
    activity.runOnUiThread(new Runnable() {
        public void run()
        {
            SmsManager sms = SmsManager.getDefault();
            sms.sendTextMessage(number, null, text, null, null);
        }
    });

    return 0; // Success
}

```


### Detectar los mensajes entrantes

Esta es una de las partes más interesantes. Cada vez que sucede un evento el sistema hace notificaciones todas la aplicaciones que así lo requieran, para ser notificados es necesario heredar la clase _BroadcastReceiver_.



```java
public class SmsReceiver extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {

        Bundle extras = intent.getExtras();
        if (extras == null)
            return;

        Object[] pdus = (Object[])extras.get("pdus");
        for (int i = 0; i < pdus.length; i++) {
            SmsMessage SMessage = SmsMessage.createFromPdu((byte[])pdus[i]);
            String sender = SMessage.getOriginatingAddress();
            String body = SMessage.getMessageBody().toString();

            Intent in = new Intent("SmsMessage.intent.MAIN").
                            putExtra("get_msg", sender + 
                                     SMSServer.FIELD_SEPARATOR +
                                     body);

            context.sendBroadcast(in);
        }
    }
}

```


Y en el método _onResume()_ de la clase SMSServer:


```java
@Override
protected void onResume()
{
    super.onResume();
    IntentFilter intentFilter = new IntentFilter("SmsMessage.intent.MAIN");
    intentReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent)
        {
            String msg = intent.getStringExtra("get_msg");

            String[] tokens = msg.split(FIELD_SEPARATOR);
            String number = tokens[0];
            String text = tokens[1];

            newMessage = true;
            lastMessageNumber = number;
            lastMessageText = text;

            logln("NOTIFICACIÓN: Nuevo mensaje");
            logln("De: " + number);
            logln("Mensaje: \"" + text + "\"");
            long id = SmsDB.insertReceivedMessage(number, text);
        }
    };

    this.registerReceiver(intentReceiver, intentFilter);
} 

```


### La base de datos

Para que el registro de mensajes enviados y recibidos persista incluso después de reiniciar el servidor es necesario almacenar dichos mensajes en algún lugar, en este caso, una base de datos, Android provee soporte nativo para SQLite. La clase _DBManager se encarga de todas las operaciones de la base de datos.


```java
public class DBManager {
    public static final String KEY_RECEIVED_ID      = "id";
    public static final String KEY_RECEIVED_FROM    = "from_number";
    public static final String KEY_RECEIVED_MSG     = "msg";

    public static final String KEY_SENT_ID          = "id";
    public static final String KEY_SENT_TO          = "to_number";
    public static final String KEY_SENT_MSG         = "msg";

    public static final String DB_NAME              = "smsdb";
    public static final String DB_TABLE_RECEIVED    = "received";
    public static final String DB_TABLE_SENT        = "sent";
    public static final int DB_VERSION = 1;

    private static final String DB_CREATE_TABLE_RECEIVED =
            "create table received(id integer primary key autoincrement, " +
                    KEY_RECEIVED_FROM + " text not null, " +
                    KEY_RECEIVED_MSG + " text not null);";

    private static final String DB_CREATE_TABLE_SENT =
            "create table sent(id integer primary key autoincrement, " +
                    KEY_SENT_TO + " text not null, " +
                    KEY_SENT_MSG + " text not null);";

    public DBManager() { }

    public static long insertSentMessage(String to,
                                         String msg,
                                         SQLiteDatabase db)
    {
        ContentValues values = new ContentValues();
        values.put(KEY_SENT_TO, to);
        values.put(KEY_SENT_MSG, msg);
        return db.insert(DB_TABLE_SENT, null, values);
    }

    public static long insertReceivedMessage(String from,
                                             String msg,
                                             SQLiteDatabase db)
    {
        ContentValues values = new ContentValues();
        values.put(KEY_RECEIVED_FROM, from);
        values.put(KEY_RECEIVED_MSG, msg);
        return db.insert(DB_TABLE_RECEIVED, null, values);
    }

    public static Cursor getAllSentMessages(SQLiteDatabase db)
    {
        String[] fields = new String[] {KEY_SENT_ID, KEY_SENT_TO, KEY_SENT_MSG};
        return db.query(DB_TABLE_SENT, fields, null, null, null, null, null);
    }

    public static Cursor getAllReceivedMessages(SQLiteDatabase db)
    {
        String[] fields = new String[]{KEY_RECEIVED_ID,
                KEY_RECEIVED_FROM,
                KEY_RECEIVED_MSG};

        return db.query(DB_TABLE_RECEIVED, fields,
                        null, null, null, null, null);
    }
}

```


### Concesión de permisos

En Android las aplicaciones por defecto cuentan con privilegios muy limitados, por lo cual es necesario conceder permisos para poder acceder al Internet, a los mensajes, a los contactos, etc. Estos permisos se especifican en el archivo _AndroidManifest.xml_ que se encuentra en folder raíz del proyecto.


```xml
<uses-permission android:name="android.permission.INTERNET" />
<uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
<uses-permission android:name="android.permission.ACCESS_WIFI_STATE" />
<uses-permission android:name="android.permission.SEND_SMS" />
<uses-permission android:name="android.permission.READ_SMS" />
<uses-permission android:name="android.permission.RECEIVE_SMS" />
<uses-permission android:name="android.permission.HARDWARE_TEST" />
<uses-permission android:name="android.permission.READ_CONTACTS" />

```

Hasta aquí la descripción del programa, veamos ahora la compilación e instalación. 

Nos posicionamos en el folder de nuestro proyecto y tecleamos lo siguiente, la primera línea es para compilar y la segunda para instalar la aplicación en el dispositivo o en el emulador, lo que encuentre primero.



```sh
ant debug
ant debug install

```

La dirección del servidor es la dirección IP que tienen el dispositivo móvil, en el puerto 8080, por ejemplo, _http://192.168.1.242:8080_. Esta dirección la tienen que conocer el cliente para poder conectarse.

![Interfaz del servidor de SMS](/report-i-send-sms/sms_02.png)

## El cliente

El cliente es una programa en Java, con una interfaz sencilla, una venta principal con tres pestañas, la primera para enviar mensajes, la segunda para visualizar los mensajes recibidos y la última para visualizar los mensajes enviados. Para esta parte utilice el IDE IntelliJ IDEA.

Además de la interfaz gráfica se ha desarrollado una clase _SmsClient_ que se encargará de obtener los recursos del servidor. A continuación se describen los métodos.

### testConnection()

Intenta conectar al servidor y retorna verdadero en caso de éxito.


```java
public boolean testConnection()
{
    String parameters = "command=" + COMMAND_CHECK_FOR_NEW_MESSAGE;
    try {
        String server = getProtocol() + "://" +
                        getServerName() + ":" +
                        getPort();

        URL url = new URL(server + "/?" + parameters);
        HttpURLConnection http = (HttpURLConnection) url.openConnection();

        return http.getResponseCode() == HTTP_STATUS_OK;
    } catch (IOException ioe) {
        System.out.println(ioe.toString());
    }

    return false;
}

```

### getSentMessages()

Obtiene del servidor la lista de mensajes enviados.


```java
public Vector<SentMessage> getSentMessages()
{
    Vector<SentMessage> sentMessages = new Vector<SentMessage>();
    String parameters = "command=" + COMMAND_GET_SENT_MESSAGES;

    try {
        String server = getProtocol() + "://" +
                        getServerName() + ":" +
                        getPort();

        URL url = new URL(server + "/?" + parameters);
        System.out.println(url.toString());

        HttpURLConnection http = (HttpURLConnection) url.openConnection();
        InputStreamReader in = new InputStreamReader(http.getInputStream());
        BufferedReader reader = new BufferedReader(in);


        String line;
        while ((line = reader.readLine()) != null) {
            String[] rows = line.split(RECORD_SEPARATOR);
            for (int i = 0; i < rows.length; i++) {
                String fields[] = rows[i].split(FIELD_SEPARATOR);
                SentMessage sm = new SentMessage(fields[0], fields[1]);
                sentMessages.add(sm);
            }
        }

    } catch (IOException ioe) {
        System.out.println(ioe.toString());
        return null;
    }

    return sentMessages;
}

```

### getReceivedMessages()

Recupera del servidor la lista de mensajes enviados.


```java
public Vector<ReceivedMessage> getReceivedMessages()
{
    Vector<ReceivedMessage> receivedMessages = new Vector<ReceivedMessage>();
    String parameters = "command=" + COMMAND_GET_RECEIVED_MESSAGES;

    try {
        String server = getProtocol() + "://" +
                        getServerName() + ":" +
                        getPort();

        URL url = new URL(server + "/?" + parameters);
        System.out.println(url.toString());

        HttpURLConnection http = (HttpURLConnection) url.openConnection();

        InputStreamReader in = new InputStreamReader(http.getInputStream());
        BufferedReader reader = new BufferedReader(in);

        String line;
        while ((line = reader.readLine()) != null) {
            String[] rows = line.split(RECORD_SEPARATOR);
            for (int i = 0; i < rows.length; i++) {
                String fields[] = rows[i].split(FIELD_SEPARATOR);
                ReceivedMessage rm = new ReceivedMessage(fields[0], fields[1]);
                receivedMessages.add(rm);
            }
        }

    } catch (IOException ioe) {
        System.out.println(ioe.toString());
        return null;
    }

    return receivedMessages;
}

```


### getContactList()

Obtiene del servidor la lista de contactos en el dispositivo.


```java
public Vector<Contact> getContactList()
{
    Vector<Contact> contacts = new Vector<Contact>();
    String command = COMMAND_GET_CONTACTS;
    String parameters = "command=" + command;

    try {
        String server = getProtocol() + "://" +
                        getServerName() + ":" +
                        getPort();

        URL url = new URL(server + "/?" + parameters);
        System.out.println(url.toString());

        HttpURLConnection http = (HttpURLConnection) url.openConnection();
        InputStreamReader in = new InputStreamReader(http.getInputStream());
        BufferedReader reader = new BufferedReader(in);

        String line;
        while ((line = reader.readLine()) != null) {
            String[] rows = line.split(RECORD_SEPARATOR);
            for (int i = 0; i < rows.length; i++) {
                String fields[] = rows[i].split(FIELD_SEPARATOR);
                Contact c = new Contact(fields[0], fields[1]);
                contacts.add(c);
            }
        }

    } catch (IOException ioe) {
        System.out.println(ioe.toString());
        return null;
    }

    return contacts;
}

```

### sendSMS()

Solicita al servidor enviar un mensaje, enviándole como parámetros el número y el mensaje.


```java
public boolean sendSMS(String number, String message) throws Exception
{
    String command = COMMAND_SEND_MESSAGE;
    message = URLEncoder.encode(message, "UTF8");
    String parameters = "command=" + command + "&" +
            "number=" + number + "&" +
            "text=" + message;

    try {
        String server = getProtocol() + "://" +
                        getServerName() + ":" +
                        getPort();

        URL url = new URL(server + "/?" + parameters);
        System.out.println(url.toString());

        HttpURLConnection http = (HttpURLConnection) url.openConnection();
        InputStreamReader in = new InputStreamReader(http.getInputStream());
        BufferedReader reader = new BufferedReader(in);
        String ans = reader.readLine();

        return ans.equals(STATUS_OK);

    } catch (IOException ioe) {
        System.out.println(ioe.toString());
    }

    return false; // Fail
}

```


### NewMessagePanel

Hacemos unas cuantas validaciones y en caso satisfactorio procedemos a enviar el mensaje.


```java
@Override
public void actionPerformed(ActionEvent event)
{
    if (event.getSource() == sendButton) {
        String number = numberText.getText();
        String message = messageArea.getText();
        try {
            if (smsClient.sendSMS(number, message)) {
                sentMessagePanel.addMessage(number, message);
                statusBar.setStatus("Enviado", StatusBar.CODE_SUCCESS);
                messageArea.setText("");
                numberText.setText("");
            } else {
                statusBar.setStatus("No se pudo enviar",
                                    StatusBar.CODE_FAILURE);
            }
        } catch(Exception e) {
            statusBar.setForeground(Client.GUI_ERROR_COLOR);
            statusBar.setStatus("No se pudo enviar",
                                StatusBar.CODE_FAILURE);
        }

    }
}

```

![Envío de mensajes](/report-i-send-sms/sms_03.png)

### InboxPanel

Esta parte si es un poco interesante, cómo saber si ha llegado un nuevo mensaje y  en su caso obtenerlo y actualizar el contenido de la bandeja de entrada. Para eso creamos una clase que se ejecuta en un hilo independiente y continuamente pregunta al servidor si hay mensajes nuevos.


```java
private class SMSMonitor implements Runnable {
    @Override
    public void run()
    {
        while (true) {
            String command = SmsClient.COMMAND_CHECK_FOR_NEW_MESSAGE;
            String parameters = "command=" + command;

            try {
                String server = smsClient.getProtocol() + "://" +
                                smsClient.getServerName() + ":" +
                                smsClient.getPort();

                URL url = new URL(server + "/?" + parameters);
                HttpURLConnection http = (HttpURLConnection)url.openConnection();
                http.getResponseCode();

                InputStreamReader in = new InputStreamReader(http.getInputStream());
                BufferedReader reader = new BufferedReader(in);

                String line = reader.readLine();
                if (line != null && line.equals(SmsClient.CODE_TRUE)) {
                    command = SmsClient.COMMAND_GET_LAST_MESSAGE;
                    parameters = "command=" + command;
                    url = new URL(server + "/?" + parameters);
                    http = (HttpURLConnection)url.openConnection();
                    http.getResponseCode();

                    in = new InputStreamReader(http.getInputStream());
                    reader = new BufferedReader(in);
                    line = reader.readLine();
                    String[] tokens = line.split(SmsClient.FIELD_SEPARATOR);

                    addMessage(tokens[0], tokens[1]);
                    statusBar.setStatus("Nuevo SMS.", StatusBar.CODE_SUCCESS);
                }

            } catch (IOException ioe) {
                System.out.println(ioe.toString());
            }

            sleep(500);
        }
    }
}

```

![Bandeja de entrada](/report-i-send-sms/sms_04.png)


### SentMessagePanel

Esta parte es más simple, únicamente muestra la lista de mensajes enviados. En caso de no poder contactar al servidor al momento de iniciar la aplicación, ésta se mantiene continuamente reintentado, lo mismo pasa con las otras partes de la aplicación.


```java
@Override
public void run()
{
    while (true) {
        if (smsClient.testConnection()) {
            sentMessages = smsClient.getSentMessages();
            if (sentMessages != null) {
                loadContacts();
                formatAllMessages();
                messagePane.updateUI();
                break;
            }
        } else {
            messagePane.setText("<h1>Intentando contactar " +
                                "al servidor...</h1>");
        }
        sleep(2000);
    }

}

```

![Mensajes enviados](/report-i-send-sms/sms_05.png)

### Bono

Al enviar un mensaje el usuario puede introducir el número directamente o presionar el botón con etiqueta "..." para acceder a la lista de contactos del dispositivo. Por cuestiones de seguridad he alterado la imagen puesto que es mi lista de contactos.

![Lista de contactos](/report-i-send-sms/sms_06.png)

El código es sencillo:



```java
private class ContactChooser extends JFrame {
    private ContactList contactList;
    public ContactChooser(String[] contacts, String[] numbers)
    {
        setSize(300, 400);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        contactList = new ContactList(contacts, numbers);
        contactList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        JScrollPane scrollPane = new JScrollPane(contactList);
        add(scrollPane, BorderLayout.CENTER);

        contactList.updateUI();
        JPanel southPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        JButton cancelButton = new JButton("Cancelar");
        cancelButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event)
            {
                contactList.setSelectedIndex(-1);
                dispose();
            }
        });

        JButton acceptButton = new JButton("Aceptar");
        acceptButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event)
            {
                int index = contactList.getSelectedIndex();
                try {
                    String number = contactList.getNumber(index);
                    numberText.setText(number);
                    dispose();
                } catch(IndexOutOfBoundsException e) {
                }
            }
        });

        southPanel.add(cancelButton);
        southPanel.add(acceptButton);
        add(southPanel, BorderLayout.SOUTH);
    }
}

```

Hasta aquí las explicaciones, espero les sea de utilidad.

## Código fuente

Tanto el servidor como el cliente se encuentran hospedados en Bitbucket, bajo la licencia GPLv3, con excepcón de NanoHTTPD, el cual tienen su propia licencia. Para obtenerlo puedes ir directamente a los siguientes sitios y descargar un archivo ZIP.

<ul>
  <li>**SMSServer:** [https://bitbucket.org/rendon/smsserver](https://bitbucket.org/rendon/smsserver)</li>
  <li>**SMSClient:** [https://bitbucket.org/rendon/smsclient](https://bitbucket.org/rendon/smsclient)</li>
</ul>

O bien puedes clonar el proyecto usando el Sistema de Control de Versiones **git**.


```sh
$ git clone https://rendon@bitbucket.org/rendon/smsserver.git
$ git clone https://rendon@bitbucket.org/rendon/smsclient.git

```

## Conclusión

Este primer proyecto fue interesante puesto que me permitió recordar algunas cosas y aprender muchas más, por ejemplo, cómo crear aplicaciones en Android, entiendo mejor la forma en que trabajan los servidores, entre otras cosas.

Los programas en realidad no son tan complicados, con un poco de investigación y análisis estoy seguro de que lograrán entenderlos.

## Por hacer

En esta sección vamos a listar algunas características que en nuestra aplicación no se implementaron pero que la harían mejor.

<ul>
  <li>Cambiar el método de comunicación con el servidor de **GET** a **POST**, éste último es más seguro.</li>
  <li>Actualmente la aplicación de escritorio tiene que estar verificando constantemente la llegada de nuevos mensajes, lo más adecuado sería que el smartphone notifique a la aplicación de escritorio en cuándo arribe  un nuevo SMS.</li>
  <li>Implementar un método de autenticación para que no cualquiera pueda enviar mensajes.</li>
</ul>

## Referencias

- [Documentación de Android](https://developer.android.com/index.html)
- [Begining Android Application Development](http://www.wrox.com/WileyCDA/WroxTitle/Beginning-Android-Application-Development.productCd-1118087291.html)
- [Documentación de NanoHTTPD](http://nanohttpd.org/)
