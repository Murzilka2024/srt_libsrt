<h2>Version:</h2>
<p>1.0.0</p>

<h2>Platform:</h2>
<p>Ubuntu 14.10 x86_64-linux </p>

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
    <code>pip install git+https://github.com/Murzilka2024/srt_libsrt.git</code>
</p>

## Usage Example

```python
import srt_libsrt
import logging
import time
import socket

# Set up logging
logging.basicConfig(level=logging.INFO)

class SRTHandler:
    def __init__(self):
        # Initialize the SRT library
        srt_libsrt.srt_startup()
        logging.info("SRT library initialized successfully.")

    def create_socket(self):
        # Create an SRT socket
        sock = srt_libsrt.srt_create_socket()
        if sock < 0:
            logging.error("Failed to create SRT socket.")
            raise Exception("Failed to create SRT socket.")
        return sock

    def configure_socket_options(self, sock, passphrase=None, latency=2000, payload_size=1456, recv_buffer_size=104857600, send_buffer_size=104857600):
        # Configure various socket options, including payload size and latency
        try:
            srt_libsrt.set_socket_option(sock, "SRTO_PAYLOADSIZE", payload_size)
            logging.info(f"SRT payload size set to: {payload_size}")

            srt_libsrt.set_socket_option(sock, "SRTO_LATENCY", latency)
            srt_libsrt.set_socket_option(sock, "SRTO_RCVLATENCY", latency)
            srt_libsrt.set_socket_option(sock, "SRTO_PEERLATENCY", latency)
            logging.info(f"SRT latency set to: {latency} ms (both RCV and PEER)")

            if passphrase:
                srt_libsrt.set_socket_option(sock, "SRTO_PASSPHRASE", passphrase)
                logging.info(f"SRT encryption configured with passphrase.")

            srt_libsrt.set_socket_option(sock, "SRTO_RCVBUF", recv_buffer_size)
            srt_libsrt.set_socket_option(sock, "SRTO_SNDBUF", send_buffer_size)
            logging.info(f"Receive buffer size set to: {recv_buffer_size}")
            logging.info(f"Send buffer size set to: {send_buffer_size}")

            srt_libsrt.set_socket_option(sock, "SRTO_TRANSTYPE", 1)  # Live mode
            logging.info("SRTO_TRANSTYPE set to 'live' (1)")

            srt_libsrt.set_socket_option(sock, "SRTO_CONGESTION", "live")
            logging.info("SRT congestion control set to 'live'")

            srt_libsrt.set_socket_option(sock, "SRTO_TSBPDMODE", True)
            logging.info("SRT TSBPD mode enabled")

            srt_libsrt.set_socket_option(sock, "SRTO_MESSAGEAPI", True)
            logging.info("SRT MESSAGE API mode enabled")

            srt_libsrt.set_socket_option(sock, "SRTO_NAKREPORT", True)
            logging.info("SRT NAK report enabled")

        except Exception as e:
            logging.error(f"Failed to set SRT socket options: {e}")

    def connect(self, sock, address, port):
        srt_libsrt.srt_connect(sock, address, port)
        logging.info(f"Connected to SRT source at {address}:{port}")

    def bind_socket(self, sock, address, port):
        srt_libsrt.srt_bind(sock, address, port)
        srt_libsrt.srt_listen(sock, 1)
        logging.info(f"SRT socket bound to {address}:{port} and listening.")

    def accept_client(self, sock):
        client_sock, client_addr = srt_libsrt.srt_accept(sock)
        if client_sock < 0:
            logging.error("Failed to accept SRT client.")
            raise Exception("SRT accept error.")
        logging.info(f"SRT client connected from {client_addr}")
        return client_sock

    def close_socket(self, sock):
        if sock < 0:
            logging.error("Attempt to close an invalid socket.")
            return
        srt_libsrt.srt_close(sock)
        logging.info("SRT socket closed.")

    def srt_recv_data(self, sock, buffer_size):
        return srt_libsrt.srt_recv_as_bytes(sock, buffer_size)

    def srt_send_data(self, sock, data):
        try:
            srt_libsrt.srt_send(sock, data)
        except Exception as e:
            logging.error(f"Failed to send data over SRT: {e}")

    def create_udp_socket(self, interface_ip, output_host, output_port):
        try:
            udp_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            udp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            if interface_ip:
                udp_sock.setsockopt(socket.SOL_IP, socket.IP_MULTICAST_IF, socket.inet_aton(interface_ip))
                udp_sock.bind((interface_ip, 0))
                logging.info(f"UDP socket bound to interface {interface_ip}")
            else:
                logging.info("UDP socket bound to default interface.")
            return udp_sock
        except Exception as e:
            logging.error(f"Failed to create UDP socket: {e}")
            raise

    def udp_send_data(self, udp_sock, data, output_host, output_port):
        try:
            udp_sock.sendto(data, (output_host, output_port))
        except Exception as e:
            logging.error(f"Failed to send UDP data: {e}")
            raise

if __name__ == "__main__":
    # Sample run of SRT server with configuration
    handler = SRTHandler()
    server_sock = handler.create_socket()
    handler.bind_socket(server_sock, "0.0.0.0", 5055)
    handler.configure_socket_options(server_sock, passphrase="your_passphrase")

    try:
        client_sock = handler.accept_client(server_sock)
        while True:
            data = handler.srt_recv_data(client_sock, 1316)
            if not data:
                break
            logging.info(f"Received data: {len(data)} bytes")
    finally:
        handler.close_socket(client_sock)
        handler.close_socket(server_sock)
