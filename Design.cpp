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

void DrawChooseOption(string options[], int toaDoX, int toaDoY, int soOption, int luaChon)
{
	if (soOption == 1) {
		SetColor(Red);

		gotoxy(toaDoX + 1, toaDoY + 1); //+1 de vao giua o
		cout << CenterTextInSpace(options[0], 20);

		SetColor(Black);
	}
	else {
		if(luaChon == 0)
			SetColor(Red);

		gotoxy(toaDoX + 1, toaDoY + 1);
		cout << CenterTextInSpace(options[0], 20);

		SetColor(Black);

		if (luaChon == 1)
			SetColor(Red);

		gotoxy(toaDoX + 20 + 8 + 1, toaDoY + 1);
		cout << CenterTextInSpace(options[1], 20);

		SetColor(Black);
	}
}

int ChooseOption(string options[], int soOption, int toaDoX, int toaDoY) //soOption chi dc la 1 hoac 2
{
	int luaChon = 0;
	int keyHit = -1;

	if (soOption == 1) {
		int x = toaDoX + 40 - 10; //+40 de vao giua va -10 de tim diem bat dau, vi do dai chieu ngang la 20
		int y = toaDoY + 16;

		DrawBorder(x, y, 20, 2); // ve khung

		while (true)
		{
			if (keyHit == 224) {
				keyHit = _getch();
			}
			if (keyHit == 0) {
				keyHit = _getch();
			}

			//cac nut bam
			if (keyHit == ENTER) {
				return 0;
			}

			//viet chu
			DrawChooseOption(options, x, y, soOption, luaChon);

			keyHit = _getch();
		}
	}
	else {
		int x = toaDoX + 40 - 20 - 4; //+40 de vao giua va -20 de tim diem bat dau, -4 de lam cai khoang cach giua 2 border (khoang cach = 8)
		int y = toaDoY + 16;

		DrawBorder(x, y, 20, 2); //ve 2 khung
		DrawBorder(x + 20 + 8, y, 20, 2);

		while (true)
		{
			if (keyHit == 224) {
				keyHit = _getch();
			}
			if (keyHit == 0) {
				keyHit = _getch();
			}

			//cac nut bam
			if (keyHit == ENTER) {
				return luaChon;
			}
			if (keyHit == KEY_LEFT) {
				luaChon = 0;
			}
			if (keyHit == KEY_RIGHT) {
				luaChon = 1;
			}

			//viet chu
			DrawChooseOption(options, x, y, soOption, luaChon);

			keyHit = _getch();
		}
	}
}

int XuatOThongBao(string thongBao[], string options[], int soOption) //soOption chi dc la 1 hoac 2, toi da chi co 2 dong thong bao
{
	int toaDoX = (MAX_X_OF_MAIN_FRAME - START_X_OF_MAIN_FRAME)/2 + 25 - 40; //diem giua, +25 vi chieu dai o option main frame, -40 de tim diem bat dau, vi do dai ngang = 80
	int toaDoY = (MAX_Y_OF_MAIN_FRAME - START_Y_OF_MAIN_FRAME)/2 - 10; //giong x
	int chieuNgang = 80;
	int chieuDoc = 20;

	DrawBorder(toaDoX, toaDoY, chieuNgang, chieuDoc);

	gotoxy(toaDoX + 1 , toaDoY + 9);
	cout << CenterTextInSpace(thongBao[0], chieuNgang);

	gotoxy(toaDoX + 1, toaDoY + 10);
	cout << CenterTextInSpace(thongBao[1], chieuNgang);

	return ChooseOption(options, soOption, toaDoX, toaDoY);
}

void Chon1Trong2(int& luaChon, string luaChon0, string luaChon1, int toaDoX, int toaDoY, int& keyHit)
{
	keyHit = -1;
	while (true) {
		if (keyHit == 224 || keyHit == 0) {
			keyHit = _getch();
			if (keyHit == KEY_DOWN || keyHit == KEY_UP || keyHit == F1 || keyHit == F2) { //ko phai nut qua trai, qua phai thi return
				return;
			}
			else if (keyHit == KEY_LEFT) {
				luaChon = 0;
			}
			else if (keyHit == KEY_RIGHT) {
				luaChon = 1;
			}
		}
		else if (keyHit == ENTER || keyHit == ESC) //ko phai nut qua trai, qua phai thi return
		{
			return;
		}

		//xuat ra string
		if (luaChon == 0) {
			gotoxy(toaDoX, toaDoY);
			SetColor(Red);
			cout << luaChon0 ;
			SetColor(Black);
			cout << " | ";
			cout << luaChon1;
		}
		else {
			gotoxy(toaDoX, toaDoY);
			cout << luaChon0;
			cout << " | ";
			SetColor(Red);
			cout << luaChon1;
			SetColor(Black);
		}

		keyHit = _getch();
	}
}

void ClearWorkFrame()
{
	string blankFill;
	blankFill.resize(MAX_X_OF_MAIN_FRAME - START_X_OF_MAIN_FRAME - 25, ' ');
	
	for (int i = 0; i < MAX_Y_OF_MAIN_FRAME - START_Y_OF_MAIN_FRAME; i++)
	{
		gotoxy(START_X_OF_MAIN_FRAME + 25 + 3, START_Y_OF_MAIN_FRAME + i + 1);
		cout << blankFill;
	}

	WriteSectionGuide(""); //chu huong dan ko chi nam trong work frame, nen khi xoa thi xoa ca cai nay cho sach
}

void WriteTitle(string title) {
	int toaDoX = START_X_OF_MAIN_FRAME + 25 + 64;
	int toaDoY = START_Y_OF_MAIN_FRAME + 8;
	int chieuNgang = 50;
	int chieuDoc = 2;

	DrawBorder(toaDoX, toaDoY, chieuNgang, chieuDoc); //border nho

	SetColor(Green);
	gotoxy(toaDoX + 1, toaDoY + 1);
	cout << CenterTextInSpace(title, 50);
	SetColor(Black);

	DrawBorder(toaDoX - 6, toaDoY - 1, chieuNgang + 12, chieuDoc + 2); //border to
}

void WriteSectionGuide(string sectionGuide)
{
	int toaDoX = START_X_OF_MAIN_FRAME + 1;
	int toaDoY = MAX_Y_OF_MAIN_FRAME - 1;
	
	int doDaiNgangCoTheViet = MAX_X_OF_MAIN_FRAME - START_X_OF_MAIN_FRAME;

	SetColor(Blue);
	gotoxy(toaDoX, toaDoY);
	cout << CenterTextInSpace(sectionGuide, doDaiNgangCoTheViet);
	SetColor(Black);
}

