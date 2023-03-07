import setuptools
from distutils.core import setup, Extension


module = Extension(
    "structura",
    sources=['src/ringbuffer.c', 'src/structura.c'],  # list of C source files
    include_dirs=['./include'],  # list of directories containing header files
)


def main():
    setup(name="structura",
          version="0.1.2",
          description="C extension module for common data structures",
          author="alperen serkan aksoz",
          author_email="a.serkanaksoz@gmail.com",
          url="https://github.com/sekomer/structura",
          license="MIT",
          ext_modules=[module],
          platforms=['manylinux1_x86_64']
          )


if __name__ == "__main__":
    main()
