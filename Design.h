#pragma once
#include <iostream>
#include "mylib.h"
#include "ValuesDefine.h"
#include "XuLyChuoi.h"

using namespace std;

void DrawBorder(int toaDoX, int toaDoY, int chieuNgang, int chieuDoc);//ve duong vien
void DrawBorderList(int toaDoX, int toaDoY, int soDong, int soCot, int doDaiNgang1Cot, int doDaiDoc1Hang);//ve mot cai table

void DrawChooseOption(string options[], int toaDoX, int toaDoY, int soOption, int luaChon);
int ChooseOption(string options[], int soOption, int toaDoX, int toaDoY);
int XuatOThongBao(string thongBao[], string options[], int soOption);
void Chon1Trong2(int& luaChon, string luaChon0, string luaChon1, int toaDoX, int toaDoY, int& keyHit);

void ClearWorkFrame();
void WriteTitle(string title);
void WriteSectionGuide(string sectionGuide);
