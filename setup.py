import os

# removing this line causes error: invalid command 'bdist_wheel', wtf...
import setuptools
from distutils.core import setup, Extension


module = Extension(
    "structura",
    # list comprehension to get all .c files in the src directory
    sources=[
        f"./src/{file}" for file in os.listdir("./src") if file.endswith(".c")],
    include_dirs=['./include'],  # list of directories containing header files
)


def main():
    setup(name="structura",
          version="0.2.1",
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
