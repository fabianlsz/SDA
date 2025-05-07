#include "Matrix.h"
#include <exception>
#include <stdexcept>
using namespace std;

///best case: theta 1
///worst case: theta 1
///avg case: theta 1

Matrix::Matrix(int nrLines, int nrCols) {
	   
	nrRow = nrLines;
	nrCol = nrCols;
	size = 0;
	head = -1;
	capacity = 99999;
	matrix = new Tuple[capacity];
	next = new int[capacity];
	for (int i = 0; i < capacity; i++)
		next[i] = i + 1;
	next[capacity - 1] = -1;
	firstEmpty = 0;
}

///bc=wc=avg: theta 1
int Matrix::nrLines() const {
	return nrRow;
}

///bc=wc=avg: theta 1
int Matrix::nrColumns() const {
	return nrCol;
}

///bc: theta 1
///wc: theta n
///avg: o n
TElem Matrix::element(int i, int j) const {
	if (i < 0 || j < 0 || i >= nrRow || j >= nrCol)
		throw invalid_argument("");
	int current = head;
	while (current != -1) {
		if (matrix[current].row == i && matrix[current].column == j)
			return matrix[current].value;
		current = next[current];
	}
	return NULL_TELEM;
}

///best: theta 1
///worst: theta n
///avg: o n
TElem Matrix::modify(int i, int j, TElem e) {
	if (i < 0 || j < 0 || i >= nrRow || j >= nrCol)
		throw invalid_argument("");

	int newNode = firstEmpty;
	firstEmpty = next[firstEmpty];
	matrix[newNode].row = i;
	matrix[newNode].column = j;
	matrix[newNode].value = e;
	next[newNode] = -1;
	if (size == 0 && e != 0) {
		head = newNode;
		size++;
		return NULL_TELEM;
	}
	int current = head;
	int previous = -1;
	while (current != -1) {
		if (matrix[current].row == i && matrix[current].column == j) {
			TElem elem = matrix[current].value;
			if (e == 0) {
				if (previous == -1) {
					head = next[head];
				} else {
					next[previous] = next[current];
				}
				next[current] = firstEmpty;
				firstEmpty = current;
			} else {
				matrix[current].value = e;
			}
			return elem;
		}
		previous = current;
		current = next[current];
	}
	if (e == 0)
		return NULL_TELEM;
	current = head;
	previous = -1;
	while (current != -1 && matrix[current].row < i) {
		previous = current;
		current = next[current];
	}// prev nod current
	if (current == -1) {
		next[previous] = newNode;
		next[newNode] = -1;
	} else if (previous == -1) {
		next[newNode] = head;
		head = newNode;
	} else {
		next[previous] = newNode;
		next[newNode] = current;
	}
	size++;
	return NULL_TELEM;
}

///wc=bc=avg: theta 1
Matrix::~Matrix() {
	delete next;
	delete matrix;
}


