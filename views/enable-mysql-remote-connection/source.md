# Enable MySQL remote connection
2016-02-04 2024-05-06 #sysadmin #post

<p>In this post I'll show you how to allow remote connections to MySQL server, just in case, my distro is Debian GNU/Linux. I am assuming that MySQL server and MySQL client are already installed in the server and client side respectively.</p>

<p>Enabling remote connections has several security issues and you should think about it before you proceed. </p>

## Step 1: Accept TCP/IP connections from any host

<p>Open the MySQL configuration file(`/etc/mysql/my.cnf`) and set the `bind-address` option to `0.0.0.0`.</p>

Embed: `my.cnf`

<p>By default only local connections are allowed. <a href="http://dev.mysql.com/doc/refman/5.1/en/server-options.html#option_mysqld_bind-address" target="_blank">see more...</a>.</p>

## Step 2: Allow root user to log on from any host

<p>Start a session as root in the server, select the mysql database and see the users who can log on in this server and from which hosts.</p>

Embed: `allow-root.sh`

<p>My hostname is intel and default user is root, to allow connections from any host we need to set the hostname to `%`.</p>

Embed: `allow-root-cmd.sql`

<p>Restart MySQL server and try a remote connection.</p>

## Can't connect yet?

<p>If remote connection is getting refused, the problem might be your firewall, Debian by default allows all traffic and so I don't need to add any rule to my firewall, to allow traffic to MySQL execute the following command.</p>

Embed: `allow-traffic.sh`

<p>Use your firewall to <a href="http://www.cyberciti.biz/faq/unix-linux-mysqld-server-bind-to-more-than-one-ip-address/" target="_blank">allow remote connection only to specific hosts</a>.</p>
<p>That is all, see you in next post.</p>
