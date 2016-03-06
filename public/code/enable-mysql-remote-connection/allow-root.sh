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
