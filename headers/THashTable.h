#pragma once
#include "Table.h"

class THashTable : public TTable {
protected:
	int HashFunc(TKey key) {
		return NULL;
	}
};