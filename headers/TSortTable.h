#pragma once
#include "TArrayTable.h"
#include "TScanTable.h"

class TSortTable : public TArrayTable {
public:
	TSortTable(int size = 100) : TArrayTable(size) {}

	TSortTable(TScanTable& table) : TArrayTable(table.GetSize()) {
		for (int i = 0; i < table.GetSize(); i++) {
			arr[i] = table.GetCurrRec();
		}

		QSort(0, table.GetSize());
	}

	void QSort(int s, int f) {
		int newS = s;
		int newF = f;
		int k = (s + f) / 2;
		TKey elem = arr[k].key;

		while (newS < newF) {
			Eff++;

			while (arr[newS].key < elem) { 
				newS++; 
				Eff++;
			}
			while (arr[newS].key > elem) { 
				newF--; 
				Eff++;
			}
			
			if (newS < newF) {
				TRecord tmp = arr[newS];
				arr[newS] = arr[newF];
				arr[newF] = tmp;
				newS++;
				newF++;
			}

			if (s < newF) QSort(s, newF);
			if (newS < f) QSort(newS, f);
		}
	}

	bool Find(TKey key) {
		int left = 0;
		int right = DataCount - 1;
		int middle;

		while (left <= right) {
			middle = (left + right) / 2;
			
			if (arr[middle].key < key) { left = middle + 1; }
			else if (arr[middle].key > key) { right = middle - 1; }
			else { 
				curr = middle;
				return true;
			}

			Eff++;
		}

		curr = left;
		return false;
	}

	bool Insert(TRecord rec) {
		if (IsFull()) return false;
		if (Find(rec.key)) return false;

		for (int i = DataCount; i > curr; i--) {
			arr[i] = arr[i - 1];
			Eff++;
		}

		arr[curr] = rec;
		DataCount++;
		Eff++;
		return true;
	}

	bool Delete(TKey key) {
		if (IsEmpty()) return false;
		if (!Find(key)) return false;

		for (int i = curr; i < DataCount; i++) {
			arr[i] = arr[i + 1];
			Eff++;
		}

		DataCount--;
		return true;
	}
};