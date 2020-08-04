#include "DanhSachTuyenTinh.h"

void CreateMangTuyenTinh(DSChiTietHoaDon& dsCTHD)
{
	dsCTHD.soLuongVatTu = 0;
}

int InsertLast(DSChiTietHoaDon& dsCTHD, ChiTietHoaDon cthd) { //tra ve vi tri them phan tu, tra ve -1 khi full ds
	if (dsCTHD.soLuongVatTu >= MAX_DS_CHITIETHOADON) {
		//cout << "TOI DA 20 VAT TU TRONG DS CTHD!" << endl;
		return -1;
	}
	dsCTHD.nodesCTHD[dsCTHD.soLuongVatTu] = cthd;
	dsCTHD.soLuongVatTu++;
	return dsCTHD.soLuongVatTu - 1;
}

void XoaCTHDTheoViTri(DSChiTietHoaDon& dsCTHD, int index)
{
	for (int i = index; i < dsCTHD.soLuongVatTu - 1; i++) { //chay vong for den ptu gan cuoi
		dsCTHD.nodesCTHD[i] = dsCTHD.nodesCTHD[i + 1];
	}
	dsCTHD.soLuongVatTu--;
}
