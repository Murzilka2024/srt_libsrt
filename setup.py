from setuptools import setup, find_packages
import shutil
import os

# Название модуля
MODULE_NAME = "srt_libsrt"
SO_FILE = "srt_libsrt.cpython-37m-x86_64-linux-gnu.so"

# Создаём папку `srt_libsrt`, если её нет
if not os.path.exists(MODULE_NAME):
    os.mkdir(MODULE_NAME)

# Копируем `.so` в `srt_libsrt/`
if os.path.exists(SO_FILE):
    shutil.copy(SO_FILE, MODULE_NAME)
    print(f"✅ Файл {SO_FILE} скопирован в {MODULE_NAME}/")

setup(
    name=MODULE_NAME,
    version="0.1",
    packages=[MODULE_NAME],  # 📌 Указываем пакет вручную
    package_data={MODULE_NAME: ["*.so"]},  # 📌 Включаем `.so`
    include_package_data=True,
)
