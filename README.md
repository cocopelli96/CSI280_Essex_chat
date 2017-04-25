Essex Project
========

An AIM Clone?

Contributing
-------------
Read [CONTRIBUTE](CONTRIBUTE.md) for information on how to get working on this project.

Installing
-------------
Read [INSTALL](INSTALL.md) for more information on how to contribute to this project.

Making and Running the project
-------------
Install the following dependencies before working with the this project:
```
cmake
```
To make the project you must do the following:
```
1. run the following command: git submodule update --init --recursive
2. if on a Mac edit line 28 of the deps/colorizer/Makefile to be: $(LD) $(LDFLAGS) $(BINDIR)/$(BINNAME) $<
3. run the following command: make
```
After this to run the project you must use the following commands in seperate windows:
```
./server/bin/chatter_server     -- This starts a server to communicate with
./client/bin/chatter_client IP_ADDRESS     -- This starts a client to use the chat where IP_ADDRESS is the server's IP address
```
While in the program you can use the following as commands inside the chat room:
```
/exit         This will exit the chat room.
/help         This will display the help menu.
/login NAME   This will set your username to NAME.
```
