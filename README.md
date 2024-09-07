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
    <li><strong>srt_startup</strong>: Initialize the SRT library.</li>
    <li><strong>srt_create_socket</strong>: Create an SRT socket.</li>
    <li><strong>srt_bind</strong>: Bind a socket to an IP and port.</li>
    <li><strong>srt_listen</strong>: Start listening on a socket.</li>
    <li><strong>srt_accept</strong>: Accept incoming connections.</li>
    <li><strong>srt_connect</strong>: Connect to a remote SRT socket.</li>
    <li><strong>srt_send</strong>: Send data through the socket.</li>
    <li><strong>srt_recv</strong>: Receive data from the socket.</li>
    <li><strong>srt_epoll_create</strong>: Create an epoll object for managing multiple sockets.</li>
    <li><strong>srt_epoll_wait</strong>: Wait for events on sockets.</li>
    <li><strong>set_socket_option</strong>: Set socket options, including encryption settings.</li>
    <li><strong>get_socket_option</strong>: Get socket options.</li>
    <li><strong>srt_bstats</strong>: Get basic statistics of the SRT socket.</li>
    <li><strong>srt_send_binary</strong>: Send binary data via SRT socket.</li>
    <li><strong>srt_recv_as_bytes</strong>: Receive data as bytes from the SRT socket.</li>
    <li><strong>srt_cleanup</strong> :Cleanup the SRT library.Encrypted stream support: Configure and manage encrypted streams, including setting encryption options (SRTO_PASSPHRASE and SRTO_CRYPTOMODE) to enable encrypted data transmission over SRT.</li>
</ul>

<h2>Installation:</h2>
<p>
    Download the precompiled <code>.so</code> file and place it in your Python project directory. 
    
    import srt_libsrt
    
    srt_libsrt.srt_startup()
    sock = srt_libsrt.srt_create_socket()
    srt_libsrt.srt_bind(sock, "127.0.0.1", 9999)
</p>

<h2>Usage Example:</h2>
<pre>
    <code>
