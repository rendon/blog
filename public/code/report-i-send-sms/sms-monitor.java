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
