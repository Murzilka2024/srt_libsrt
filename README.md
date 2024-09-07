<h2>Version:</h2>
<p>1.0.0</p>

<h2>Platform:</h2>
<p>Ubuntu 14.10</p>

<h2>Description:</h2>
<p>
    The <strong>srt_libsrt</strong> library provides Python bindings for the Secure Reliable Transport (SRT) protocol, 
    enabling high-performance, reliable data transfer in real-time applications. It integrates with the native C++ 
    SRT library using <code>pybind11</code> and exposes key functions for creating and managing SRT connections in Python.
</p>

<h2>Features:</h2>
<ul>
    <li>Create and manage SRT sockets</li>
    <li>Send and receive messages over SRT</li>
    <li>Bind, connect, listen, and accept SRT sockets</li>
    <li>Set and get socket options</li>
    <li>Use epoll for event-driven socket management</li>
</ul>

<h2>Commands:</h2>
<ul>
    <li><strong>srt_startup</strong>: Initialize the SRT library</li>
    <li><strong>srt_create_socket</strong>: Create an SRT socket</li>
    <li><strong>srt_bind</strong>: Bind a socket to an IP and port</li>
    <li><strong>srt_listen</strong>: Start listening on a socket</li>
    <li><strong>srt_accept</strong>: Accept incoming connections</li>
    <li><strong>srt_connect</strong>: Connect to a remote SRT socket</li>
    <li><strong>srt_send</strong>: Send data through the socket</li>
    <li><strong>srt_recv</strong>: Receive data from the socket</li>
    <li><strong>srt_epoll_create</strong>: Create an epoll object for managing multiple sockets</li>
    <li><strong>srt_epoll_wait</strong>: Wait for events on sockets</li>
</ul>

<h2>Installation:</h2>
<p>
    Download the precompiled <code>.so</code> file and place it in your Python project directory. import srt_libsrt .
</p>

<h2>Usage Example:</h2>
<pre>
    <code>
