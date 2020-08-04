#pragma once
#include "mylib.h"
#include <iostream>
#include <windows.h> //su dung system("color f0"); -> mau nen trang
#include "ValuesDefine.h"
#include "Design.h"
#include "XuLyChuoi.h"
#include "DanhSachNhanVien.h"
#include "DanhSachVatTu.h"

using namespace std;

enum class OptionFirstMenu {
	VatTu,
	NhanVien,
	InHoaDon,
	TraHang,
	ThongKe,
};

void Keyhit_Enter(int keyHit, OptionFirstMenu optionFirstMenu, DSNhanVien& dsNhanVien, ListVatTu& listVatTu, PTRVatTu& root);
void Keyhit_Move(int keyHit, OptionFirstMenu& optionFirstMenu);
void WriteOptionString(string optionString[], OptionFirstMenu optionFirstMenu, int soOption, int doDaiNgang1Cot, int doDaiDoc1Hang);
void DrawMainFrame(int soOption, int doDaiNgang1Cot, int doDaiDoc1Hang);
void MainFirstMenu(DSNhanVien& dsNhanVien, ListVatTu& listVatTu, PTRVatTu& root);
