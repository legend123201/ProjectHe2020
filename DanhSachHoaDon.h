#pragma once
#include "Structure.h"
#include <iostream>
#include "mylib.h"
#include <windows.h> //_getch() trong nay
#include "Design.h"
#include "ValuesDefine.h"
#include "DanhSachTuyenTinh.h"
#include "DanhSachLienKetDon.h"
#include "DanhSachChiTietHoaDon.h"

enum class OptionThemHoaDon {
	ThemSoHoaDon,
	ThemNgay,
	ThemThang,
	ThemNam,
	ThemLoai
};

PTRHoaDon endNode(PTRHoaDon firstNode);
PTRHoaDon prevNode(PTRHoaDon firstNode, PTRHoaDon currentNode);
void KhoiTaoHoaDon(HoaDon& addHoaDon);
long long TriGiaHoaDon(DSChiTietHoaDon dsCTHD);

int KiemTraHoaDonRong(HoaDon addHoaDon);
int KiemTraHoaDonTrung(HoaDon addHoaDon, DSNhanVien dsNhanVien);

void TimTrangChuaCurrentNode(ListHoaDon listHoaDon, PTRHoaDon& firstNode, PTRHoaDon currentNode, PTRHoaDon& lastNode, int& trangHienTai);

//key hit after press INS (them hoa don)
void INS_Keyhit_F1_ThemHoaDon(int keyHit, HoaDon addHoaDon, ListHoaDon& listHoaDon, bool& flagThemHoaDon, int toaDoX, int toaDoY, PTRHoaDon& firstNode, PTRHoaDon& lastNode, PTRHoaDon& currentNode, int& trangHienTai, DSNhanVien dsNhanVien, ListVatTu& listVatTu, PTRVatTu& root);
void INS_Keyhit_F2_XemDsCTHD(int keyHit, HoaDon& addHoaDon, bool& flagDaQuyetDinhLoaiHoaDon, int toaDoX, int toaDoY, ListVatTu listVatTu, PTRVatTu root);
void INS_Keyhit_Move_And_Enter(int keyHit, OptionThemHoaDon& optionThemHoaDon);
void INS_NhapThongTin(int& keyHit, OptionThemHoaDon optionThemHoaDon, HoaDon& addHoaDon, bool flagDaQuyetDinhLoaiHoaDon, int toaDoX, int toaDoY);
//------------------------

void WriteForm_INS(int toaDoX, int toaDoY, HoaDon addHoaDon);

//key hit cua main ds hoa don
void Keyhit_Move(ListHoaDon listHoaDon, PTRHoaDon& firstNode, PTRHoaDon& lastNode, PTRHoaDon& currentNode, int& trangHienTai, int keyhit);
void Keyhit_INS(int keyHit, int toaDoXFormDSHD, int toaDoYFormDSHD, ListHoaDon& listHoaDon, PTRHoaDon& firstNode, PTRHoaDon& lastNode, PTRHoaDon& currentNode, int& trangHienTai, DSNhanVien dsNhanVien, ListVatTu& listVatTu, PTRVatTu& root);
void Keyhit_Enter(int keyHit, int toaDoXFormDSHD, int toaDoYFormDSHD, ListHoaDon listHoaDon, PTRHoaDon currentNode);
//-------------------------------

void Output10Nodes(PTRHoaDon firstNode, PTRHoaDon lastNode, PTRHoaDon currentNode, int trangHienTai, int toaDoX, int toaDoY);
void DrawFormDSHoaDon(int toaDoX, int toaDoY);

void MainDanhSachHoaDon(ListHoaDon& listHoaDon, DSNhanVien dsNhanVien, ListVatTu& listVatTu, PTRVatTu& root);

////////////////////////-in hoa don dua vao so hoa don do user nhap

void WriteForm_TimKiemHoaDon(int toaDoX, int toaDoY, char findSoHoaDon[]);

void MainXemHoaDon(DSNhanVien dsNhanVien);

////////////////////////-in hoa don va cho phep tra hang dua vao so hoa don do user nhap

void MainTraHangHoaDon(DSNhanVien& dsNhanVien);
