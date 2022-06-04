#pragma once
#include "TNode.h"
#include "Table.h"
#include <stack>

class TTreeTable : public TTable{
protected:
	TNode* pRoot, * pCurr, * pPrev;
	std::stack<TNode*> st;
	int currPos;

private:
	void ClearStack() {
		while (!st.empty()) {
			st.pop();
		}
	}

public:
	TTreeTable() : pRoot(NULL), pCurr(NULL), pPrev(NULL), currPos(0) {}

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
			}
			else {
				if (pCurr->rec.key > pPrev->rec.key) {
					pPrev->pRight = pCurr->pLeft;
				}
				else {
					pPrev->pLeft = pCurr->pRight;
				}
			}
		}
		else if (pCurr->pLeft == NULL) {
			if (pPrev == NULL) {
				pRoot = pCurr->pRight;
			}
			else {
				if (pCurr->rec.key > pPrev->rec.key) {
					pPrev->pLeft = pCurr->pRight;
				}
				else {
					pPrev->pRight = pCurr->pLeft;
				}
			}
		}
		else {
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
		Eff++;
		return true;
	}

	TRecord GetCurrRec() { return pCurr->rec; }

	bool IsFull() const { return false; }

	void Reset() {
		currPos = 0;
		pCurr = pRoot;
		ClearStack();
		if (pCurr) {
			while (pCurr->pLeft) {
				st.push(pCurr);
				pCurr = pCurr->pLeft;
			}
		}
		st.push(pCurr);
	}

	void GoNext() {
		pCurr = st.top();
		st.pop();

		if (pCurr) {
			if (pCurr->pRight) {
				pCurr = pCurr->pRight;

				while (pCurr->pLeft) {
					st.push(pCurr);
					pCurr = pCurr->pLeft;
				}
				st.push(pCurr);

			}
			else {
				pCurr = st.top();
			}
			currPos++;
		}
	}

	bool IsEnd() { return currPos == DataCount;  }

	void PrintRec(std::ostream& os, TNode* node, int level) {
		if (node) {
			for (int i = 0; i < level; i++) {
				os << ' ';
			}

			os << node->rec.key << std::endl;
			PrintRec(os, node->pLeft, level + 1);
			PrintRec(os, node->pRight, level + 1);
		}
	}

	void Print (std::ostream& os) {
		PrintRec(os, pRoot, 0);
	}
};
