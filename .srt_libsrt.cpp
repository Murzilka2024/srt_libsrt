#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <srt/srt.h>
#include <arpa/inet.h>

namespace py = pybind11;

std::unordered_map<std::string, SRT_SOCKOPT> socket_options = {
    {"SRTO_BINDTODEVICE", SRTO_BINDTODEVICE},
    {"SRTO_CONGESTION", SRTO_CONGESTION},
    {"SRTO_CONNTIMEO", SRTO_CONNTIMEO},
    {"SRTO_MAXBW", SRTO_MAXBW},
    {"SRTO_LATENCY", SRTO_LATENCY},
    {"SRTO_RCVBUF", SRTO_RCVBUF},
    {"SRTO_SNDBUF", SRTO_SNDBUF},
    {"SRTO_PAYLOADSIZE", SRTO_PAYLOADSIZE},
    {"SRTO_TLPKTDROP", SRTO_TLPKTDROP},
    {"SRTO_NAKREPORT", SRTO_NAKREPORT},
    {"SRTO_PASSPHRASE", SRTO_PASSPHRASE},
#ifdef SRTO_CRYPTOMODE
    {"SRTO_CRYPTOMODE", SRTO_CRYPTOMODE},
#endif
    {"SRTO_TSBPDMODE", SRTO_TSBPDMODE},
    {"SRTO_KMREFRESHRATE", SRTO_KMREFRESHRATE},
    {"SRTO_RCVLATENCY", SRTO_RCVLATENCY},
    {"SRTO_PEERLATENCY", SRTO_PEERLATENCY},
    {"SRTO_LOSSMAXTTL", SRTO_LOSSMAXTTL},
#ifdef SRTO_COMPCHECK
    {"SRTO_COMPCHECK", SRTO_COMPCHECK},
#endif
    {"SRTO_STREAMID", SRTO_STREAMID},
    {"SRTO_MESSAGEAPI", SRTO_MESSAGEAPI},
    {"SRTO_RETRANSMITALGO", SRTO_RETRANSMITALGO},
    {"SRTO_PEERIDLETIMEO", SRTO_PEERIDLETIMEO},
    {"SRTO_IPV6ONLY", SRTO_IPV6ONLY},
    {"SRTO_MINVERSION", SRTO_MINVERSION},
    {"SRTO_PBKEYLEN", SRTO_PBKEYLEN},
    {"SRTO_IPTTL", SRTO_IPTTL},
    {"SRTO_IPTOS", SRTO_IPTOS}
};

// Инициализация библиотеки SRT
void srt_startup_wrapper() {
    if (srt_startup() == SRT_ERROR) {
        throw std::runtime_error("Failed to initialize SRT: " + std::string(srt_getlasterror_str()));
    }
}

// Очистка библиотеки SRT
void srt_cleanup_wrapper() {
    srt_cleanup();
}

// Создание сокета SRT
SRTSOCKET srt_create_socket_wrapper() {
    SRTSOCKET sock = srt_create_socket();
    if (sock == SRT_ERROR) {
        throw std::runtime_error("Failed to create socket: " + std::string(srt_getlasterror_str()));
    }
    return sock;
}

// Привязка сокета
int srt_bind_wrapper(SRTSOCKET sock, const std::string& ip, int port) {
    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &sa.sin_addr);
    return srt_bind(sock, (struct sockaddr*)&sa, sizeof(sa));
}

// Прослушивание на сокете
int srt_listen_wrapper(SRTSOCKET sock, int backlog) {
    return srt_listen(sock, backlog);
}

// Принятие подключений
SRTSOCKET srt_accept_wrapper(SRTSOCKET sock) {
    struct sockaddr_in client_addr;
    int addr_len = sizeof(client_addr);
    return srt_accept(sock, (struct sockaddr*)&client_addr, &addr_len);
}

// Подключение к удалённому сокету
int srt_connect_wrapper(SRTSOCKET sock, const std::string& ip, int port) {
    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &sa.sin_addr);
    return srt_connect(sock, (struct sockaddr*)&sa, sizeof(sa));
}

// Закрытие сокета
void srt_close_wrapper(SRTSOCKET sock) {
    srt_close(sock);
}

// Отправка данных через SRT
int srt_send_wrapper(SRTSOCKET sock, const std::string& data) {
    return srt_send(sock, data.c_str(), data.size());
}

// Получение данных через SRT
std::string srt_recv_wrapper(SRTSOCKET sock, int size) {
    std::vector<char> buf(size);
    int recv_len = srt_recv(sock, buf.data(), size);
    if (recv_len < 0) {
        throw std::runtime_error("Failed to receive data: " + std::string(srt_getlasterror_str()));
    }
    return std::string(buf.data(), recv_len);
}

// Работа с опциями сокета (установка)
int srt_setsockopt_wrapper(SRTSOCKET sock, int optname, const py::object& value) {
    int optlen = sizeof(int);
    int val = value.cast<int>();
    return srt_setsockopt(sock, 0, (SRT_SOCKOPT)optname, &val, optlen);
}

// Работа с опциями сокета (получение)
int srt_getsockopt_wrapper(SRTSOCKET sock, int optname) {
    int val;
    int optlen = sizeof(val);
    srt_getsockopt(sock, 0, (SRT_SOCKOPT)optname, &val, &optlen);
    return val;
}

// Получение состояния сокета
SRT_SOCKSTATUS srt_getsockstate_wrapper(SRTSOCKET sock) {
    return srt_getsockstate(sock);
}

// Получение статистики сокета
py::dict srt_bstats_wrapper(SRTSOCKET sock) {
    SRT_TRACEBSTATS stats;
    srt_bstats(sock, &stats, 1);
    py::dict result;
    result["pktSent"] = stats.pktSent;
    result["pktRecv"] = stats.pktRecv;
    result["pktRetrans"] = stats.pktRetrans;
    return result;
}

// Работа с epoll
int srt_epoll_create_wrapper() {
    return srt_epoll_create();
}

int srt_epoll_add_usock_wrapper(int eid, SRTSOCKET sock, int events) {
    return srt_epoll_add_usock(eid, sock, &events);
}

int srt_epoll_wait_wrapper(int eid, int timeout) {
    SRTSOCKET ready_sockets[10];   // Массив для готовых сокетов (чтение)
    int rnum = 10;                 // Количество готовых сокетов для чтения
    SRTSOCKET write_sockets[10];   // Массив для готовых сокетов (запись)
    int wnum = 10;                 // Количество готовых сокетов для записи
    SYSSOCKET local_read_sockets[10];  // Локальные дескрипторы для чтения
    int lrnum = 0;                    // Количество локальных дескрипторов для чтения
    SYSSOCKET local_write_sockets[10]; // Локальные дескрипторы для записи
    int lwnum = 0;                    // Количество локальных дескрипторов для записи

    // Вызов srt_epoll_wait с полным набором параметров
    int len = srt_epoll_wait(
        eid, 
        ready_sockets, &rnum, 
        write_sockets, &wnum, 
        timeout, 
        local_read_sockets, &lrnum, 
        local_write_sockets, &lwnum
    );

    if (len == SRT_ERROR) {
        throw std::runtime_error("Failed to wait on epoll: " + std::string(srt_getlasterror_str()));
    }

    return len;
}
// Обработка ошибок
std::string srt_getlasterror_str_wrapper() {
    return std::string(srt_getlasterror_str());
}

int srt_getlasterror_wrapper() {
    int err;
    return srt_getlasterror(&err);
}

int srt_sendmsg2_wrapper(SRTSOCKET sock, const std::string& data, SRT_MSGCTRL *mctrl) {
    return srt_sendmsg2(sock, data.c_str(), data.size(), mctrl);
}

std::string srt_recvmsg2_wrapper(SRTSOCKET sock, int size, SRT_MSGCTRL *mctrl) {
    std::vector<char> buf(size);
    int recv_len = srt_recvmsg2(sock, buf.data(), size, mctrl);
    if (recv_len < 0) {
        throw std::runtime_error("Failed to receive data: " + std::string(srt_getlasterror_str()));
    }
    return std::string(buf.data(), recv_len);
}

// Убедитесь, что этот блок кода вызывается только один раз
PYBIND11_MODULE(srt_libsrt, m) {
    m.def("srt_startup", &srt_startup_wrapper, "Initialize SRT library");
    m.def("srt_cleanup", &srt_cleanup_wrapper, "Cleanup SRT library");
    m.def("srt_create_socket", &srt_create_socket_wrapper, "Create SRT socket");
    m.def("srt_bind", &srt_bind_wrapper, "Bind SRT socket to IP and port");
    m.def("srt_listen", &srt_listen_wrapper, "Listen on SRT socket");
    m.def("srt_accept", &srt_accept_wrapper, "Accept client connection");
    m.def("srt_connect", &srt_connect_wrapper, "Connect SRT socket to IP and port");
    m.def("srt_close", &srt_close_wrapper, "Close SRT socket");
    m.def("srt_send", &srt_send_wrapper, "Send data over SRT socket");
    m.def("srt_recv", &srt_recv_wrapper, "Receive data over SRT socket");
    m.def("srt_setsockopt", &srt_setsockopt_wrapper, "Set SRT socket option");
    m.def("srt_getsockopt", &srt_getsockopt_wrapper, "Get SRT socket option");
    m.def("srt_getsockstate", &srt_getsockstate_wrapper, "Get socket state");
    m.def("srt_bstats", &srt_bstats_wrapper, "Get basic statistics of the SRT socket");
    m.def("srt_epoll_create", &srt_epoll_create_wrapper, "Create epoll");
    m.def("srt_epoll_add_usock", &srt_epoll_add_usock_wrapper, "Add socket to epoll");
    m.def("srt_epoll_wait", &srt_epoll_wait_wrapper, "Wait for events in epoll");
    m.def("srt_getlasterror_str", &srt_getlasterror_str_wrapper, "Get last error string");
    m.def("srt_getlasterror", &srt_getlasterror_wrapper, "Get last error code");
    m.def("srt_sendmsg2", &srt_sendmsg2_wrapper, "Send message with control options");
    m.def("srt_recvmsg2", &srt_recvmsg2_wrapper, "Receive message with control options");
}