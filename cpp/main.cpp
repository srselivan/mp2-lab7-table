#include <iostream>
#include "../headers/TSortTable.h"
#include "../headers/THashTable.h"
#include "../headers/TArrayHash.h"
#include "../headers/TTreeTable.h"
#include "../headers/TBalTree.h"
#include <conio.h>	

#define C	99
#define I	105
#define F	102
#define D	100
#define ENTER	13
#define ESC		27

struct TableConfig {
	int type;
	int size;
	int key_interval;

	TableConfig(int t, int s, int k) : type(t), size(s), key_interval(k) {};
	
	TableConfig() : type(0), size(10), key_interval(10) {};
};

TTable* table;
TTreeTable* treetable;
TableConfig config;

bool result = true;
int eff = 0;

void PrintMenu(bool result, int eff) {
	std::cout <<
		"C - Create table" << "\n" <<
		"I - Insert key" << "\n" <<
		"F - Find key" << "\n" <<
		"D - Delete key" << "\n" <<
		"Result: " << std::to_string(result) << "\n" <<
		"Efficiency: " << eff << "\n"
		;
}

void PrintVariations() {
	std::cout <<
		"\n0 - Scan Table" << "\n" <<
		"1 - Sort Table" << "\n" <<
		"2 - Hash Table" << "\n" <<
		"3 - Tree Table" << "\n" <<
		"4 - Bal  Table" << "\n" <<
		"Insert: type, size, key range" << "\n" << 
		"> "
		;
}

void CreateTable(TableConfig config) {
	switch (config.type)
	{
		case 0: {
			table = new TScanTable(config.size);
			break;
		}	

		case 1: {
			table = new TSortTable(config.size);
			break;
		}	
	
		case 2: {
			table = new TArrayHash(config.size);
			break;
		}

		case 3: {
			treetable = new TTreeTable();
			break;
		}

		case 4: {
			treetable = new TBalTree();
			break;
		}

		default:
			break;
	}

	srand(time(NULL));

	for (int i = 0; i < config.size; i++) {
		TRecord rec;

		result = false;
		while (result == false) {
			rec.key = rand() % config.key_interval;
			rec.value = std::string("record ") + std::to_string(i);

			if (config.type >= 3) {
				treetable->ClearEff();
				result = treetable->Insert(rec);
				eff = treetable->GetEff();
			}
			else {
				table->ClearEff();
				result = table->Insert(rec);
				eff = table->GetEff();
			}
		}
	}
}

void InsertKey(TTable* table) {
	TRecord rec;
	std::cout << "\nInsert: key" << "\n> ";
	std::cin >> rec.key;
	rec.value = std::string("record ") + std::to_string(table->GetDataCount() + 1);

	table->ClearEff();
	result = table->Insert(rec);
	eff = table->GetEff();
}

void DeleteKey(TTable* table) {
	TKey delKey;
	std::cout << "\nDelete: key" << "\n> ";
	std::cin >> delKey;

	table->ClearEff();
	result = table->Delete(delKey);
	eff = table->GetEff();
}

void FindKey(TTable* table) {
	TKey findKey;
	std::cout << "\nFind: key" << "\n> ";
	std::cin >> findKey;

	table->ClearEff();
	result = table->Find(findKey);
	eff = table->GetEff();
}

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

	t.Print(std::cout);*/

	/*TBalTree t;
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

	t.Print(std::cout);*/

	char key;

	do {
		system("CLS");
		PrintMenu(result, eff);
		if (table != NULL || treetable != NULL) {
			if (config.type >= 3) {
				treetable->Print(std::cout);
			}
			else {
				std::cout << *table;
			}
		}

		key = _getch();
		if (key == 0xE0) key = _getch();
		if (key == ESC) break;
		if (key != ENTER) key = _getch();
		switch (key) {
			case ENTER:
				break;

			case C: {
				PrintVariations();
				std::cin >> config.type;
				std::cin >> config.size;
				std::cin >> config.key_interval;
				CreateTable(config);
				break;
			}

			case I: {
				if (table != NULL) {
					InsertKey(table);
				}
				else if (treetable != NULL) {
					InsertKey(treetable);
				}
				break;
			}

			case F: {
				if (table != NULL) {
					FindKey(table);
				}
				else if (treetable != NULL) {
					FindKey(treetable);
				}
				break;
			}

			case D: {
				if (table != NULL) {
					DeleteKey(table);
				}
				else if (treetable != NULL) {
					DeleteKey(treetable);
				}
				break;
			}
		}

		std::cout << std::endl;
	} while (key != ESC);

}