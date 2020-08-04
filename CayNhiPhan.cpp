#include "CayNhiPhan.h"

void CreateTree(PTRVatTu& root)
{
	root = NULL;
}

bool Empty(PTRVatTu root)
{
	if (root == NULL)
		return true;
	return false;
}

PTRVatTu InsertTree(PTRVatTu& p, char addKey[], VatTu addVatTu)
{
	if (p == NULL) //tim duoc vi tri de them, tao cho no vung nho va cho no gia tri
	{
		p = new NodeVatTu;
		p->infoVatTu = addVatTu;
		strcpy(p->maVatTu, addKey);
		p->left = NULL;
		p->right = NULL;
		return p;
	}
	else if (strcmp(addKey, p->maVatTu) < 0) //khoa can them nho hon khoa nut hien tai thi qua trai
		InsertTree(p->left, addKey, addVatTu);
	else //khoa can them lon hon khoa nut hien tai thi qua phai
		InsertTree(p->right, addKey, addVatTu);
}

//bien maVatTuThayDoiVungNho de phuc vu cho viec cap nhat double linked list
//boi vi double linked list phan gia tri la vung nho cua tree, khi xoa delete case 3, vung nho node bi xoa la node tan cung ben trai cua cay con ben phai cua node can xoa (copy gia tri tu node tan cung ben trai vo cho node can xoa, roi xoa node con tan cung ben trai do) chu khong phai la vung nho node can xoa, vay nen vung nho moi cua node tree tan cung ben trai do trong double linked list se la vung nho cua "node tree can xoa ban dau"
void DeleteTree(PTRVatTu& p, char deleteKey[], char maVatTuThayDoiVungNho[])
{
	if (p == NULL) //dieu kien dung de quy
		cout << "Phan tu can xoa khong ton tai!";
	else //van con phan tu
	{
		if (strcmp(deleteKey, p->maVatTu) < 0) //khoa can them nho hon nut hien tai thi qua trai
			DeleteTree(p->left, deleteKey, maVatTuThayDoiVungNho);
		else if (strcmp(deleteKey, p->maVatTu) > 0) //khoa can them lon hon nut hien tai thi qua phai
			DeleteTree(p->right, deleteKey, maVatTuThayDoiVungNho);
		else //tim duoc phan tu de xoa, deleteKey = p->maVatTu
		{
			PTRVatTu temp = p; //tao temp va tro vao vi tri cua phan tu can xoa
			if (p->left == NULL) //TH ko co cay con ben trai
				p = p->right; // vi la de quy nen dong nay co nghia la p->right = p->right->right(TH can xoa nut ben phai cua nut nao do) hoac la p->left = p->left->right(TH can xoa nut ben trai cua nut nao do), the nen no lien ket voi nhau duoc
			else if (p->right == NULL)//TH ko co cay con ben phai
				p = p->left;
			else
				DeleteTreeCase3(p->right, temp, maVatTuThayDoiVungNho); //TH nut can xoa co 2 nut con, tim nut tan cung ben trai cua cay con ben phai
			delete temp;
		}
	}

}

void DeleteTreeCase3(PTRVatTu& p, PTRVatTu& temp, char maVatTuThayDoiVungNho[])
{
	if (p->left != NULL) //de quy de tim ra phan tu trai tan cung 
		DeleteTreeCase3(p->left, temp, maVatTuThayDoiVungNho);
	else //p luc nay la phan tu trai tan cung, temp van giu gia tri p dau tien
	{
		strcpy(maVatTuThayDoiVungNho, p->maVatTu);
		//copy infoVatTu tu p qua temp
		strcpy(temp->maVatTu, p->maVatTu);
		temp->infoVatTu = p->infoVatTu;
		temp = p; //temp giu vi tri can xoa
		p = p->right; //noi lai cay con ben phai cua p vao lai cay //vi no la nut tan cung ben trai nen no chi co cay con ben phai hoac ko co nut la nao
	}
}

PTRVatTu TimKiemVatTu(PTRVatTu p, char findKey[])
{
	if (p == NULL){
		return NULL; //dieu kien dung de quy->ko tim thay node can tim
	}
	
	if (strcmp(findKey, p->maVatTu) == 0) {
		return p;
	}
	else if (strcmp(findKey, p->maVatTu) > 0) {
		return TimKiemVatTu(p->right, findKey); //return ve ham chu ko don thuan la chi goi ham nhu cac thuat toan duyet, nhu vay se giu duoc ket qua cua vong de quy sau nhat da di toi
	}
	else {
		return TimKiemVatTu(p->left, findKey);
	}
}
