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
