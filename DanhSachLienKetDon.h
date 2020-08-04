#pragma once
#include "Structure.h"
#include <iostream>
#include "XuLyChuoi.h"

using namespace std;

void CreateList(ListHoaDon& listHoaDon);
bool Empty(ListHoaDon listHoaDon);

int InsertFirst(ListHoaDon& listHoaDon, HoaDon addHoaDon);
int InsertLast(ListHoaDon& listHoaDon, HoaDon addHoaDon);
int InsertAfter(PTRHoaDon& p, HoaDon addHoaDon);
PTRHoaDon InsertOrder(ListHoaDon& listHoaDon, HoaDon addHoaDon);

void DeleteFirst(ListHoaDon& listHoaDon);
void DeleteLast(ListHoaDon& listHoaDon);
void DeleteAfter(PTRHoaDon& p);

PTRHoaDon TimKiemHoaDon(DSNhanVien dsNhanVien, char findSoHoaDon[]);

void DeleteInfo(ListHoaDon& listHoaDon, char delSoHoaDon[]);
