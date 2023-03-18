import os

# removing this line causes error: invalid command 'bdist_wheel', wtf...
import setuptools
from distutils.core import setup, Extension


module = Extension(
    "structura",
    sources=[
        f"./src/{file}" for file in os.listdir("./src") if file.endswith(".c")],
    include_dirs=['./include'],
    extra_compile_args=["-O3", "-std=c99"],
)


def main():
    setup(name="structura",
          version="0.3.0",
          description="C extension module for common data structures",
          author="alperen serkan aksoz",
          author_email="a.serkanaksoz@gmail.com",
          url="https://github.com/sekomer/structura",
          license="MIT",
          ext_modules=[module],
          platforms=['manylinux1_x86_64'],
          classifiers=[
              "Development Status :: 3 - Alpha",
              "Intended Audience :: Developers",
              "License :: OSI Approved :: MIT License",
              "Operating System :: POSIX :: Linux",
              "Programming Language :: C",
              "Programming Language :: Python :: 3",
              "Topic :: Software Development :: Libraries :: Python Modules",
          ])


if __name__ == "__main__":
    main()
