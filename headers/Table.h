#pragma once
#include "TRecord.h"

class TTable {
protected:
	int DataCount; 
	int Eff;

public:
	TTable() : DataCount(0), Eff(0) {}

	virtual ~TTable() {} 

	virtual bool IsFull() const = 0;

	virtual bool Find(TKey key) = 0;

	virtual bool Insert(TRecord rec) = 0;

	virtual bool Delete(TKey key) = 0;

	virtual void Reset() = 0;

	virtual bool IsEnd() = 0;

	virtual void GoNext() = 0;

	virtual TRecord GetCurrRec() = 0;

	int GetDataCount() const { return DataCount; }

	int GetEff() const { return Eff; }

	void ClearEff() { Eff = 0; }

	bool IsEmpty() const { return DataCount == 0; }

	friend std::ostream& operator<< (std::ostream& os, TTable& t) {
		for (t.Reset(); !t.IsEnd(); t.GoNext()) {
			os << t.GetCurrRec() << std::endl;
		}
		return os;
	}
};