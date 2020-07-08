#include <iostream>
#include "FirstMenu.h"
#include "Structure.h"

using namespace std;

void mainTest(DSNhanVien& dsNhanVien);

//int main() {
//	DSNhanVien dsNhanVien;
//	//MainFirstMenu();
//	mainTest(dsNhanVien);
//	cout << dsNhanVien.soLuongNhanVien;
//	return 0;
//}

void mainTest(DSNhanVien& dsNhanVien) {
	dsNhanVien.soLuongNhanVien++;
}
