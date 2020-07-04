//khai bao kieu du lieu Date
typedef struct Date
{
	int ngay;
	int thang;
	int nam;
};

//khai bao Vat Tu
typedef struct VatTu
{
	char tenVatTu[50];
	char donViTinh[10];
	float soLuongTon;
};

typedef struct NodeVatTu
{
	char maVT[10]; //key
	VatTu infoVatTu;
	struct NodeVatTu* left;
	struct NodeVatTu* right;
}
typedef struct NodeVatTu* PTRVatTu;

//khai bao Chi Tiet Hoa Don
typedef struct ChiTietHoaDon
{
	char maVatTu[10];
	int soLuong;
	int donGia;
	int VAT;
	int trangThai;
};

typedef struct DSChiTietHoaDon
{
	int soLuongVatTu;
	ChiTietHoaDon nodesCTHD[20];
}

//khai bao Hoa Don
typedef struct HoaDon
{
	char soHoaDon[20];
	Date ngayLap;
	char loai[2];
};

typedef struct NodeHoaDon
{
	HoaDon infoHoaDon;
	NodeHoaDon* next;
	DSChiTietHoaDon dsCTHD;
}
typedef struct NodeHoaDon* PTRHoaDon;

//khai bao nhan vien
typedef struct NhanVien
{
	int maNhanVien;
	char ho[10];
	char ten[10];
	int phai;
	int soCMND;
	PTRHoaDon first;
};

typedef struct DSNhanVien
{
	int soLuongNhanVien;
	NhanVien* nodesNhanVien[500]; 
}
