#include <iostream>
#include "FirstMenu.h"
#include "Structure.h"
#include "WorkWithFile.h"

using namespace std;

void OutputConsole_NodesLeftRight(PTRVatTu p)
{
	if (p->left != NULL) //co nut trai 
		cout << "\n " << p->maVatTu << " " << p->left->maVatTu << " ";
	else
		cout << "\n " << p->maVatTu << " none ";
	if (p->right != NULL) //co nut phai
		cout << p->right->maVatTu;
	else
		cout << " none ";
}

void OutPutConsole_NLR(PTRVatTu p)
{
	if (p != NULL)
	{
		OutputConsole_NodesLeftRight(p);
		OutPutConsole_NLR(p->left);
		OutPutConsole_NLR(p->right);
	}
}

//dung LRN de ko xoa delete case 3 -> ton time
void GiaiPhongVungNhoVatTu_LRN(PTRVatTu& p){
	if (p != NULL)
	{
		GiaiPhongVungNhoVatTu_LRN(p->left);
		GiaiPhongVungNhoVatTu_LRN(p->right);		
		
		//phan xu ly
		delete p;
	}
}

void GiaiPhongVungNhoNhanVien(DSNhanVien& dsNhanVien){
	PTRHoaDon temp;
	for(int i = 0; i < dsNhanVien.soLuongNhanVien; i++){
		
		while(dsNhanVien.nodesNhanVien[i]->listHoaDon.first != NULL){
			
			temp = dsNhanVien.nodesNhanVien[i]->listHoaDon.first;
			dsNhanVien.nodesNhanVien[i]->listHoaDon.first = dsNhanVien.nodesNhanVien[i]->listHoaDon.first->next;
			delete temp;
		}
		delete dsNhanVien.nodesNhanVien[i];
	}
}

int main() {

	PTRVatTu root;
	CreateTree(root);
	DocFileVatTu(root, "VatTu.txt");
	
	//OutPutConsole_NLR(root);

	DSNhanVien dsNhanVien;
	CreateMangConTro(dsNhanVien);
	DocFileNhanVien(dsNhanVien, "NhanVien.txt");

	ListVatTu listVatTu;
	CreateList(listVatTu);
	LoadTreeToDoubleLinkedList_RNL(root, listVatTu);

	MainFirstMenu(dsNhanVien, listVatTu, root);

	GhiFileVatTu(root, "VatTu.txt");
	GhiFileNhanVien(dsNhanVien, "NhanVien.txt");
	
	GiaiPhongVungNhoVatTu_LRN(root);
	GiaiPhongVungNhoNhanVien(dsNhanVien);
	
	return 0;
}
