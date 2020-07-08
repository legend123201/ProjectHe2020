#include "MangConTro.h"

int TimViTriThem(DSNhanVien dsNV, NhanVien addNhanVien) {
	int i;
	for (i = 0; i < dsNV.soLuongNhanVien; i++) {
		if (dsNV.nodesNhanVien[i]->a > addNhanVien.a) { //vi tri nao dau tien hon cai addNhanVien thi do chinh la dia diem them
			return i;
		}
	}
	return dsNV.soLuongNhanVien; //ko thi them o cuoi ds //dung cho ca truong hop chua co nhan vien nao
}

int InsertOrder(DSNhanVien& dsNV, NhanVien addNhanVien) {
	if (dsNV.soLuongNhanVien == 10) {
		return 1; //full nhan vien
	}
	int viTriThem = TimViTriThem(dsNV, addNhanVien);
	//dsNV.nodesNhanVien[dsNV.soLuongNhanVien] = new NhanVien;
	for (int i = dsNV.soLuongNhanVien; i > viTriThem; i--) {
		dsNV.nodesNhanVien[i] = dsNV.nodesNhanVien[i - 1]; //dia chi con tro nay dang tro vao bang dia chi con tro truoc no dang tro toi
	}
	dsNV.nodesNhanVien[viTriThem] = new NhanVien;
	*dsNV.nodesNhanVien[viTriThem] = addNhanVien;
	dsNV.soLuongNhanVien++;
	return 0;
}

int InsertLast(DSNhanVien& dsNV, NhanVien addNhanVien) {
	dsNV.nodesNhanVien[dsNV.soLuongNhanVien] = new NhanVien;
	*dsNV.nodesNhanVien[dsNV.soLuongNhanVien] = addNhanVien;
	dsNV.soLuongNhanVien++;
	return 0;
}

int XoaNhanVienTheoViTri(DSNhanVien& dsNV, int index) {
	if (index < 0 || index >= dsNV.soLuongNhanVien || dsNV.soLuongNhanVien == 0) {
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
