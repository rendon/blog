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
