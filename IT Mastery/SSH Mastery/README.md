# SSH Mastery: OpenSSH, PuTTY, Tunnels and Keys

## Chapter 0: Introduction

Always use SSH-2 and never SSH-1.

## Chapter 1: Encryption, Algorithms, and Keys

Most encryption algorithms use a _key_.

### Algorithm Types

Algorithms come in two varieties: symmetric and asymmetric.

A _symmetric algorithm_ uses the same key for encryption and decryption.

Some examples:
- AES (Advanced Encryption Standard)
- ChaCha20

These can be very fast and secure, but only if authorized individuals have the key.

An _asymmetric algorithm_ uses different keys for encryption and decryption.

Make one key public and share it, and keep one key private at all costs. This is the basis of _public key encryption_.

The public key and matching private key are called a _key pair_.

Learn more: [Diffie-Hellman key exchange](https://en.wikipedia.org/wiki/Diffie%E2%80%93Hellman_key_exchange)

### How SSH Uses Encryption

Every SSH server has a key pair. A client connects and the server uses this key pair to make a temporary key pair shared only between these two hosts. The client and server both use this temporary key pair to derive a symmetric key to use during that session. Related keys are also derived to provide connection integrity. The computers will negotiate a new temporary key pair and new symmetric key depending on the amount of data or length of time they are connected.

Leave the encryption settings alone!

## Chapter 2: Common Configuration

OpenSSH config files reside in **/etc/ssh** by default.

Default settings for the SSH client are found in **ssh\_config**.

The server's private keys start with **ssh\_host** and end in **\_key**.

Finally, **sshd\_config** contains the server configuration.

### Multiple Values in Config

Port can appear multiple times, each with a seperate value:
```
Port 22
Port 2222
```

Host can accept multiple values, seperated by space:
```
Host envy.mwl.io avarice.mwl.io
```

Other keywords like Address expect values seperated by commas:
```
Address 192.0.2.0/25, 198.51.100.0/24
```

### Wildcards in OpenSSH Configuration Files

The wildcard characters are:
- ? (Matches exactly one character)
- * (Matches zero or more characters)

You can negate with the '!' character.

### Conditional Configuration with Match

Your server can act differently depending on the source address or hostname of an incoming connection or username. This can be achieved through **sshd\_config** match statements.

#### Matching Users and Groups

Example of user matching:
```
X11Forwarding no
Match User rawb2020
X11Forwarding yes
```

Example of group matching:
```
X11Forwarding no
Match Group wheel
X11Forwarding yes
```

You can also use multiple match terms seperated by commas:
```
Match User rawb2020, rawb2021
```

#### Matching Addresses or Hosts

You can match based on IP addresses as well:
```
X11Forwarding no
Match Address 203.0.113.0/29, 198.51.100.0/24
X11Forwarding yes
```

If you set UseDNS to yes in sshd\_config, you can match based on hostnames:
```
X11Forwarding no
Match Host *.rawb.io, *.robertcrawford.com
X11Forwarding yes
```

**Note:** For ssh\_config only, skip the word match:
```
X11Forwarding no
Host rawb2020
X11Forwarding yes
```

#### Multiple Match Conditions

You can use multiple match terms on a single line:
```
Match Address 192.0.2.5 User rawb2020
PasswordAuthentication yes
```

#### Placing Match Statements

All statements that follow a match statement belong to that match statement until another match, or the end of the file.

## Chapter 3: The OpenSSH Server

The OpenSSH server is called sshd.

### Is sshd Running?

To check from a client, you can use netcat:
```
$ nc -v localhost 22
Connection to localhost 22 port [tcp/ssh] succeeded!
SSH-2.0-OpenSSH_7.9
```

From the server:
```
$ ps ax | grep sshd
626 - Is 0:00.03 /usr/sbin/sshd
31965 - Is 0:00.38 sshd: mwrob [priv] (sshd)
44382 - S 0:05.75 sshd: mwrob@pts/0 (sshd)
```

The first line is the master process that listens to TCP port 22.

The second line is the priviledged process that handles my SSH connection into this host.

The third line is the unpriviledged child process that handles my login session.

### Configuring sshd

Before making changes to the sshd\_config file, you should know how to debug sshd. The 3 most simple ways are:
1. Alternate configuration files
2. Alternate ports
3. Debugging mode

#### Alternate Configuration Files and Ports

The -f flag tells sshd to use an alternate configuration file:
```
# /usr/sbin/sshd -f sshd_config.test
```

However, this presents a problem as only one sshd instance can attach to a particular TCP port. Instead of editing the test file, you should override the configured TCP port and assign a new one with the -p flag:
```
# /usr/sbin/sshd -f sshd_config.test -p 2022
```

#### Validating sshd\_config Changes

Ask sshd to verify the configuration file and all the key files with the -t flag:
```
# sshd -t
```

#### Debugging sshd

The -d flag tells sshd to run in foreground debugging mode, without detaching from the controlling terminal. Note that in debugging mode, sshd can only handle a single login request. Don't do this in production, run it on an alternate port.

```
# /usr/sbin/sshd -p 2022 -d
```

### Configuring sshd

This section includes usefull configuration options.

#### Set Host Keys

The HostKey keyword gives the full path to a file containing a private key:
```
HostKey /usr/local/etc/ssh/ssh_host_rsa_key
HostKey /usr/local/etc/ssh/ssh_host_ecdsa_key
HostKey /usr/local/etc/ssh/ssh_host_ed25519_key
```

#### Network Options

You can control how sshd uses the network:
```
Port 22
AddressFamily any 		<inet | inet6>
ListenAddress 0.0.0.0		<all ipv4 addresses>
ListenAddress ::		<all ipv6 addresses>
```

If a host has many IP addresses, it might be better to block traffic with a packet filter instead of using many ListenAddress statements.

**If you're stuck behind a firewall that blocks everything except ports 80 and 443, running sshd on those ports would let you evade the firewall** Although, this is generally unwise.

#### Banners and Login Messages

Not required but a message can be displayed to a user before they log in:
```
Banner /etc/ssh/banner
```

#### Authentication Options

```
LoginGraceTime 2m
MaxAuthTries 6
```

#### Verify Login Attempts against DNS

The owner of an IP address controls the reverse DNS for that address. An intruder who controls the reverse DNS for his IP address can change the apparent hostname to something within your company.

```
UseDNS yes
```

If you're a home user, your ISP probably controls the reverse DNS on your connection.

Micahel reccommends against enabling UseDNS.


