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
