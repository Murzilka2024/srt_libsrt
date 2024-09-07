from setuptools import setup, Extension
import pybind11

# Указываем путь к Pybind11 заголовкам
pybind11_include = pybind11.get_include()

# Настройка для библиотеки
srt_libsrt = Extension(
    'srt_libsrt',  # Имя модуля
    sources=['srt_libsrt.cpp'],  # Файлы с исходным кодом
    include_dirs=[pybind11_include, '/usr/src/Python-3.7.17/vega/srt_project/includes'],  # Директории с заголовками
    libraries=['srt'],  # Зависимые библиотеки
    library_dirs=['/usr/local/lib/x86_64-linux-gnu/libsrt.so.1.5.4'],  # Путь к библиотекам
    language='c++'  # Указываем, что это C++
)

setup(
    name='srt_libsrt',
    version='0.1',
    ext_modules=[srt_libsrt],
    install_requires=['pybind11'],  # Зависимости
)