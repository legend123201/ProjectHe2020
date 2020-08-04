#pragma once
#include "Structure.h"
#include <iostream>
#include "mylib.h"
#include <windows.h> //_getch() trong nay
#include "Design.h"
#include "ValuesDefine.h"
#include "CayNhiPhan.h"
#include "DanhSachLienKetKep.h"

enum class OptionThemVatTu {
	ThemMaVatTu,
	ThemTenVatTu,
	ThemDonViTinh,
	ThemSoLuongTon
};

PTRVatTu2 endNode(PTRVatTu2 firstNode);
PTRVatTu2 startNode(PTRVatTu2 lastNode);
void KhoiTaoVatTu(char addMaVatTu[], VatTu& addVatTu);
void VatTucpy(PTRVatTu& p1, PTRVatTu p2);
void CapNhatMaVatTuMoiCuaCTHD(PTRVatTu oldInfo, PTRVatTu newInfo, DSNhanVien& dsNhanVien);

int KiemTraVatTuRong(char addMaVatTu[], VatTu addVatTu);
int KiemTraVatTuTrung(char addMaVatTu[], PTRVatTu root);
int KiemTraVatTuTrung_CaseSuaVatTu(char addMaVatTu[], PTRVatTu2 currentNode, PTRVatTu root);

void TimTrangChuaCurrentNode(ListVatTu listVatTu, PTRVatTu2& firstNode, PTRVatTu2& lastNode, PTRVatTu2 currentNode, int& trangHienTai);

//key hit after press ENTER (xem nhan vien, sua nhan vien, xem hoa don)
void ENTER_Keyhit_F1_SuaVatTu(int keyHit, ListVatTu& listVatTu, PTRVatTu& root, PTRVatTu2& firstNode, PTRVatTu2& lastNode, PTRVatTu2& currentNode, int& trangHienTai, bool& isSuaVatTuAndSucceeds, DSNhanVien dsNhanVien);
void ENTER_Keyhit_F1_Keyhit_F1_SuaVatTu(int keyHit, PTRVatTu fixingVatTu, ListVatTu& listVatTu, PTRVatTu& root, bool& flagSuaThanhCong, int toaDoX, int toaDoY, PTRVatTu2& firstNode, PTRVatTu2& lastNode, PTRVatTu2& currentNode, int& trangHienTai, DSNhanVien dsNhanVien);
void ENTER_Keyhit_F1_Keyhit_Move_And_Enter(int keyHit, OptionThemVatTu& optionThemVatTu);
//------------------------

//key hit after press INS (them vat tu)
void INS_Keyhit_F1_ThemVatTu(int keyHit, char addMaVatTu[], VatTu addVatTu, ListVatTu& listVatTu, PTRVatTu& root, bool& flagThemVatTu, int toaDoX, int toaDoY, PTRVatTu2& firstNode, PTRVatTu2& lastNode, PTRVatTu2& currentNode, int& trangHienTai);
void INS_Keyhit_Move_And_Enter(int keyHit, OptionThemVatTu& optionThemVatTu);
void INS_NhapThongTin(int& keyHit, OptionThemVatTu optionThemVatTu, char addMaVatTu[], VatTu& addVatTu, int toaDoX, int toaDoY);
//------------------------

void WriteForm_INS(int toaDoX, int toaDoY, char addMaVatTu[], VatTu addVatTu);

//key hit of MainDanhSachVatTu
void Keyhit_Move(ListVatTu listVatTu, PTRVatTu2& firstNode, PTRVatTu2& lastNode, PTRVatTu2& currentNode, int& trangHienTai, int keyhit);
void Keyhit_INS(int keyHit, int toaDoXFormDSVatTu, int toaDoYFormDSVatTu, ListVatTu& listVatTu, PTRVatTu& root, PTRVatTu2& firstNode, PTRVatTu2& lastNode, PTRVatTu2& currentNode, int& trangHienTai);
void Keyhit_Enter(int keyHit, int toaDoXFormDSVatTu, int toaDoYFormDSVatTu, ListVatTu& listVatTu, PTRVatTu& root, PTRVatTu2& firstNode, PTRVatTu2& lastNode, PTRVatTu2& currentNode, int& trangHienTai, DSNhanVien dsNhanVien);
void Keyhit_Delete(int keyHit, int toaDoXFormDSVatTu, int toaDoYFormDSVatTu, ListVatTu& listVatTu, PTRVatTu& root, PTRVatTu2& firstNode, PTRVatTu2& lastNode, PTRVatTu2& currentNode, int& trangHienTai, DSNhanVien dsNhanVien);
//-----------------------------

void Output10Nodes(PTRVatTu2 firstNode, PTRVatTu2 lastNode, PTRVatTu2 currentNode, int trangHienTai, int toaDoX, int toaDoY);
void DrawFormDSVatTu(int toaDoX, int toaDoY);

void MainDanhSachVatTu(ListVatTu& listVatTu, PTRVatTu& root, DSNhanVien dsNhanVien);

///////////////////////////////////////////////////

void WriteForm_F2_TimKiemVatTu(int toaDoX, int toaDoY, char tempMaVatTu[]);

//cac nut cua MainTimKiemVatTu
void Keyhit_F2_TimTheoMaVatTu(int keyHit, ListVatTu listVatTu, PTRVatTu root, PTRVatTu2& firstNode, PTRVatTu2& lastNode, PTRVatTu2& currentNode, int& trangHienTai, int toaDoXFormDSVatTu, int toaDoYFormDSVatTu);
//------------------------------

PTRVatTu MainTimKiemVatTu(ListVatTu listVatTu, PTRVatTu root);

/////////////////////////////////////////////////// - cap nhap so luong ton khi them hoa don

void CapNhatSoLuongTon(HoaDon addHoaDon, PTRVatTu& root);
