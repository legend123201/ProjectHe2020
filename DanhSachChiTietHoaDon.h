#pragma once
#include "Structure.h"
#include <iostream>
#include "mylib.h"
#include <windows.h> //_getch() trong nay
#include "Design.h"
#include "ValuesDefine.h"
#include "DanhSachVatTu.h"
#include "DanhSachTuyenTinh.h"
#include "DanhSachHoaDon.h"

enum class OptionThemChiTietHoaDon { //ko co them ma vat tu va trang thai cua chi tiet hoa don, ma vat tu se tim bang phim F2
	ThemSoLuong,
	ThemDonGia,
	ThemVat
};

int endIndex(DSChiTietHoaDon dsCTHD, int indexFirst);
void KhoiTaoChiTietHoaDon(ChiTietHoaDon& addCTHD);
long long TriGiaChiTietHoaDon(ChiTietHoaDon cthd);

int KiemTraCTHDRong(ChiTietHoaDon addCTHD);
bool KiemTraSoVATDung(ChiTietHoaDon addCTHD);
int KiemTraSoLuongTonVaDuSoLuongTon(ChiTietHoaDon addCTHD, char loaiHoaDon, PTRVatTu addVatTuCTHD);
bool KiemTraTrungMaVatTu(DSChiTietHoaDon dsCTHD, ChiTietHoaDon addCTHD);

//key hit after press INS (them cthd)
void INS_Keyhit_F1_ThemCTHD(int keyHit, ChiTietHoaDon addCTHD, char loaiHoaDon, PTRVatTu addVatTuCTHD, DSChiTietHoaDon& dsCTHD, bool& flagThemThanhCong, int toaDoX, int toaDoY, int& indexFirst, int& indexLast, int& indexCurrent);
void INS_Keyhit_F2_TimVatTu(int keyHit, ChiTietHoaDon& addCTHD, int toaDoX, int toaDoY, PTRVatTu& addVatTuCTHD, ListVatTu& listVatTu, PTRVatTu& root);
void INS_Keyhit_Move_And_Enter(int keyHit, OptionThemChiTietHoaDon& optionThemChiTietHoaDon);
void INS_NhapThongTin(int& keyHit, OptionThemChiTietHoaDon optionThemChiTietHoaDon, ChiTietHoaDon& addCTHD, int toaDoX, int toaDoY);
//------------------------

void WriteForm_INS(int toaDoX, int toaDoY, ChiTietHoaDon addCTHD, PTRVatTu addVatTuCTHD);

//key hit of main
void Keyhit_Move(int keyHit, int& indexFirst, int& indexLast, int& indexCurrent, DSChiTietHoaDon dsCTHD);
void Keyhit_INS(int keyHit, int toaDoXFormDSCTHD, int toaDoYFormDSCTHD, DSChiTietHoaDon& dsCTHD, char loaiHoaDon, int& indexFirst, int& indexLast, int& indexCurrent, ListVatTu& listVatTu, PTRVatTu& root);
void Keyhit_Delete(int keyHit, int toaDoXFormDSCTHD, int toaDoYFormDSCTHD, DSChiTietHoaDon& dsCTHD, int& indexFirst, int& indexLast, int& indexCurrent);
//--------------------

void Output10Nodes(DSChiTietHoaDon dsCTHD, int indexFirst, int indexLast, int indexCurrent, int toaDoX, int toaDoY);
void DrawFormDSChiTietHoaDon(int toaDoX, int toaDoY);

void MainDanhSachChiTietHoaDon(DSChiTietHoaDon& dsCTHD, char loaiHoaDon, ListVatTu& listVatTu, PTRVatTu& root);

/////////////////////////-in ra ds cthd

void DrawFormXemDSChiTietHoaDon(int toaDoX, int toaDoY, HoaDon infoHoaDon);

void MainXemCTHD(HoaDon xemHoaDon);

/////////////////////////-in ra ds cthd va cho phep tra hang

bool DateDuocPhepTraHang(Date kiemTraDate);

void Keyhit_F1_TraHang(int keyHit, ListHoaDon& listHoaDon, HoaDon& xuLyHoaDon, bool& flagXoaHoaDon, int indexCurrent, int toaDoX, int toaDoY);

void MainTraHangCTHD(ListHoaDon& listHoaDon, HoaDon& xuLyHoaDon);
