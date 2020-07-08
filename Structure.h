#pragma once
#include "ValuesDefine.h"

//khai bao kieu du lieu Date
typedef struct Date
{
	int ngay;
	int thang;
	int nam;
};

//khai bao kieu du lieu Name
typedef struct Name
{
	char ho[MAX_HO];
	char ten[MAX_TEN];
};

//khai bao Vat Tu
typedef struct VatTu
{
	char tenVatTu[MAX_TEN_VAT_TU];
	char donViTinh[MAX_DON_VI_TINH];
	float soLuongTon;
};

typedef struct NodeVatTu
{
	char maVatTu[MAX_MA_VAT_TU]; //key 
	VatTu infoVatTu;
	NodeVatTu* left;
	NodeVatTu* right;
};
typedef struct NodeVatTu* PTRVatTu;

//khai bao Chi Tiet Hoa Don
typedef struct ChiTietHoaDon
{
	char maVatTu[MAX_MA_VAT_TU];
	float soLuong;
	float donGia;
	float VAT;
	int trangThai;
};

typedef struct DSChiTietHoaDon
{
	int soLuongVatTu;
	ChiTietHoaDon nodesCTHD[MAX_DS_CHITIETHOADON];
};

//khai bao Hoa Don
typedef struct HoaDon
{
	char soHoaDon[MAX_SO_HOA_DON];
	Date ngayLap;
	char loai[2];
};

typedef struct NodeHoaDon
{
	HoaDon infoHoaDon;
	NodeHoaDon* next;
	DSChiTietHoaDon dsCTHD;
};
typedef struct NodeHoaDon* PTRHoaDon;

typedef struct ListHoaDon
{
	PTRHoaDon first;
	PTRHoaDon last;
};

//khai bao nhan vien
typedef struct NhanVien
{
	int maNhanVien;
	Name name;
	int phai;
	int soCMND;
	ListHoaDon listHoaDon;
};

typedef struct DSNhanVien
{
	int soLuongNhanVien;
	NhanVien* nodesNhanVien[MAX_DS_NHANVIEN];
};
