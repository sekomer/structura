Structura
=====================================

.. explain where does the name come from and what library does

.. image:: https://img.shields.io/pypi/v/structura.svg
   :alt: PyPI version
   :target: https://pypi.org/project/structura/

.. image:: https://static.pepy.tech/personalized-badge/structura?period=total&units=none&left_color=grey&right_color=brightgreen&left_text=Downloads
 :target: https://pepy.tech/project/structura


``Structura`` is a Python library that provides data structures that are implemented in C for better performance.
Its main purpose is to provide a simple and easy interface for data structures.
The name comes from the Latin word **structura** which means **structure**.




.. .. image:: https://github.com/sekomer/structura/workflows/Tests/badge.svg
   :alt: Structura build status on GitHub Actions
   :target: https://github.com/sekomer/structura/actions



.. contents::



Installation
------------
Structura is available on PyPI and can be installed with pip. 
It requires Python 3.5 or above.

.. code-block:: bash

   pip install structura

    
From Source

.. code-block:: bash

   git clone github.com/sekomer/structura
   cd structura
   sudo python3 setup.py install


Documentation
-------------
Detailed documentation can be found in the `docs <./docs/>`_ folder.


General Information
-------------------
- Source code: https://github.com/sekomer/structura
- Documentation: https://github.com/Sekomer/structura/tree/main/docs
- Issue tracker: https://github.com/sekomer/structura/issues

Using Structura
---------------
Structura API follows the pythonic way of doing things. 
It has a simple and straightforward interface. 
Its works with any type of data and python objects.
Heres a quick example of how to use it with RingBuffer data structure.


.. code-block:: python

    from structura import RingBuffer

    buffer = RingBuffer(capacity=3)

    buffer.enqueue(0) # [0]
    buffer.enqueue(1) # [0, 1]
    buffer.enqueue(2) # [0, 1, 2]
    buffer.enqueue(3) # [1, 2, 3]

    buffer.is_full() # True
    buffer.peek()    # 1

    a = buffer.dequeue() # [2, 3]
    b = buffer.dequeue() # [3]
    c = buffer.dequeue() # []
    print(a, b, c)       # 1 2 3

    for i in range(3):
        buffer.enqueue(i)
    
    buffer.clear()    # []
    buffer.is_empty() # True



Detailed documentation and examples can be found in the `docs <./docs/>`_ folder


What's New
----------
- 0.1.0
    - RingBuffer
- 0.2.0
    - Stack
    - LinkedList
- 0.2.1
    - Bug fixes
    - Documentation
- 3.0.0
    - Queue
    - HashMap
    - PriorityQueue
    - Bug fixes
- 3.0.1
    - Python version support added. (3.5 and above)

What's Coming
-------------
Trees, Ropes, Graphs, iterables.

Contributing
------------
All contributions, suggestions, and optimization ideas are welcome!

Proposals for enhancement
-------------------------
You can create an issue or mail me at a.serkanaksoz@gmail.com
