class Bag:
    def __init__(self):
        self.items = []

    def add(self, item):
        self.items.append(item)

    def remove(self, item):
        if item in self.items and self.items is not None:
            self.items.remove(item)

    def search(self, item):
        return item in self.items

    def size(self):
        return len(self.items)

    def destroy(self):
        self.items = []

    def nr_occurrences(self, item):
        return self.items.count(item)