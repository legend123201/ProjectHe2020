#pragma once
#include "ValuesDefine.h"
#include <string.h>

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
	int donGia;
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
	char loai;
	DSChiTietHoaDon dsCTHD;
};

typedef struct NodeHoaDon
{
	HoaDon infoHoaDon;
	NodeHoaDon* next;
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
	int phai; //0 la nu, 1 la nam
	char soCMND[MAX_SO_CMND];
	ListHoaDon listHoaDon;
};

typedef struct DSNhanVien
{
	int soLuongNhanVien;
	NhanVien* nodesNhanVien[MAX_DS_NHANVIEN];
};

//------------------Cau truc moi------------------------
//khai bao ds Vat Tu 2 la 1 dslk kep
typedef struct NodeVatTu2
{
	char maVatTu[MAX_MA_VAT_TU]; //key 
	PTRVatTu nodeTreeVatTu;
	NodeVatTu2* left;
	NodeVatTu2* right;
};
typedef struct NodeVatTu2* PTRVatTu2;

typedef struct ListVatTu
{
	PTRVatTu2 first;
	PTRVatTu2 last;
};

//khai bao che do nhap thong tin
typedef struct CheDoNhap
{
	bool coGhiChu = false;
	bool coGhiSo = false;
	bool coGhiHoaFull = false; //true la ghi hoa full, false la chi ghi hoa chu cai dau 
	bool coKhoangTrang = false;
};
