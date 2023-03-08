from structura import LinkedList

l = LinkedList()

for i in range(100):
    l.append(f"q{i}")
    print(l.head()) # this generates error
    print(l.tail()) # no error

for i in range(100):
    l.delete_at(0)

print(31)

