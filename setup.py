import os
import glob
import pathlib
import setuptools
from setuptools.command.build_ext import build_ext


module = setuptools.Extension(
    name="structura",
    define_macros=[("MAJOR_VERSION", "0"), ("MINOR_VERSION", "3")],
    sources=glob.glob("./src/*.c"),
    include_dirs=["./src", "./include"],
)


with pathlib.Path(__file__).parent.joinpath("README.rst").open() as f:
    long_description = f.read()


def main():
    setuptools.setup(name="structura",
                     version="0.3.1",
                     description="C extension module for common data structures",
                     author="alperen serkan aksoz",
                     author_email="a.serkanaksoz@gmail.com",
                     long_description=long_description,
                     url="https://github.com/sekomer/structura",
                     license="MIT",
                     ext_modules=[module],
                     python_requires=">=3",
                     cmdclass={'build_ext': build_ext},
                     zip_safe=False,
                     classifiers=[
                         "Development Status :: 3 - Alpha",
                         "Intended Audience :: Developers",
                         "License :: OSI Approved :: MIT License",
                         "Operating System :: POSIX :: Linux",
                         "Programming Language :: C",
                         "Programming Language :: Python :: 3.x",
                         "Topic :: Software Development :: Libraries :: Python Modules",
                     ],
                     options={'bdist_wheel': {'universal': True},
                              'build_ext': {'inplace': True}})


if __name__ == "__main__":
    main()
