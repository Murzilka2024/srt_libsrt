import socket
import pybind11
import srt_module

# Функция для создания SRT сокета
def create_srt_socket(url, passphrase=None):
    sock = srt_module.srt_create_socket()
    
    # Установка шифрования, если указана парольная фраза
    if passphrase:
        srt_module.set_socket_option(sock, "SRTO_PASSPHRASE", passphrase)
    
    # Подключаемся к источнику
    ip, port = parse_url(url)
    srt_module.srt_connect(sock, ip, port)
    return sock

# Функция для создания UDP сокета
def create_udp_socket(url):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    ip, port = parse_url(url)
    sock.connect((ip, port))
    return sock

# Парсинг URL для получения IP и порта
def parse_url(url):
    if "://" in url:
        url = url.split("://")[1]  # Удаляем протокол
    ip, port = url.split(":")
    return ip, int(port)

# Основная функция, создающая сокеты для источника и назначения
def create_input_output_sockets(source_url, dest_url, source_passphrase=None, dest_passphrase=None):
    # Создание входного сокета
    if source_url.startswith("srt://"):
        input_socket = create_srt_socket(source_url, source_passphrase)
    elif source_url.startswith("udp://"):
        input_socket = create_udp_socket(source_url)
    else:
        raise ValueError(f"Неизвестный протокол для source_url: {source_url}")
    
    # Создание выходного сокета
    if dest_url.startswith("srt://"):
        output_socket = create_srt_socket(dest_url, dest_passphrase)
    elif dest_url.startswith("udp://"):
        output_socket = create_udp_socket(dest_url)
    else:
        raise ValueError(f"Неизвестный протокол для dest_url: {dest_url}")
    
    return input_socket, output_socket

# Пример использования
source_url = "srt://194.190.3.49:5006"
dest_url = "udp://89.163.140.96:5050"

source_passphrase = "source_passphrase"
dest_passphrase = None

input_socket, output_socket = create_input_output_sockets(source_url, dest_url, source_passphrase, dest_passphrase)

# Теперь можно работать с input_socket и output_socket для передачи данных
