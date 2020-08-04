#pragma once
#include<iostream>
#include "Structure.h"
#include <iostream>
#include "XuLyChuoi.h"

using namespace std;

void CreateMangConTro(DSNhanVien& dsNV);

int TimViTriThem(DSNhanVien dsNV, NhanVien addNhanVien);
int TimViTriNhanVien(DSNhanVien dsNV, int findMaNhanVien);

int InsertOrder(DSNhanVien& dsNV, NhanVien addNhanVien);
int InsertLast(DSNhanVien& dsNV, NhanVien addNhanVien);

int XoaNhanVienTheoViTri(DSNhanVien& dsNV, int index);
