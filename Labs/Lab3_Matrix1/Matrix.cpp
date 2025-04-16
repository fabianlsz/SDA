#include "Matrix.h"
#include <exception>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
	   
	//TODO - Implementation
}


int Matrix::nrLines() const {
	return nrRow;
}


int Matrix::nrColumns() const {
	return nrCol;
}


TElem Matrix::element(int i, int j) const {
	//TODO - Implementation
	return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {
	//TODO - Implementation
	return NULL_TELEM;
}

Matrix::~Matrix() {
	delete next;
	delete matrix;
}


