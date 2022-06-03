#pragma once
#include "TNode.h"
#include "Table.h"
#include <stack>

class TTreeTable : public TTable{
protected:
	TNode* pRoot, * pCurr, * pPrev;
	std::stack<TNode> st;

	TTreeTable() : pRoot(NULL), pCurr(NULL), pPrev(NULL) {}

	bool Find(TKey key) {
		pCurr = pRoot;
		pPrev = NULL;

		while (pCurr != NULL) {
			if (pCurr->rec.key == key) return true;

			pPrev = pCurr;

			if (pCurr->rec.key > key) {
				pCurr = pCurr->pLeft;
			}
			else {
				pCurr = pCurr->pRight;
			}
		}

		pCurr = pPrev;
		return false;
	}

	bool Insert(TRecord rec) {
		if (Find(rec.key)) return false;

		TNode* tmp = new TNode(rec);

		if (IsEmpty()) {
			pRoot = tmp;
		}
		else {
			if (rec.key > pCurr->rec.key) {
				pCurr->pRight = tmp;
			}
			else {
				pCurr->pLeft = tmp;
			}
		}

		DataCount++;
		return true;
	}

	bool Delete(TKey key) {
		if (!Find(key)) return false;
		TNode* tmp = pCurr;

		if (pCurr->pRight == NULL) {
			if (pPrev == NULL) {
				pRoot = pCurr->pLeft;
				delete pCurr;
			}
		}
		else {
			if (pCurr->rec.key > pPrev->rec.key) {
				pPrev->pRight = pCurr->pLeft;
			}
			else {
				pPrev->pLeft = pCurr->pRight;
			}
			delete pCurr;
		}

		if (pCurr->pLeft == NULL) {
			if (pPrev == NULL) {
				pRoot = pCurr->pRight;
				delete pCurr;
			}
		}
		else {
			if (pCurr->rec.key > pPrev->rec.key) {
				pPrev->pLeft = pCurr->pRight;
			}
			else {
				pPrev->pRight = pCurr->pLeft;
			}
			delete pCurr;
		}

		{
			tmp = tmp->pLeft;
			pPrev = pCurr;
			
			while (tmp->pRight != NULL) {
				pPrev = tmp;
				tmp = tmp->pRight;
			}

			pCurr->rec = tmp->rec;
			if (pCurr->pLeft == tmp) {
				pPrev->pLeft = tmp->pLeft;
			} 
			else {
				pPrev->pRight = tmp->pLeft;
			}
			
			delete tmp;
		}

		DataCount--;
		return true;
	}
};
