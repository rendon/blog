public boolean testConnection()
{
    String parameters = "command=" + COMMAND_CHECK_FOR_NEW_MESSAGE;
    try {
        String server = getProtocol() + "://" +
                        getServerName() + ":" +
                        getPort();

        URL url = new URL(server + "/?" + parameters);
        HttpURLConnection http = (HttpURLConnection) url.openConnection();

        return http.getResponseCode() == HTTP_STATUS_OK;
    } catch (IOException ioe) {
        System.out.println(ioe.toString());
    }

    return false;
}
