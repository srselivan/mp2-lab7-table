#pragma once
#include "Table.h"

class TArrayTable : public TTable {
protected:
	TRecord* arr;
	int size;
	int curr;

public:
	TArrayTable(int size) : size(size), curr(-1), arr(new TRecord[size]) {}

	~TArrayTable() { delete[] arr; }

	bool IsFull() const { return DataCount == size; }

	void Reset() { curr = 0; }

	bool IsEnd() { return curr == DataCount; }

	void GoNext() { curr++; }

	TRecord GetCurrRec() { return arr[curr]; }

	int GetSize() { return size; }
};