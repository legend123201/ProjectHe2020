#include "DanhSachLienKetKep.h"

void CreateList(ListVatTu& listVatTu)
{
	listVatTu.first = NULL;
	listVatTu.last = NULL;
}

bool Empty(ListVatTu& listVatTu)
{
	if (listVatTu.first == NULL)
		return true;
	return false;
}

void InsertFirst(ListVatTu& listVatTu, PTRVatTu& nodeTreeVatTu)
{
	PTRVatTu2 p = new NodeVatTu2;

	//khoi tao gia tri
	strcpy(p->maVatTu, nodeTreeVatTu->maVatTu);
	p->nodeTreeVatTu = nodeTreeVatTu;
	p->left = NULL;
	p->right = NULL;

	//TH rong va TH khong rong
	if (Empty(listVatTu))
	{
		listVatTu.first = listVatTu.last = p;
	}
	else
	{
		p->right = listVatTu.first;
		listVatTu.first->left = p;
		listVatTu.first = p;
	}
}

void InsertLast(ListVatTu& listVatTu, PTRVatTu& nodeTreeVatTu)
{
	PTRVatTu2 p = new NodeVatTu2;

	//khoi tao gia tri
	strcpy(p->maVatTu, nodeTreeVatTu->maVatTu);
	p->nodeTreeVatTu = nodeTreeVatTu;
	p->left = NULL;
	p->right = NULL;

	if(Empty(listVatTu)) {
		listVatTu.first = listVatTu.last = p;
	}
	else
	{
		listVatTu.last->right = p; 
		p->left = listVatTu.last;
		listVatTu.last = p;
	}
}

void InsertAfter(PTRVatTu2& p, PTRVatTu& nodeTreeVatTu)
{
	PTRVatTu2 q = new NodeVatTu2;

	//khoi tao gia tri
	strcpy(q->maVatTu, nodeTreeVatTu->maVatTu);
	q->nodeTreeVatTu = nodeTreeVatTu;

	//q->right la node dang sau p, q->left la p
	q->right = p->right;
	q->left = p;
	//phan tu dang sau p se co left la q (ptu vua them), va p -> right la q
	p->right->left = q; //hoac q->right->left = q;
	p->right = q;
}

PTRVatTu2 InsertOrder(ListVatTu& listVatTu, PTRVatTu& nodeTreeVatTu) //sap xep giam dan theo ma vat tu, tra ve node vua them
{
	//neu ma rong thi cho vao dau, hoac la thu tu ngay vi tri dau thi cho vao dau, dung de chan dau
	if (Empty(listVatTu) || strcmp(nodeTreeVatTu->maVatTu, listVatTu.first->maVatTu) > 0) //them vao dau tien
	{
		InsertFirst(listVatTu, nodeTreeVatTu);
		return listVatTu.first;
	}
	else if (strcmp(nodeTreeVatTu->maVatTu, listVatTu.last->maVatTu) < 0) //ko co if nay thi van them vao cuoi dc o else phia duoi nhung last no ko cap nhat va cai nay cung de chan cuoi
	{
		InsertLast(listVatTu, nodeTreeVatTu);
		return listVatTu.last;
	}
	else //ko rong va ko phai thu tu dau va khong phai thu tu cuoi
	{
		PTRVatTu2 run;
		//dieu kien van chay la node dang them nho hon node dang sau node dang xet, vua lon hon 1 phat thi them vao ben phai cua node dang xet
		for (run = listVatTu.first; strcmp(nodeTreeVatTu->maVatTu, run->right->maVatTu) < 0 ; run = run->right);
		InsertAfter(run, nodeTreeVatTu);
		return run->right; //tra ve node vua them
	}
}

void DeleteFirst(ListVatTu& listVatTu)
{
	if (listVatTu.first == listVatTu.last) //danh sach chi 1 phan tu
	{
		delete listVatTu.first;
		listVatTu.first = listVatTu.last = NULL;
	}
	else {//nhieu hon 1 phan tu
		PTRVatTu2 temp = listVatTu.first;

		listVatTu.first = listVatTu.first->right; //cap nhat first
		delete temp;

		listVatTu.first->left = NULL; //khac ds lien ket don, o day phai cap nhat ca first.left
	}
}

void DeleteLast(ListVatTu& listVatTu)
{
	if (listVatTu.first == listVatTu.last) //danh sach chi 1 phan tu
	{
		delete listVatTu.first;
		listVatTu.first = listVatTu.last = NULL;
	}
	else {//nhieu hon 1 phan tu
		PTRVatTu2 temp = listVatTu.last;

		listVatTu.last = listVatTu.last->left; //cap nhat last
		delete temp;

		listVatTu.last->right = NULL;
	}
}

void DeleteInfo(ListVatTu& listVatTu, char deleteMaVatTu[])
{
	PTRVatTu2 run = listVatTu.first;
	while (strcmp(run->maVatTu, deleteMaVatTu) != 0) {
		run = run->right;
	}

	//run dang nam o cho can xoa
	if (run == listVatTu.first) {
		DeleteFirst(listVatTu);
	}
	else if (run == listVatTu.last) {
		DeleteLast(listVatTu);
	}
	else {//trung hop node nam o giua, va tat nhien no ko phai last va first
		run->left->right = run->right;
		run->right->left = run->left;
		delete run;
	}
}
