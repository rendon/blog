private class HelloServer extends NanoHTTPD {
    public HelloServer()
    {
        super(8080);
    }

    @Override
    public Response serve(String uri, Method method,
                          Map<String, String> header,
                          Map<String, String> parameters,
                          Map<String, String> files) {

        boolean checkForNewMsg = false;
        String answer = "";
        String command = parameters.get("command");
        if (command != null) {
            if (command.equals(COMMAND_GET_CONTACTS)) {
                log("GET: Lista de contactos...");

                answer = "";
                for (int i = 0; i < contactList.size(); i++) {
                    String name = contactList.get(i).getName();
                    String number = contactList.get(i).getNumber();
                    answer += name + FIELD_SEPARATOR + number;
                    answer += RECORD_SEPARATOR;
                }
                logln(LOG_SERVED);

            } else if (command.equals(COMMAND_SEND_MESSAGE)) {
                String number = parameters.get("number");
                String text = parameters.get("text");

                logln("GET: Enviar mensaje:");
                logln("Para: " + number);
                logln("Mensaje: \"" + text + "\"");

                if (number.matches("[+]?\\d{10,}")) {
                    sendSMS(number, text);
                    logln(LOG_SERVED);

                    long id = SmsDB.insertSentMessage(number, text);
                    // Test
                    //logln("Guardado con id " + id);
                    answer = STATUS_OK;
                } else {
                    logln(LOG_FAIL + " (Verifique el número)");
                    answer = STATUS_FAIL;
                }

            } else if (command.equals(COMMAND_GET_SENT_MESSAGES)) {
                log("GET: Mensajes enviados...");
                Cursor c = SmsDB.getAllSentMessages();
                if (c.moveToFirst()) {
                    do {
                        //answer += c.getString(0) + FIELD_SEPARATOR;
                        answer += c.getString(1) + FIELD_SEPARATOR;
                        answer += c.getString(2);
                        answer += RECORD_SEPARATOR;
                    } while (c.moveToNext());
                }
                logln(LOG_SERVED);

            } else if (command.equals(COMMAND_GET_RECEIVED_MESSAGES)) {
                log("GET: Mensajes recibidos...");
                Cursor c = SmsDB.getAllReceivedMessages();
                if (c.moveToFirst()) {
                    do {
                        //answer += c.getString(0) + FIELD_SEPARATOR;
                        answer += c.getString(1) + FIELD_SEPARATOR;
                        answer += c.getString(2);
                        answer += RECORD_SEPARATOR;
                    } while (c.moveToNext());
                }
                logln(LOG_SERVED);

            } else if (command.equals(COMMAND_CHECK_FOR_NEW_MESSAGE)) {
                if (newMessage) {
                    newMessage = false;
                    answer = CODE_TRUE;
                } else {
                    answer = CODE_FALSE;
                }

                checkForNewMsg = true;
            } else if (command.equals(COMMAND_GET_LAST_MESSAGE)) {
                answer = lastMessageNumber +
                         FIELD_SEPARATOR +
                         lastMessageText;
            }
        }


        if (!checkForNewMsg)
            logln(LOG_WAITING);
        return new NanoHTTPD.Response(answer);
    }

}
