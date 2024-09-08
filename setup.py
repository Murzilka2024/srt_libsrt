from setuptools import setup, find_packages
from setuptools.command.install import install
import shutil
import os

class CustomInstallCommand(install):
    def run(self):
        # Выполняем стандартную установку
        install.run(self)
        
        # Путь к файлу .so
        so_file = 'srt_libsrt.cpython-37m-x86_64-linux-gnu.so'
        # Директория установки
        target_dir = self.install_lib
        
        # Копируем .so файл в директорию установки, если файл существует
        if os.path.exists(so_file):
            shutil.copy(so_file, target_dir)
            print(f"Файл {so_file} успешно скопирован в {target_dir}.")
        else:
            print(f"Файл {so_file} не найден!")

setup(
    name='srt_libsrt',
    version='0.1',
    packages=find_packages(),
    cmdclass={'install': CustomInstallCommand},
    package_data={
        '': ['srt_libsrt.cpython-37m-x86_64-linux-gnu.so'],
    },
)