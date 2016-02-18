"=========== Meta ============
"StrID : 654
"Title : Setup a DHCP server
"Slug  : setup-dhcp-server
"Cats  :
"Tags  :
"=============================
"EditType   : post
"EditFormat : markdown
"TextAttach : vimpress_53796437_mkd.txt
"========== Content ==========
DHCP stands for Dynamic Host Configuration Protocol, a network protocol used to automatically configure hosts in a network. There are some concepts you need to know to understand what is a DHCP server.

A subnetwork has some settings that indentify their hosts and itself from other subnetworks, settings such as <a href="http://en.wikipedia.org/wiki/Subnetwork#Network_addressing_and_routing" target="_blank">network address</a>, <a href="http://en.wikipedia.org/wiki/Subnet_mask" target="_blank">subnet mask</a>, <a href="http://en.wikipedia.org/wiki/Default_gateway" target="_blank">gateway</a>, <a href="http://en.wikipedia.org/wiki/IP_address" target="_blank">IP</a>, etc. Each host connected to a subnetwork must have at least an IP and subnet mask address, a gateway address to comunicate out with other subnetworks, and possibly one or more DNS server addresses to go out to the Internet. In a small network is not a problem setting up each PC manually, but if the network has one or two hundred PCs or the users don't know anything about networks and only wish to connect to the internet things get complicated.

That said, a DHCP server serves all settings the that clients(PCs) needs to configure their connection. In this post I show you how to setup a DHCP server using Debian GNU/Linux, here is the schema.

[php]figure('DHCP_LAN_0','Network diagram', 'label', 'svg', 'EN');[/php]

My ISP is Telmex and its router comes with the DHCP option so I had to rearrange the network this way. Since the server provides two services it has two NICs too. Let's go!.

[php]section("Instalation");[/php]

<pre lang="bash" theme="slate">
$ sudo apt-get install dhcp3-server
</pre>

[php]section("Configuration");[/php]

First configure your NICs.

<pre lang="bash" theme="slate">
$ sudo dhclient eth0 -v
Internet Systems Consortium DHCP Client 4.2.2
Copyright 2004-2011 Internet Systems Consortium.
All rights reserved.
For info, please visit https://www.isc.org/software/dhcp/

Listening on LPF/eth0/10:78:d2:39:03:2e
Sending on   LPF/eth0/10:78:d2:39:03:2e
Sending on   Socket/fallback
DHCPREQUEST on eth0 to 255.255.255.255 port 67
DHCPACK from 192.168.1.254
RTNETLINK answers: File exists
bound to 192.168.1.64 -- renewal in 36506 seconds.

$ sudo ifconfig eth1 128.64.32.1 netmask 255.255.255.0
</pre>

Now, go to <code>/etc/dhcp/</code> and open the <code>dhcpd.conf</code> file, add these lines.

<pre lang="bash" theme="slate">
subnet 128.64.32.0 netmask 255.255.255.0 {
  range                     128.64.32.2 128.64.32.253;
  option subnet-mask        255.255.255.0;
  option broadcast-address  128.64.32.255;
  option routers            128.64.32.1;    # Router IP or Gateway
  default-lease-time        600;
  max-lease-time            7200;
}
</pre>

Here is the meaning of the options:

<ul>
<li><strong><em>range:</em></strong> Range of valid IPs the server can assign to clients.</li>
<li><strong><em>subnet-mask:</em></strong> Subnetwork Mask address.</li>
<li><strong><em>broadcast-address:</em></strong> Broadcast address. </li>
<li><strong><em>routers:</em></strong> Gateway, to go out of the subnetwork.</li>
<li><strong><em>default-lease-time n:</em></strong> Number of seconds the connection is leased by default. After n seconds the connection ends and the client needs to renew the connection.</li>
<li><strong><em>max-lease-time n:</em></strong> Maximun number of seconds the connections is leased.</li>
</ul>

Save the file and restart the service.

<pre lang="bash" theme="slate">
$ sudo service isc-dhcp-server restart
</pre>

[php]section("Testing");[/php]

Most operating systems comes with a network manager that detect and try to connect automatically to a network when detected, if not, execute the following command, change <code>eth0</code> with your NIC.

<pre lang="bash" theme="slate">
$ sudo dhclient eth0 -v
Internet Systems Consortium DHCP Client 4.2.2
Copyright 2004-2011 Internet Systems Consortium.
All rights reserved.
For info, please visit https://www.isc.org/software/dhcp/

Listening on LPF/eth0/10:78:d2:39:03:2e
Sending on   LPF/eth0/10:78:d2:39:03:2e
Sending on   Socket/fallback
DHCPDISCOVER on eth0 to 255.255.255.255 port 67 interval 7
DHCPREQUEST on eth0 to 255.255.255.255 port 67
DHCPOFFER from 128.64.32.1
DHCPACK from 128.64.32.1
bound to 128.64.32.3 -- renewal in 273 seconds.
</pre>

Follow this <a href="http://en.wikipedia.org/wiki/Dynamic_Host_Configuration_Protocol#Technical_details" target="_blank">link</a> to know what every message(DHCPDISCOVER, DHCPREQUEST, DHCPOFFER, etc.) means, recommended.

At this point your DHCP server is working, you should be able to comunicate with other hosts in the network, however, you can't go out to the internet yet, we need to configure our server to act as an Internet router too.

[php]section("Configure Internet Router");[/php]

In the server execute the next lines to redirect the traffic on <code>eth1</code> to <code>eth0</code>.

<pre lang="bash" theme="slate">
$ sudo iptables --table nat --append POSTROUTING --out-interface eth0 -j MASQUERADE
$ sudo iptables --append FORWARD --in-interface eth1 -j ACCEPT
</pre>

If there were no problems now you can go out to the internet too.

There are more options to customize the DHCP server, DNS server addresses, for example, the configuration that we just created is one of the most basic, but I think it's good to start.
That is all for this post, I hope it be useful for you. Comments or corrections are welcome.
