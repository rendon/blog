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
