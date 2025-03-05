from iterator import *
from bag import *

bag = Bag()
bag.add(1)
bag.add(2)
bag.add(3)
iterator = BagIterator(bag)

iterator.first()
assert iterator._index == 0
iterator.next()
assert iterator._index == 1

iterator.first()
assert iterator.valid() == True
iterator.next()
iterator.next()
iterator.next()
assert iterator.valid() == False

bag.add(4)
assert bag.search(4) == True
bag.remove(4)
assert bag.search(4) == False

assert bag.size() == 3
bag.destroy()
assert bag.size() == 0

print("All tests passed!")