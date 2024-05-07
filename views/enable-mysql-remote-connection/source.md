# Enable MySQL remote connection
2016-02-04 2024-05-06 #sysadmin #post

In this post I'll show you how to allow remote connections to MySQL server, just in case, my distro is Debian GNU/Linux. I am assuming that MySQL server and MySQL client are already installed in the server and client side respectively.

Enabling remote connections has several security issues and you should think about it before you proceed. 

## Step 1: Accept TCP/IP connections from any host

Open the MySQL configuration file(`/etc/mysql/my.cnf`) and set the `bind-address` option to `0.0.0.0`.


```cnf
# Instead of skip-networking the default is now to listen only on
# localhost which is more compatible and is not less secure.
#bind-address   = 127.0.0.1
bind-address    = 0.0.0.0

```

By default only local connections are allowed. [see more...](http://dev.mysql.com/doc/refman/5.1/en/server-options.html#option_mysqld_bind-address).

## Step 2: Allow root user to log on from any host

Start a session as root in the server, select the mysql database and see the users who can log on in this server and from which hosts.


```sh
$ mysql -h localhost -u root -p
Enter password:
.
.
.
Type 'help;' or '\h' for help. Type '\c' to clear the current input statement.
mysql> use mysql;
Reading table information for completion of table and column names
You can turn off this feature to get a quicker startup with -A

Database changed
mysql> select user, host, from user;
+------------------+-----------+
| user             | host      |
+------------------+-----------+
| root             | 127.0.0.1 |
| root             | ::1       |
|                  | intel     |
| root             | intel     | <--
|                  | localhost |
| debian-sys-maint | localhost |
| root             | localhost |
+------------------+-----------+

```

My hostname is intel and default user is root, to allow connections from any host we need to set the hostname to `%`.


```sql
mysql> UPDATE user SET host='%' WHERE user='root' AND host='intel';

```

Restart MySQL server and try a remote connection.

## Can't connect yet?

If remote connection is getting refused, the problem might be your firewall, Debian by default allows all traffic and so I don't need to add any rule to my firewall, to allow traffic to MySQL execute the following command.


```sh
iptables -A INPUT -i eth0 -p tcp -m tcp --dport 3306 -j ACCEPT

```

Use your firewall to [allow remote connection only to specific hosts](http://www.cyberciti.biz/faq/unix-linux-mysqld-server-bind-to-more-than-one-ip-address/).
That is all, see you in next post.
