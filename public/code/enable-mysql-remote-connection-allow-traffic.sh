iptables -A INPUT -i eth0 -p tcp -m tcp --dport 3306 -j ACCEPT
