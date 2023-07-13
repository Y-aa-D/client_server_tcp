# client_server_tcp
Implementation of a program that allows several clients to connect to it via TCP protocol and send messages.

If the client sends 'hello' message, the server should respond 'world'. If any other message is sent, the server should send it back to the client without changing it. Implement a client that can connect to the server described earlier and send messages to it.

The client and server should be able to maintain a TCP connection and exchange messages until an explicit 'disconnect' command is received from the user.
