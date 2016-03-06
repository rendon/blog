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
