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
