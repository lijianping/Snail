# zfsync

A remote file synchorization software like rsync.

## Usage

zfsync [options] user@host:file1.txt :file2.txt dst

zfsync [options] file1.txt file2.txt user@host:dst

zfsync [options] file1.txt file2.txt dst

## Options

```
-v              : show version
-h              : show help

-V              : increase verbosity
-R              : recurse subdirecories
-B blocksize    : setting block size

-0              : running as server
-1              : running as synchronization destination
```

### pull

zfsync [options] japin@10.10.4.23:test/hello.txt :test/world.txt codes

brief: download files on the remote machine

remote host information: {user:'japin', host:'10.10.4.23', path:'test'}

### push

zfsync [options] ~/test/world.txt ~/test/hello.txt japin@10.10.4.23:codes

brief: upload files to remote machine

remote host information: {user:'japin', host:'10.10.4.23', path:'codes'}

### Description

After client parse host information, client will use SSH to push path to remote machine.

zfs_server: remote machine or not. If this machine is running as a remote machine, zfs_server is 1. Otherwise, zfs_server is 0.

zfs_syncer: synchronization destination. If this machine is running as a synchronization destination, zfs_syncer is 1. Otherwise, zfs_syncer is 0.

If a machine is running as a synchronization, it should perform receiving file list at first. Then, check the file list and make blocks if the file exists.

## Flow chart

```flow
st=>start: Start
e=>end: end
op1=>operation: parsing parameters
isserver=>condition: is server?
run_server=>subroutine: run server
run_client=>subroutine: run client

st->op1->isserver
isserver(yes)->run_server->e
isserver(no)->run_client->e
```
Figure.1 flow of zfsync

```flow
st=>start: server start
ed=>end: server end
is_syncer=>condition: is syncer?
send_file_list=>operation: send file list
recv_file_list=>operation: recv file list

st->is_syncer
is_syncer(yes)->send_file_list->ed
is_syncer(no)->recv_file_list->ed
```
Figure.2 server flow

```flow
st=>start: client start
ed=>end: client end
parse_remote=>operation: get remote machine
is_syncer=>condition: is syncer?
send_file_list=>operation: send file list
recv_file_list=>operation: recv file list
ssh_connection=>subroutine: ssh connect
ssh_ok=>condition: connect ok?

st->parse_remote->ssh_connection->ssh_ok
ssh_ok(yes)->is_syncer
ssh_ok(no)->ed
is_syncer(yes)->send_file_list->ed
is_syncer(no)->recv_file_list->ed
```
Figure.3 client flow
