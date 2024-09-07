srt_libsrt - Python Bindings for SRT Library
Version: 1.0.0
Platform: Ubuntu 14.10

Description:
srt_libsrt provides Python bindings for the Secure Reliable Transport (SRT) protocol, enabling high-performance, reliable data transfer in real-time applications. It integrates with the native C++ SRT library using pybind11 and exposes key functions for creating and managing SRT connections in Python.

Features:
Create and manage SRT sockets
Send and receive messages over SRT
Bind, connect, listen, and accept SRT sockets
Set and get socket options
Use epoll for event-driven socket management
Commands:
srt_startup: Initialize the SRT library
srt_create_socket: Create an SRT socket
srt_bind: Bind a socket to an IP and port
srt_listen: Start listening on a socket
srt_accept: Accept incoming connections
srt_connect: Connect to a remote SRT socket
srt_send: Send data through the socket
srt_recv: Receive data from the socket
srt_epoll_create: Create an epoll object for managing multiple sockets
srt_epoll_wait: Wait for events on sockets
Installation:
Download the precompiled .so file and place it in your Python project directory.
