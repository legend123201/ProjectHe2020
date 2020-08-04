#include "DanhSachNhanVien.h"

int endIndex(DSNhanVien dsNhanVien, int indexFirst)
{
	if (indexFirst + 9 > dsNhanVien.soLuongNhanVien - 1) { //neu sau indexFirst ko du 9 phan tu thi tra ve index cuoi cung cua ds
		return dsNhanVien.soLuongNhanVien - 1;
	}
	else { //con neu co thi tra ve index vi tri phan tu thu 10
		return indexFirst + 9;
	}
}

void KhoiTaoNhanVien(NhanVien& addNhanVien)
{
	addNhanVien.maNhanVien = -1;
	addNhanVien.name.ho[0] = '\0';
	addNhanVien.name.ten[0] = '\0';
	addNhanVien.phai = 0;
	addNhanVien.soCMND[0] = '\0';
	CreateList(addNhanVien.listHoaDon);
}

void NhanViencpy(NhanVien& nv1, NhanVien nv2) //chi copy thong tin nhan vien, ko copy ds hoa don
{
	nv1 = nv2;
	nv1.listHoaDon.first = nv1.listHoaDon.first = NULL; //dong nay de con tro ds hoa don nv1 khong tro vao ds hoa don cua nv2 nua
}

int KiemTraNhanVienRong(NhanVien addNhanVien) //theo thu tu thi 4 la phai, nhung phai ko the rong vi mac dinh la "Nu"
{
	if (addNhanVien.maNhanVien == -1) {
		return 1;
	}
	else if (string(addNhanVien.name.ho).length() == 0) {
		return 2;
	}
	else if (string(addNhanVien.name.ten).length() == 0) {
		return 3;
	}
	else if (string(addNhanVien.soCMND).length() == 0) {
		return 5;
	}
	return 0;
}

int KiemTraNhanVienTrungVaSoCMND(NhanVien addNhanVien, DSNhanVien dsNhanVien)
{
	if (string(addNhanVien.soCMND).length() < 9) {
		return 3;
	}

	for (int i = 0; i < dsNhanVien.soLuongNhanVien; i++) {
		if (addNhanVien.maNhanVien == dsNhanVien.nodesNhanVien[i]->maNhanVien) {
			return 1;
		}
		if (strcmp(addNhanVien.soCMND, dsNhanVien.nodesNhanVien[i]->soCMND) == 0) {
			return 2;
		}
	}
	return 0;
}

int KiemTraNhanVienTrungKhiSuaNhanVien(NhanVien fixingNhanVien, int indexCurrent, DSNhanVien dsNhanVien)
{
	if (fixingNhanVien.maNhanVien != dsNhanVien.nodesNhanVien[indexCurrent]->maNhanVien) { //neu ma nhan vien bi thay doi moi xet
		for (int i = 0; i < dsNhanVien.soLuongNhanVien; i++) {
			if (fixingNhanVien.maNhanVien == dsNhanVien.nodesNhanVien[i]->maNhanVien) {
				return 1;
			}
		}
	}
	if (strcmp(fixingNhanVien.soCMND, dsNhanVien.nodesNhanVien[indexCurrent]->soCMND) != 0) { //neu so CMND bi thay doi moi xet
		for (int i = 0; i < dsNhanVien.soLuongNhanVien; i++) {
			if (strcmp(fixingNhanVien.soCMND, dsNhanVien.nodesNhanVien[i]->soCMND) == 0) {
				return 2;
			}
		}
	}
	return 0;
}

//y tuong cua viec sua nhan vien gan giong them nhan vien, luu lai gia tri nhan vien dang sua va xoa no trong ds sinh vien, chi khac phan them nhan vien o cho huy viec sua thi no add cai nhan vien da luu tru vao lai
void ENTER_Keyhit_F1_SuaNhanVien(int keyHit, DSNhanVien& dsNhanVien, int& indexFirst, int& indexLast, int& indexCurrent, bool& isSuaNhanVienAndSucceeds)
{
	if (keyHit == F1) {
		/*NhanVien luuTruNhanVienDangSua = *dsNhanVien.nodesNhanVien[indexCurrent];
		XoaNhanVienTheoViTri(dsNhanVien, indexCurrent);
		NhanVien fixingNhanVien = luuTruNhanVienDangSua;*/

		NhanVien fixingNhanVien;
		NhanViencpy(fixingNhanVien, *dsNhanVien.nodesNhanVien[indexCurrent]);

		OptionThemNhanVien optionThemNhanVien;
		optionThemNhanVien = OptionThemNhanVien::ThemMaNhanVien;

		bool flagSuaThanhCong = false;

		int toaDoX = START_X_OF_MAIN_FRAME + 25 + 70; //toa do diem bat dau dong dau tien (Ma nhan vien: )
		int toaDoY = START_Y_OF_MAIN_FRAME + 20;

		ClearWorkFrame();
		WriteForm_INS(toaDoX, toaDoY, fixingNhanVien);
		WriteTitle("SUA NHAN VIEN");

		keyHit = -1;
		while (true)
		{
			INS_Keyhit_Move_And_Enter(keyHit, optionThemNhanVien); //xai lai ham cua them nhan vien
			ENTER_Keyhit_F1_Keyhit_F1_SuaNhanVien(keyHit, fixingNhanVien, dsNhanVien, flagSuaThanhCong, toaDoX, toaDoY, indexFirst, indexLast, indexCurrent);

			//them thanh cong
			if (flagSuaThanhCong) {
				isSuaNhanVienAndSucceeds = true;
				return;
			}
			//nut ESCape
			if (keyHit == ESC) {

				string thongBao[3] = { "Ban co muon huy viec sua nhan vien?", "xxxxxxxxxxxxxxxx" };
				string options[3] = { "Co", "Khong" };
				ClearWorkFrame();
				int luaChon = XuatOThongBao(thongBao, options, 2);
				if (luaChon == 0) { //huy viec sua
					ClearWorkFrame();
					WriteForm_INS(toaDoX, toaDoY, fixingNhanVien);
					WriteTitle("XEM NHAN VIEN");
					return;
				}
				else {
					keyHit = -1;
					ClearWorkFrame();
					WriteForm_INS(toaDoX, toaDoY, fixingNhanVien);
					WriteTitle("SUA NHAN VIEN");
				}
			}

			WriteSectionGuide("F1: xac nhan sua nhan vien - KEY_UP_DOWN: di chuyen len, xuong - ENTER: di chuyen xuong - ESC: thoat");

			INS_NhapThongTin(keyHit, optionThemNhanVien, fixingNhanVien, toaDoX, toaDoY); //ham nay se thay doi gia tri keyHit va xuat ra thong tin moi bang ham NhapThongTin()
		}
	}
}


void ENTER_Keyhit_F1_Keyhit_F1_SuaNhanVien(int keyHit, NhanVien fixingNhanVien, DSNhanVien& dsNhanVien, bool& flagSuaNhanVien, int toaDoX, int toaDoY, int& indexFirst, int& indexLast, int& indexCurrent)
{
	if (keyHit == F1) {
		int kiemTraRong = KiemTraNhanVienRong(fixingNhanVien);

		if (kiemTraRong == 0) { //ko rong
			int kiemTraTrung = KiemTraNhanVienTrungKhiSuaNhanVien(fixingNhanVien, indexCurrent, dsNhanVien);

			if (kiemTraTrung == 0) { //ko trung
				string thongBao[3] = { "Thong tin cua nhan vien hop le!", "Ban co chac chan muon sua nhan vien?" };
				string options[3] = { "Dong y", "Huy" };
				ClearWorkFrame();

				int luaChon = XuatOThongBao(thongBao, options, 2);

				if (luaChon == 0) {
					if (NameCmp(fixingNhanVien.name, dsNhanVien.nodesNhanVien[indexCurrent]->name) == 0) { //neu nhu nhan vien dang sua khong thay doi ho ten, thi don gian chi la copy thong tin
						dsNhanVien.nodesNhanVien[indexCurrent]->maNhanVien = fixingNhanVien.maNhanVien;
						dsNhanVien.nodesNhanVien[indexCurrent]->phai = fixingNhanVien.phai;
						strcpy(dsNhanVien.nodesNhanVien[indexCurrent]->soCMND, fixingNhanVien.soCMND);
						flagSuaNhanVien = true;
					}
					else { //con co thay doi name thi phai xoa di them vao lai de no sap xep, luu y phai luu ds hoa don lai
						fixingNhanVien.listHoaDon = dsNhanVien.nodesNhanVien[indexCurrent]->listHoaDon; //giu lai hoa don

						XoaNhanVienTheoViTri(dsNhanVien, indexCurrent);
						int viTriThem = InsertOrder(dsNhanVien, fixingNhanVien);//tra ve vi tri them, -1 la loi full nhan vien, khac -1 la them thanh cong
						//boi vi truoc khi sua la no xoa nhan vien, nen se ko co truong hop full nhan vien khi sua
						flagSuaNhanVien = true;
						indexCurrent = viTriThem;
						indexFirst = (viTriThem / 10) * 10; // chia 10 sau do nhan 10 de lam mat so dang sau -> vd: (26 / 10) * 10 = 20
						indexLast = endIndex(dsNhanVien, indexFirst);
					}
				}
				else {
					keyHit = -1; //tru truong hop sua thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
					ClearWorkFrame();
					WriteForm_INS(toaDoX, toaDoY, fixingNhanVien);
					WriteTitle("SUA NHAN VIEN");
				}
			}
			else { //bi trung
				string thongBaoLoi;

				switch (kiemTraTrung)
				{
				case 1:
					thongBaoLoi = "Ma nhan vien bi trung!";
					break;
				case 2:
					thongBaoLoi = "So CMND cua nhan vien bi trung!";
					break;
				default:
					break;
				}

				string thongBao[3] = { "Nhan vien dang sua khong hop le!", thongBaoLoi };
				string options[3] = { "OK" };
				ClearWorkFrame();
				XuatOThongBao(thongBao, options, 1);

				keyHit = -1; //tru truong hop sua thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
				ClearWorkFrame();
				WriteForm_INS(toaDoX, toaDoY, fixingNhanVien);
				WriteTitle("SUA NHAN VIEN");
			}
		}
		else { //bi rong
			string thongBaoLoi;

			switch (kiemTraRong) //ko co case 4 vi phai nhan vien dc khoi tao san la Nu
			{
			case 1:
				thongBaoLoi = "Ma nhan vien rong!";
				break;
			case 2:
				thongBaoLoi = "Ho cua nhan vien rong!";
				break;
			case 3:
				thongBaoLoi = "Ten cua nhan vien rong!";
				break;
			case 5:
				thongBaoLoi = "So CMND cua nhan vien rong!";
				break;
			default:
				break;
			}

			string thongBao[3] = { "Nhan vien dang sua khong hop le!", thongBaoLoi };
			string options[3] = { "OK" };
			ClearWorkFrame();
			XuatOThongBao(thongBao, options, 1);

			keyHit = -1; //tru truong hop sua thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
			ClearWorkFrame();
			WriteForm_INS(toaDoX, toaDoY, fixingNhanVien);
			WriteTitle("SUA NHAN VIEN");
		}
	}
}

void ENTER_Keyhit_F2_XemHoaDon(int keyHit, int toaDoX, int toaDoY, DSNhanVien& dsNhanVien, int indexCurrent, ListVatTu& listVatTu, PTRVatTu& root)
{
	if (keyHit == F2) {
		MainDanhSachHoaDon(dsNhanVien.nodesNhanVien[indexCurrent]->listHoaDon, dsNhanVien, listVatTu, root);

		//xem hoac xu ly ds hoa don xong thi ve lai nhan vien do
		ClearWorkFrame();
		WriteForm_INS(toaDoX, toaDoY, *dsNhanVien.nodesNhanVien[indexCurrent]);
		WriteTitle("XEM NHAN VIEN");
	}
}

void INS_Keyhit_F1_ThemNhanVien(int keyHit, NhanVien addNhanVien, DSNhanVien& dsNhanVien, bool& flagThemNhanVien, int toaDoX, int toaDoY, int& indexFirst, int& indexLast, int& indexCurrent)
{
	if (keyHit == F1) {
		int kiemTraRong = KiemTraNhanVienRong(addNhanVien);

		if (kiemTraRong == 0) { //ko rong
			int kiemTraTrung = KiemTraNhanVienTrungVaSoCMND(addNhanVien, dsNhanVien);

			if (kiemTraTrung == 0) { //ko trung va so CMND hop le
				string thongBao[3] = { "Thong tin cua nhan vien hop le!", "Ban co chac chan muon them nhan vien?" };
				string options[3] = { "Dong y", "Huy" };
				ClearWorkFrame();

				int luaChon = XuatOThongBao(thongBao, options, 2);

				if (luaChon == 0) { //dong y them
					int viTriThem = InsertOrder(dsNhanVien, addNhanVien);//tra ve vi tri them, -1 la loi full nhan vien, khac -1 la them thanh cong

					if (viTriThem != -1) {
						flagThemNhanVien = true;
						indexCurrent = viTriThem;
						indexFirst = (viTriThem / 10) * 10; // chia 10 sau do nhan 10 de lam mat so dang sau -> vd: (26 / 10) * 10 = 20
						indexLast = endIndex(dsNhanVien, indexFirst);
					}
					else {
						string thongBao[3] = { "Danh sach nhan vien da day!", "Vui long tang so luong nhan vien toi da hoac xoa nhan vien de them!" };
						string options[3] = { "OK" };
						ClearWorkFrame();
						XuatOThongBao(thongBao, options, 1);

						keyHit = -1; //tru truong hop them thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
						ClearWorkFrame();
						WriteForm_INS(toaDoX, toaDoY, addNhanVien);
					}
				}
				else { //huy viec them
					keyHit = -1; //tru truong hop them thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
					ClearWorkFrame();
					WriteForm_INS(toaDoX, toaDoY, addNhanVien);
				}
			}
			else { //loi bi trung nhan vien hoac sai so CMND
				string thongBaoLoi;

				switch (kiemTraTrung)
				{
				case 1:
					thongBaoLoi = "Ma nhan vien bi trung!";
					break;
				case 2:
					thongBaoLoi = "So CMND cua nhan vien bi trung!";
					break;
				case 3:
					thongBaoLoi = "So CMND cua nhan vien phai co it nhat 9 ki tu!";
				default:
					break;
				}

				string thongBao[3] = { "Nhan vien dang them khong hop le!", thongBaoLoi };
				string options[3] = { "OK" };
				ClearWorkFrame();
				XuatOThongBao(thongBao, options, 1);

				keyHit = -1; //tru truong hop them thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
				ClearWorkFrame();
				WriteForm_INS(toaDoX, toaDoY, addNhanVien);
			}
		}
		else { //loi bi rong nhan vien
			string thongBaoLoi;

			switch (kiemTraRong) //ko co case 4 vi phai nhan vien dc khoi tao san la Nu
			{
			case 1:
				thongBaoLoi = "Ma nhan vien rong!";
				break;
			case 2:
				thongBaoLoi = "Ho cua nhan vien rong!";
				break;
			case 3:
				thongBaoLoi = "Ten cua nhan vien rong!";
				break;
			case 5:
				thongBaoLoi = "So CMND cua nhan vien rong!";
				break;
			default:
				break;
			}

			string thongBao[3] = { "Nhan vien dang them khong hop le!", thongBaoLoi };
			string options[3] = { "OK" };
			ClearWorkFrame();
			XuatOThongBao(thongBao, options, 1);

			keyHit = -1; //tru truong hop them thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
			ClearWorkFrame();
			WriteForm_INS(toaDoX, toaDoY, addNhanVien);
		}
	}
}

void INS_Keyhit_Move_And_Enter(int keyHit, OptionThemNhanVien& optionThemNhanVien)
{
	if (keyHit == KEY_UP) {
		switch (optionThemNhanVien)
		{
		case OptionThemNhanVien::ThemMaNhanVien:
			optionThemNhanVien = OptionThemNhanVien::ThemSoCMND;
			break;
		case OptionThemNhanVien::ThemHo:
			optionThemNhanVien = OptionThemNhanVien::ThemMaNhanVien;
			break;
		case OptionThemNhanVien::ThemTen:
			optionThemNhanVien = OptionThemNhanVien::ThemHo;
			break;
		case OptionThemNhanVien::ThemPhai:
			optionThemNhanVien = OptionThemNhanVien::ThemTen;
			break;
		case OptionThemNhanVien::ThemSoCMND:
			optionThemNhanVien = OptionThemNhanVien::ThemPhai;
			break;
		default:
			break;
		}
	}
	else if (keyHit == KEY_DOWN || keyHit == ENTER) {
		switch (optionThemNhanVien)
		{
		case OptionThemNhanVien::ThemMaNhanVien:
			optionThemNhanVien = OptionThemNhanVien::ThemHo;
			break;
		case OptionThemNhanVien::ThemHo:
			optionThemNhanVien = OptionThemNhanVien::ThemTen;
			break;
		case OptionThemNhanVien::ThemTen:
			optionThemNhanVien = OptionThemNhanVien::ThemPhai;
			break;
		case OptionThemNhanVien::ThemPhai:
			optionThemNhanVien = OptionThemNhanVien::ThemSoCMND;
			break;
		case OptionThemNhanVien::ThemSoCMND:
			optionThemNhanVien = OptionThemNhanVien::ThemMaNhanVien;
			break;
		default:
			break;
		}
	}
}

void INS_NhapThongTin(int& keyHit, OptionThemNhanVien optionThemNhanVien, NhanVien& addNhanVien, int toaDoX, int toaDoY)
{
	string temp;
	CheDoNhap cheDoNhap;

	int toaDoXNhapThongTin = toaDoX + 20;
	int xuongDong = 2;

	switch (optionThemNhanVien)
	{
	case OptionThemNhanVien::ThemMaNhanVien:
		temp = to_string(addNhanVien.maNhanVien); //cho vao bien tam
		//ma nhan vien co so, ko co chu, khong co khoang trang
		cheDoNhap.coGhiSo = true;

		if (addNhanVien.maNhanVien == -1) {
			temp = "";
		}

		NhapThongTin(temp, 9, toaDoXNhapThongTin, toaDoY, keyHit, cheDoNhap); //max int la 2 ty (10 so), nen chi cho toi da nhap 9 so thoi

		if (temp.length() == 0) {
			addNhanVien.maNhanVien = -1;
		}
		else {
			addNhanVien.maNhanVien = stoi(temp); //doi thanh int va gan lai

			//truong hop dac biet: rieng so nguyen va so thuc thi phai loai truong hop viet so 0 o dau
			gotoxy(toaDoXNhapThongTin, toaDoY);
			cout << CenterTextInSpace(" ", 9 + 2); //vi cai ham nay de viet trong border, nen +2 cho 2 gach 2 ben thi moi dung la khoang 9 phan tu
			gotoxy(toaDoXNhapThongTin, toaDoY);
			cout << to_string(addNhanVien.maNhanVien);
		}
		break;
	case OptionThemNhanVien::ThemHo:
		temp = string(addNhanVien.name.ho);

		//ten nhan vien co chu,co khoang trang, ghi hoa chu cai dau, ko co so
		cheDoNhap.coGhiChu = true;
		cheDoNhap.coKhoangTrang = true;

		NhapThongTin(temp, MAX_HO - 1, toaDoXNhapThongTin, toaDoY + xuongDong * 1, keyHit, cheDoNhap);

		strcpy(addNhanVien.name.ho, temp.c_str());
		break;
	case OptionThemNhanVien::ThemTen:
		temp = string(addNhanVien.name.ten);

		//ho nhan vien co chu,co khoang trang, ghi hoa chu cai dau, ko co so
		cheDoNhap.coGhiChu = true;
		cheDoNhap.coKhoangTrang = true;

		NhapThongTin(temp, MAX_TEN - 1, toaDoXNhapThongTin, toaDoY + xuongDong * 2, keyHit, cheDoNhap);

		strcpy(addNhanVien.name.ten, temp.c_str());
		break;
	case OptionThemNhanVien::ThemPhai:
		int luaChon;
		if (addNhanVien.phai == 0) {
			luaChon = 0;
		}
		else {
			luaChon = 1;
		}

		Chon1Trong2(luaChon, "Nu", "Nam", toaDoXNhapThongTin, toaDoY + xuongDong * 3, keyHit);

		if (luaChon == 0) {

			addNhanVien.phai = 0;
		}
		else {
			addNhanVien.phai = 1;
		}

		break;
	case OptionThemNhanVien::ThemSoCMND:
		temp = string(addNhanVien.soCMND);

		//so cmnd chi co so
		cheDoNhap.coGhiSo = true;

		NhapThongTin(temp, MAX_SO_CMND - 1, toaDoXNhapThongTin, toaDoY + xuongDong * 4, keyHit, cheDoNhap);

		strcpy(addNhanVien.soCMND, temp.c_str());
		break;
	default:
		break;
	}
}

void WriteForm_INS(int toaDoX, int toaDoY, NhanVien addNhanVien)
{
	int xuongDong = 2;
	int toaDoXNhapThongTin = toaDoX + 20;

	gotoxy(toaDoX, toaDoY);
	cout << "Ma Nhan Vien: ";
	gotoxy(toaDoXNhapThongTin, toaDoY);
	if (addNhanVien.maNhanVien == -1) {
		cout << "";
	}
	else {
		cout << to_string(addNhanVien.maNhanVien);
	}

	gotoxy(toaDoX, toaDoY + xuongDong * 1);
	cout << "Ho: ";
	gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 1);
	cout << string(addNhanVien.name.ho);

	gotoxy(toaDoX, toaDoY + xuongDong * 2);
	cout << "Ten: ";
	gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 2);
	cout << string(addNhanVien.name.ten);

	gotoxy(toaDoX, toaDoY + xuongDong * 3);
	cout << "Phai: ";
	gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 3);
	if (addNhanVien.phai == 0) {
		SetColor(Red);
		cout << "Nu";
		SetColor(Black);
		cout << " | ";
		cout << "Nam";
	}
	else {
		cout << "Nu";
		cout << " | ";
		SetColor(Red);
		cout << "Nam";
		SetColor(Black);
	}

	gotoxy(toaDoX, toaDoY + xuongDong * 4);
	cout << "So CMND: ";
	gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 4);
	cout << string(addNhanVien.soCMND);

	WriteTitle("THEM NHAN VIEN");
}

void WriteForm_F2_TimKiemNhanVien(int toaDoX, int toaDoY, int findMaNhanVien)
{
	int toaDoXNhapThongTin = toaDoX + 20;

	gotoxy(toaDoX, toaDoY);
	cout << "Ma nhan vien: ";
	gotoxy(toaDoXNhapThongTin, toaDoY);
	if (findMaNhanVien == -1) {
		cout << "";
	}
	else {
		cout << to_string(findMaNhanVien);
	}

	WriteTitle("TIM KIEM NHAN VIEN");
}

void Keyhit_Move(int keyHit, int& indexFirst, int& indexLast, int& indexCurrent, DSNhanVien dsNhanVien)
{
	if (dsNhanVien.soLuongNhanVien == 0)
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
			indexLast = endIndex(dsNhanVien, indexFirst);
			indexCurrent = indexFirst;
		}
	}
	else if (keyHit == KEY_RIGHT) {
		if (indexLast != dsNhanVien.soLuongNhanVien - 1) { //neu ko phai trang cuoi cung
			indexFirst += 10;
			indexLast = endIndex(dsNhanVien, indexFirst);
			indexCurrent = indexFirst;
		}
	}
}

void Keyhit_INS(int keyHit, int toaDoXFormDSNV, int toaDoYFormDSNV, DSNhanVien& dsNhanVien, int& indexFirst, int& indexLast, int& indexCurrent)
{
	if (keyHit == INS) {
		NhanVien addNhanVien;
		KhoiTaoNhanVien(addNhanVien);

		OptionThemNhanVien optionThemNhanVien;
		optionThemNhanVien = OptionThemNhanVien::ThemMaNhanVien;

		bool flagThemThanhCong = false;

		ClearWorkFrame();

		int toaDoX = START_X_OF_MAIN_FRAME + 25 + 70; //toa do diem bat dau dong dau tien (Ma nhan vien: )
		int toaDoY = START_Y_OF_MAIN_FRAME + 20;
		WriteForm_INS(toaDoX, toaDoY, addNhanVien);

		keyHit = -1;
		while (true)
		{
			INS_Keyhit_Move_And_Enter(keyHit, optionThemNhanVien);
			INS_Keyhit_F1_ThemNhanVien(keyHit, addNhanVien, dsNhanVien, flagThemThanhCong, toaDoX, toaDoY, indexFirst, indexLast, indexCurrent);

			//them thanh cong
			if (flagThemThanhCong) {
				ClearWorkFrame();
				DrawFormDSNhanVien(toaDoXFormDSNV, toaDoYFormDSNV);
				return;
			}
			//nut ESCape
			if (keyHit == ESC) {

				string thongBao[3] = { "Ban co muon huy viec them nhan vien?", "xxxxxxxxxxxxxxxx" };
				string options[3] = { "Co", "Khong" };
				ClearWorkFrame();
				int luaChon = XuatOThongBao(thongBao, options, 2);
				if (luaChon == 0) {
					ClearWorkFrame();
					DrawFormDSNhanVien(toaDoXFormDSNV, toaDoYFormDSNV);
					return;
				}
				else {
					keyHit = -1;
					ClearWorkFrame();
					WriteForm_INS(toaDoX, toaDoY, addNhanVien);
				}
			}

			WriteSectionGuide("F1: xac nhan them nhan vien - KEY_UP_DOWN: di chuyen len, xuong - ENTER: di chuyen xuong - ESC: thoat");

			INS_NhapThongTin(keyHit, optionThemNhanVien, addNhanVien, toaDoX, toaDoY); //ham nay se thay doi gia tri keyHit va xuat ra thong tin moi bang ham NhapThongTin()
		}
	}
}

void Keyhit_Delete(int keyHit, int toaDoXFormDSNV, int toaDoYFormDSNV, DSNhanVien& dsNhanVien, int& indexFirst, int& indexLast, int& indexCurrent)
{
	if (dsNhanVien.soLuongNhanVien == 0) {
		return;
	}
	if (keyHit == DEL) {
		if (dsNhanVien.nodesNhanVien[indexCurrent]->listHoaDon.first == NULL) { //chua co hoa don

			string thongBao[3] = { "Nhan vien duoc phep xoa, nhan vien chua co hoa don!", "Ban co chac chan muon xoa nhan vien nay?" };
			string options[3] = { "Dong y", "Huy" };
			ClearWorkFrame();
			int luaChon = XuatOThongBao(thongBao, options, 2);

			if (luaChon == 0) { //dong y xoa

				XoaNhanVienTheoViTri(dsNhanVien, indexCurrent);

				if (indexCurrent != 0) { //xet truong hop cur ko la 0 //neu la 0 thi cu de no la 0, truong hop ko con ptu nao thi indexCur, first, last deu = 0
					if (indexCurrent == dsNhanVien.soLuongNhanVien) { //neu la xoa cuoi thi indexCurrent se nam ngoai index cua ds, nen gan cho no gia tri cuoi ds
						indexCurrent = dsNhanVien.soLuongNhanVien - 1;
					}
				}

				indexFirst = (indexCurrent / 10) * 10; // chia 10 sau do nhan 10 de lam mat so dang sau -> vd: (26 / 10) * 10 = 20
				indexLast = endIndex(dsNhanVien, indexFirst);

				//ve lai ds vat tu
				keyHit = -1;
				ClearWorkFrame();
				DrawFormDSNhanVien(toaDoXFormDSNV, toaDoYFormDSNV);
			}
			else { //ko dong y xoa
				//ve lai ds nhan vien
				keyHit = -1;
				ClearWorkFrame();
				DrawFormDSNhanVien(toaDoXFormDSNV, toaDoYFormDSNV);
			}
		}
		else { //da duoc su dung -> ko cho xoa
			string thongBao[3] = { "Nhan vien dang co hoa don!", "Khong the xoa nhan vien nay!" };
			string options[3] = { "OK" };
			ClearWorkFrame();
			XuatOThongBao(thongBao, options, 1);

			//ve lai ds vat tu
			keyHit = -1;
			ClearWorkFrame();
			DrawFormDSNhanVien(toaDoXFormDSNV, toaDoYFormDSNV);
		}
	}
}

void Keyhit_Enter(int keyHit, int toaDoXFormDSNV, int toaDoYFormDSNV, DSNhanVien& dsNhanVien, int& indexFirst, int& indexLast, int& indexCurrent, ListVatTu& listVatTu, PTRVatTu& root)
{
	if (dsNhanVien.soLuongNhanVien == 0) {
		return;
	}
	if (keyHit == ENTER) {
		int toaDoX = START_X_OF_MAIN_FRAME + 25 + 70; //toa do diem bat dau dong dau tien (Ma nhan vien: )
		int toaDoY = START_Y_OF_MAIN_FRAME + 20;

		ClearWorkFrame();
		WriteForm_INS(toaDoX, toaDoY, *dsNhanVien.nodesNhanVien[indexCurrent]);
		WriteTitle("XEM NHAN VIEN");

		bool isSuaNhanVienAndSucceed = false;

		keyHit = -1;
		while (true)
		{
			if (keyHit == 224)
				keyHit = _getch();
			if (keyHit == 0)
				keyHit = _getch();

			//cac nut
			ENTER_Keyhit_F1_SuaNhanVien(keyHit, dsNhanVien, indexFirst, indexLast, indexCurrent, isSuaNhanVienAndSucceed);
			ENTER_Keyhit_F2_XemHoaDon(keyHit, toaDoX, toaDoY, dsNhanVien, indexCurrent, listVatTu, root);

			if (isSuaNhanVienAndSucceed) {
				ClearWorkFrame();
				DrawFormDSNhanVien(toaDoXFormDSNV, toaDoYFormDSNV);
				return;
			}

			//nut ESCape
			if (keyHit == ESC) {
				ClearWorkFrame();
				DrawFormDSNhanVien(toaDoXFormDSNV, toaDoYFormDSNV);
				return;
			}

			WriteSectionGuide("F1: sua nhan vien - F2: xem hoa don - ESC: thoat");

			keyHit = _getch();
		}
	}
}

void Keyhit_F2_TimTheoMaNhanVien(int keyHit, DSNhanVien dsNhanVien, int& indexFirst, int& indexLast, int& indexCurrent, int toaDoXFormDSNhanVien, int toaDoYFormDSNhanVien)
{
	if (keyHit == F2) {
		/*char findMaVatTu[MAX_MA_VAT_TU];
		findMaVatTu[0] = '\0';*/
		int findMaNhanVien;
		findMaNhanVien = -1;
		string temp; // bien nay de nhap thong tin
		//ma nhan vien chi co so
		CheDoNhap cheDoNhap;
		cheDoNhap.coGhiSo = true;

		int toaDoX = START_X_OF_MAIN_FRAME + 25 + 70; //toa do diem bat dau dong dau tien (Ma nhan vien: )
		int toaDoY = START_Y_OF_MAIN_FRAME + 20;
		int toaDoXNhapThongTin = toaDoX + 20;

		ClearWorkFrame();
		WriteForm_F2_TimKiemNhanVien(toaDoX, toaDoY, findMaNhanVien);

		keyHit = -1;
		while (true)
		{
			//nut enter
			if (keyHit == ENTER) {
				int viTriTimKiem = TimViTriNhanVien(dsNhanVien, findMaNhanVien); //tra ve vi tri cua nhan vien, -1 neu nhu ko tim thay ma nhan vien

				if (viTriTimKiem != -1) { //tim thay nhan vien
					//cap nhat current node
					indexCurrent = viTriTimKiem;
					indexFirst = (viTriTimKiem / 10) * 10; // chia 10 sau do nhan 10 de lam mat so dang sau -> vd: (26 / 10) * 10 = 20
					indexLast = endIndex(dsNhanVien, indexFirst);

					ClearWorkFrame();
					DrawFormDSNhanVien(toaDoXFormDSNhanVien, toaDoYFormDSNhanVien);
					return;
				}
				else { //ko tim thay vat tu
					string thongBao[3] = { "Nhan vien tim kiem khong ton tai!", "xxxxxxxxxxxxxxxx" };
					string options[3] = { "Dong y" };
					ClearWorkFrame();
					XuatOThongBao(thongBao, options, 1);

					keyHit = -1;
					ClearWorkFrame();
					WriteForm_F2_TimKiemNhanVien(toaDoX, toaDoY, findMaNhanVien);
				}
			}

			//nut ESCape
			if (keyHit == ESC) {
				string thongBao[3] = { "Ban co muon huy viec tim kiem theo ma nhan vien?", "xxxxxxxxxxxxxxxx" };
				string options[3] = { "Co", "Khong" };
				ClearWorkFrame();
				int luaChon = XuatOThongBao(thongBao, options, 2);
				if (luaChon == 0) {
					ClearWorkFrame();
					DrawFormDSNhanVien(toaDoXFormDSNhanVien, toaDoYFormDSNhanVien);
					return;
				}
				else {
					keyHit = -1;
					ClearWorkFrame();
					WriteForm_F2_TimKiemNhanVien(toaDoX, toaDoY, findMaNhanVien);
				}
			}

			WriteSectionGuide("ENTER: tim kiem - ESC: thoat");

			temp = to_string(findMaNhanVien); //cho vao bien tam
			//ma nhan vien co so, ko co chu, khong co khoang trang
			cheDoNhap.coGhiSo = true;
			if (findMaNhanVien == -1) {
				temp = "";
			}

			NhapThongTin(temp, 9, toaDoXNhapThongTin, toaDoY, keyHit, cheDoNhap); //max int la 2 ty (10 so), nen chi cho toi da nhap 9 so thoi

			if (temp.length() == 0) {
				findMaNhanVien = -1;
			}
			else {
				findMaNhanVien = stoi(temp); //doi thanh int va gan lai

				//truong hop dac biet: rieng so nguyen va so thuc thi phai loai truong hop viet so 0 o dau
				gotoxy(toaDoXNhapThongTin, toaDoY);
				cout << CenterTextInSpace(" ", 9 + 2); //vi cai ham nay de viet trong border, nen +2 cho 2 gach 2 ben thi moi dung la khoang 9 phan tu
				gotoxy(toaDoXNhapThongTin, toaDoY);
				cout << to_string(findMaNhanVien);
			}
		}
	}
}

void Output10Nodes(DSNhanVien dsNhanVien, int indexFirst, int indexLast, int indexCurrent, int toaDoX, int toaDoY)
{
	if (dsNhanVien.soLuongNhanVien == 0)
		return;
	int dem = 0;
	for (int i = indexFirst; i <= indexLast; i++) {
		dem++;

		if (i == indexCurrent) {
			SetColor(Red);
		}

		gotoxy(toaDoX + 1, toaDoY + 1 + 2 * dem);
		cout << CenterTextInSpace(to_string(i + 1), 32);

		gotoxy(toaDoX + 1 + 32 * 1, toaDoY + 1 + 2 * dem);
		cout << CenterTextInSpace(to_string(dsNhanVien.nodesNhanVien[i]->maNhanVien), 32);

		gotoxy(toaDoX + 1 + 32 * 2, toaDoY + 1 + 2 * dem);
		cout << CenterTextInSpace(NameToString(dsNhanVien.nodesNhanVien[i]->name), 32);

		if (dsNhanVien.nodesNhanVien[i]->phai == 0) {
			gotoxy(toaDoX + 1 + 32 * 3, toaDoY + 1 + 2 * dem);
			cout << CenterTextInSpace("Nu", 32);
		}
		else
		{
			gotoxy(toaDoX + 1 + 32 * 3, toaDoY + 1 + 2 * dem);
			cout << CenterTextInSpace("Nam", 32);
		}


		gotoxy(toaDoX + 1 + 32 * 4, toaDoY + 1 + 2 * dem);
		cout << CenterTextInSpace(string(dsNhanVien.nodesNhanVien[i]->soCMND), 32);

		SetColor(Black);
	}

	//neu ko du 10 node thi xoa trang nhung o con lai
	if (dem < 10) {
		dem++;
		for (; dem <= 10; dem++) {
			gotoxy(toaDoX + 1, toaDoY + 1 + 2 * dem);
			cout << CenterTextInSpace(" ", 32);

			gotoxy(toaDoX + 1 + 32 * 1, toaDoY + 1 + 2 * dem);
			cout << CenterTextInSpace(" ", 32);

			gotoxy(toaDoX + 1 + 32 * 2, toaDoY + 1 + 2 * dem);
			cout << CenterTextInSpace(" ", 32);

			gotoxy(toaDoX + 1 + 32 * 3, toaDoY + 1 + 2 * dem);
			cout << CenterTextInSpace(" ", 32);

			gotoxy(toaDoX + 1 + 32 * 4, toaDoY + 1 + 2 * dem);
			cout << CenterTextInSpace(" ", 32);
		}
	}

	gotoxy(toaDoX + 1 + 32 * 0, toaDoY + 1 + 2 * 11); //*11 vi dong dau tien la tieu de border
	cout << "Trang " << indexFirst / 10 + 1; //vd: 16 / 10 + 1 = 2 -> trang 2 
}

void DrawFormDSNhanVien(int toaDoX, int toaDoY)
{
	int soDong = 11;
	int soCot = 5;
	int doDaiNgang1Cot = 32;
	int doDaiDoc1Hang = 1;

	DrawBorderList(toaDoX, toaDoY, soDong, soCot, doDaiNgang1Cot, doDaiDoc1Hang);
	WriteTitle("DANH SACH NHAN VIEN");

	SetColor(Green);

	gotoxy(toaDoX + 1, toaDoY + 1);
	cout << CenterTextInSpace("STT", doDaiNgang1Cot);

	gotoxy(toaDoX + 1 + doDaiNgang1Cot * 1, toaDoY + 1);
	cout << CenterTextInSpace("MA NHAN VIEN", doDaiNgang1Cot);

	gotoxy(toaDoX + 1 + doDaiNgang1Cot * 2, toaDoY + 1);
	cout << CenterTextInSpace("HO TEN", doDaiNgang1Cot);

	gotoxy(toaDoX + 1 + doDaiNgang1Cot * 3, toaDoY + 1);
	cout << CenterTextInSpace("PHAI", doDaiNgang1Cot);

	gotoxy(toaDoX + 1 + doDaiNgang1Cot * 4, toaDoY + 1);
	cout << CenterTextInSpace("SO CMND", doDaiNgang1Cot);

	SetColor(Black);
}

void MainDanhSachNhanVien(DSNhanVien& dsNhanVien, ListVatTu& listVatTu, PTRVatTu& root)
{
	int indexFirst = 0, indexCurrent = 0;
	int indexLast = endIndex(dsNhanVien, indexFirst);

	int keyHit = -1;

	//toa do diem bat dau ve khung
	int toaDoX = START_X_OF_MAIN_FRAME + 25 + 8;
	int toaDoY = START_Y_OF_MAIN_FRAME + 18;
	DrawFormDSNhanVien(toaDoX, toaDoY);

	while (true) {
		if (keyHit == 224)
			keyHit = _getch();
		if (keyHit == 0)
			keyHit = _getch();

		//cac nut 
		Keyhit_Move(keyHit, indexFirst, indexLast, indexCurrent, dsNhanVien);
		Keyhit_INS(keyHit, toaDoX, toaDoY, dsNhanVien, indexFirst, indexLast, indexCurrent);
		Keyhit_Enter(keyHit, toaDoX, toaDoY, dsNhanVien, indexFirst, indexLast, indexCurrent, listVatTu, root);
		Keyhit_F2_TimTheoMaNhanVien(keyHit, dsNhanVien, indexFirst, indexLast, indexCurrent, toaDoX, toaDoY);
		Keyhit_Delete(keyHit, toaDoX, toaDoY, dsNhanVien, indexFirst, indexLast, indexCurrent);
		if (keyHit == ESC) {
			return;
		}
		//

		Output10Nodes(dsNhanVien, indexFirst, indexLast, indexCurrent, toaDoX, toaDoY);
		WriteSectionGuide("ENTER: chon nhan vien - INSERT: them nhan vien - DELETE: xoa nhan vien - F2: tim kiem nhan vien - KEY_UP_DOWN: di chuyen len, xuong - KEY_LEFT_RIGHT: lui trang, sang trang - ESC: thoat");

		keyHit = _getch();
	}
}

void DrawAndWriteFormThongKe(int doangThu[], int namThongKe)
{
	int soDong = 13;
	int soCot = 2;
	int doDaiNgang1Cot = 32;
	int doDaiDoc1Hang = 1;
	//toa do diem bat dau ve khung
	int toaDoX = START_X_OF_MAIN_FRAME + 25 + 57;
	int toaDoY = START_Y_OF_MAIN_FRAME + 16;

	DrawBorderList(toaDoX, toaDoY, soDong, soCot, doDaiNgang1Cot, doDaiDoc1Hang);

	string title;
	title = "BANG THONG KE DOANH THU NAM " + to_string(namThongKe);
	WriteTitle(title);

	SetColor(Red);
	gotoxy(toaDoX + 1, toaDoY + 1);
	cout << CenterTextInSpace("THANG", doDaiNgang1Cot);
	gotoxy(toaDoX + 1 + doDaiNgang1Cot, toaDoY + 1);
	cout << CenterTextInSpace("DOANH THU", doDaiNgang1Cot);
	SetColor(Black);

	for (int i = 0; i < 12; i++) {
		gotoxy(toaDoX + 1, toaDoY + 1 + 2 * (i + 1)); //moi hang cach nhau 2 don vi, i tu dau = 0 nen phai + 1 //toa do x va y cong them 1 vi x va y la toa do cua nhung duong thang cua border, + 1 cho no vao khoang trang tung o de xuat ra
		cout << CenterTextInSpace(to_string(i + 1), doDaiNgang1Cot);

		gotoxy(toaDoX + 1 + doDaiNgang1Cot, toaDoY + 1 + 2 * (i + 1));
		cout << CenterTextInSpace(to_string(doangThu[i]), doDaiNgang1Cot);
	}
}

void WriteForm_NhapNamThongKe(int toaDoX, int toaDoY, int namThongKe)
{
	int toaDoXNhapThongTin = toaDoX + 20;

	gotoxy(toaDoX, toaDoY);
	cout << "Nam thong ke: ";
	gotoxy(toaDoXNhapThongTin, toaDoY);
	cout << to_string(namThongKe);

	WriteTitle("THONG KE");
}

void MainThongKe(DSNhanVien dsNhanVien)
{
	int namThongKe;
	namThongKe = -1;
	string temp; // bien nay de nhap thong tin
	//nam thong ke chi co so
	CheDoNhap cheDoNhap;
	cheDoNhap.coGhiSo = true;

	int toaDoX = START_X_OF_MAIN_FRAME + 25 + 70; //toa do diem bat dau dong dau tien (Nam thong ke: )
	int toaDoY = START_Y_OF_MAIN_FRAME + 20;
	int toaDoXNhapThongTin = toaDoX + 20;

	ClearWorkFrame();
	WriteForm_NhapNamThongKe(toaDoX, toaDoY, namThongKe);

	int keyHit = -1;
	while (true)
	{
		if (keyHit == ENTER) {
			time_t hientai = time(0);
			tm* now = localtime(&hientai);

			int namHienTai;
			namHienTai = now->tm_year + 1900;

			if (namThongKe == -1 || namThongKe > namHienTai || namThongKe <= 0) {//rong || ko dc xem truoc tuong lai || ko duoc nho hon hoac bang 0
				string thongBao[3] = { "Nam thong ke khong hop le!", "Khong duoc rong, bang 0, hoac lon hon nam hien tai!" };
				string options[3] = { "Dong y" };
				ClearWorkFrame();
				XuatOThongBao(thongBao, options, 1);

				keyHit = -1;
				ClearWorkFrame();
				WriteForm_NhapNamThongKe(toaDoX, toaDoY, namThongKe);
			}
			else {
				int doanhThu[12]; //12 phan tu dai dien cho tung thang index tu 0 -> 11
				for (int i = 0; i < 12; i++) {
					doanhThu[i] = 0;
				}

				for (int i = 0; i < dsNhanVien.soLuongNhanVien; i++) {//duyet tung nhan vien

					for (PTRHoaDon run = dsNhanVien.nodesNhanVien[i]->listHoaDon.first; run != NULL; run = run->next) { //duyet tung hoa don nhan vien do

						if (run->infoHoaDon.ngayLap.nam == namThongKe && run->infoHoaDon.loai == 'X') { //neu nhu dung nam thong ke va la hoa don xuat

							doanhThu[run->infoHoaDon.ngayLap.thang - 1] += TriGiaHoaDon(run->infoHoaDon.dsCTHD); //cong vao mang doanh thu
						}
					}
				}

				keyHit = -1;
				while (true) {
					if (keyHit == 224)
						keyHit = _getch();
					if (keyHit == 0)
						keyHit = _getch();


					if (keyHit == ESC) {
						string thongBao[3] = { "Ban co muon thoat khoi thong ke nay?", "xxxxxxxxxxxxx" };
						string options[3] = { "Co", "Khong" };
						ClearWorkFrame();

						int luaChon = XuatOThongBao(thongBao, options, 2);

						if (luaChon == 0) {
							keyHit = -1;
							ClearWorkFrame();
							WriteForm_NhapNamThongKe(toaDoX, toaDoY, namThongKe);
							break;
						}
						else {
							ClearWorkFrame();
							DrawAndWriteFormThongKe(doanhThu, namThongKe);
						}
					}

					DrawAndWriteFormThongKe(doanhThu, namThongKe);
					WriteSectionGuide("ESC: thoat");

					keyHit = _getch();
				}
			}
		}

		//nut ESCape
		if (keyHit == ESC) {
			return;
		}

		WriteSectionGuide("ENTER: thong ke - ESC: thoat");

		temp = to_string(namThongKe); //cho vao bien tam

		if (namThongKe == -1) {
			temp = "";
		}

		NhapThongTin(temp, 4, toaDoXNhapThongTin, toaDoY, keyHit, cheDoNhap); //max nam la 4 so

		if (temp.length() == 0) {
			namThongKe = -1;
		}
		else {
			namThongKe = stoi(temp); //doi thanh int va gan lai

			//truong hop dac biet: rieng so nguyen va so thuc thi phai loai truong hop viet so 0 o dau
			gotoxy(toaDoXNhapThongTin, toaDoY);
			cout << CenterTextInSpace(" ", 2 + 2); //vi cai ham nay de viet trong border, nen +2 cho 2 gach 2 ben thi moi dung la khoang 2 phan tu
			gotoxy(toaDoXNhapThongTin, toaDoY);
			cout << to_string(namThongKe);
		}
	}
}
