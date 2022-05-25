#pragma once
#include "THashTable.h"

class TArrayHash : public THashTable {
	TRecord* arr;
	TRecord free, del;
	int size;
	int step;
	int curr;

public:
	TArrayHash(int size = 100, int step = 7) : size(size), step(step) {
		arr = new TRecord[size];

		free.key = -1;
		del.key = -2;

		for (int i = 0; i < size; i++) {
			arr[i] = free;
		}
	}

	~TArrayHash() { delete [] arr; }

	void Reset() { 
		for (curr = 0; curr < size; curr++) {
			if (arr[curr] != free && arr[curr] != del) return;
		}
	}

	bool IsEnd() { return curr == size - 1; }

	void GoNext() { 
		for (curr++ ; curr < size; curr++) {
			if (arr[curr] != free && arr[curr] != del) return;
		}
	}
	
	bool Find(TKey key) {
		int n = HashFunc(key);
		n %= size;
		int delPosition = -1;

		for (int i = 0; i < size; i++) {
			if (arr[n] == free) {
				curr = n;
				return false;
			}
			else if (arr[n].key == key) {
				curr = n;
				return true;
			}
			else if (arr[i] == del && delPosition == -1) {
				delPosition = n;
				curr = n;
				n = (n + step) % size;
			}
		}

		if (delPosition != -1) {
			curr = delPosition;
		}
		return false;
	}

	bool Insert(TRecord rec) {
		if (IsFull) return false;
		if (Find(rec.key)) return false;

		arr[curr] = rec;
		DataCount++;
		Eff++;
		return true;
	}

	bool Delete(TKey key) {
		if (IsEmpty()) return false;
		if (!Find(key)) return false;

		for (Reset(); !IsEnd(); GoNext()){
			if (arr[curr].key == key) {
				arr[curr] = del;
			}
			Eff++;
		}

		DataCount--;
		return true;
	}

};