#pragma once
#include "TArrayTable.h"

class TScanTable : public TArrayTable {
public:
	TScanTable(int size = 100) : TArrayTable(size) {}

	bool Find(TKey key) {
		for (int i = 0; i < DataCount; i++) {
			if (key == arr[i].key) {
				curr = i;
				return true;
			}
			Eff++;
		}

		curr = DataCount;
		return false;
	}

	bool Insert(TRecord rec) {
		if (IsFull()) return false;
		if (Find(rec.key)) return false;

		arr[curr] = rec;
		DataCount++;
		Eff++;
		return true;
	}

	bool Delete(TKey key) {
		if (IsEmpty()) return false;
		if (!Find(key)) return false;

		arr[curr] = arr[DataCount - 1];
		DataCount--;
		Eff++;
		return true;
	}
};