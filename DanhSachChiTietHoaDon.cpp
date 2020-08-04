#include "DanhSachChiTietHoaDon.h"

int endIndex(DSChiTietHoaDon dsCTHD, int indexFirst)
{
	if (indexFirst + 9 > dsCTHD.soLuongVatTu - 1) {  //neu sau indexFirst ko du 9 phan tu thi tra ve index cuoi cung cua ds
		return dsCTHD.soLuongVatTu - 1;
	}
	else {//con neu co thi tra ve index vi tri phan tu thu 10
		return indexFirst + 9;
	}
}

void KhoiTaoChiTietHoaDon(ChiTietHoaDon& addCTHD)
{
	addCTHD.maVatTu[0] = '\0';
	addCTHD.soLuong = -1;
	addCTHD.donGia = -1;
	addCTHD.VAT = -1;
	addCTHD.trangThai = 1;
}

long long TriGiaChiTietHoaDon(ChiTietHoaDon cthd)
{
	long long triGia;
	triGia = cthd.soLuong * (float)cthd.donGia * (1 + cthd.VAT / 100.0);
	return triGia;
}

int KiemTraCTHDRong(ChiTietHoaDon addCTHD) //trang thai ko cho nhap nen ko can ktra
{
	if (string(addCTHD.maVatTu).length() == 0) {
		return 1;
	}
	else if (addCTHD.soLuong == -1) {
		return 2;
	}
	else if (addCTHD.donGia == -1) {
		return 3;
	}
	else if (addCTHD.VAT == -1) {
		return 4;
	}
	return 0;
}

bool KiemTraSoVATDung(ChiTietHoaDon addCTHD)
{
	if (addCTHD.VAT <= 100)
		return true;
	return false;
}

bool KiemTraDuSoLuongTon(ChiTietHoaDon addCTHD, char loaiHoaDon, PTRVatTu addVatTuCTHD) //neu no la hoa don xuat thi moi can ktra
{
	if (loaiHoaDon == 'X') {
		if (addCTHD.soLuong > addVatTuCTHD->infoVatTu.soLuongTon) {
			return false;
		}
	}
	return true;
}

bool KiemTraTrungMaVatTu(DSChiTietHoaDon dsCTHD, ChiTietHoaDon addCTHD)
{
	for (int i = 0; i < dsCTHD.soLuongVatTu; i++) {
		if (strcmp(addCTHD.maVatTu, dsCTHD.nodesCTHD[i].maVatTu) == 0) {
			return true;
		}
	}
	return false;
}

void INS_Keyhit_F1_ThemCTHD(int keyHit, ChiTietHoaDon addCTHD, char loaiHoaDon, PTRVatTu addVatTuCTHD, DSChiTietHoaDon& dsCTHD, bool& flagThemThanhCong, int toaDoX, int toaDoY, int& indexFirst, int& indexLast, int& indexCurrent)
{
	if (keyHit == F1) {
		int kiemTraRong = KiemTraCTHDRong(addCTHD);

		if (kiemTraRong == 0) { //ko rong
			int kiemTraVAT = KiemTraSoVATDung(addCTHD);
			if (kiemTraVAT == true) { //so VAT hop le
				int kiemTraDuHang = KiemTraDuSoLuongTon(addCTHD, loaiHoaDon, addVatTuCTHD);

				if (kiemTraDuHang == true) { //du so luong ton kho de them
					int kiemTraTrungMaVT = KiemTraTrungMaVatTu(dsCTHD, addCTHD);

					if (kiemTraTrungMaVT == false) { //khong trung vat tu voi cac chi tiet hoa don da co
						string thongBao[3] = { "Thong tin cua chi tiet hoa don hop le!", "Ban co chac chan muon them chi tiet hoa don?" };
						string options[3] = { "Dong y", "Huy" };
						ClearWorkFrame();

						int luaChon = XuatOThongBao(thongBao, options, 2);

						if (luaChon == 0) {//dong y viec them
							int viTriThem = InsertLast(dsCTHD, addCTHD);

							if (viTriThem != -1) {
								flagThemThanhCong = true;
								indexCurrent = viTriThem;
								indexFirst = (viTriThem / 10) * 10; // chia 10 sau do nhan 10 de lam mat so dang sau -> vd: (26 / 10) * 10 = 20
								indexLast = endIndex(dsCTHD, indexFirst);
							}
							else {
								string thongBao[3] = { "Danh sach chi tiet hoa don da day!", "Vui long xoa vat tu hoac lam them 1 hoa don khac de them!" };
								string options[3] = { "OK" };
								ClearWorkFrame();
								XuatOThongBao(thongBao, options, 1);

								keyHit = -1; //tru truong hop them thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
								ClearWorkFrame();
								WriteForm_INS(toaDoX, toaDoY, addCTHD, addVatTuCTHD);
							}
						}
						else { //huy viec them
							keyHit = -1; //tru truong hop them thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
							ClearWorkFrame();
							WriteForm_INS(toaDoX, toaDoY, addCTHD, addVatTuCTHD);
						}
					}
					else { //trung vat tu voi cac chi tiet hoa don da co
						string thongBao[3] = { "Vat tu chi tiet hoa don nay da co trong danh sach!", "Muon them so luong vui long xoa chi tiet hoa don cu va them moi!" };
						string options[3] = { "OK" };
						ClearWorkFrame();
						XuatOThongBao(thongBao, options, 1);

						keyHit = -1; //tru truong hop them thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
						ClearWorkFrame();
						WriteForm_INS(toaDoX, toaDoY, addCTHD, addVatTuCTHD);
					}
				}
				else { //loi ko du so luong ton kho de them
					string thongBao[3] = { "Chi tiet hoa don dang them khong hop le!", "So luong ton khong du de them!" };
					string options[3] = { "OK" };
					ClearWorkFrame();
					XuatOThongBao(thongBao, options, 1);

					keyHit = -1; //tru truong hop them thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
					ClearWorkFrame();
					WriteForm_INS(toaDoX, toaDoY, addCTHD, addVatTuCTHD);
				}
			}
			else {//so VAT khong hop le (> 100%)
				string thongBao[3] = { "Chi tiet hoa don dang them khong hop le!", "So VAT phai nho hon 100% !" };
				string options[3] = { "OK" };
				ClearWorkFrame();
				XuatOThongBao(thongBao, options, 1);

				keyHit = -1; //tru truong hop them thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
				ClearWorkFrame();
				WriteForm_INS(toaDoX, toaDoY, addCTHD, addVatTuCTHD);
			}
		}
		else { //loi bi rong cthd
			string thongBaoLoi;

			switch (kiemTraRong) //ko co case 5 vi ko dc nhap trang thai
			{
			case 1:
				thongBaoLoi = "Ban chua chon vat tu muon them!";
				break;
			case 2:
				thongBaoLoi = "So luong muon them rong!";
				break;
			case 3:
				thongBaoLoi = "Don gia rong!";
				break;
			case 5:
				thongBaoLoi = "VAT rong!";
				break;
			default:
				break;
			}

			string thongBao[3] = { "Chi tiet hoa don dang them khong hop le!", thongBaoLoi };
			string options[3] = { "OK" };
			ClearWorkFrame();
			XuatOThongBao(thongBao, options, 1);

			keyHit = -1; //tru truong hop them thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
			ClearWorkFrame();
			WriteForm_INS(toaDoX, toaDoY, addCTHD, addVatTuCTHD);
		}
	}
}

void INS_Keyhit_F2_TimVatTu(int keyHit, ChiTietHoaDon& addCTHD, int toaDoX, int toaDoY, PTRVatTu& addVatTuCTHD,ListVatTu& listVatTu, PTRVatTu& root)
{
	if (keyHit == F2) {
		string thongBao[3] = { "Ban co chac chan muon chuyen den danh sach vat tu", "va tim kiem vat tu?" };
		string options[3] = { "Dong y", "Huy" };
		ClearWorkFrame();

		int luaChon = XuatOThongBao(thongBao, options, 2);
		if (luaChon == 0) { //dong y vao kiem vat tu
			addVatTuCTHD = MainTimKiemVatTu(listVatTu, root); //tra ve node tree Vat Tu, tra ve NULL neu nhu thoat trong qua trinh tim kiem

			if (addVatTuCTHD != NULL) { //addVatTuCTHD co gia tri roi thi cai cthd.maVT cung se nhan gia tri
				strcpy(addCTHD.maVatTu, addVatTuCTHD->maVatTu);
			}

			//ve lai form INS
			keyHit = -1;
			ClearWorkFrame();
			WriteForm_INS(toaDoX, toaDoY, addCTHD, addVatTuCTHD);
		}
		else { //huy viec vao kiem vat tu
			keyHit = -1; 
			ClearWorkFrame();
			WriteForm_INS(toaDoX, toaDoY, addCTHD, addVatTuCTHD);
		}
	}
}

void INS_Keyhit_Move_And_Enter(int keyHit, OptionThemChiTietHoaDon& optionThemChiTietHoaDon)
{
	if (keyHit == KEY_UP) {
		switch (optionThemChiTietHoaDon)
		{
		case OptionThemChiTietHoaDon::ThemSoLuong:
			optionThemChiTietHoaDon = OptionThemChiTietHoaDon::ThemVat;
			break;
		case OptionThemChiTietHoaDon::ThemDonGia:
			optionThemChiTietHoaDon = OptionThemChiTietHoaDon::ThemSoLuong;
			break;
		case OptionThemChiTietHoaDon::ThemVat:
			optionThemChiTietHoaDon = OptionThemChiTietHoaDon::ThemDonGia;
			break;
		default:
			break;
		}
	}
	else if (keyHit == KEY_DOWN || keyHit == ENTER) {
		switch (optionThemChiTietHoaDon)
		{
		case OptionThemChiTietHoaDon::ThemSoLuong:
			optionThemChiTietHoaDon = OptionThemChiTietHoaDon::ThemDonGia;
			break;
		case OptionThemChiTietHoaDon::ThemDonGia:
			optionThemChiTietHoaDon = OptionThemChiTietHoaDon::ThemVat;
			break;
		case OptionThemChiTietHoaDon::ThemVat:
			optionThemChiTietHoaDon = OptionThemChiTietHoaDon::ThemSoLuong;
			break;
		default:
			break;
		}
	}
}

void INS_NhapThongTin(int& keyHit, OptionThemChiTietHoaDon optionThemChiTietHoaDon, ChiTietHoaDon& addCTHD, int toaDoX, int toaDoY)
{
	string temp;
	CheDoNhap cheDoNhap;

	int toaDoXNhapThongTin = toaDoX + 20;
	int xuongDong = 2;

	switch (optionThemChiTietHoaDon)
	{
	case OptionThemChiTietHoaDon::ThemSoLuong:
		temp = FloatToString(addCTHD.soLuong); //cho vao bien tam
		//so luong la so thuc

		if (addCTHD.soLuong == -1) {
			temp = "";
		}

		NhapSoThuc(temp, MAX_FLOAT, toaDoXNhapThongTin, toaDoY + xuongDong * 4, keyHit);

		if (temp.length() == 0) {
			addCTHD.soLuong = -1;
		}
		else {
			addCTHD.soLuong = stof(temp); //doi thanh float va gan lai

			//truong hop dac biet: rieng so nguyen va so thuc thi phai loai truong hop viet so 0 o dau
			gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 4);
			cout << CenterTextInSpace(" ", MAX_FLOAT + 2); //vi cai ham nay de viet trong border, nen +2 cho 2 gach 2 ben thi moi dung la khoang MAX_FLOAT phan tu
			gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 4);
			cout << FloatToString(addCTHD.soLuong);
		}
		break;
	case OptionThemChiTietHoaDon::ThemDonGia:
		temp = to_string(addCTHD.donGia);

		//don gia la int, chi co so
		cheDoNhap.coGhiSo = true;

		if (addCTHD.donGia == -1) {
			temp = "";
		}

		NhapThongTin(temp, 9, toaDoXNhapThongTin, toaDoY + xuongDong * 5, keyHit, cheDoNhap); //max int la 2 ty (10 so), nen chi cho toi da nhap 9 so thoi

		if (temp.length() == 0) {
			addCTHD.donGia = -1;
		}
		else {
			addCTHD.donGia = stoi(temp); //doi thanh int va gan lai

			//truong hop dac biet: rieng so nguyen va so thuc thi phai loai truong hop viet so 0 o dau
			gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 5);
			cout << CenterTextInSpace(" ", 9 + 2); //vi cai ham nay de viet trong border, nen +2 cho 2 gach 2 ben thi moi dung la khoang 9 phan tu
			gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 5);
			cout << to_string(addCTHD.donGia);
		}
		break;
	case OptionThemChiTietHoaDon::ThemVat:
		temp = FloatToString(addCTHD.VAT); //cho vao bien tam
		//so luong la so thuc

		if (addCTHD.VAT == -1) {
			temp = "";
		}

		NhapSoThuc(temp, MAX_FLOAT, toaDoXNhapThongTin, toaDoY + xuongDong * 6, keyHit);

		if (temp.length() == 0) {
			addCTHD.VAT = -1;
		}
		else {
			addCTHD.VAT = stof(temp); //doi thanh float va gan lai

			//truong hop dac biet: rieng so nguyen va so thuc thi phai loai truong hop viet so 0 o dau
			gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 6);
			cout << CenterTextInSpace(" ", MAX_FLOAT + 2); //vi cai ham nay de viet trong border, nen +2 cho 2 gach 2 ben thi moi dung la khoang MAX_FLOAT phan tu
			gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 6);
			cout << FloatToString(addCTHD.VAT);
		}
		break;
	default:
		break;
	}
}

void WriteForm_INS(int toaDoX, int toaDoY, ChiTietHoaDon addCTHD, PTRVatTu addVatTuCTHD)
{
	int xuongDong = 2;
	int toaDoXNhapThongTin = toaDoX + 20;

	gotoxy(toaDoX, toaDoY + xuongDong * 0);
	cout << "Ma vat tu: ";
	gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 0);
	cout << string(addCTHD.maVatTu);

	gotoxy(toaDoX, toaDoY + xuongDong * 1);
	cout << "Ten vat tu: ";
	gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 1);
	if (addVatTuCTHD == NULL) {
		cout << "";
	}
	else {
		cout << string(addVatTuCTHD->infoVatTu.tenVatTu);
	}

	gotoxy(toaDoX, toaDoY + xuongDong * 2);
	cout << "Don vi tinh: ";
	gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 2);
	if (addVatTuCTHD == NULL) {
		cout << "";
	}
	else {
		cout << string(addVatTuCTHD->infoVatTu.donViTinh);
	}

	gotoxy(toaDoX, toaDoY + xuongDong * 3);
	cout << "So luong ton: ";
	gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 3);
	if (addVatTuCTHD == NULL) {
		cout << "";
	}
	else {
		cout << FloatToString(addVatTuCTHD->infoVatTu.soLuongTon);
	}

	gotoxy(toaDoX, toaDoY + xuongDong * 4);
	cout << "So luong: ";
	gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 4);
	if (addCTHD.soLuong == -1) {
		cout << "";
	}
	else {
		cout << FloatToString(addCTHD.soLuong);
	}

	gotoxy(toaDoX, toaDoY + xuongDong * 5);
	cout << "Don gia: ";
	gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 5);
	if (addCTHD.donGia == -1) {
		cout << "";
	}
	else {
		cout << to_string(addCTHD.donGia);
	}

	gotoxy(toaDoX, toaDoY + xuongDong * 6);
	cout << "Vat: ";
	gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 6);
	if (addCTHD.VAT == -1) {
		cout << "";
	}
	else {
		cout << FloatToString(addCTHD.VAT);
	}

	WriteTitle("THEM CHI TIET HOA DON");
}

void Keyhit_Move(int keyHit, int& indexFirst, int& indexLast, int& indexCurrent, DSChiTietHoaDon dsCTHD)
{
	if (dsCTHD.soLuongVatTu == 0)
		return;
	if (keyHit == KEY_UP) {
		if (indexCurrent == indexFirst) {//neu la first thi cho la last
			indexCurrent = indexLast;
		}
		else { //truong hop con lai
			indexCurrent--;
		}
	}
	else if (keyHit == KEY_DOWN) {
		if (indexCurrent == indexLast) {//neu la last thi cho la first
			indexCurrent = indexFirst;
		}
		else { //truong hop con lai
			indexCurrent++;
		}
	}
	else if (keyHit == KEY_LEFT) {
		if (indexFirst != 0) { //neu ko phai trang dau tien
			indexFirst -= 10;
			indexLast = endIndex(dsCTHD, indexFirst);
			indexCurrent = indexFirst;
		}
	}
	else if (keyHit == KEY_RIGHT) {
		if (indexLast != dsCTHD.soLuongVatTu - 1) { //neu ko phai trang cuoi cung
			indexFirst += 10;
			indexLast = endIndex(dsCTHD, indexFirst);
			indexCurrent = indexFirst;
		}
	}
}

void Keyhit_INS(int keyHit, int toaDoXFormDSCTHD, int toaDoYFormDSCTHD, DSChiTietHoaDon& dsCTHD, char loaiHoaDon, int& indexFirst, int& indexLast, int& indexCurrent, ListVatTu& listVatTu, PTRVatTu& root)
{
	if (keyHit == INS) {
		ChiTietHoaDon addCTHD;
		KhoiTaoChiTietHoaDon(addCTHD);
		PTRVatTu addVatTuCTHD = NULL; //bien de luu giu vat tu hien tai muon them vao cthd

		OptionThemChiTietHoaDon optionThemChiTietHoaDon;
		optionThemChiTietHoaDon = OptionThemChiTietHoaDon::ThemSoLuong;

		bool flagThemThanhCong = false;

		ClearWorkFrame();

		int toaDoX = START_X_OF_MAIN_FRAME + 25 + 70; //toa do diem bat dau dong dau tien (Ma vat tu: )
		int toaDoY = START_Y_OF_MAIN_FRAME + 20;
		WriteForm_INS(toaDoX, toaDoY, addCTHD, addVatTuCTHD);

		keyHit = -1;
		while (true)
		{
			INS_Keyhit_Move_And_Enter(keyHit, optionThemChiTietHoaDon);
			INS_Keyhit_F1_ThemCTHD(keyHit, addCTHD, loaiHoaDon, addVatTuCTHD, dsCTHD, flagThemThanhCong, toaDoX, toaDoY, indexFirst, indexLast, indexCurrent);
			INS_Keyhit_F2_TimVatTu(keyHit, addCTHD,toaDoX, toaDoY,addVatTuCTHD,listVatTu, root);

			//them thanh cong
			if (flagThemThanhCong) {
				ClearWorkFrame();
				DrawFormDSChiTietHoaDon(toaDoXFormDSCTHD, toaDoYFormDSCTHD);
				return;
			}
			//nut ESCape
			if (keyHit == ESC) {

				string thongBao[3] = { "Ban co muon huy viec them chi tiet hoa don?", "xxxxxxxxxxxxxxxx" };
				string options[3] = { "Co", "Khong" };
				ClearWorkFrame();
				int luaChon = XuatOThongBao(thongBao, options, 2);
				if (luaChon == 0) {
					ClearWorkFrame();
					DrawFormDSChiTietHoaDon(toaDoXFormDSCTHD, toaDoYFormDSCTHD);
					return;
				}
				else {
					keyHit = -1;
					ClearWorkFrame();
					WriteForm_INS(toaDoX, toaDoY, addCTHD, addVatTuCTHD);
				}
			}

			WriteSectionGuide("F1: xac nhan them chi tiet hoa don - F2: tim kiem vat tu - KEY_UP_DOWN: di chuyen len, xuong - ENTER: di chuyen xuong - ESC: thoat");

			INS_NhapThongTin(keyHit, optionThemChiTietHoaDon, addCTHD, toaDoX, toaDoY); //ham nay se thay doi gia tri keyHit va xuat ra thong tin moi bang ham NhapThongTin()
		}
	}
}

void Keyhit_Delete(int keyHit, int toaDoXFormDSCTHD, int toaDoYFormDSCTHD, DSChiTietHoaDon& dsCTHD, int& indexFirst, int& indexLast, int& indexCurrent)
{
	if (dsCTHD.soLuongVatTu == 0) {
		return;
	}
	if (keyHit == DEL) {

		string thongBao[3] = { "Ban co chac chan muon xoa chi tiet hoa don nay?", "xxxxxxxxxxxxxxxxxx" };
		string options[3] = { "Dong y", "Huy" };
		ClearWorkFrame();
		int luaChon = XuatOThongBao(thongBao, options, 2);

		if (luaChon == 0) { //dong y xoa

			XoaCTHDTheoViTri(dsCTHD, indexCurrent);

			if (indexCurrent != 0) { //xet truong hop cur ko la 0 //neu la 0 thi cu de no la 0, truong hop ko con ptu nao thi indexCur, first, last deu = 0
				if (indexCurrent == dsCTHD.soLuongVatTu) { //neu la xoa cuoi thi indexCurrent se nam ngoai index cua ds, nen gan cho no gia tri cuoi ds
					indexCurrent = dsCTHD.soLuongVatTu - 1;
				}
			}

			indexFirst = (indexCurrent / 10) * 10; // chia 10 sau do nhan 10 de lam mat so dang sau -> vd: (26 / 10) * 10 = 20
			indexLast = endIndex(dsCTHD, indexFirst);

			//ve lai ds vat tu
			keyHit = -1;
			ClearWorkFrame();
			DrawFormDSChiTietHoaDon(toaDoXFormDSCTHD, toaDoYFormDSCTHD);
		}
		else { //ko dong y xoa
			//ve lai ds nhan vien
			keyHit = -1;
			ClearWorkFrame();
			DrawFormDSChiTietHoaDon(toaDoXFormDSCTHD, toaDoYFormDSCTHD);
		}
	}
}

void Output10Nodes(DSChiTietHoaDon dsCTHD, int indexFirst, int indexLast, int indexCurrent, int toaDoX, int toaDoY)
{
	if (dsCTHD.soLuongVatTu == 0)
		return;
	int doDaiNgang1Cot = (32 * 5) / 6 + 1; //form bth co 5 cot, lay 1 cot * 5 roi chia 6 de ra so do dai 1 cot moi, cong 1 de lam tron len

	int dem = 0;
	for (int i = indexFirst; i <= indexLast; i++) {
		dem++;

		if (i == indexCurrent) {
			SetColor(Red);
		}

		gotoxy(toaDoX + 1 + doDaiNgang1Cot * 0, toaDoY + 1 + 2 * dem);
		cout << CenterTextInSpace(string(dsCTHD.nodesCTHD[i].maVatTu), doDaiNgang1Cot);

		gotoxy(toaDoX + 1 + doDaiNgang1Cot * 1, toaDoY + 1 + 2 * dem);
		cout << CenterTextInSpace(FloatToString(dsCTHD.nodesCTHD[i].soLuong), doDaiNgang1Cot);

		gotoxy(toaDoX + 1 + doDaiNgang1Cot * 2, toaDoY + 1 + 2 * dem);
		cout << CenterTextInSpace(to_string(dsCTHD.nodesCTHD[i].donGia), doDaiNgang1Cot);

		gotoxy(toaDoX + 1 + doDaiNgang1Cot * 3, toaDoY + 1 + 2 * dem);
		cout << CenterTextInSpace(FloatToString(dsCTHD.nodesCTHD[i].VAT), doDaiNgang1Cot);

		gotoxy(toaDoX + 1 + doDaiNgang1Cot * 4, toaDoY + 1 + 2 * dem);
		cout << CenterTextInSpace(to_string(TriGiaChiTietHoaDon(dsCTHD.nodesCTHD[i])), doDaiNgang1Cot);

		gotoxy(toaDoX + 1 + doDaiNgang1Cot * 5, toaDoY + 1 + 2 * dem);
		if (dsCTHD.nodesCTHD[i].trangThai == 1) {
			cout << CenterTextInSpace("Mua", doDaiNgang1Cot);
		}
		else
		{
			cout << CenterTextInSpace("Da Tra Hang", doDaiNgang1Cot);
		}

		SetColor(Black);
	}

	//neu ko du 10 node thi xoa trang nhung o con lai
	if (dem < 10) {
		dem++;
		for (; dem <= 10; dem++) {
			gotoxy(toaDoX + 1, toaDoY + 1 + 2 * dem);
			cout << CenterTextInSpace(" ", doDaiNgang1Cot);

			gotoxy(toaDoX + 1 + doDaiNgang1Cot * 1, toaDoY + 1 + 2 * dem);
			cout << CenterTextInSpace(" ", doDaiNgang1Cot);

			gotoxy(toaDoX + 1 + doDaiNgang1Cot * 2, toaDoY + 1 + 2 * dem);
			cout << CenterTextInSpace(" ", doDaiNgang1Cot);

			gotoxy(toaDoX + 1 + doDaiNgang1Cot * 3, toaDoY + 1 + 2 * dem);
			cout << CenterTextInSpace(" ", doDaiNgang1Cot);

			gotoxy(toaDoX + 1 + doDaiNgang1Cot * 4, toaDoY + 1 + 2 * dem);
			cout << CenterTextInSpace(" ", doDaiNgang1Cot);

			gotoxy(toaDoX + 1 + doDaiNgang1Cot * 5, toaDoY + 1 + 2 * dem);
			cout << CenterTextInSpace(" ", doDaiNgang1Cot);
		}
	}

	gotoxy(toaDoX + 1 + 32 * 0, toaDoY + 1 + 2 * 11); //*11 vi dong dau tien la tieu de border
	cout << "Trang " << indexFirst / 10 + 1; //vd: 16 / 10 + 1 = 2 -> trang 2 
}

void DrawFormDSChiTietHoaDon(int toaDoX, int toaDoY)
{
	int soDong = 11;
	int soCot = 6;
	int doDaiNgang1Cot = (32 * 5) / 6 + 1; //form bth co 5 cot, lay 1 cot * 5 roi chia 6 de ra so do dai 1 cot moi, cong 1 de lam tron len
	int doDaiDoc1Hang = 1;

	DrawBorderList(toaDoX, toaDoY, soDong, soCot, doDaiNgang1Cot, doDaiDoc1Hang);
	WriteTitle("DANH SACH CHI TIET HOA DON");

	SetColor(Green);

	gotoxy(toaDoX + 1, toaDoY + 1);
	cout << CenterTextInSpace("MA VAT TU", doDaiNgang1Cot);

	gotoxy(toaDoX + 1 + doDaiNgang1Cot * 1, toaDoY + 1);
	cout << CenterTextInSpace("SO LUONG", doDaiNgang1Cot);

	gotoxy(toaDoX + 1 + doDaiNgang1Cot * 2, toaDoY + 1);
	cout << CenterTextInSpace("DON GIA", doDaiNgang1Cot);

	gotoxy(toaDoX + 1 + doDaiNgang1Cot * 3, toaDoY + 1);
	cout << CenterTextInSpace("VAT(%)", doDaiNgang1Cot);

	gotoxy(toaDoX + 1 + doDaiNgang1Cot * 4, toaDoY + 1);
	cout << CenterTextInSpace("TRI GIA", doDaiNgang1Cot);

	gotoxy(toaDoX + 1 + doDaiNgang1Cot * 5, toaDoY + 1);
	cout << CenterTextInSpace("TRANG THAI", doDaiNgang1Cot);

	SetColor(Black);
}

void MainDanhSachChiTietHoaDon(DSChiTietHoaDon& dsCTHD, char loaiHoaDon, ListVatTu& listVatTu, PTRVatTu& root)
{
	int indexFirst = 0, indexCurrent = 0;
	int indexLast = endIndex(dsCTHD, indexFirst);

	int keyHit = -1;

	//toa do diem bat dau ve khung
	int toaDoX = START_X_OF_MAIN_FRAME + 25 + 8;
	int toaDoY = START_Y_OF_MAIN_FRAME + 18;
	ClearWorkFrame();
	DrawFormDSChiTietHoaDon(toaDoX, toaDoY);

	while (true) {
		if (keyHit == 224)
			keyHit = _getch();
		if (keyHit == 0)
			keyHit = _getch();

		//cac nut 
		Keyhit_Move(keyHit, indexFirst, indexLast, indexCurrent, dsCTHD);
		Keyhit_INS(keyHit, toaDoX, toaDoY, dsCTHD, loaiHoaDon, indexFirst, indexLast, indexCurrent, listVatTu, root);
		Keyhit_Delete(keyHit, toaDoX, toaDoY, dsCTHD, indexFirst, indexLast, indexCurrent);
		if (keyHit == ESC) {
			return;
		}
		//

		Output10Nodes(dsCTHD, indexFirst, indexLast, indexCurrent, toaDoX, toaDoY);
		WriteSectionGuide("INSERT: them chi tiet hoa don - DELETE: xoa chi tiet hoa don - KEY_UP_DOWN: di chuyen len, xuong - KEY_LEFT_RIGHT: lui trang, sang trang - ESC: thoat");

		keyHit = _getch();
	}
}

void DrawFormXemDSChiTietHoaDon(int toaDoX, int toaDoY, HoaDon infoHoaDon)
{
	int soDong = 11;
	int soCot = 6;
	int doDaiNgang1Cot = (32 * 5) / 6 + 1; //form bth co 5 cot, lay 1 cot * 5 roi chia 6 de ra so do dai 1 cot moi, cong 1 de lam tron len
	int doDaiDoc1Hang = 1;

	DrawBorderList(toaDoX, toaDoY, soDong, soCot, doDaiNgang1Cot, doDaiDoc1Hang);

	SetColor(Green);

	gotoxy(toaDoX + 1, toaDoY + 1);
	cout << CenterTextInSpace("MA VAT TU", doDaiNgang1Cot);

	gotoxy(toaDoX + 1 + doDaiNgang1Cot * 1, toaDoY + 1);
	cout << CenterTextInSpace("SO LUONG", doDaiNgang1Cot);

	gotoxy(toaDoX + 1 + doDaiNgang1Cot * 2, toaDoY + 1);
	cout << CenterTextInSpace("DON GIA", doDaiNgang1Cot);

	gotoxy(toaDoX + 1 + doDaiNgang1Cot * 3, toaDoY + 1);
	cout << CenterTextInSpace("VAT(%)", doDaiNgang1Cot);

	gotoxy(toaDoX + 1 + doDaiNgang1Cot * 4, toaDoY + 1);
	cout << CenterTextInSpace("TRI GIA", doDaiNgang1Cot);

	gotoxy(toaDoX + 1 + doDaiNgang1Cot * 5, toaDoY + 1);
	cout << CenterTextInSpace("TRANG THAI", doDaiNgang1Cot);

	SetColor(Black);

	//viet thong tin hoa don, lay toa do viet chu "don gia" (cot giua) lam chuan 
	int toaDoXBatDau = toaDoX + 1 + doDaiNgang1Cot * 2;
	int toaDoYBatDau = START_Y_OF_MAIN_FRAME + 5;

	int toaDoXVietThongTin = toaDoXBatDau + 20;

	gotoxy(toaDoXBatDau, toaDoYBatDau);
	cout << "So hoa don: ";
	gotoxy(toaDoXVietThongTin, toaDoYBatDau);
	cout << string(infoHoaDon.soHoaDon);

	gotoxy(toaDoXBatDau, toaDoYBatDau + 1);
	cout << "Ngay lap: ";
	gotoxy(toaDoXVietThongTin, toaDoYBatDau + 1);
	cout << OutputDate(infoHoaDon.ngayLap);

	gotoxy(toaDoXBatDau, toaDoYBatDau + 2);
	cout << "Loai: ";
	gotoxy(toaDoXVietThongTin, toaDoYBatDau + 2);
	if (infoHoaDon.loai == 'N') {
		cout << "nhap";
	}
	else {
		cout << "xuat";
	}

	gotoxy(toaDoXBatDau, toaDoYBatDau + 3);
	cout << "Tri gia: ";
	gotoxy(toaDoXVietThongTin, toaDoYBatDau + 3);
	cout << TriGiaHoaDon(infoHoaDon.dsCTHD);
}

void MainXemCTHD(HoaDon xemHoaDon)
{
	int indexFirst = 0, indexCurrent = 0;
	int indexLast = endIndex(xemHoaDon.dsCTHD, indexFirst);

	int keyHit = -1;

	//toa do diem bat dau ve khung
	int toaDoX = START_X_OF_MAIN_FRAME + 25 + 8;
	int toaDoY = START_Y_OF_MAIN_FRAME + 18;
	ClearWorkFrame();
	DrawFormXemDSChiTietHoaDon(toaDoX, toaDoY, xemHoaDon);

	while (true) {
		if (keyHit == 224)
			keyHit = _getch();
		if (keyHit == 0)
			keyHit = _getch();

		//cac nut 
		Keyhit_Move(keyHit, indexFirst, indexLast, indexCurrent, xemHoaDon.dsCTHD);
		if (keyHit == ESC) {
			return;
		}
		//

		Output10Nodes(xemHoaDon.dsCTHD, indexFirst, indexLast, indexCurrent, toaDoX, toaDoY);
		WriteSectionGuide("KEY_UP_DOWN: di chuyen len, xuong - KEY_LEFT_RIGHT: lui trang, sang trang - ESC: thoat");

		keyHit = _getch();
	}
}

bool DateDuocPhepTraHang(Date kiemTraDate)
{
	//kiemTraDate chac chan se nho hon hoac bang ngay hien tai
	if (SoNgayDaDatHang(kiemTraDate) <= 2) {//max la 3 ngay, nhung tinh ca ngay lap ngay hom do. vd: ngay 1 lap, thi ngay 1, 2, 3 dc tra hang, ngay 4 ko dc tra hang, 4 - 1 = 3, vay <= 2 la hop le
		return true;
	}
	return false;
}

void Keyhit_F1_TraHang(int keyHit, ListHoaDon& listHoaDon, HoaDon& xuLyHoaDon, bool& flagXoaHoaDon , int indexCurrent, int toaDoX, int toaDoY)
{
	if (xuLyHoaDon.dsCTHD.soLuongVatTu == 0) {
		return;
	}
	if (keyHit == F1) {
		if (xuLyHoaDon.dsCTHD.nodesCTHD[indexCurrent].trangThai == 0) { //0 la trang thai da tra hang, ko cho tra hang nua

			string thongBao[3] = { "Chi tiet hoa don nay da tra hang!", "xxxxxxxxxxxxx!" };
			string options[3] = { "OK" };
			ClearWorkFrame();
			XuatOThongBao(thongBao, options, 1);

			//ve lai ds
			ClearWorkFrame();
			DrawFormXemDSChiTietHoaDon(toaDoX, toaDoY, xuLyHoaDon); //xai lai ham xem ds cthd
		}
		else { //duoc phep tra hang
			if (DateDuocPhepTraHang(xuLyHoaDon.ngayLap) == true) { //date hop le de tra hang
				string thongBao[3] = { "Ban co thuc su muon tra hang chi tiet hoa don nay?", "xxxxxxxxxxxxxxxxx" };
				string options[3] = { "Dong y", "Huy" };
				ClearWorkFrame();
				int luaChon = XuatOThongBao(thongBao, options, 2);

				if (luaChon == 0) { //dong y tra hang

					int soLuongVatTuChuaTraHang = 0;
					for (int i = 0; i < xuLyHoaDon.dsCTHD.soLuongVatTu; i++) {
						if (xuLyHoaDon.dsCTHD.nodesCTHD[i].trangThai == 1) {
							soLuongVatTuChuaTraHang++;
						}
					}

					if (soLuongVatTuChuaTraHang == 1) { //neu nhu chi con 1 chi tiet trong hoa don nay, thi xoa se xoa luon hoa don nay, vi hoa don ko con tac dung
						string thongBao[3] = { "Day la chi tiet cuoi cung cua hoa don nay!", "Neu nhu ban tra hang thi hoa don se bi xoa, ban co dong y tra hang?" };
						string options[3] = { "Dong y", "Huy" };

						ClearWorkFrame();
						int luaChon = XuatOThongBao(thongBao, options, 2);

						if (luaChon == 0) { //dong y tra hang thi xoa hoa don
							DeleteInfo(listHoaDon, xuLyHoaDon.soHoaDon);
							flagXoaHoaDon = true;
							return;
						}
						//tu choi tra hang thi ko sua gi het
					}
					else { //con nhieu chi tiet khac chua tra hang thi cu tra hang, ko can phai hoi y kien
						xuLyHoaDon.dsCTHD.nodesCTHD[indexCurrent].trangThai = 0;
					}
				}
				//tu choi tra hang thi ko sua gi het

				//ve lai ds
				ClearWorkFrame();
				DrawFormXemDSChiTietHoaDon(toaDoX, toaDoY, xuLyHoaDon); //xai lai ham xem ds cthd
			}
			else {//date ko hop le de tra hang
				string thongBao[3] = { "Hoa don da lap duoc tu 3 ngay tro len!", "Ban khong the tra hang duoc nua!" };
				string options[3] = { "OK" };
				ClearWorkFrame();
				XuatOThongBao(thongBao, options, 1);

				//ve lai ds
				ClearWorkFrame();
				DrawFormXemDSChiTietHoaDon(toaDoX, toaDoY, xuLyHoaDon); //xai lai ham xem ds cthd
			}
		}
	}
}

void MainTraHangCTHD(ListHoaDon& listHoaDon, HoaDon& xuLyHoaDon)
{
	int indexFirst = 0, indexCurrent = 0;
	int indexLast = endIndex(xuLyHoaDon.dsCTHD, indexFirst);

	bool flagXoaHoaDon = false; //neu nhu tra hang het thi se xoa hoa don, xoa xong se ko con ds de in ra nen thoat ra ngoai luon

	//toa do diem bat dau ve khung
	int toaDoX = START_X_OF_MAIN_FRAME + 25 + 8;
	int toaDoY = START_Y_OF_MAIN_FRAME + 18;
	ClearWorkFrame();
	DrawFormXemDSChiTietHoaDon(toaDoX, toaDoY, xuLyHoaDon); //xai lai ham xem ds cthd

	int keyHit = -1;
	while (true) {
		if (keyHit == 224)
			keyHit = _getch();
		if (keyHit == 0)
			keyHit = _getch();

		//cac nut 
		Keyhit_Move(keyHit, indexFirst, indexLast, indexCurrent, xuLyHoaDon.dsCTHD);
		Keyhit_F1_TraHang(keyHit, listHoaDon, xuLyHoaDon, flagXoaHoaDon, indexCurrent, toaDoX, toaDoY);

		if (flagXoaHoaDon == true) {
			return;
		}
		if (keyHit == ESC) {
			return;
		}
		//

		Output10Nodes(xuLyHoaDon.dsCTHD, indexFirst, indexLast, indexCurrent, toaDoX, toaDoY);
		WriteSectionGuide("F1: tra hang - KEY_UP_DOWN: di chuyen len, xuong - KEY_LEFT_RIGHT: lui trang, sang trang - ESC: thoat");

		keyHit = _getch();
	}
}
