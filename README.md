<h2>Version:</h2>
<p>1.0.0</p>

<h2>Platform:</h2>
<p>Ubuntu 14.10</p>

<h2>Description:</h2>
<p>
The <strong>srt_libsrt</strong> library provides Python bindings for the <strong>Secure Reliable Transport (SRT) protocol</strong>, enabling developers to handle real-time, high-performance, and reliable data transfer. This library integrates SRT's native C++ functions using <code>pybind11</code>, allowing Python applications to create, manage, and control SRT connections seamlessly. It supports UDP and MPEG-TS <strong>(MPEG Transport Stream)</strong> formats, making it ideal for streaming applications.

With built-in encryption support, it secures data transmission over SRT. The library is easy to incorporate into projects requiring real-time video, audio, or data transmission. Developers can manage socket options, send/receive data, and configure encryption with minimal effort.

For a basic use case, create an SRT socket, bind it to an IP, listen for incoming connections, and transfer data using the <code>srt_send</code> and <code>srt_recv</code> methods. The library also supports epoll for managing multiple sockets, enabling event-driven architecture for high-performance networked applications.

This makes it an excellent fit for projects requiring secure, low-latency, and reliable video streaming or real-time communications over unreliable networks, like live broadcasts or remote media distribution.
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
    <li><strong>srt_cleanup</strong> :Cleanup the SRT library.</li>
    <li><strong>Encrypted stream support: Configure and manage encrypted streams, including setting encryption options (SRTO_PASSPHRASE and SRTO_CRYPTOMODE) to enable encrypted data transmission over SRT.</li>
</ul>

<h2>Installation:</h2>
<p>
    Download the precompiled <code>.so</code> file and place it in your Python project directory.
</p>
<pre><code>
import srt_libsrt

srt_libsrt.srt_startup()
sock = srt_libsrt.srt_create_socket()
srt_libsrt.srt_bind(sock, "127.0.0.1", 9999)
</code></pre>

<h2>Usage Example:</h2>
<pre><code>
import srt_libsrt
import logging
    
logging.basicConfig(level=logging.INFO)

def run_srt_server(ip, port):
    # Initialize the SRT library
    srt_libsrt.srt_startup()

    try:
        # Create an SRT socket
        server_sock = srt_libsrt.srt_create_socket()

        # Bind the socket to IP and port
        srt_libsrt.srt_bind(server_sock, ip, port)
        logging.info(f"Bound to {ip}:{port}")

        # Start listening for incoming connections
        srt_libsrt.srt_listen(server_sock, backlog=1)
        logging.info(f"Listening on {ip}:{port}")

        # Accept an incoming connection
        client_sock, client_ip = srt_libsrt.srt_accept(server_sock)
        logging.info(f"Accepted connection from {client_ip}")

        # Receive data from the client
        while True:
            data = srt_libsrt.srt_recv_as_bytes(client_sock, 1316)
            if not data:
                break
            logging.info(f"Received data: {len(data)} bytes")

        # Close client socket
        srt_libsrt.srt_close(client_sock)
    finally:
        # Cleanup the SRT socket and library
        srt_libsrt.srt_close(server_sock)
        srt_libsrt.srt_cleanup()

if __name__ == "__main__":
    run_srt_server("0.0.0.0", 5055)
</code></pre>
