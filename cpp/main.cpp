#include <iostream>
#include "../headers/TSortTable.h"

void main() {
	TSortTable t;
	TRecord insertRec;

	for (int i = 0; i < 5; i++){
		insertRec.key = i;
		insertRec.value = "value" + i;
		t.Insert(insertRec);
	}

	std::cout << t;
	int lastEff = t.GetEff();
	std::cout << lastEff;

	t.Find(3);
	std::cout << "\n" << t.GetEff() - lastEff;
	
	t.Delete(2);
	std::cout << t;
}