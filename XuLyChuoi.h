#pragma once
#include <string.h>
//#include <cstring>
#include "Structure.h"
//#include <string>
#include <string>
#include <iostream>
#include <windows.h>
#include "mylib.h"

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS //bo qua loi khi dung ham localtime, no warning la nen dung localtime_s
#include <ctime>

using namespace std;

char KyTuCuoi(char s[]);
void ThemVaoCuoiChuoi(char s[], char addChar);
bool isFullString(char s[], int maxChuoi);
int NameCmp(Name name1, Name name2);

string FloatToString(float a);
//float StringToFloat(string s);

Date StringToDate(string s);
string DateToString(Date date);
string OutputDate(Date date);
int KiemTraDate(Date date);
int DateCmp(Date date1, Date date2);
int MaxNgayCuaThangTrongNam(int thang, int nam);
int SoNgayDaDatHang(Date dateDatHang);

string NameToString(Name name);

string CenterTextInSpace(string s, int wide);

void OutputString(string info, int maxChuoi, int toaDoX, int toaDoY);
void NhapThongTin(string& s, int maxChuoi, int toaDoX, int toaDoY, int& keyHit, CheDoNhap cheDoNhap);

bool DaCoDauCham(string s);
void NhapSoThuc(string& s, int maxChuoi, int toaDoX, int toaDoY, int& keyHit);
