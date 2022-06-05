#include <iostream>
#include "../headers/TSortTable.h"
#include "../headers/THashTable.h"
#include "../headers/TArrayHash.h"
#include "../headers/TTreeTable.h"
#include "../headers/TBalTree.h"

void main() {
	/*TSortTable t;
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
	std::cout << t;*/

	/*TArrayHash t;
	//TRecord insertRec;

	//for (int i = 0; i < 5; i++) {
	//	insertRec.key = i;
	//	insertRec.value = "value" + i;
	//	t.Insert(insertRec);
	//	if (i == 0) {
	//		insertRec.key = 100;
	//		insertRec.value = "second key 0";
	//		t.Insert(insertRec);
	//	}
	//}

	std::cout << t;

	t.Delete(2);

	std::cout << t;*/

	/*TTreeTable t;
	TRecord insertRec;

	for (int i = 0; i < 5; i++) {
		insertRec.key = i;
		insertRec.value = "value" + i;
		t.Insert(insertRec);
	}

	t.Print(std::cout);

	t.Delete(2);

	t.Print(std::cout);*/\

	TBalTree t;
	TRecord insertRec;

	for (int i = 5; i > 0; i--) {
		insertRec.key = i;
		insertRec.value = "value" + i;
		t.Insert(insertRec);
	}

	t.Print(std::cout);
	std::cout << "\n\n";

	t.Delete(2);

	t.Print(std::cout);

	std::cout << "\n\n";

	t.Delete(4);

	t.Print(std::cout);

}