from setuptools import setup, find_packages
from setuptools.command.install import install
import shutil
import os

class CustomInstall(install):
    def run(self):
        target_dir = os.path.join(self.install_lib, 'srt_libsrt')
        self.mkpath(target_dir)
        shutil.copy('srt_libsrt.cpython-37m-x86_64-linux-gnu.so', target_dir)
        install.run(self)

setup(
    name='srt_libsrt',
    version='0.1',
    description='Precompiled SRT library for Python',
    author='murzilka2024',
    packages=find_packages(),
    cmdclass={'install': CustomInstall},
    classifiers=[
        'Programming Language :: Python :: 3',
        'Operating System :: Linux',
    ],
)