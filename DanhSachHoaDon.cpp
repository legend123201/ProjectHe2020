#include "DanhSachHoaDon.h"

PTRHoaDon endNode(PTRHoaDon firstNode)
{
	if (firstNode == NULL)
		return NULL;
	PTRHoaDon run = firstNode;
	//moi vao i = 0, ko lam gi ca, sau do i = 1 thi run da la phan tu sau first (phan tu thu 2), nhu vay i = 9 (dieu kien ket thuc vong lap) thi run la phan tu thu 10 va return phan tu thu 10
	for (int i = 0; i < 9 && run->next != NULL; i++, run = run->next); //run -> next != NULL de ko bi chay lo them dong run = run -> next, thi no moi return node last duoc, no se tra ve phan tu truoc NULL neu ma ko du 10 phan tu
	return run;
}

PTRHoaDon prevNode(PTRHoaDon firstNode, PTRHoaDon currentNode)
{
	if (firstNode == NULL)
		return NULL;
	PTRHoaDon run;
	for (run = firstNode; run->next != currentNode; run = run->next); //run->next = curruntNode thi return 
	return run;
}

void KhoiTaoHoaDon(HoaDon& addHoaDon)
{
	time_t hientai = time(0);
	tm* now = localtime(&hientai);

	Date dateHienTai;
	dateHienTai.ngay = now->tm_mday;
	dateHienTai.thang = now->tm_mon + 1;
	dateHienTai.nam = now->tm_year + 1900;

	addHoaDon.soHoaDon[0] = '\0';
	addHoaDon.ngayLap.ngay = dateHienTai.ngay;
	addHoaDon.ngayLap.thang = dateHienTai.thang;
	addHoaDon.ngayLap.nam = dateHienTai.nam;
	addHoaDon.loai = 'N';
	CreateMangTuyenTinh(addHoaDon.dsCTHD);
}

long long TriGiaHoaDon(DSChiTietHoaDon dsCTHD)
{
	long long triGia = 0;
	for (int i = 0; i < dsCTHD.soLuongVatTu; i++) {
		if (dsCTHD.nodesCTHD[i].trangThai == 1) { //phai la mua thi moi cong vao, da tra hang thi ko cong
			triGia += TriGiaChiTietHoaDon(dsCTHD.nodesCTHD[i]);
		}	
	}
	return triGia;
}

int KiemTraHoaDonRong(HoaDon addHoaDon) //loai hoa don ko the rong vi mac dinh la "Nhap"
{
	if (string(addHoaDon.soHoaDon).length() == 0) {
		return 1;
	}
	else if (addHoaDon.ngayLap.ngay == -1) {
		return 2;
	}
	else if (addHoaDon.ngayLap.thang == -1) {
		return 3;
	}
	else if (addHoaDon.ngayLap.nam == -1) {
		return 4;
	}
	return 0;
}

int KiemTraHoaDonTrung(HoaDon addHoaDon, DSNhanVien dsNhanVien)
{
	for (int i = 0; i < dsNhanVien.soLuongNhanVien; i++) { //duyet tung nhan vien
		for (PTRHoaDon run = dsNhanVien.nodesNhanVien[i]->listHoaDon.first; run != NULL; run = run->next) { //duyet tung hoa don cua nhan vien do
			if (strcmp(addHoaDon.soHoaDon, run->infoHoaDon.soHoaDon) == 0) {
				return 1;
			}
		}
	}
	return 0;
}

void TimTrangChuaCurrentNode(ListHoaDon listHoaDon, PTRHoaDon& firstNode, PTRHoaDon currentNode, PTRHoaDon& lastNode, int& trangHienTai)
{
	int dem = 0;
	PTRHoaDon run = listHoaDon.first;
	firstNode = listHoaDon.first;
	lastNode = endNode(firstNode);
	trangHienTai = 1;

	while (run != currentNode) {
		run = run->next;
		dem++;
		if (dem == 10) { //0 -> 9 la du 10 phan tu, dem = 10 la dang o phan tu thu 11 thi gan lai cac gia tri
			dem = 0;
			firstNode = run;
			lastNode = endNode(firstNode);
			trangHienTai++;
		}
	}
}

void INS_Keyhit_F1_ThemHoaDon(int keyHit, HoaDon addHoaDon, ListHoaDon& listHoaDon, bool& flagThemHoaDon, int toaDoX, int toaDoY, PTRHoaDon& firstNode, PTRHoaDon& lastNode, PTRHoaDon& currentNode, int& trangHienTai, DSNhanVien dsNhanVien, ListVatTu& listVatTu, PTRVatTu& root)
{
	if (keyHit == F1) {
		int kiemTraRong = KiemTraHoaDonRong(addHoaDon);

		if (kiemTraRong == 0) { //ko rong
			int kiemTraTrung = KiemTraHoaDonTrung(addHoaDon, dsNhanVien);

			if (kiemTraTrung == 0) { //ko trung

				if (KiemTraDate(addHoaDon.ngayLap) == 0) { //ko sai ngay lap

					if (addHoaDon.dsCTHD.soLuongVatTu != 0) { //co chi tiet hoa don

						string thongBao[3] = { "Thong tin cua hoa don hop le!", "Ban co chac chan muon them hoa don va chi tiet hoa don?" };
						string options[3] = { "Dong y", "Huy" };
						ClearWorkFrame();

						int luaChon = XuatOThongBao(thongBao, options, 2);

						if (luaChon == 0) { //dong y them
							PTRHoaDon nodeHoaDonVuaThem = InsertOrder(listHoaDon, addHoaDon);//tra ve con tro cua hoa don vua them, tra ve NULL neu ko du o nho

							if (nodeHoaDonVuaThem != NULL) { //them thanh cong 						
									flagThemHoaDon = true;
									CapNhatSoLuongTon(addHoaDon, root);

									currentNode = nodeHoaDonVuaThem;
									TimTrangChuaCurrentNode(listHoaDon, firstNode, currentNode, lastNode, trangHienTai);							
							}
							else { //ko du o nho de them
								string thongBao[3] = { "O nho cua ban khong du de thuc hien viec them!", "xxxxxxxxxxxxxxxx" };
								string options[3] = { "OK" };
								ClearWorkFrame();
								XuatOThongBao(thongBao, options, 1);

								keyHit = -1; //tru truong hop them thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
								ClearWorkFrame();
								WriteForm_INS(toaDoX, toaDoY, addHoaDon);
							}
						}
						else { //huy viec them
							keyHit = -1; //tru truong hop them thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
							ClearWorkFrame();
							WriteForm_INS(toaDoX, toaDoY, addHoaDon);
						}
					}
					else { //khong co chi tiet hoa don
						string thongBao[3] = { "Hoa don dang them khong hop le!", "Chua co chi tiet hoa don nao duoc them vao!" };
						string options[3] = { "OK" };
						ClearWorkFrame();
						XuatOThongBao(thongBao, options, 1);

						keyHit = -1; //tru truong hop them thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
						ClearWorkFrame();
						WriteForm_INS(toaDoX, toaDoY, addHoaDon);
					}
				}
				else { //loi ngay lap ko hop le
					string thongBaoLoi;

					switch (KiemTraDate(addHoaDon.ngayLap))
					{
					case 1:
						thongBaoLoi = "Ngay lap hoa don sai!";
						break;
					case 2:
						thongBaoLoi = "Thang lap hoa don sai!";
						break;
					case 3:
						thongBaoLoi = "Nam lap hoa don sai!";
						break;
					case 4:
						thongBaoLoi = "Ngay thang nam lap hoa don lon hon ngay thang nam hien tai!";
						break;
					default:
						break;
					}

					string thongBao[3] = { "Hoa don dang them khong hop le!", thongBaoLoi };
					string options[3] = { "OK" };
					ClearWorkFrame();
					XuatOThongBao(thongBao, options, 1);

					keyHit = -1; //tru truong hop them thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
					ClearWorkFrame();
					WriteForm_INS(toaDoX, toaDoY, addHoaDon);
				}
			}
			else { //loi bi trung hoa don
				string thongBaoLoi;
				thongBaoLoi = "So hoa don bi trung!";

				string thongBao[3] = { "Hoa don dang them khong hop le!", thongBaoLoi };
				string options[3] = { "OK" };
				ClearWorkFrame();
				XuatOThongBao(thongBao, options, 1);

				keyHit = -1; //tru truong hop them thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
				ClearWorkFrame();
				WriteForm_INS(toaDoX, toaDoY, addHoaDon);
			}
		}
		else { //loi bi rong hoa don
			string thongBaoLoi;

			switch (kiemTraRong) //ko co case 5 vi loai hoa don dc khoi tao san la Nhap
			{
			case 1:
				thongBaoLoi = "So hoa don rong!";
				break;
			case 2:
				thongBaoLoi = "Ngay lap hoa don rong!";
				break;
			case 3:
				thongBaoLoi = "Thang lap hoa don rong!";
				break;
			case 4:
				thongBaoLoi = "Nam lap hoa don rong!";
				break;
			default:
				break;
			}

			string thongBao[3] = { "Hoa don dang them khong hop le!", thongBaoLoi };
			string options[3] = { "OK" };
			ClearWorkFrame();
			XuatOThongBao(thongBao, options, 1);

			keyHit = -1; //tru truong hop them thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
			ClearWorkFrame();
			WriteForm_INS(toaDoX, toaDoY, addHoaDon);
		}
	}
}

void INS_Keyhit_F2_XemDsCTHD(int keyHit, HoaDon& addHoaDon, bool& flagDaQuyetDinhLoaiHoaDon, int toaDoX, int toaDoY, ListVatTu listVatTu, PTRVatTu root)
{
	if (keyHit == F2) {
		MainDanhSachChiTietHoaDon(addHoaDon.dsCTHD, addHoaDon.loai, listVatTu, root);

		if (addHoaDon.dsCTHD.soLuongVatTu == 0) {
			flagDaQuyetDinhLoaiHoaDon = false;
		}
		else {
			flagDaQuyetDinhLoaiHoaDon = true;
		}

		ClearWorkFrame();
		WriteForm_INS(toaDoX, toaDoY, addHoaDon);
	}
}

void INS_Keyhit_Move_And_Enter(int keyHit, OptionThemHoaDon& optionThemHoaDon)
{
	if (keyHit == KEY_UP) {
		switch (optionThemHoaDon)
		{
		case OptionThemHoaDon::ThemSoHoaDon:
			optionThemHoaDon = OptionThemHoaDon::ThemLoai;
			break;
		case OptionThemHoaDon::ThemNgay:
			optionThemHoaDon = OptionThemHoaDon::ThemSoHoaDon;
			break;
		case OptionThemHoaDon::ThemThang:
			optionThemHoaDon = OptionThemHoaDon::ThemNgay;
			break;
		case OptionThemHoaDon::ThemNam:
			optionThemHoaDon = OptionThemHoaDon::ThemThang;
			break;
		case OptionThemHoaDon::ThemLoai:
			optionThemHoaDon = OptionThemHoaDon::ThemNam;
			break;
		default:
			break;
		}
	}
	else if (keyHit == KEY_DOWN || keyHit == ENTER) {
		switch (optionThemHoaDon)
		{
		case OptionThemHoaDon::ThemSoHoaDon:
			optionThemHoaDon = OptionThemHoaDon::ThemNgay;
				break;
		case OptionThemHoaDon::ThemNgay:
			optionThemHoaDon = OptionThemHoaDon::ThemThang;
				break;
		case OptionThemHoaDon::ThemThang:
			optionThemHoaDon = OptionThemHoaDon::ThemNam;
				break;
		case OptionThemHoaDon::ThemNam:
			optionThemHoaDon = OptionThemHoaDon::ThemLoai;
				break;
		case OptionThemHoaDon::ThemLoai:
			optionThemHoaDon = OptionThemHoaDon::ThemSoHoaDon;
				break;
		default:
			break;
		}
	}
}

void INS_NhapThongTin(int& keyHit, OptionThemHoaDon optionThemHoaDon, HoaDon& addHoaDon, bool flagDaQuyetDinhLoaiHoaDon, int toaDoX, int toaDoY)
{
	string temp;
	CheDoNhap cheDoNhap;

	int toaDoXNhapThongTin = toaDoX + 20;
	int xuongDong = 2;

	switch (optionThemHoaDon)
	{
	case OptionThemHoaDon::ThemSoHoaDon:
		temp = string(addHoaDon.soHoaDon);

		//so hoa don co chu, co so, ghi hoa full, ko co khoang trang
		cheDoNhap.coGhiChu = true;
		cheDoNhap.coGhiSo = true;
		cheDoNhap.coGhiHoaFull = true;

		NhapThongTin(temp, MAX_SO_HOA_DON - 1, toaDoXNhapThongTin, toaDoY + xuongDong * 0, keyHit, cheDoNhap);

		strcpy(addHoaDon.soHoaDon, temp.c_str());
		break;
	case OptionThemHoaDon::ThemNgay:
		temp = to_string(addHoaDon.ngayLap.ngay); //cho vao bien tam
		//ngay co so, ko co chu, khong co khoang trang
		cheDoNhap.coGhiSo = true;

		if (addHoaDon.ngayLap.ngay == -1) {
			temp = "";
		}

		NhapThongTin(temp, 2, toaDoXNhapThongTin, toaDoY + xuongDong * 1, keyHit, cheDoNhap); //max ngay la 2 so

		if (temp.length() == 0) {
			addHoaDon.ngayLap.ngay = -1;
		}
		else {
			addHoaDon.ngayLap.ngay = stoi(temp); //doi thanh int va gan lai

			//truong hop dac biet: rieng so nguyen va so thuc thi phai loai truong hop viet so 0 o dau
			gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 1);
			cout << CenterTextInSpace(" ", 2 + 2); //vi cai ham nay de viet trong border, nen +2 cho 2 gach 2 ben thi moi dung la khoang 2 phan tu
			gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 1);
			cout << to_string(addHoaDon.ngayLap.ngay);
		}
		break;
	case OptionThemHoaDon::ThemThang:
		temp = to_string(addHoaDon.ngayLap.thang); //cho vao bien tam
		//thang co so, ko co chu, khong co khoang trang
		cheDoNhap.coGhiSo = true;

		if (addHoaDon.ngayLap.thang == -1) {
			temp = "";
		}

		NhapThongTin(temp, 2, toaDoXNhapThongTin, toaDoY + xuongDong * 2, keyHit, cheDoNhap); //max thang la 2 so

		if (temp.length() == 0) {
			addHoaDon.ngayLap.thang = -1;
		}
		else {
			addHoaDon.ngayLap.thang = stoi(temp); //doi thanh int va gan lai

			//truong hop dac biet: rieng so nguyen va so thuc thi phai loai truong hop viet so 0 o dau
			gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 2);
			cout << CenterTextInSpace(" ", 2 + 2); //vi cai ham nay de viet trong border, nen +2 cho 2 gach 2 ben thi moi dung la khoang 2 phan tu
			gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 2);
			cout << to_string(addHoaDon.ngayLap.thang);
		}
		break;
	case OptionThemHoaDon::ThemNam:
		temp = to_string(addHoaDon.ngayLap.nam); //cho vao bien tam
		//nam co so, ko co chu, khong co khoang trang
		cheDoNhap.coGhiSo = true;

		if (addHoaDon.ngayLap.nam == -1) {
			temp = "";
		}

		NhapThongTin(temp, 4, toaDoXNhapThongTin, toaDoY + xuongDong * 3, keyHit, cheDoNhap); //max nam la 4 so

		if (temp.length() == 0) {
			addHoaDon.ngayLap.nam = -1;
		}
		else {
			addHoaDon.ngayLap.nam = stoi(temp); //doi thanh int va gan lai

			//truong hop dac biet: rieng so nguyen va so thuc thi phai loai truong hop viet so 0 o dau
			gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 3);
			cout << CenterTextInSpace(" ", 4 + 2); //vi cai ham nay de viet trong border, nen +2 cho 2 gach 2 ben thi moi dung la khoang 4 phan tu
			gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 3);
			cout << to_string(addHoaDon.ngayLap.nam);
		}
		break;
	case OptionThemHoaDon::ThemLoai:
		int luaChon;
		char loaiHoaDonBanDau;

		loaiHoaDonBanDau = addHoaDon.loai;

		if (addHoaDon.loai == 'N') {
			luaChon = 0;
		}
		else {
			luaChon = 1;
		}

		Chon1Trong2(luaChon, "Nhap", "Xuat", toaDoXNhapThongTin, toaDoY + xuongDong * 4, keyHit);

		if (luaChon == 0) {
			addHoaDon.loai = 'N';
		}
		else {
			addHoaDon.loai = 'X';
		}

		if (flagDaQuyetDinhLoaiHoaDon == true && addHoaDon.loai != loaiHoaDonBanDau) { //da co chi tiet hoa don thi ko cho doi loai hoa don

			string thongBao[3] = { "Hoa don dang them da co chi tiet hoa don!", "Muon doi loai hoa don vui long xoa het chi tiet hoac tao hoa don moi!" };
			string options[3] = { "OK" };
			ClearWorkFrame();
			XuatOThongBao(thongBao, options, 1);

			keyHit = -1; //ve lai form INS
			ClearWorkFrame();
			WriteForm_INS(toaDoX, toaDoY, addHoaDon);

			addHoaDon.loai = loaiHoaDonBanDau;
		}
		break;
	default:
		break;
	}
}

void WriteForm_INS(int toaDoX, int toaDoY, HoaDon addHoaDon)
{
	int xuongDong = 2;
	int toaDoXNhapThongTin = toaDoX + 20;

	gotoxy(toaDoX, toaDoY);
	cout << "So Hoa Don: ";
	gotoxy(toaDoXNhapThongTin, toaDoY);
	cout << string(addHoaDon.soHoaDon);

	gotoxy(toaDoX, toaDoY + xuongDong * 1);
	cout << "Ngay: ";
	gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 1);
	if (addHoaDon.ngayLap.ngay == -1) {
		cout << "";
	}
	else {
		cout << to_string(addHoaDon.ngayLap.ngay);
	}

	gotoxy(toaDoX, toaDoY + xuongDong * 2);
	cout << "Thang: ";
	gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 2);
	if (addHoaDon.ngayLap.thang == -1) {
		cout << "";
	}
	else {
		cout << to_string(addHoaDon.ngayLap.thang);
	}

	gotoxy(toaDoX, toaDoY + xuongDong * 3);
	cout << "Nam: ";
	gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 3);
	if (addHoaDon.ngayLap.nam == -1) {
		cout << "";
	}
	else {
		cout << to_string(addHoaDon.ngayLap.nam);
	}

	gotoxy(toaDoX, toaDoY + xuongDong * 4);
	cout << "Loai: ";
	gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 4);
	if (addHoaDon.loai == 'N') {
		SetColor(Red);
		cout << "Nhap";
		SetColor(Black);
		cout << " | ";
		cout << "Xuat";
	}
	else {
		cout << "Nhap";
		cout << " | ";
		SetColor(Red);
		cout << "Xuat";
		SetColor(Black);
	}

	WriteTitle("THEM HOA DON");
}

void Keyhit_Move(ListHoaDon listHoaDon, PTRHoaDon& firstNode, PTRHoaDon& lastNode, PTRHoaDon& currentNode, int& trangHienTai, int keyhit)
{
	if (firstNode == NULL)
		return;
	if (keyhit == KEY_UP) {
		if (currentNode != firstNode) //khong phai nut dau 
		{
			currentNode = prevNode(firstNode, currentNode);
		}
		else if (currentNode == firstNode) //la nut dau thi cho thanh nut cuoi
		{
			currentNode = lastNode;
		}
	}
	else if (keyhit == KEY_DOWN) {
		if (currentNode != lastNode) //khong phai nut cuoi
		{
			currentNode = currentNode->next;
		}
		else if (currentNode == lastNode) //la nut cuoi thi cho thanh nut dau
		{
			currentNode = firstNode;
		}
	}
	else if (keyhit == KEY_RIGHT) {
		if (lastNode->next != NULL) // van con phan tu cho page sau
		{
			trangHienTai++;
			firstNode = lastNode->next;
			lastNode = endNode(firstNode);
			currentNode = firstNode;
		}
	}
	else if (keyhit == KEY_LEFT) {
		if (trangHienTai > 1) //ko phai page dau tien
		{
			currentNode = prevNode(listHoaDon.first, firstNode);
			TimTrangChuaCurrentNode(listHoaDon, firstNode, currentNode, lastNode, trangHienTai);
		}
	}
}

void Keyhit_INS(int keyHit, int toaDoXFormDSHD, int toaDoYFormDSHD, ListHoaDon& listHoaDon, PTRHoaDon& firstNode, PTRHoaDon& lastNode, PTRHoaDon& currentNode, int& trangHienTai, DSNhanVien dsNhanVien, ListVatTu& listVatTu, PTRVatTu& root)
{
	if (keyHit == INS) {
		HoaDon addHoaDon;
		bool flagDaQuyetDinhLoaiHoaDon = false; //Bien flagDaQuyetDinhLoaiHoaDon la de loai bo truong hop vi du la tu dau la nhap, cho nen ko xet so luong ton, tu nhien khi sua hoa don thanh xuat cai ko du so luong ton nhung da ghi chi tiet hoa don roi con dau
		KhoiTaoHoaDon(addHoaDon);

		OptionThemHoaDon optionThemHoaDon;
		optionThemHoaDon = OptionThemHoaDon::ThemSoHoaDon;

		bool flagThemThanhCong = false;

		ClearWorkFrame();

		int toaDoX = START_X_OF_MAIN_FRAME + 25 + 70; //toa do diem bat dau dong dau tien (Ma nhan vien: )
		int toaDoY = START_Y_OF_MAIN_FRAME + 20;
		WriteForm_INS(toaDoX, toaDoY, addHoaDon);

		keyHit = -1;
		while (true)
		{
			INS_Keyhit_Move_And_Enter(keyHit, optionThemHoaDon);
			INS_Keyhit_F1_ThemHoaDon(keyHit, addHoaDon, listHoaDon, flagThemThanhCong, toaDoX, toaDoY, firstNode, lastNode, currentNode, trangHienTai, dsNhanVien, listVatTu, root);
			INS_Keyhit_F2_XemDsCTHD(keyHit, addHoaDon, flagDaQuyetDinhLoaiHoaDon, toaDoX, toaDoY, listVatTu, root);

			//them thanh cong thi tro ve hien ds hoa don
			if (flagThemThanhCong) {
				ClearWorkFrame();
				DrawFormDSHoaDon(toaDoXFormDSHD, toaDoYFormDSHD);
				return;
			}
			//nut ESCape
			if (keyHit == ESC) {

				string thongBao[3] = { "Ban co muon huy viec them hoa don?", "xxxxxxxxxxxxxxxx" };
				string options[3] = { "Co", "Khong" };
				ClearWorkFrame();
				int luaChon = XuatOThongBao(thongBao, options, 2);
				if (luaChon == 0) {
					ClearWorkFrame();
					DrawFormDSHoaDon(toaDoXFormDSHD, toaDoYFormDSHD);
					return;
				}
				else {
					keyHit = -1;
					ClearWorkFrame();
					WriteForm_INS(toaDoX, toaDoY, addHoaDon);
				}
			}

			WriteSectionGuide("F1: them hoa don - F2: truy cap danh sach chi tiet hoa don - KEY_UP_DOWN: di chuyen len, xuong - ENTER: di chuyen xuong - ESC: thoat");

			INS_NhapThongTin(keyHit, optionThemHoaDon, addHoaDon, flagDaQuyetDinhLoaiHoaDon, toaDoX, toaDoY); //ham nay se thay doi gia tri keyHit va xuat ra thong tin moi bang ham NhapThongTin()
		}
	}
}

void Keyhit_Enter(int keyHit, int toaDoXFormDSHD, int toaDoYFormDSHD, ListHoaDon listHoaDon, PTRHoaDon currentNode)
{
	if (listHoaDon.first == NULL) {
		return;
	}
	if (keyHit == ENTER) {
		MainXemCTHD(currentNode->infoHoaDon);

		ClearWorkFrame();
		DrawFormDSHoaDon(toaDoXFormDSHD, toaDoYFormDSHD);
	}
}

void Output10Nodes(PTRHoaDon firstNode, PTRHoaDon lastNode, PTRHoaDon currentNode, int trangHienTai, int toaDoX, int toaDoY)
{
	if (firstNode == NULL) {
		return;
	}

	int dem = 0;
	for (PTRHoaDon run = firstNode; run != lastNode->next; run = run->next) { //de run != lastNode->next de van xu ly khi run = lastNode
		dem++;

		if (run == currentNode) {
			SetColor(Red);
		}

		gotoxy(toaDoX + 1, toaDoY + 1 + 2 * dem);
		cout << CenterTextInSpace(to_string(trangHienTai * 10 - 10 + dem), 32);

		gotoxy(toaDoX + 1 + 32 * 1, toaDoY + 1 + 2 * dem);
		cout << CenterTextInSpace(string(run->infoHoaDon.soHoaDon), 32);

		gotoxy(toaDoX + 1 + 32 * 2, toaDoY + 1 + 2 * dem);
		cout << CenterTextInSpace(OutputDate(run->infoHoaDon.ngayLap), 32);

		gotoxy(toaDoX + 1 + 32 * 3, toaDoY + 1 + 2 * dem);
		if (run->infoHoaDon.loai == 'N') {
			cout << CenterTextInSpace("Nhap", 32);
		}
		else {
			cout << CenterTextInSpace("Xuat", 32);
		}
		
		gotoxy(toaDoX + 1 + 32 * 4, toaDoY + 1 + 2 * dem);
		cout << CenterTextInSpace(to_string(TriGiaHoaDon(run->infoHoaDon.dsCTHD)), 32);

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
	cout << "Trang " << trangHienTai;
}

void DrawFormDSHoaDon(int toaDoX, int toaDoY)
{
	int soDong = 11;
	int soCot = 5;
	int doDaiNgang1Cot = 32;
	int doDaiDoc1Hang = 1;

	DrawBorderList(toaDoX, toaDoY, soDong, soCot, doDaiNgang1Cot, doDaiDoc1Hang);
	WriteTitle("DANH SACH HOA DON");

	SetColor(Green);

	gotoxy(toaDoX + 1, toaDoY + 1);
	cout << CenterTextInSpace("STT", doDaiNgang1Cot);
	gotoxy(toaDoX + 1 + doDaiNgang1Cot * 1, toaDoY + 1);
	cout << CenterTextInSpace("SO HOA DON", doDaiNgang1Cot);
	gotoxy(toaDoX + 1 + doDaiNgang1Cot * 2, toaDoY + 1);
	cout << CenterTextInSpace("NGAY LAP", doDaiNgang1Cot);
	gotoxy(toaDoX + 1 + doDaiNgang1Cot * 3, toaDoY + 1);
	cout << CenterTextInSpace("LOAI", doDaiNgang1Cot);
	gotoxy(toaDoX + 1 + doDaiNgang1Cot * 4, toaDoY + 1);
	cout << CenterTextInSpace("TRI GIA", doDaiNgang1Cot);

	SetColor(Black);
}

void MainDanhSachHoaDon(ListHoaDon& listHoaDon, DSNhanVien dsNhanVien, ListVatTu& listVatTu, PTRVatTu& root)
{
	PTRHoaDon firstNode, lastNode, currentNode;
	firstNode = currentNode = listHoaDon.first;
	lastNode = endNode(firstNode);

	int trangHienTai = 1;

	int keyHit = -1;

	//toa do diem bat dau ve khung
	int toaDoX = START_X_OF_MAIN_FRAME + 25 + 8;
	int toaDoY = START_Y_OF_MAIN_FRAME + 18;
	DrawFormDSHoaDon(toaDoX, toaDoY);

	while (true) {
		if (keyHit == 224)
			keyHit = _getch();
		if (keyHit == 0)
			keyHit = _getch();

		//cac nut 
		Keyhit_Move(listHoaDon, firstNode, lastNode, currentNode, trangHienTai, keyHit);
		Keyhit_INS(keyHit, toaDoX, toaDoY, listHoaDon, firstNode, lastNode, currentNode, trangHienTai, dsNhanVien, listVatTu, root);
		Keyhit_Enter(keyHit, toaDoX, toaDoY, listHoaDon, currentNode);
		if (keyHit == ESC) {
			return;
		}
		//

		Output10Nodes(firstNode, lastNode, currentNode, trangHienTai, toaDoX, toaDoY);
		WriteSectionGuide("ENTER: xem hoa don - INS: them hoa don - KEY_UP_DOWN: di chuyen len, xuong - KEY_LEFT_RIGHT: lui trang, sang trang - ESC: thoat");


		keyHit = _getch();
	}
}

void WriteForm_TimKiemHoaDon(int toaDoX, int toaDoY, char findSoHoaDon[])
{
	int toaDoXNhapThongTin = toaDoX + 20;

	gotoxy(toaDoX, toaDoY);
	cout << "So hoa don: ";
	gotoxy(toaDoXNhapThongTin, toaDoY);
	cout << string(findSoHoaDon);

	WriteTitle("IN HOA DON");
}

void MainXemHoaDon(DSNhanVien dsNhanVien)
{
	char findSoHoaDon[MAX_MA_VAT_TU];
	findSoHoaDon[0] = '\0';
	string temp; // bien nay de nhap thong tin
	//so hoa don thi co chu, co so, chu ghi hoa full, va khong co khoang trang
	CheDoNhap cheDoNhap;
	cheDoNhap.coGhiChu = true;
	cheDoNhap.coGhiHoaFull = true;
	cheDoNhap.coGhiSo = true;

	int toaDoX = START_X_OF_MAIN_FRAME + 25 + 70; //toa do diem bat dau dong dau tien (So hoa don: )
	int toaDoY = START_Y_OF_MAIN_FRAME + 20;
	int toaDoXNhapThongTin = toaDoX + 20;

	ClearWorkFrame();
	WriteForm_TimKiemHoaDon(toaDoX, toaDoY, findSoHoaDon);

	int keyHit = -1;
	while (true)
	{
		if (keyHit == ENTER) {
			PTRHoaDon nodeTimKiem = TimKiemHoaDon(dsNhanVien, findSoHoaDon);

			if (nodeTimKiem != NULL) { //tim thay hoa don
				MainXemCTHD(nodeTimKiem->infoHoaDon);
				
				findSoHoaDon[0] = '\0'; //reset so hoa don dang kiem
				
				keyHit = -1;
				ClearWorkFrame();
				WriteForm_TimKiemHoaDon(toaDoX, toaDoY, findSoHoaDon);
			}
			else { //ko tim thay hoa don
				string thongBao[3] = { "Hoa don tim kiem khong ton tai!", "xxxxxxxxxxxxxxxx" };
				string options[3] = { "Dong y" };
				ClearWorkFrame();
				XuatOThongBao(thongBao, options, 1);

				keyHit = -1;
				ClearWorkFrame();
				WriteForm_TimKiemHoaDon(toaDoX, toaDoY, findSoHoaDon);
			}
		}

		//nut ESCape
		if (keyHit == ESC) {
			return;
		}

		WriteSectionGuide("ENTER: xem hoa don - ESC: thoat");

		temp = string(findSoHoaDon);
		NhapThongTin(temp, MAX_MA_VAT_TU - 1, toaDoXNhapThongTin, toaDoY, keyHit, cheDoNhap);
		strcpy(findSoHoaDon, temp.c_str());
	}
}

void MainTraHangHoaDon(DSNhanVien& dsNhanVien)
{
	char findSoHoaDon[MAX_MA_VAT_TU];
	findSoHoaDon[0] = '\0';
	string temp; // bien nay de nhap thong tin
	//so hoa don thi co chu, co so, chu ghi hoa full, va khong co khoang trang
	CheDoNhap cheDoNhap;
	cheDoNhap.coGhiChu = true;
	cheDoNhap.coGhiHoaFull = true;
	cheDoNhap.coGhiSo = true;

	int toaDoX = START_X_OF_MAIN_FRAME + 25 + 70; //toa do diem bat dau dong dau tien (So hoa don: )
	int toaDoY = START_Y_OF_MAIN_FRAME + 20;
	int toaDoXNhapThongTin = toaDoX + 20;

	ClearWorkFrame();
	WriteForm_TimKiemHoaDon(toaDoX, toaDoY, findSoHoaDon);

	int keyHit = -1;
	while (true)
	{
		if (keyHit == ENTER) {
			PTRHoaDon nodeTimKiem = NULL;
			//ListHoaDon listHoaDonTimKiem; //tu dau lam cach nay nhung sai, vi day la 2 con tro moi, listHoaDonTimKiem cap nhat duoc nhung ds hoa don chinh ko cap nhat duoc
			int indexNhanVienCuaHoaDon;

			bool daTimThay = false;
			for (int i = 0; i < dsNhanVien.soLuongNhanVien; i++) {//duyet tung nhan vien

				for (PTRHoaDon run = dsNhanVien.nodesNhanVien[i]->listHoaDon.first; run != NULL; run = run->next) { //duyet tung hoa don nhan vien do

					if (strcmp(run->infoHoaDon.soHoaDon, findSoHoaDon) == 0) {
						nodeTimKiem = run;
						indexNhanVienCuaHoaDon = i;
						//listHoaDonTimKiem = dsNhanVien.nodesNhanVien[i]->listHoaDon;
						daTimThay = true;
						break;
					}
				}

				if (daTimThay) {
					break;
				}
			}

			if (nodeTimKiem != NULL) { //tim thay hoa don
				//MainTraHangCTHD(listHoaDonTimKiem, nodeTimKiem->infoHoaDon);
				MainTraHangCTHD(dsNhanVien.nodesNhanVien[indexNhanVienCuaHoaDon]->listHoaDon, nodeTimKiem->infoHoaDon);

				findSoHoaDon[0] = '\0'; //reset so hoa don dang kiem

				keyHit = -1;
				ClearWorkFrame();
				WriteForm_TimKiemHoaDon(toaDoX, toaDoY, findSoHoaDon);
			}
			else { //ko tim thay hoa don
				string thongBao[3] = { "Hoa don tim kiem khong ton tai!", "xxxxxxxxxxxxxxxx" };
				string options[3] = { "Dong y" };
				ClearWorkFrame();
				XuatOThongBao(thongBao, options, 1);

				keyHit = -1;
				ClearWorkFrame();
				WriteForm_TimKiemHoaDon(toaDoX, toaDoY, findSoHoaDon);
			}
		}

		//nut ESCape
		if (keyHit == ESC) {
			return;
		}

		WriteSectionGuide("ENTER: truy cap hoa don - ESC: thoat");

		temp = string(findSoHoaDon);
		NhapThongTin(temp, MAX_MA_VAT_TU - 1, toaDoXNhapThongTin, toaDoY, keyHit, cheDoNhap);
		strcpy(findSoHoaDon, temp.c_str());
	}
}
