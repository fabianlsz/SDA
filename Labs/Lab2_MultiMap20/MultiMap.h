#pragma once
#include <vector>
#include <utility>

// DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int, int>(-111111, -111111)

class MultiMapIterator;

struct ValueNode {
	TValue value;
	ValueNode* next;
	ValueNode* prev;
};

struct KeyNode {
	TKey key;
	ValueNode* valueHead;
	KeyNode* next;
	KeyNode* prev;
};

class MultiMap {
	friend class MultiMapIterator;

private:
	KeyNode* head; // Head of the doubly linked list for keys
	KeyNode* tail; // Tail of the doubly linked list for keys
	int totalSize; // Total number of key-value pairs

public:
	// Constructor
	MultiMap();

	// Adds a key-value pair to the multimap
	void add(TKey c, TValue v);

	// Removes a key-value pair from the multimap
	// Returns true if the pair was removed (if it was in the multimap) and false otherwise
	bool remove(TKey c, TValue v);

	// Returns the vector of values associated with a key
	std::vector<TValue> search(TKey c) const;

	// Returns the number of pairs in the multimap
	int size() const;

	// Checks whether the multimap is empty
	bool isEmpty() const;

	// Returns an iterator for the multimap
	MultiMapIterator iterator() const;

	// Destructor
	~MultiMap();

private:
	// Helper to find a KeyNode by key
	KeyNode* findKeyNode(TKey key) const;

	// Helper to delete a ValueNode list
	void deleteValueList(ValueNode* valueHead);
};