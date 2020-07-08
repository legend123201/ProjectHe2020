#pragma once
#include "Structure.h"
#include <iostream>

using namespace std;

void CreateList(ListHoaDon& listHoaDon);
bool Empty(ListHoaDon listHoaDon);
void InsertFirst(ListHoaDon& listHoaDon, HoaDon addHoaDon);
void InsertLast(ListHoaDon& listHoaDon, HoaDon addHoaDon);
void InsertAfter(PTRHoaDon& p, HoaDon addHoaDon);
//PTRHoaDon InsertOrder(ListHoaDon& listHoaDon, HoaDon addHoaDon);
void DeleteFirst(ListHoaDon& listHoaDon);
void DeleteLast(ListHoaDon& listHoaDon);
void DeleteAfter(PTRHoaDon& p);
//void DeleteInfo(ListHoaDon& listHoaDon, HoaDon delHoaDon);

