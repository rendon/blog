# Enable MySQL remote connection
2016-02-04 2024-05-06 #sysadmin #post

In this post I'll show you how to allow remote connections to MySQL server, just in case, my distro is Debian GNU/Linux. I am assuming that MySQL server and MySQL client are already installed in the server and client side respectively.

Enabling remote connections has several security issues and you should think about it before you proceed. 

## Step 1: Accept TCP/IP connections from any host

Open the MySQL configuration file(`/etc/mysql/my.cnf`) and set the `bind-address` option to `0.0.0.0`.

Embed: `my.cnf`

By default only local connections are allowed. [see more...](http://dev.mysql.com/doc/refman/5.1/en/server-options.html#option_mysqld_bind-address).

## Step 2: Allow root user to log on from any host

Start a session as root in the server, select the mysql database and see the users who can log on in this server and from which hosts.

Embed: `allow-root.sh`

My hostname is intel and default user is root, to allow connections from any host we need to set the hostname to `%`.

Embed: `allow-root-cmd.sql`

Restart MySQL server and try a remote connection.

## Can't connect yet?

If remote connection is getting refused, the problem might be your firewall, Debian by default allows all traffic and so I don't need to add any rule to my firewall, to allow traffic to MySQL execute the following command.

Embed: `allow-traffic.sh`

Use your firewall to [allow remote connection only to specific hosts](http://www.cyberciti.biz/faq/unix-linux-mysqld-server-bind-to-more-than-one-ip-address/).
That is all, see you in next post.
