# Absolute FreeBSD

Unix programs have three channels of communication (pipes):
1. Standard input
2. Standard output
3. Standard error

Everything is a file, including system hardware and virtual devices.

## Chapter 1: Getting More Help

### Man Pages

The FreeBSD manual is divided into 9 sections:
1. General user commands
2. System calls and error numbers
3. C programming libraries
4. Devices and device drivers
5. File formats
6. Game instructions
7. Miscellaneous information
8. System maintenance commands
9. Kernel interfaces

Search for keywords in man pages with apropos(1). To search for only manual page names, use whatis(1).

## Chapter 2: Before You Install

No Notes.

## Chapter 3: Installing

No Notes.

## Chapter 4: The Boot Process

FreeBSD stores boot messages in /var/run/dmesg.boot

## Chapter 5: Backup and Recovery

You can use tar(1) for backing up your system.

Tarsnap is a network-based backup tool.

#### Create an Archive

The following command backs up everything from the root directory to $TAPE (or /dev/sa0 if $TAPE isn't set):

```
$ tar -c /
```

Note: Be careful when backing up with a leading / as when you extract the contents from a tarball, they will always be restored relative to the root directory. If you leave out the leading /, you can restore the file anywheres you want.

##### Non-default Storage

Instead of writing to $TAPE (or /dev/sa0), you can specify a location with the -f flag:

```
$ tar -c -f /dev/ssd0 /
```

The -f flag is also used to specify a name for the tarball:

```
$ tar -cf books.tar /home/rawb2020/books
```

##### Compression

| Compression Type | Flag | File Extension |
| --- | --- | --- |
| XZ | -J | .txz |
| bzip | -j | .tbz |
| gzip | -z | .tar.gz, .tgz, .taz |

##### Permission Restore

The -p flag restores original permissions. Use this for system restores.

## Chapter 6: Kernel


