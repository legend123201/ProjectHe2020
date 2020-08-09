#include "MangConTro.h"

void CreateMangConTro(DSNhanVien& dsNV)
{
	dsNV.soLuongNhanVien = 0;
}

int TimViTriThem(DSNhanVien dsNV, NhanVien addNhanVien) {
	int i;
	for (i = 0; i < dsNV.soLuongNhanVien; i++) {
		if (NameCmp(dsNV.nodesNhanVien[i]->name, addNhanVien.name) > 0) { //vi tri nao dau tien lon hon cai addNhanVien thi do chinh la dia diem them
			return i;
		}
	}
	return dsNV.soLuongNhanVien; //ko thi them o cuoi ds //dung cho ca truong hop chua co nhan vien nao
}

int TimViTriNhanVien(DSNhanVien dsNV, int findMaNhanVien) //tra ve vi tri cua nhan vien, -1 neu nhu ko tim thay ma nhan vien
{
	for (int i = 0; i < dsNV.soLuongNhanVien; i++) {
		if (dsNV.nodesNhanVien[i]->maNhanVien == findMaNhanVien) {
			return i;
		}
	}
	return -1;
}

int InsertOrder(DSNhanVien& dsNV, NhanVien addNhanVien) { //tra ve vi tri them, -1 la loi full nhan vien
	if (dsNV.soLuongNhanVien == MAX_DS_NHANVIEN) {
		cout << "FULL NHAN VIEN";
		return -1; //full nhan vien
	}
	int viTriThem = TimViTriThem(dsNV, addNhanVien);
	//dsNV.nodesNhanVien[dsNV.soLuongNhanVien] = new NhanVien;
	for (int i = dsNV.soLuongNhanVien; i > viTriThem; i--) {
		dsNV.nodesNhanVien[i] = dsNV.nodesNhanVien[i - 1]; //dia chi con tro nay dang tro vao bang dia chi con tro truoc no dang tro toi
	}
	dsNV.nodesNhanVien[viTriThem] = new NhanVien;
	*dsNV.nodesNhanVien[viTriThem] = addNhanVien;
	dsNV.soLuongNhanVien++;
	return viTriThem;
}

void InsertLast(DSNhanVien& dsNV, NhanVien addNhanVien) {
	dsNV.nodesNhanVien[dsNV.soLuongNhanVien] = new NhanVien;
	*dsNV.nodesNhanVien[dsNV.soLuongNhanVien] = addNhanVien;
	dsNV.soLuongNhanVien++;
}

int XoaNhanVienTheoViTri(DSNhanVien& dsNV, int index) {
	if (index < 0 || index >= dsNV.soLuongNhanVien || dsNV.soLuongNhanVien == 0) {
		cout << "VI TRI MANG CON TRO XOA BI LOI";
		return 1;
	}
	delete dsNV.nodesNhanVien[index];
	for (int i = index; i < dsNV.soLuongNhanVien - 1; i++) {
		dsNV.nodesNhanVien[i] = dsNV.nodesNhanVien[i + 1]; //dia chi con tro nay dang tro vao bang dia chi con tro sau no dang tro toi
	}
	dsNV.nodesNhanVien[dsNV.soLuongNhanVien - 1] = NULL;//con tro cuoi cung tro ve NULL
	dsNV.soLuongNhanVien--;
	return 0;
}
