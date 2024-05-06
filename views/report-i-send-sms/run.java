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
