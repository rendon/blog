# Ports
2017-10-14 2024-05-06 #sysadmin #post

## Open up SSH port (or any other port)

<pre>
sudo iptables -A INPUT -p tcp -s 10.0.0.0/24 --dport 22 -m conntrack --ctstate NEW,ESTABLISHED -j ACCEPT
sudo iptables -A OUTPUT -p tcp --sport 22 -m conntrack --ctstate ESTABLISHED -j ACCEPT
```

## Delete rules
First off, you can delete ALL the rules using:
<pre>
sudo iptables -F
```

But that's probably not what you want. In order to delete specific rules first get the list of existing rules:
<pre>
$ sudo iptables -S
.
.
.
-N DOCKER-USER
-A INPUT -s 10.0.0.0/24 -p tcp -m tcp --dport 22 -m conntrack --ctstate NEW,ESTABLISHED -j ACCEPT
-A FORWARD -j DOCKER-USER
-A FORWARD -j DOCKER-ISOLATION
.
.
.
```

Then remove the rule you want:
<pre>
$ sudo iptables -D INPUT -s 10.0.0.0/24 -p tcp -m tcp --dport 22 -m conntrack --ctstate NEW,ESTABLISHED -j ACCEPT
```


## References
- [Iptables Essentials: Common Firewall Rules and Commands](https://www.digitalocean.com/community/tutorials/iptables-essentials-common-firewall-rules-and-commands)
- [How To List and Delete Iptables Firewall Rules](https://www.digitalocean.com/community/tutorials/how-to-list-and-delete-iptables-firewall-rules)
