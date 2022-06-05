#pragma once
#include "TTreeTable.h"

class TBalTree : public TTreeTable {
	int LeftTreeBalIns(TNode*& p) {
		Eff++;
		int result = 0;

		if (p->balance == 1) {
			p->balance = 0;
			result = 0;
		} 
		else if (p->balance == 0) {
			p->balance = -1;
			result = 1;
		}
		else {
			TNode* pL = p->pLeft;

			if (pL->balance == -1) {
				p->pLeft = pL->pRight;
				pL->pRight = p;
				p->balance = 0;
				pL->balance = 0;
				result = 0;
				p = pL;
			} 
			else if (pL->balance == 1) {
				TNode* pR = pL->pRight;

				pL->pRight = pR->pLeft;
				p->pLeft = pR->pRight;
				pR->pLeft = pL;
				pR->pRight = p;

				if (pR->balance == -1) {
					pR->balance == 0;
					pL->balance == 1;
					p->balance == 1;
				}
				else {
					pR->balance == 1;
					pL->balance == 0;
					p->balance == 0;
				}

				result = 0;
				p = pR;
			}
		}

		return result;
	}

	int RightTreeBalIns(TNode*& p) {
		Eff++;
		int result = 0;

		if (p->balance == 0) {
			p->balance = 1;
			result = 1;
		}
		else if (p->balance == -1) {
			p->balance = 0;
			result = 0;
		}
		else {
			TNode* pR = p->pRight;

			if (pR->balance == 1) {
				p->pRight = pR->pLeft;
				pR->pLeft = p;
				p->balance = 0;
				pR->balance = 0;
				result = 0;
				p = pR;
			}
			else if (pR->balance == -1) {
				TNode* pL = pR->pLeft;

				pR->pLeft = pL->pRight;
				p->pRight = pL->pLeft;
				pL->pRight = pR;
				pL->pLeft = p;

				if (pL->balance == -1) {
					pR->balance == 0;
					pL->balance == -1;
					p->balance == 0;
				}
				else {
					pR->balance == -1;
					pL->balance == 0;
					p->balance == -1;
				}

				result = 0;
				p = pL;
			}
		}

		return result;
	}

	int LeftTreeBalDel(TNode*& p) {
		Eff++;
		int result = 0;

		if (p->balance == 1)
		{
			p->balance = 0;
			result = -1;
		}
		else if (p->balance == 0)
		{
			p->balance = -1;
			result = 0;
		}
		else {
			TNode* pl = p->pLeft;

			if (pl->balance == -1)
			{
				p->pLeft = pl->pRight;
				pl->pRight = p;

				pl->balance = 0;
				p->balance = 0;

				p = pl;
				result = -1;
			}
			else if (pl->balance == 1)
			{
				TNode* plpr = pl->pRight;

				pl->pRight = plpr->pLeft;
				plpr->pLeft = pl;
				p->pLeft = plpr->pRight;
				plpr->pRight = p;
				if (plpr->balance == -1)
				{
					p->balance = 1;
				}
				else
				{
					p->balance = 0;
				}
				if (plpr->balance == 1)
				{
					pl->balance = -1;
				}
				else
				{
					pl->balance = 0;
				}
				p = plpr;
				p->balance = 0;
				result = -1;
			}
			else
			{
				TNode* pp = p;
				TNode* plpl = pl->pLeft;
				TNode* plpr = pl->pRight;

				p = pl;
				p->pLeft = plpl;
				p->pRight = pp;
				pp->pLeft = plpr;
				pl->balance = 1;
				return 0;
			}
		}
		return result;
	}

	int RightTreeBalDel(TNode*& p) {
		Eff++;
		int result = 0;

		if (p->balance == -1)
		{
			p->balance = 0;
			result = -1;
		}
		else if (p->balance == 0)
		{
			p->balance = 1;
			result = 0;
		}
		else
		{
			TNode* pr = p->pRight;
			if (pr->balance == 1)
			{
				p->pRight = pr->pLeft;
				pr->pLeft = p;

				pr->balance = 0;
				p->balance = 0;

				p = pr;
				result = -1;
			}
			else if (pr->balance == -1)
			{
				TNode* prpl = pr->pLeft;

				pr->pLeft = prpl->pRight;
				prpl->pRight = pr;
				p->pRight = prpl->pLeft;
				prpl->pLeft = p;
				if (prpl->balance == 1)
				{
					p->balance = -1;
				}
				else
				{
					p->balance = 0;
				}
				if (prpl->balance == -1)
				{
					pr->balance = 1;
				}
				else
				{
					pr->balance = 0;
				}
				p = prpl;
				p->balance = 0;
				result = -1;
			}
			else
			{
				TNode* pp = p;
				TNode* prpl = pr->pLeft;
				TNode* prpr = pr->pRight;

				p = pr;
				p->pLeft = pp;
				p->pRight = prpr;
				pp->pRight = prpl;
				pr->balance = -1;
				return 0;
			}
		}
		return result;
	}

	int InsBalTree(TNode*& p, TRecord rec) {
		Eff++;
		int result = 0;

		if (p == NULL) {
			p = new TNode(rec);
			result = 1;
			DataCount++;
		}
		else if (p->rec.key > rec.key) {
			int tmp = InsBalTree(p->pLeft, rec);

			if (tmp == 1) {
				result = LeftTreeBalIns(p);
			}
		}
		else {
			int tmp = InsBalTree(p->pRight, rec);

			if (tmp == 1) {
				result = RightTreeBalIns(p);
			}
		}

		return result;
	}

	int DelBalTree(TNode*& p, TKey key) {
		Eff++;
		int result = 0;

		if (p == NULL) {
			return result;
		}
		if (key > p->rec.key) {
			int tmp = DelBalTree(p->pRight, key);

			if (tmp != 0) {
				result = LeftTreeBalDel(p);
			}
		}
		else if (key < p->rec.key) {
			int tmp = DelBalTree(p->pLeft, key);

			if (tmp != 0) {
				result = RightTreeBalDel(p);
			}
		}
		else if (key == p->rec.key) {
			DataCount--;
			if (p->pLeft == NULL && p->pRight == NULL) {
				delete p;
				p = NULL;
				result = -1;
			}
			else if (p->pLeft != NULL && p->pRight == NULL) {
				p->rec = p->pLeft->rec;
				delete p->pLeft;
				p->pLeft = NULL;
				p->balance = 0;
				result = -1;
			}
			else if (p->pLeft == NULL && p->pRight != NULL) {
				p->rec = p->pRight->rec;
				delete p->pRight;
				p->pRight = NULL;
				p->balance = 0;
				result = 1;
			}
			else {
				TNode* pL = p->pLeft;
				TNode* pR = p->pRight;
				TNode* pMax = FindMax(pL);

				p->rec = pMax->rec;
				int tmp = DelBalTree(p->pLeft, pMax->rec.key);

				if (tmp != 0) {
					result = RightTreeBalDel(p->pRight);
				}
			}
		}
		return result;
	}

	TNode* FindMax(TNode* p) const {
		while (p->pRight != NULL) {
			p = p->pRight;
		}
		return p;
	}

public:
	bool Insert(TRecord rec) {
		if (Find(rec.key)) return false;

		InsBalTree(pRoot, rec);
		return true;
	}

	bool Delete(TKey key) {
		if (!Find(key)) return false;

		DelBalTree(pRoot, key);
		return true;
	}
};