"=========== Meta ============
"StrID : 642
"Title : Enable MySQL remote connection
"Slug  : enable-mysql-remote-connection
"Cats  :
"Tags  :
"=============================
"EditType   : post
"EditFormat : markdown
"TextAttach : wpid1520-vimpress_53796247_mkd.txt
"========== Content ==========
[php]
set_setting("show_numbers_in_sections", false);
set_setting("show_numbers_in_subsections", false);
set_setting("show_numbers_in_subsubsections", false);
[/php]

In this post I'll show you how to allow remote connections to MySQL server, just in case, my distro is Debian GNU/Linux. I am assuming that MySQL server and MySQL client are already installed in the server and client side respectively.

Enabling remote connections has several security issues and you should think about it before you proceed. 

[php]section("Step 1: Accept TCP/IP connections from any host");[/php]

Open the MySQL configuration file(<code>/etc/mysql/my.cnf</code>) and set the <code>bind-address</code> option to <code>0.0.0.0</code>.

<pre lang="bash" line="48" theme="slate">
# Instead of skip-networking the default is now to listen only on
# localhost which is more compatible and is not less secure.
#bind-address   = 127.0.0.1
bind-address    = 0.0.0.0
</pre>

By default only local connections are allowed. <a href="http://dev.mysql.com/doc/refman/5.1/en/server-options.html#option_mysqld_bind-address" target="_blank">see more...</a>.

[php]section("Step 2: Allow root user to log on from any host");[/php]

Start a session as root in the server, select the mysql database and see the users who can log on in this server and from which hosts.

<pre lang="bash" theme="slate">
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
</pre>

My hostname is intel and default user is root, to allow connections from any host we need to set the hostname to <code>%</code>.

<pre lang="bash" theme="slate">
mysql> UPDATE user SET host='%' WHERE user='root' AND host='intel';
</pre>

Restart MySQL server and try a remote connection.

[php]section("Can't connect yet?");[/php]

If remote connection is getting refused, the problem might be your firewall, Debian by default allows all traffic and so I don't need to add any rule to my firewall, to allow traffic to MySQL execute the following command.

<pre lang="bash" theme="slate">
iptables -A INPUT -i eth0 -p tcp -m tcp --dport 3306 -j ACCEPT
</pre>

Use your firewall to <a href="http://www.cyberciti.biz/faq/unix-linux-mysqld-server-bind-to-more-than-one-ip-address/" target="_blank">allow remote connection only to specific hosts</a>.
That is all, see you in next post.
