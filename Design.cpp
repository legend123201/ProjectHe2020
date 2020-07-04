#include "Design.h"

//ve duong vien
void DrawBorder(int toaDoX, int toaDoY, int chieuNgang, int chieuDoc)
{
	gotoxy(toaDoX, toaDoY); //goc trai tren
	cout << char(KY_TU_GOC_TRAI_TREN);
	gotoxy(toaDoX, toaDoY + chieuDoc); 	//goc trai duoi
	cout << char(KY_TU_GOC_TRAI_DUOI);
	gotoxy(toaDoX + chieuNgang, toaDoY); //goc phai tren
	cout << char(KY_TU_GOC_PHAI_TREN);
	gotoxy(toaDoX + chieuNgang, toaDoY + chieuDoc); //goc phai duoi
	cout << char(KY_TU_GOC_PHAI_DUOI);

	//ve hang
	gotoxy(toaDoX + 1, toaDoY);
	for (int i = 0; i < chieuNgang - 1; i++) {
		cout << char(KY_TU_THANH_NAM_NGANG);
	}
	gotoxy(toaDoX + 1, toaDoY + chieuDoc);
	for (int i = 0; i < chieuNgang - 1; i++) {
		cout << char(KY_TU_THANH_NAM_NGANG);
	}
	//ve cot
	for (int i = 0; i < chieuDoc - 1; i++) {
		gotoxy(toaDoX, toaDoY + i + 1);
		cout << char(KY_TU_THANH_NAM_DOC);
		gotoxy(toaDoX + chieuNgang, toaDoY + i + 1);
		cout << char(KY_TU_THANH_NAM_DOC);
	}
	cout << "\n";
}

//ve mot cai table
void DrawBorderList(int toaDoX, int toaDoY, int soDong, int soCot, int doDaiNgang1Cot, int doDaiDoc1Hang)
{
	for (int i = 0; i < soDong; i++) {
		int tempX = toaDoX;
		for (int j = 0; j < soCot; j++) {
			DrawBorder(tempX, toaDoY, doDaiNgang1Cot, doDaiDoc1Hang + 1);

			if (i == 0 && j > 0) {
				gotoxy(tempX, toaDoY);
				cout << char(KY_TU_CHU_T_TREN_XUONG); //doi goc trai tren cua cac o hang tren cung			
			}
			if (i == soDong - 1 && j > 0) {
				gotoxy(tempX, toaDoY + doDaiDoc1Hang + 1); //doi goc trai duoi cua cac o hang cuoi cung
				cout << char(KY_TU_CHU_T_DUOI_LEN);
			}
			if (j == 0 && i > 0) {
				gotoxy(tempX, toaDoY);//doi goc trai tren cua nhung o cot dau tien
				cout << char(KY_TU_CHU_T_TRAI_SANG);
			}
			if (j == soCot - 1 && i > 0) {
				gotoxy(tempX + doDaiNgang1Cot, toaDoY); //doi goc phai duoi cua nhung o cot cuoi cung
				cout << char(KY_TU_CHU_T_PHAI_SANG);
			}
			if (j > 0 && j < soCot && i > 0 && i < soDong) {
				gotoxy(tempX, toaDoY); //con cac goc phai tren cua cac o con lai cho thanh dau cong la xong
				cout << char(KY_TU_DAU_CONG);
			}

			tempX += doDaiNgang1Cot;
		}
		toaDoY += doDaiDoc1Hang + 1;
	}
}
