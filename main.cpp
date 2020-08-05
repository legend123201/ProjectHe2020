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

int main() {

	PTRVatTu root;
	CreateTree(root);
	DocFileVatTu(root, "VatTu.txt");
	
	//OutPutConsole_NLR(root);

	DSNhanVien dsNhanVien;
	CreateMangConTro(dsNhanVien);
	DocFileNhanVien(dsNhanVien, "NhanVien.txt");
	
	
	//tu dau file co tat ca chi tiet hoa don la trang thai 0
//	for (int i = 0; i < dsNhanVien.soLuongNhanVien; i++) { //ktra tung nhan vien
//
//		for (PTRHoaDon run = dsNhanVien.nodesNhanVien[i]->listHoaDon.first; run != NULL; run = run->next) { //kiem tra tung hoa don cua nhan vien do
//
//			for (int j = 0; j < run->infoHoaDon.dsCTHD.soLuongVatTu; j++) {//kiem tra tung cthd cua hoa don do
//
//				if (run->infoHoaDon.dsCTHD.nodesCTHD[j].trangThai == 0) {
//					run->infoHoaDon.dsCTHD.nodesCTHD[j].trangThai = 1;
//				}
//			}	
//		}
//	}

	ListVatTu listVatTu;
	CreateList(listVatTu);
	LoadTreeToDoubleLinkedList_RNL(root, listVatTu);

	MainFirstMenu(dsNhanVien, listVatTu, root);

	GhiFileVatTu(root, "VatTu.txt");
	GhiFileNhanVien(dsNhanVien, "NhanVien.txt");
	return 0;
}
