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
