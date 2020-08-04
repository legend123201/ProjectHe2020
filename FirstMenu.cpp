#include "FirstMenu.h"
// - 1 de no nam trong o main frame 

void Keyhit_Enter(int keyHit, OptionFirstMenu optionFirstMenu, DSNhanVien& dsNhanVien, ListVatTu& listVatTu, PTRVatTu& root)
{
	if (keyHit == ENTER) {
		switch (optionFirstMenu)
		{
		case OptionFirstMenu::VatTu:
			MainDanhSachVatTu(listVatTu, root, dsNhanVien);
			break;
		case OptionFirstMenu::NhanVien:
			MainDanhSachNhanVien(dsNhanVien, listVatTu, root);
			break;
		case OptionFirstMenu::InHoaDon:
			MainXemHoaDon(dsNhanVien);
			break;
		case OptionFirstMenu::TraHang:
			MainTraHangHoaDon(dsNhanVien);
			break;
		case OptionFirstMenu::ThongKe:
			MainThongKe(dsNhanVien);
			break;
		default:
			break;
		}

		ClearWorkFrame();
	}
}

void Keyhit_Move(int keyHit, OptionFirstMenu& optionFirstMenu)
{
	if (keyHit == KEY_UP) {
		switch (optionFirstMenu)
		{
		case OptionFirstMenu::VatTu:
			optionFirstMenu = OptionFirstMenu::ThongKe;
			break;
		case OptionFirstMenu::NhanVien:
			optionFirstMenu = OptionFirstMenu::VatTu;
			break;
		case OptionFirstMenu::InHoaDon:
			optionFirstMenu = OptionFirstMenu::NhanVien;
			break;
		case OptionFirstMenu::TraHang:
			optionFirstMenu = OptionFirstMenu::InHoaDon;
			break;
		case OptionFirstMenu::ThongKe:
			optionFirstMenu = OptionFirstMenu::TraHang;
			break;
		default:
			break;
		}
	}
	else if (keyHit == KEY_DOWN) {
		switch (optionFirstMenu)
		{
		case OptionFirstMenu::VatTu:
			optionFirstMenu = OptionFirstMenu::NhanVien;
			break;
		case OptionFirstMenu::NhanVien:
			optionFirstMenu = OptionFirstMenu::InHoaDon;
			break;
		case OptionFirstMenu::InHoaDon:
			optionFirstMenu = OptionFirstMenu::TraHang;
			break;
		case OptionFirstMenu::TraHang:
			optionFirstMenu = OptionFirstMenu::ThongKe;
			break;
		case OptionFirstMenu::ThongKe:
			optionFirstMenu = OptionFirstMenu::VatTu;
			break;
		default:
			break;
		}
	}
}

void WriteOptionString(string optionString[], OptionFirstMenu optionFirstMenu, int soOption, int doDaiNgang1Cot, int doDaiDoc1Hang)
{
	int x = START_X_OF_MAIN_FRAME + 2; //x bat dau dong dau tien
	int y = doDaiDoc1Hang / 2 + START_Y_OF_MAIN_FRAME + 1; //y bat dau dong dau tien //cong 1 de lam tron len, can giua dep hon
	int i = 0;

	//in ra option
	gotoxy(x, y);
	cout << CenterTextInSpace(optionString[i], doDaiNgang1Cot);
	
	gotoxy(x, y + (doDaiDoc1Hang + 1) * 1);
	cout << CenterTextInSpace(optionString[i + 1], doDaiNgang1Cot);

	gotoxy(x, y + (doDaiDoc1Hang + 1) * 2);
	cout << CenterTextInSpace(optionString[i + 2], doDaiNgang1Cot);

	gotoxy(x, y + (doDaiDoc1Hang + 1) * 3);
	cout << CenterTextInSpace(optionString[i + 3], doDaiNgang1Cot);

	gotoxy(x, y + (doDaiDoc1Hang + 1) * 4);
	cout << CenterTextInSpace(optionString[i + 4], doDaiNgang1Cot);
	
	//to mau option dang chon
	SetColor(Red);
	switch (optionFirstMenu)
	{
	case OptionFirstMenu::VatTu:
		gotoxy(x, y);
		cout << CenterTextInSpace(optionString[i], doDaiNgang1Cot);
		break;
	case OptionFirstMenu::NhanVien:
		gotoxy(x, y + (doDaiDoc1Hang + 1) * 1);
		cout << CenterTextInSpace(optionString[i + 1], doDaiNgang1Cot);
		break;
	case OptionFirstMenu::InHoaDon:
		gotoxy(x, y + (doDaiDoc1Hang + 1) * 2);
		cout << CenterTextInSpace(optionString[i + 2], doDaiNgang1Cot);
		break;
	case OptionFirstMenu::TraHang:
		gotoxy(x, y + (doDaiDoc1Hang + 1) * 3);
		cout << CenterTextInSpace(optionString[i + 3], doDaiNgang1Cot);
		break;
	case OptionFirstMenu::ThongKe:
		gotoxy(x, y + (doDaiDoc1Hang + 1) * 4);
		cout << CenterTextInSpace(optionString[i + 4], doDaiNgang1Cot);
		break;
	default:
		break;
	}
	SetColor(Black);
}

void DrawMainFrame(int soOption, int doDaiNgang1Cot, int doDaiDoc1Hang) {
	fullScreen(); //cua so console toan man hinh
	RemoveScroll(); //bo thanh keo tren console
	system("color f0"); // dat nen man hinh mau trang

	//ve duong vien
	DrawBorder(START_X_OF_MAIN_FRAME, START_Y_OF_MAIN_FRAME, MAX_X_OF_MAIN_FRAME, MAX_Y_OF_MAIN_FRAME);

	//ve cac o Option
	DrawBorderList(START_X_OF_MAIN_FRAME + 1, START_Y_OF_MAIN_FRAME + 1, soOption, 1, doDaiNgang1Cot, doDaiDoc1Hang);
}

void MainFirstMenu(DSNhanVien& dsNhanVien, ListVatTu& listVatTu, PTRVatTu& root) {
	OptionFirstMenu optionFirstMenu = OptionFirstMenu::VatTu;
	int soOption = 5;
	string optionString[10] = { "Vat Tu", "Nhan Vien" , "In Hoa Don", "Tra Hang", "Thong Ke" };

	int doDaiNgang1Cot = 25;
	int doDaiDoc1Hang = (MAX_Y_OF_MAIN_FRAME - START_Y_OF_MAIN_FRAME) / soOption - 1; // - 1 de no nam trong o main frame 

	DrawMainFrame(soOption, doDaiNgang1Cot, doDaiDoc1Hang);
	int keyHit = -1;
	while (true) {	
		if (keyHit == 224)
			keyHit = _getch();
		if (keyHit == 0)
			keyHit = _getch();

		Keyhit_Enter(keyHit, optionFirstMenu, dsNhanVien, listVatTu, root);
		Keyhit_Move(keyHit, optionFirstMenu);

		if (keyHit == ESC) {
			string thongBao[3] = { "Ban muon thoat chuong trinh?", "xxxxxxxxxxxxxxxx" };
			string options[3] = { "Dong y", "Huy" };
			int luaChon = XuatOThongBao(thongBao, options, 2);
			if (luaChon == 0) {
				return;
			}
			else {
				ClearWorkFrame();
			}
		}

		WriteOptionString(optionString, optionFirstMenu, soOption, doDaiNgang1Cot, doDaiDoc1Hang);
		WriteSectionGuide("ENTER: chon chuc nang - KEY_UP/KEY_DOWN: len, xuong - ESC: thoat chuong trinh");

		keyHit = _getch();
	}
}
