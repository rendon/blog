@Override
public void actionPerformed(ActionEvent event)
{
    if (event.getSource() == sendButton) {
        String number = numberText.getText();
        String message = messageArea.getText();
        try {
            if (smsClient.sendSMS(number, message)) {
                sentMessagePanel.addMessage(number, message);
                statusBar.setStatus("Enviado", StatusBar.CODE_SUCCESS);
                messageArea.setText("");
                numberText.setText("");
            } else {
                statusBar.setStatus("No se pudo enviar",
                                    StatusBar.CODE_FAILURE);
            }
        } catch(Exception e) {
            statusBar.setForeground(Client.GUI_ERROR_COLOR);
            statusBar.setStatus("No se pudo enviar",
                                StatusBar.CODE_FAILURE);
        }

    }
}
