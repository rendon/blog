private class ContactChooser extends JFrame {
    private ContactList contactList;
    public ContactChooser(String[] contacts, String[] numbers)
    {
        setSize(300, 400);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        contactList = new ContactList(contacts, numbers);
        contactList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        JScrollPane scrollPane = new JScrollPane(contactList);
        add(scrollPane, BorderLayout.CENTER);

        contactList.updateUI();
        JPanel southPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        JButton cancelButton = new JButton("Cancelar");
        cancelButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event)
            {
                contactList.setSelectedIndex(-1);
                dispose();
            }
        });

        JButton acceptButton = new JButton("Aceptar");
        acceptButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event)
            {
                int index = contactList.getSelectedIndex();
                try {
                    String number = contactList.getNumber(index);
                    numberText.setText(number);
                    dispose();
                } catch(IndexOutOfBoundsException e) {
                }
            }
        });

        southPanel.add(cancelButton);
        southPanel.add(acceptButton);
        add(southPanel, BorderLayout.SOUTH);
    }
}
