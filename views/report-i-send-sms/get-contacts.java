public String getContacts()
{
    String ans = "";
    for (int i = 0; i < contactList.size(); i++) {
        String name = contactList.get(i).getName();
        String number = contactList.get(i).getNumber();
        ans += name + FIELD_SEPARATOR + number;
        ans += RECORD_SEPARATOR;
    }

    return ans;
}

    return ans;
}
