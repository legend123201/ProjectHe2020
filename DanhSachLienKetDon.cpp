#include "DanhSachLienKetDon.h"

void CreateList(ListHoaDon& listHoaDon)
{
	listHoaDon.first = NULL;
	listHoaDon.last = NULL;
}

bool Empty(ListHoaDon listHoaDon)
{
	if (listHoaDon.first == NULL)
		return true;
	return false;
}

void InsertFirst(ListHoaDon& listHoaDon, HoaDon addHoaDon)
{
	PTRHoaDon p = new NodeHoaDon;
	if (p == NULL)
	{
		cout << "Bo nho cua ban da het. Khong them duoc phan tu.";
		return;
	}
	p->infoHoaDon = addHoaDon;
	p->next = NULL;
	//TH rong va TH khong rong
	if (Empty(listHoaDon))
	{
		listHoaDon.first = listHoaDon.last = p;
	}
	else
	{
		p->next = listHoaDon.first;
		listHoaDon.first = p;
	}
}

void InsertLast(ListHoaDon& listHoaDon, HoaDon addHoaDon)
{
	PTRHoaDon p = new NodeHoaDon;
	if (p == NULL)
	{
		cout << "Bo nho cua ban da het. Khong them duoc phan tu.";
		return;
	}
	p->infoHoaDon = addHoaDon;
	p->next = NULL;
	//TH rong va TH khong rong
	if (Empty(listHoaDon))
	{
		listHoaDon.first = listHoaDon.last = p;
	}
	else
	{
		listHoaDon.last->next = p;
		listHoaDon.last = p;
	}
}

void InsertAfter(PTRHoaDon& p, HoaDon addHoaDon)//khi dung ham nay thi ko cap nhat last nen khi goi ham nay phai ktra no co phai last hay ko
{
	PTRHoaDon q = new NodeHoaDon;
	if (q == NULL)
	{
		cout << "Bo nho cua ban da het. Khong them duoc phan tu.";
		return;
	}
	q->infoHoaDon = addHoaDon;
	//q la phan tu can them sau p, lay q tro toi node ma p dang tro toi truoc vi lat nua mat, roi sau do cho p tro toi q
	q->next = p->next;
	p->next = q;
}

//PTRHoaDon InsertOrder(ListHoaDon& listHoaDon, HoaDon addHoaDon) //sap xep tang dan, tra ve node vua them
//{
//	int soLuongNut = 1;
//	//neu ma rong thi cho vao dau, hoac la thu tu ngay vi tri dau thi cho vao dau, dung de chan dau
//	if (Empty(listHoaDon) || listHoaDon.first->infoHoaDon > addHoaDon) //them vao dau tien
//	{
//		InsertFirst(listHoaDon, addHoaDon);
//		return listHoaDon.first;
//	}
//	else if (listHoaDon.last->infoHoaDon <= addHoaDon) //ko co if nay thi van them vao cuoi dc o else phia duoi nhung last no ko cap nhat va cai nay cung de chan cuoi
//	{
//		InsertLast(listHoaDon, addHoaDon);
//		return listHoaDon.last;
//	}
//	else //ko rong va ko phai thu tu dau
//	{
//		PTRHoaDon run;
//		for (run = listHoaDon.first; (run->next != NULL) && (run->next->infoHoaDon < addHoaDon); run = run->next, soLuongNut++); //luon xu li tren run->next, de khi tim dc "run" thi xu li node dang sau run cho ez
//		InsertAfter(run, addHoaDon);
//		return run->next; //tra ve node vua them
//	}
//}

void DeleteFirst(ListHoaDon& listHoaDon)
{
	if (Empty(listHoaDon))
	{
		cout << "Khong co phan tu de xoa.";
		return;
	}
	if (listHoaDon.first == listHoaDon.last) //danh sach chi 1 phan tu
	{
		delete listHoaDon.first;
		listHoaDon.first = listHoaDon.last = NULL;
	}
	PTRHoaDon p = listHoaDon.first;
	listHoaDon.first = listHoaDon.first->next;
	delete p;
}

void DeleteLast(ListHoaDon& listHoaDon)
{
	if (Empty(listHoaDon))
	{
		cout << "Khong co phan tu de xoa.";
		return;
	}
	if (listHoaDon.first == listHoaDon.last) //danh sach chi 1 phan tu
	{
		delete listHoaDon.first;
		listHoaDon.first = listHoaDon.last = NULL;
	}
	for (PTRHoaDon p = listHoaDon.first; p != NULL; p = p->next)
	{
		if (p->next == listHoaDon.last) // tim dc cai truoc cai last
		{
			delete listHoaDon.last;
			p->next = NULL;
			listHoaDon.last = p;
		}
	}
}

void DeleteAfter(PTRHoaDon& p) //khi dung ham nay thi ko cap nhat last nen khi goi ham nay phai ktra no co phai last hay ko
{
	PTRHoaDon q;
	q = p->next; //p -> next = q
	p->next = q->next; //noi cai next bac cau qua roi xoa
	delete q;
}

//void DeleteInfo(ListHoaDon& listHoaDon, HoaDon delData)
//{
//	if (Empty(listHoaDon))
//	{
//		cout << "\nKhong the xoa vi danh sach rong.";
//		return;
//	}
//	if (listHoaDon.first->infoHoaDon == delData) //neu node can xoa la first
//	{
//		cout << "\nDa xoa xong" << endl;
//		DeleteFirst(listHoaDon);
//		return;
//	}
//	if (listHoaDon.last->infoHoaDon == delData) //neu node can xoa la last, ham duoi co xoa neu no la last luon nhung no ko cap nhat lai last
//	{
//		cout << "\nDa xoa xong" << endl;
//		DeleteLast(listHoaDon);
//		return;
//	}
//	/*PTRHoaDon run;*/
//	/*for (run = listHoaDon.first; run->next != NULL && run->next->infoHoaDon != delData; run = run->next); */
//	//luon xu li tren run->next, de khi tim dc "run" thi xu li node dang sau run cho ez
//	//(luc truoc suy nghi the nay) dong nay khac voi dong o tren cho run != NULL, neu de la run->next != NULL thi neu ko co phan tu can tim thi no se dung o phan tu cuoi-> sai (run den cuoi cai ko co run-> next->infoHoaDon luon, chuong trinh ko chay duoc)
//	for (PTRHoaDon run = listHoaDon.first; run->next != NULL; run = run->next)
//	{
//		if (run->next->infoHoaDon == delData)
//		{
//			DeleteAfter(run);
//			return;
//		}
//	}
//	cout << "Phan tu can xoa ko ton tai!";
//}
