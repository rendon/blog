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
