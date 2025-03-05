class BagIterator:
    def __init__(self, bag):
        self._bag = bag
        self._index = 0

    def first(self):
        try:
            self._index = 0
        except self._bag is None:
            raise Exception("Bag is empty")

    def next(self):
        if not self.valid():
            raise Exception("Index error")
        self._index += 1

    def get_current(self):
        if not self.valid():
            raise Exception("Index error")
        return self._bag.items[self._index]

    def valid(self):
        return self._index < len(self._bag.items)