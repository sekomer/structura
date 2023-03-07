from collections import deque
from structura import RingBuffer


# python ringbuffer implementation
class RingBuffer:
    def __init__(self, size):
        self.size = size
        self.data = [None] * size
        self.head = 0
        self.tail = 0

    def enqueue(self, x):
        self.data[self.head] = x
        self.head = (self.head + 1) % self.size
        if self.head == self.tail:
            self.tail = (self.tail + 1) % self.size

    def dequeue(self):
        x = self.data[self.tail]
        self.tail = (self.tail + 1) % self.size
        return x

    def size(self):
        return self.size

    def peek(self):
        return self.data[self.tail]

    def __getitem__(self, i):
        return self.data[(self.tail + i) % self.size]

    def __setitem__(self, i, x):
        self.data[(self.tail + i) % self.size] = x

    def __iter__(self):
        for i in range(len(self)):
            yield self[i]


def native():
    # generate a speed test for pyhon ringbuffer
    rb = RingBuffer(10000000)
    for i in range(10000000):
        rb.enqueue(f'qwerqwer[{i}]]')
    for i in range(10000000):
        rb.dequeue()


def external():
    # generate a speed test for structura ringbuffer
    rb = RingBuffer(10000000)
    for i in range(10000000):
        rb.enqueue(f'qwerqwer[{i}]]')
    for i in range(10000000):
        rb.dequeue()


def builtin():
    # generate a speed test for python deque
    rb = deque(maxlen=10000000)
    for i in range(10000000):
        rb.append(f'qwerqwer[{i}]]')
    for i in range(10000000):
        rb.popleft()


if __name__ == '__main__':
    # run the speed test
    import timeit
    print(timeit.timeit(native, number=1))
    print(timeit.timeit(external, number=1))
    print(timeit.timeit(builtin, number=1))
