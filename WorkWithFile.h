#pragma once

#include <fstream>
#include <iostream>
#include "Structure.h"
#include <string> //ham getline() trong day
#include "CayNhiPhan.h"
#include "MangConTro.h"
#include "DanhSachLienKetDon.h"
#include "DanhSachTuyenTinh.h"
#include "DanhSachLienKetKep.h"
#include "XuLyChuoi.h"

using namespace std;

void DocFileVatTu(PTRVatTu& root, string nameFile);
void GhiFileVatTu(PTRVatTu root, string nameFile);
void GhiFile_NLR(PTRVatTu p, fstream& f);
void LineToVatTu(string line, char addKey[], VatTu& addVatTu);

void DocFileNhanVien(DSNhanVien& dsNhanVien, string nameFile);
void GhiFileNhanVien(DSNhanVien dsNhanVien, string nameFile);
void LineToNhanVien(string line, NhanVien& addNhanVien);

void LoadTreeToDoubleLinkedList_RNL(PTRVatTu& p, ListVatTu& listVatTu);
