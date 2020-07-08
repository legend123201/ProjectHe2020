#include <iostream>

using namespace std;

typedef struct NV
{
	int a;
	char b[10];
};

typedef struct DSNhanVien
{
	int soLuongNhanVien = 0;
	NV* nodesNhanVien[10] = {NULL};
};

//int SoSanhChuoi(char* a, char* b) {
//
//}

int TimViTriThem(DSNhanVien dsNV, NV addNV) {
	int i;
	for (i = 0; i < dsNV.soLuongNhanVien; i++) {
		if (dsNV.nodesNhanVien[i]->a > addNV.a) { //vi tri nao dau tien hon cai addNV thi do chinh la dia diem them
			return i;
		}
	}
	return dsNV.soLuongNhanVien; //ko thi them o cuoi ds //dung cho ca truong hop chua co nhan vien nao
}

int Them(DSNhanVien& dsNV, NV addNV) {
	if (dsNV.soLuongNhanVien == 10) {
		return 1; //full nhan vien
	}
	int viTriThem = TimViTriThem(dsNV, addNV);
	//dsNV.nodesNhanVien[dsNV.soLuongNhanVien] = new NV;
	for (int i = dsNV.soLuongNhanVien; i > viTriThem; i--) {
		dsNV.nodesNhanVien[i] = dsNV.nodesNhanVien[i - 1]; //dia chi con tro nay dang tro vao bang dia chi con tro truoc no dang tro toi
	}
	dsNV.nodesNhanVien[viTriThem] = new NV;
	*dsNV.nodesNhanVien[viTriThem] = addNV;
	dsNV.soLuongNhanVien++;
	return 0;
}

int Them2(DSNhanVien& dsNV, NV addNV) {
	dsNV.nodesNhanVien[dsNV.soLuongNhanVien] = new NV;
	*dsNV.nodesNhanVien[dsNV.soLuongNhanVien] = addNV;
	dsNV.soLuongNhanVien++;
	return 0;
}

int XoaNhanVienTheoViTri(DSNhanVien& dsNV, int index) {
	if (index < 0 || index >= dsNV.soLuongNhanVien || dsNV.soLuongNhanVien == 0) {
		return 1;
	}
	delete dsNV.nodesNhanVien[index];
	for (int i = index; i < dsNV.soLuongNhanVien - 1; i++) {
		dsNV.nodesNhanVien[i] = dsNV.nodesNhanVien[i + 1]; //dia chi con tro nay dang tro vao bang dia chi con tro sau no dang tro toi
	}
	dsNV.nodesNhanVien[dsNV.soLuongNhanVien - 1] = NULL;//con tro cuoi cung tro ve NULL
	dsNV.soLuongNhanVien--;
	return 0;
}

void Xuat(DSNhanVien dsNV) {
	for (int i = 0; i < dsNV.soLuongNhanVien; i++) {
		cout << dsNV.nodesNhanVien[i]->a <<" "<< dsNV.nodesNhanVien[i]->b <<"\n";
	}
}

int main() {
	DSNhanVien dsNV;
	dsNV.soLuongNhanVien = 0;
	char a[10] = "abc";
	char b[10] = "";
	//cout << strlen(a) << " " << sizeof(a);

	NV nv1, nv2, nv3, nv4, nv5, nv6,nv7,nv8,nv9,nv10, nv11;
	nv1.a = 1;
	nv2.a = 2;
	nv3.a = 3;
	nv4.a = 4;
	nv5.a = 5;
	nv6.a = 6;
	nv7.a = 7;
	nv8.a = 8;
	nv9.a = 9;
	nv10.a = 10;

	nv1.b[0] = 'a';
	nv2.b[0] = 'b';
	nv3.b[0] = 'c';
	nv4.b[0] = 'd';
	nv5.b[0] = 'e';
	nv6.b[0] = 'f';
	nv7.b[0] = 'g';
	nv8.b[0] = 'h';
	nv9.b[0] = 'i';
	nv10.b[0] = 'j';
	nv1.b[1] = '\0';
	nv2.b[1] = '\0';
	nv3.b[1] = '\0';
	nv4.b[1] = '\0';
	nv5.b[1] = '\0';
	nv6.b[1] = '\0';
	nv7.b[1] = '\0';
	nv8.b[1] = '\0';
	nv9.b[1] = '\0';
	nv10.b[1] = '\0';

	Them(dsNV, nv2);	
	Them(dsNV, nv4);
	Them(dsNV, nv3);
	Them(dsNV, nv10);
	Them(dsNV, nv5);
	Them(dsNV, nv6);
	Them(dsNV, nv7);
	Them(dsNV, nv8);
	Them(dsNV, nv9);
	Them(dsNV, nv1);

	XoaNhanVienTheoViTri(dsNV, 5);
	XoaNhanVienTheoViTri(dsNV, 0);
	XoaNhanVienTheoViTri(dsNV, 7);
	XoaNhanVienTheoViTri(dsNV, 0);
	XoaNhanVienTheoViTri(dsNV, 0);
	XoaNhanVienTheoViTri(dsNV, 0);
	XoaNhanVienTheoViTri(dsNV, 0);
	XoaNhanVienTheoViTri(dsNV, 0);
	XoaNhanVienTheoViTri(dsNV, 0);
	//XoaNhanVienTheoViTri(dsNV, 0);
	//cout << dsNV.soLuongNhanVien;
	/*float f;
	cin >> f;
	cout << f;*/

	Them(dsNV, nv8);
	Them(dsNV, nv9);
	Them(dsNV, nv1);

	Xuat(dsNV);

	/*int c;
	int* a;
	int* b;
	int* d;
	a = &c;
	b = &*a;
	d = a;
	cout << &c << endl;
	cout << a << endl;
	cout << &*a << endl;
	cout << b << endl;
	cout << d << endl;*/

	/*int* a = new int;
	*a = 1;
	cout << a << endl;
	cout << &a << endl;
	cout << *a << endl;*/

	return 0;
}
