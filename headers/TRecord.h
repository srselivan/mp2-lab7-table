#pragma once
#include <iostream>
#include <string>

typedef int TKey;
typedef std::string TValue;

struct TRecord {
	TKey key;
	TValue value;

	TRecord() {}

	TRecord(TKey key, TValue value) : key(key), value(value) {}

	bool operator > (const TRecord& rec) const {
		return key > rec.key;
	}

	bool operator < (const TRecord& rec) const {
		return key < rec.key;
	}

	bool operator == (const TRecord& rec) const {
		return key == rec.key;
	}
	
	bool operator != (const TRecord& rec) const {
		return key != rec.key;
	}

	friend std::ostream& operator<< (std::ostream& os, const TRecord rec) {
		os << rec.key << " " << rec.value;
		return os;
	}
};