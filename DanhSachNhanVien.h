#pragma once
#include "Structure.h"
#include <iostream>
#include "mylib.h"
#include <windows.h> //_getch() trong nay
#include "Design.h"
#include "ValuesDefine.h"
#include "MangConTro.h"
#include "DanhSachHoaDon.h"
#include "DanhSachLienKetDon.h"

using namespace std;

enum class OptionThemNhanVien {
	ThemMaNhanVien,
	ThemHo,
	ThemTen,
	ThemPhai,
	ThemSoCMND
};

int endIndex(DSNhanVien dsNhanVien, int indexFirst);
void KhoiTaoNhanVien(NhanVien& addNhanVien);
void NhanViencpy(NhanVien& nv1, NhanVien nv2);

int KiemTraNhanVienRong(NhanVien addNhanVien);
int KiemTraNhanVienTrungVaSoCMND(NhanVien addNhanVien, DSNhanVien dsNhanVien);
int KiemTraNhanVienTrungKhiSuaNhanVien(NhanVien fixingNhanVien, int indexCurrent, DSNhanVien dsNhanVien);

//key hit after press ENTER (xem nhan vien, sua nhan vien, xem hoa don)
//y tuong cua viec sua nhan vien y chang them nhan vien, luu lai gia tri nhan vien dang sua va xoa no trong ds sinh vien, chi khac phan them nhan vien o cho huy viec sua thi no add cai nhan vien da luu tru vao lai
void ENTER_Keyhit_F1_SuaNhanVien(int keyHit, DSNhanVien& dsNhanVien, int& indexFirst, int& indexLast, int& indexCurrent, bool& isSuaNhanVienAndSucceeds);
void ENTER_Keyhit_F1_Keyhit_F1_SuaNhanVien(int keyHit, NhanVien addNhanVien, DSNhanVien& dsNhanVien, bool& flagThemNhanVien, int toaDoX, int toaDoY, int& indexFirst, int& indexLast, int& indexCurrent);
void ENTER_Keyhit_F2_XemHoaDon(int keyHit, int toaDoX, int toaDoY, DSNhanVien& dsNhanVien, int indexCurrent, ListVatTu& listVatTu, PTRVatTu& root);
//------------------------

//key hit after press INS (them nhan vien)
void INS_Keyhit_F1_ThemNhanVien(int keyHit, NhanVien addNhanVien, DSNhanVien& dsNhanVien, bool& flagThemNhanVien, int toaDoX, int toaDoY, int& indexFirst, int& indexLast, int& indexCurrent);
void INS_Keyhit_Move_And_Enter(int keyHit, OptionThemNhanVien& optionThemNhanVien);
void INS_NhapThongTin(int& keyHit, OptionThemNhanVien optionThemNhanVien, NhanVien& addNhanVien, int toaDoX, int toaDoY);
//------------------------

void WriteForm_INS(int toaDoX, int toaDoY, NhanVien addNhanVien);
void WriteForm_F2_TimKiemNhanVien(int toaDoX, int toaDoY, int findMaNhanVien);

//key hit of main
void Keyhit_Move(int keyHit, int& indexFirst, int& indexLast, int& indexCurrent, DSNhanVien dsNhanVien);
void Keyhit_INS(int keyHit, int toaDoXFormDSNV, int toaDoYFormDSNV, DSNhanVien& dsNhanVien, int& indexFirst, int& indexLast, int& indexCurrent);
void Keyhit_Delete(int keyHit, int toaDoXFormDSNV, int toaDoYFormDSNV, DSNhanVien& dsNhanVien, int& indexFirst, int& indexLast, int& indexCurrent);
void Keyhit_Enter(int keyHit, int toaDoXFormDSNV, int toaDoYFormDSNV, DSNhanVien& dsNhanVien, int& indexFirst, int& indexLast, int& indexCurrent, ListVatTu& listVatTu, PTRVatTu& root);
void Keyhit_F2_TimTheoMaNhanVien(int keyHit, DSNhanVien dsNhanVien, int& indexFirst, int& indexLast, int& indexCurrent, int toaDoXFormDSNhanVien, int toaDoYFormDSNhanVien);
//------------------------

void Output10Nodes(DSNhanVien dsNhanVien, int indexFirst, int indexLast, int indexCurrent, int toaDoX, int toaDoY);
void DrawFormDSNhanVien(int toaDoX, int toaDoY);

void MainDanhSachNhanVien(DSNhanVien& dsNhanVien, ListVatTu& listVatTu, PTRVatTu& root);

//////////////////////////////////////////////-Thong ke doanh thu

void DrawAndWriteFormThongKe(int doangThu[], int namThongKe);

void WriteForm_NhapNamThongKe(int toaDoX, int toaDoY, int namThongKe);

void MainThongKe(DSNhanVien dsNhanVien);
