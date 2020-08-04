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

int InsertFirst(ListHoaDon& listHoaDon, HoaDon addHoaDon)
{
	PTRHoaDon p = new NodeHoaDon;
	if (p == NULL)
	{
		//cout << "Bo nho cua ban da het. Khong them duoc phan tu.";
		return 1;
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
	return 0;
}

int InsertLast(ListHoaDon& listHoaDon, HoaDon addHoaDon)
{
	PTRHoaDon p = new NodeHoaDon;
	if (p == NULL)
	{
		//cout << "Bo nho cua ban da het. Khong them duoc phan tu.";
		return 1;
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
	return 0;
}

int InsertAfter(PTRHoaDon& p, HoaDon addHoaDon)//khi dung ham nay thi ko cap nhat last nen khi goi ham nay phai ktra no co phai last hay ko
{
	PTRHoaDon q = new NodeHoaDon;
	if (q == NULL)
	{
		//cout << "Bo nho cua ban da het. Khong them duoc phan tu.";
		return 1;
	}
	q->infoHoaDon = addHoaDon;
	//q la phan tu can them sau p, lay q tro toi node ma p dang tro toi truoc vi lat nua mat, roi sau do cho p tro toi q
	q->next = p->next;
	p->next = q;
	return 0;
}

PTRHoaDon InsertOrder(ListHoaDon& listHoaDon, HoaDon addHoaDon) //sap xep giam dan theo thoi gian lap hoa don, tra ve node vua them
{
	//neu ma rong thi cho vao dau, hoac la thu tu ngay vi tri dau thi cho vao dau, dung de chan dau
	if (Empty(listHoaDon) || DateCmp(addHoaDon.ngayLap, listHoaDon.first->infoHoaDon.ngayLap) > 0) //them vao dau tien
	{
		int ketQua = InsertFirst(listHoaDon, addHoaDon);
		if (ketQua == 0) {
			return listHoaDon.first;
		}
		else {
			return NULL;
		}
	}
	else if (DateCmp(addHoaDon.ngayLap, listHoaDon.last->infoHoaDon.ngayLap) <= 0) //ko co if nay thi van them vao cuoi dc o else phia duoi nhung last no ko cap nhat va cai nay cung de chan cuoi
	{
		int ketQua = InsertLast(listHoaDon, addHoaDon);
		if (ketQua == 0) {
			return listHoaDon.last;
		}
		else {
			return NULL;
		}	
	}
	else //ko rong va ko phai thu tu dau va khong phai thu tu cuoi
	{
		PTRHoaDon run;
		//dieu kien van chay la node dang them nho hon node dang sau node dang xet, vua lon hon 1 phat thi them vao ben phai cua node dang xet
		for (run = listHoaDon.first; (DateCmp(addHoaDon.ngayLap, run->next->infoHoaDon.ngayLap) < 0); run = run->next); //luon xu li tren run->next, de khi tim dc "run" thi xu li node dang sau run cho ez
		int ketQua = InsertAfter(run, addHoaDon);
		if (ketQua == 0) {
			return run->next; //tra ve node vua them
		}
		else {
			return NULL;
		}
	}
	//note bonus: truong hop co cac date bang nhau thi date vua them vao se nam o cuoi cung, 3 cai if o tren deu the hien dieu do
}

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
	else {
		PTRHoaDon p = listHoaDon.first;
		listHoaDon.first = listHoaDon.first->next;
		delete p;
	}	
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

PTRHoaDon TimKiemHoaDon(DSNhanVien dsNhanVien, char findSoHoaDon[]) //tra ve con tro hoa don, tra ve NULL neu ko tim thay
{
	for (int i = 0; i < dsNhanVien.soLuongNhanVien; i++) {//duyet tung nhan vien

		for (PTRHoaDon run = dsNhanVien.nodesNhanVien[i]->listHoaDon.first; run != NULL; run = run->next) { //duyet tung hoa don nhan vien do

			if (strcmp(run->infoHoaDon.soHoaDon, findSoHoaDon) == 0) {
				return run;
			}
		}
	}
	return NULL;
}

void DeleteInfo(ListHoaDon& listHoaDon, char delSoHoaDon[])
{
	/*if (Empty(listHoaDon))
	{
		cout << "\nKhong the xoa vi danh sach rong.";
		return;
	}*/

	if (strcmp(listHoaDon.first->infoHoaDon.soHoaDon, delSoHoaDon) == 0) //neu node can xoa la first
	{
		//cout << "\nDa xoa xong" << endl;
		DeleteFirst(listHoaDon);
		return;
	}
	if (strcmp(listHoaDon.last->infoHoaDon.soHoaDon, delSoHoaDon) == 0) //neu node can xoa la last, ham duoi co xoa neu no la last luon nhung no ko cap nhat lai last
	{
		//cout << "\nDa xoa xong" << endl;
		DeleteLast(listHoaDon);
		return;
	}
	/*PTRHoaDon run;*/
	/*for (run = listHoaDon.first; run->next != NULL && run->next->infoHoaDon != delData; run = run->next); */
	//luon xu li tren run->next, de khi tim dc "run" thi xu li node dang sau run cho ez
	//(luc truoc suy nghi the nay) dong nay khac voi dong o tren cho run != NULL, neu de la run->next != NULL thi neu ko co phan tu can tim thi no se dung o phan tu cuoi-> sai (run den cuoi cai ko co run-> next->infoHoaDon luon, chuong trinh ko chay duoc)
	for (PTRHoaDon run = listHoaDon.first; run->next != NULL; run = run->next)
	{
		if (strcmp(run->next->infoHoaDon.soHoaDon, delSoHoaDon) == 0)
		{
			DeleteAfter(run);
			return;
		}
	}
	//cout << "Phan tu can xoa ko ton tai!";
}
