#include "DanhSachVatTu.h"

PTRVatTu2 endNode(PTRVatTu2 firstNode)
{
	if (firstNode == NULL)
		return NULL;
	PTRVatTu2 run = firstNode;
	//moi vao i = 0, ko lam gi ca, sau do i = 1 thi run da la phan tu sau first (phan tu thu 2), nhu vay i = 9 (dieu kien ket thuc vong lap) thi run la phan tu thu 10
	for (int i = 0; i < 9 && run->right != NULL; i++, run = run->right); //run -> right != NULL de ko bi chay lo them dong run = run -> right, thi no moi return node last duoc, no se tra ve phan tu truoc NULL neu ma ko du 10 phan tu
	return run;
}

PTRVatTu2 startNode(PTRVatTu2 lastNode)//ham nay su dung khi chac chan last node ko nam o trang dau, tu do lui 10 phan tu ko lo loi
{
	PTRVatTu2 run = lastNode;
	for (int i = 0; i < 9; i++, run = run->left); 
	return run;
}

void KhoiTaoVatTu(char addMaVatTu[], VatTu& addVatTu)
{
	addMaVatTu[0] = '\0';
	addVatTu.tenVatTu[0] = '\0';
	addVatTu.donViTinh[0] = '\0';
	addVatTu.soLuongTon = -1;
}

void VatTucpy(PTRVatTu& p1, PTRVatTu p2) //tao vung nho cho p1 sau do chi copy thong tin vat tu p2 cho p1, ko copy con tro
{
	if (p1 == NULL) { //neu p1 chua co vung nho thi khoi tao cho no 1 vung nho moi
		p1 = new NodeVatTu;
		p1->left = NULL;
		p1->right = NULL;
	}
	//copy thong tin
	strcpy(p1->maVatTu, p2->maVatTu);
	p1->infoVatTu = p2->infoVatTu;
}

void CapNhatMaVatTuMoiCuaCTHD(PTRVatTu oldInfo, PTRVatTu newInfo, DSNhanVien& dsNhanVien)
{
	for (int i = 0; i < dsNhanVien.soLuongNhanVien; i++) { //ktra tung nhan vien
		
		for (PTRHoaDon run = dsNhanVien.nodesNhanVien[i]->listHoaDon.first; run != NULL; run = run->next) { //kiem tra tung hoa don cua nhan vien do

			for (int j = 0; j < run->infoHoaDon.dsCTHD.soLuongVatTu; j++) {//kiem tra tung cthd cua hoa don do

				if (strcmp(run->infoHoaDon.dsCTHD.nodesCTHD[j].maVatTu, oldInfo->maVatTu) == 0) {

					strcpy(run->infoHoaDon.dsCTHD.nodesCTHD[j].maVatTu, newInfo->maVatTu);
					break; //1 ds cthd chi co 1 vat tu cung info nen break o day luon, qua xet hoa don moi
				}
			}
		}
	}
}

int KiemTraVatTuRong(char addMaVatTu[], VatTu addVatTu)
{
	if (string(addMaVatTu).length() == 0) {
		return 1;
	}
	else if (string(addVatTu.tenVatTu).length() == 0) {
		return 2;
	}
	else if (string(addVatTu.donViTinh).length() == 0) {
		return 3;
	}
	else if (addVatTu.soLuongTon == -1) {
		return 4;
	}
	return 0;
}

int KiemTraVatTuTrung(char addMaVatTu[], PTRVatTu root)
{
	if (TimKiemVatTu(root, addMaVatTu) == NULL) {
		return 0;
	}
	return 1;
}

int KiemTraVatTuTrung_CaseSuaVatTu(char fixingMaVatTu[], PTRVatTu2 currentNode, PTRVatTu root)
{
	if (strcmp(fixingMaVatTu, currentNode->maVatTu) != 0) { //chi xet trung khi ma vat tu cua fixing bi thay doi
		if (TimKiemVatTu(root, fixingMaVatTu) != NULL) { //trung ma vat tu
			return 1;
		}
	}
	return 0;
}

void TimTrangChuaCurrentNode(ListVatTu listVatTu, PTRVatTu2& firstNode, PTRVatTu2& lastNode, PTRVatTu2 currentNode, int& trangHienTai)
{
	int dem = 0;
	PTRVatTu2 run = listVatTu.first;
	firstNode = listVatTu.first;
	lastNode = endNode(firstNode);
	trangHienTai = 1;

	while (run != currentNode) {
		run = run->right;
		dem++;
		if (dem == 10) { //0 -> 9 la du 10 phan tu, dem = 10 la dang o phan tu thu 11 thi gan lai cac gia tri
			dem = 0;
			firstNode = run;
			lastNode = endNode(firstNode);
			trangHienTai++;
		}
	}
}

void ENTER_Keyhit_F1_SuaVatTu(int keyHit, ListVatTu& listVatTu, PTRVatTu& root, PTRVatTu2& firstNode, PTRVatTu2& lastNode, PTRVatTu2& currentNode, int& trangHienTai, bool& isSuaVatTuAndSucceeds, DSNhanVien dsNhanVien)
{
	if (keyHit == F1) {
	
		PTRVatTu fixingVatTu = NULL;
		VatTucpy(fixingVatTu, currentNode->nodeTreeVatTu);

		OptionThemVatTu optionThemVatTu;
		optionThemVatTu = OptionThemVatTu::ThemMaVatTu;

		bool flagSuaThanhCong = false;

		int toaDoX = START_X_OF_MAIN_FRAME + 25 + 70; //toa do diem bat dau dong dau tien (Ma vat tu: )
		int toaDoY = START_Y_OF_MAIN_FRAME + 20;

		ClearWorkFrame();
		WriteForm_INS(toaDoX, toaDoY, fixingVatTu->maVatTu, fixingVatTu->infoVatTu);
		WriteTitle("SUA VAT TU");

		keyHit = -1;
		while (true)
		{
			ENTER_Keyhit_F1_Keyhit_Move_And_Enter(keyHit, optionThemVatTu); //lam ham moi, ko dc sua so luong ton
			ENTER_Keyhit_F1_Keyhit_F1_SuaVatTu(keyHit, fixingVatTu, listVatTu, root, flagSuaThanhCong, toaDoX, toaDoY, firstNode, lastNode, currentNode, trangHienTai, dsNhanVien);

			//sua thanh cong
			if (flagSuaThanhCong) {
				isSuaVatTuAndSucceeds = true;
				return;
			}
			//nut ESCape
			if (keyHit == ESC) {

				string thongBao[3] = { "Ban co muon huy viec sua vat tu?", "xxxxxxxxxxxxxxxx" };
				string options[3] = { "Co", "Khong" };
				ClearWorkFrame();
				int luaChon = XuatOThongBao(thongBao, options, 2);
				if (luaChon == 0) { //huy viec sua
					ClearWorkFrame();
					WriteForm_INS(toaDoX, toaDoY, currentNode->maVatTu, currentNode->nodeTreeVatTu->infoVatTu);
					WriteTitle("XEM VAT TU");
					return;
				}
				else {
					keyHit = -1;
					ClearWorkFrame();
					WriteForm_INS(toaDoX, toaDoY, fixingVatTu->maVatTu, fixingVatTu->infoVatTu);
					WriteTitle("SUA VAT TU");
				}
			}

			WriteSectionGuide("F1: xac nhan sua - KEY_UP_DOWN: di chuyen len, xuong - ESC: thoat");

			INS_NhapThongTin(keyHit, optionThemVatTu, fixingVatTu->maVatTu, fixingVatTu->infoVatTu, toaDoX, toaDoY); //ham nay se thay doi gia tri keyHit va xuat ra thong tin moi bang ham NhapThongTin()
		}
	}
}

void ENTER_Keyhit_F1_Keyhit_F1_SuaVatTu(int keyHit, PTRVatTu fixingVatTu, ListVatTu& listVatTu, PTRVatTu& root, bool& flagSuaThanhCong, int toaDoX, int toaDoY, PTRVatTu2& firstNode, PTRVatTu2& lastNode, PTRVatTu2& currentNode, int& trangHienTai, DSNhanVien dsNhanVien)
{
	if (keyHit == F1) {
		int kiemTraRong = KiemTraVatTuRong(fixingVatTu->maVatTu, fixingVatTu->infoVatTu);

		if (kiemTraRong == 0) { //ko rong
			int kiemTraTrung = KiemTraVatTuTrung_CaseSuaVatTu(fixingVatTu->maVatTu, currentNode, root);

			if (kiemTraTrung == 0) { //ko trung
				string thongBao[3] = { "Thong tin cua vat tu hop le!", "Ban co chac chan muon sua vat tu?" };
				string options[3] = { "Dong y", "Huy" };
				ClearWorkFrame();

				int luaChon = XuatOThongBao(thongBao, options, 2);

				if (luaChon == 0) {
				
					if (strcmp(fixingVatTu->maVatTu, currentNode->maVatTu) == 0) { //neu nhu ko sua ma vat tu thi don gian chi la copy thong tin
						VatTucpy(currentNode->nodeTreeVatTu, fixingVatTu);
						flagSuaThanhCong = true;
					}
					else { //con khong thi phai xoa ca trong tree va ca trong double linked list, boi vi ma vat tu thay doi thi vi tri cung thay doi
						CapNhatMaVatTuMoiCuaCTHD(currentNode->nodeTreeVatTu, fixingVatTu, dsNhanVien); //cthd chi trung ma vat tu voi vat tu, nen chi can cap nhat ma vat tu cua nhung hoa don co vat tu cu

						char deleteKey[MAX_MA_VAT_TU];
						strcpy(deleteKey, currentNode->maVatTu); //tu dau ko dung bien nay, dung han currentNode->maVatTu co 2 ham duoi, bi loi, vi ham 1 xoa luon current node luon roi, ham 2 ko co gi xai

						char maVatTuThayDoiVungNho[MAX_MA_VAT_TU]; //boi vi double linked list phan gia tri la vung nho cua tree, khi xoa delete case 3, vung nho node bi xoa la node tan cung ben trai cua cay con ben phai cua node can xoa (copy gia tri tu node tan cung ben trai vo cho node can xoa, roi xoa node con tan cung ben trai do) chu khong phai la vung nho node can xoa, vay nen vung nho moi cua node tree tan cung ben trai do trong double linked list se la vung nho cua "node tree can xoa ban dau"
						maVatTuThayDoiVungNho[0] = '\0';

						DeleteTree(root, deleteKey, maVatTuThayDoiVungNho); //xoa o tree
						if (string(maVatTuThayDoiVungNho).length() != 0) { //neu nhu la delete case 3
							PTRVatTu2 run = listVatTu.first;
							while (strcmp(run->maVatTu, maVatTuThayDoiVungNho) != 0)
							{
								run = run->right;
							}
							run->nodeTreeVatTu = TimKiemVatTu(root, maVatTuThayDoiVungNho);
						}
						DeleteInfo(listVatTu, deleteKey); //xoa o double linked list

						PTRVatTu nodeVuaThem = InsertTree(root, fixingVatTu->maVatTu, fixingVatTu->infoVatTu); //them o tree
						currentNode = InsertOrder(listVatTu, nodeVuaThem); //them o double linked list

						TimTrangChuaCurrentNode(listVatTu, firstNode, lastNode, currentNode, trangHienTai);
						flagSuaThanhCong = true;
					}
				}
				else {
					keyHit = -1; //tru truong hop sua thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
					ClearWorkFrame();
					WriteForm_INS(toaDoX, toaDoY, fixingVatTu->maVatTu, fixingVatTu->infoVatTu);
					WriteTitle("SUA VAT TU");
				}
			}
			else { //bi trung

				string thongBao[3] = { "Vat tu dang them khong hop le!", "Ma vat tu bi trung!" };
				string options[3] = { "OK" };
				ClearWorkFrame();
				XuatOThongBao(thongBao, options, 1);

				keyHit = -1; //tru truong hop sua thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
				ClearWorkFrame();
				WriteForm_INS(toaDoX, toaDoY, fixingVatTu->maVatTu, fixingVatTu->infoVatTu);
				WriteTitle("SUA VAT TU");
			}
		}
		else { //bi rong
			string thongBaoLoi;

			switch (kiemTraRong) //ko co case 4 vi khi sua vat tu so luong ton khong duoc sua, co san gia tri cu nen ko the rong
			{
			case 1:
				thongBaoLoi = "Ma vat tu rong!";
				break;
			case 2:
				thongBaoLoi = "Ten vat tu rong!";
				break;
			case 3:
				thongBaoLoi = "Don vi tinh rong!";
				break;
			default:
				break;
			}

			string thongBao[3] = { "Vat tu dang them khong hop le!", thongBaoLoi };
			string options[3] = { "OK" };
			ClearWorkFrame();
			XuatOThongBao(thongBao, options, 1);

			keyHit = -1; //tru truong hop sua thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
			ClearWorkFrame();
			WriteForm_INS(toaDoX, toaDoY, fixingVatTu->maVatTu, fixingVatTu->infoVatTu);
			WriteTitle("SUA VAT TU");
		}
	}
}

void ENTER_Keyhit_F1_Keyhit_Move_And_Enter(int keyHit, OptionThemVatTu& optionThemVatTu)
{
	if (keyHit == KEY_UP) {
		switch (optionThemVatTu)
		{
		case OptionThemVatTu::ThemMaVatTu:
			optionThemVatTu = OptionThemVatTu::ThemDonViTinh;
			break;
		case OptionThemVatTu::ThemTenVatTu:
			optionThemVatTu = OptionThemVatTu::ThemMaVatTu;
			break;
		case OptionThemVatTu::ThemDonViTinh:
			optionThemVatTu = OptionThemVatTu::ThemTenVatTu;
			break;
		default:
			break;
		}
	}
	else if (keyHit == KEY_DOWN || keyHit == ENTER) {
		switch (optionThemVatTu)
		{
		case OptionThemVatTu::ThemMaVatTu:
			optionThemVatTu = OptionThemVatTu::ThemTenVatTu;
			break;
		case OptionThemVatTu::ThemTenVatTu:
			optionThemVatTu = OptionThemVatTu::ThemDonViTinh;
			break;
		case OptionThemVatTu::ThemDonViTinh:
			optionThemVatTu = OptionThemVatTu::ThemMaVatTu;
			break;
		default:
			break;
		}
	}
}

void INS_Keyhit_F1_ThemVatTu(int keyHit, char addMaVatTu[], VatTu addVatTu, ListVatTu& listVatTu, PTRVatTu& root, bool& flagThemVatTu, int toaDoX, int toaDoY, PTRVatTu2& firstNode, PTRVatTu2& lastNode, PTRVatTu2& currentNode, int& trangHienTai)
{
	if (keyHit == F1) {
		int kiemTraRong = KiemTraVatTuRong(addMaVatTu, addVatTu);

		if (kiemTraRong == 0) { //ko rong
			int kiemTraTrung = KiemTraVatTuTrung(addMaVatTu, root);

			if (kiemTraTrung == 0) { //ko trung

				string thongBao[3] = { "Thong tin cua vat tu hop le!", "Ban co chac chan muon them vat tu?" };
				string options[3] = { "Dong y", "Huy" };
				ClearWorkFrame();

				int luaChon = XuatOThongBao(thongBao, options, 2);

				if (luaChon == 0) { //dong y them
					PTRVatTu nodeTreeVatTu = InsertTree(root, addMaVatTu, addVatTu);
					PTRVatTu2 nodeDSLienKetKepVatTu = InsertOrder(listVatTu, nodeTreeVatTu);
					
					flagThemVatTu = true;
					currentNode = nodeDSLienKetKepVatTu;
					TimTrangChuaCurrentNode(listVatTu, firstNode, lastNode, currentNode, trangHienTai);
				}
				else { //huy viec them
					keyHit = -1; //tru truong hop them thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
					ClearWorkFrame();
					WriteForm_INS(toaDoX, toaDoY, addMaVatTu, addVatTu);
				}
			}
			else { //loi bi trung vat tu
				string thongBaoLoi;
				thongBaoLoi = "Ma vat tu bi trung!";

				string thongBao[3] = { "Vat tu dang them khong hop le!", thongBaoLoi };
				string options[3] = { "OK" };
				ClearWorkFrame();
				XuatOThongBao(thongBao, options, 1);

				keyHit = -1; //tru truong hop them thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
				ClearWorkFrame();
				WriteForm_INS(toaDoX, toaDoY, addMaVatTu, addVatTu);
			}
		}
		else { //loi bi rong vat tu
			string thongBaoLoi;

			switch (kiemTraRong) 
			{
			case 1:
				thongBaoLoi = "Ma vat tu rong!";
				break;
			case 2:
				thongBaoLoi = "Ten vat tu rong!";
				break;
			case 3:
				thongBaoLoi = "Don vi tinh rong!";
				break;
			case 4:
				thongBaoLoi = "So luong ton rong!";
				break;
			default:
				break;
			}

			string thongBao[3] = { "Vat tu dang them khong hop le!", thongBaoLoi };
			string options[3] = { "OK" };
			ClearWorkFrame();
			XuatOThongBao(thongBao, options, 1);

			keyHit = -1; //tru truong hop them thanh cong thi tat ca cac truong hop con lai phai ve lai form INS
			ClearWorkFrame();
			WriteForm_INS(toaDoX, toaDoY, addMaVatTu, addVatTu);
		}
	}
}

void INS_Keyhit_Move_And_Enter(int keyHit, OptionThemVatTu& optionThemVatTu)
{
	if (keyHit == KEY_UP) {
		switch (optionThemVatTu)
		{
		case OptionThemVatTu::ThemMaVatTu:
			optionThemVatTu = OptionThemVatTu::ThemSoLuongTon;
			break;
		case OptionThemVatTu::ThemTenVatTu:
			optionThemVatTu = OptionThemVatTu::ThemMaVatTu;
			break;
		case OptionThemVatTu::ThemDonViTinh:
			optionThemVatTu = OptionThemVatTu::ThemTenVatTu;
			break;
		case OptionThemVatTu::ThemSoLuongTon:
			optionThemVatTu = OptionThemVatTu::ThemDonViTinh;
			break;
		default:
			break;
		}
	}
	else if (keyHit == KEY_DOWN || keyHit == ENTER) {
		switch (optionThemVatTu)
		{
		case OptionThemVatTu::ThemMaVatTu:
			optionThemVatTu = OptionThemVatTu::ThemTenVatTu;
			break;
		case OptionThemVatTu::ThemTenVatTu:
			optionThemVatTu = OptionThemVatTu::ThemDonViTinh;
			break;
		case OptionThemVatTu::ThemDonViTinh:
			optionThemVatTu = OptionThemVatTu::ThemSoLuongTon;
			break;
		case OptionThemVatTu::ThemSoLuongTon:
			optionThemVatTu = OptionThemVatTu::ThemMaVatTu;
			break;
		default:
			break;
		}
	}
}

void INS_NhapThongTin(int& keyHit, OptionThemVatTu optionThemVatTu, char addMaVatTu[], VatTu& addVatTu, int toaDoX, int toaDoY)
{
	string temp;
	CheDoNhap cheDoNhap;

	int toaDoXNhapThongTin = toaDoX + 20;
	int xuongDong = 2;

	switch (optionThemVatTu)
	{
	case OptionThemVatTu::ThemMaVatTu:
		temp = string(addMaVatTu);

		//so hoa don co chu, co so, ghi hoa full, ko co khoang trang
		cheDoNhap.coGhiChu = true;
		cheDoNhap.coGhiSo = true;
		cheDoNhap.coGhiHoaFull = true;

		NhapThongTin(temp, MAX_MA_VAT_TU - 1, toaDoXNhapThongTin, toaDoY + xuongDong * 0, keyHit, cheDoNhap);

		strcpy(addMaVatTu, temp.c_str()); 
		break;
	case OptionThemVatTu::ThemTenVatTu:
		temp = string(addVatTu.tenVatTu);

		//ten vat tu co chu, co so,co khoang trang, ghi hoa chu cai dau
		cheDoNhap.coGhiChu = true;
		cheDoNhap.coGhiSo = true;
		cheDoNhap.coKhoangTrang = true;

		NhapThongTin(temp, 30, toaDoXNhapThongTin, toaDoY + xuongDong * 1, keyHit, cheDoNhap); //chi cho nhap toi da 30 ki tu, cho du mang cua no toi da 50 ki tu, boi 1 o border co chieu dai la 32

		strcpy(addVatTu.tenVatTu, temp.c_str());
		break;
	case OptionThemVatTu::ThemDonViTinh:
		temp = string(addVatTu.donViTinh);

		//don vi tinh co chu, co so,co khoang trang, ghi hoa chu cai dau
		cheDoNhap.coGhiChu = true;
		cheDoNhap.coGhiSo = true;
		cheDoNhap.coKhoangTrang = true;

		NhapThongTin(temp, MAX_DON_VI_TINH - 1, toaDoXNhapThongTin, toaDoY + xuongDong * 2, keyHit, cheDoNhap);

		strcpy(addVatTu.donViTinh, temp.c_str());
		break;
	case OptionThemVatTu::ThemSoLuongTon:
		temp = FloatToString(addVatTu.soLuongTon); //cho vao bien tam
		//so luong la so thuc

		if (addVatTu.soLuongTon == -1) {
			temp = "";
		}

		NhapSoThuc(temp, MAX_FLOAT, toaDoXNhapThongTin, toaDoY + xuongDong * 3, keyHit);

		if (temp.length() == 0) {
			addVatTu.soLuongTon = -1;
		}
		else {
			addVatTu.soLuongTon = stof(temp); //doi thanh float va gan lai

			//truong hop dac biet: rieng so nguyen va so thuc thi phai loai truong hop viet so 0 o dau
			gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 3);
			cout << CenterTextInSpace(" ", MAX_FLOAT + 2); //vi cai ham nay de viet trong border, nen +2 cho 2 gach 2 ben thi moi dung la khoang MAX_FLOAT phan tu
			gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 3);
			cout << FloatToString(addVatTu.soLuongTon);
		}
		break;
	default:
		break;
	}
}

void WriteForm_INS(int toaDoX, int toaDoY, char addMaVatTu[], VatTu addVatTu)
{
	int xuongDong = 2;
	int toaDoXNhapThongTin = toaDoX + 20;

	gotoxy(toaDoX, toaDoY);
	cout << "Ma vat tu: ";
	gotoxy(toaDoXNhapThongTin, toaDoY);
	cout << string(addMaVatTu);

	gotoxy(toaDoX, toaDoY + xuongDong * 1);
	cout << "Ten vat tu: ";
	gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 1);
	cout << string(addVatTu.tenVatTu);

	gotoxy(toaDoX, toaDoY + xuongDong * 2);
	cout << "Don vi tinh: ";
	gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 2);
	cout << string(addVatTu.donViTinh);

	gotoxy(toaDoX, toaDoY + xuongDong * 3);
	cout << "So luong ton: ";
	gotoxy(toaDoXNhapThongTin, toaDoY + xuongDong * 3);
	if (addVatTu.soLuongTon == -1) {
		cout << "";
	}
	else {
		cout << FloatToString(addVatTu.soLuongTon);
	}

	WriteTitle("THEM VAT TU");
}

void Keyhit_Move(ListVatTu listVatTu, PTRVatTu2& firstNode, PTRVatTu2& lastNode, PTRVatTu2& currentNode, int& trangHienTai, int keyhit)
{
	if (firstNode == NULL)
		return;
	if (keyhit == KEY_UP) {
		if (currentNode != firstNode) //khong phai nut dau 
		{
			currentNode = currentNode->left;
		}
		else if (currentNode == firstNode) //la nut dau thi cho thanh nut cuoi
		{
			currentNode = lastNode;
		}
	}
	else if (keyhit == KEY_DOWN) {
		if (currentNode != lastNode) //khong phai nut cuoi
		{
			currentNode = currentNode->right;
		}
		else if (currentNode == lastNode) //la nut cuoi thi cho thanh nut dau
		{
			currentNode = firstNode;
		}
	}
	else if (keyhit == KEY_RIGHT) {
		if (lastNode->right != NULL) // van con phan tu cho page sau
		{
			trangHienTai++;
			firstNode = lastNode->right;
			lastNode = endNode(firstNode);
			currentNode = firstNode;
		}
	}
	else if (keyhit == KEY_LEFT) {
		if (trangHienTai > 1) //ko phai page dau tien
		{
			trangHienTai--;
			lastNode = firstNode->left;
			firstNode = startNode(lastNode);
			currentNode = firstNode;
		}
	}
}

void Keyhit_INS(int keyHit, int toaDoXFormDSVatTu, int toaDoYFormDSVatTu, ListVatTu& listVatTu, PTRVatTu& root, PTRVatTu2& firstNode, PTRVatTu2& lastNode, PTRVatTu2& currentNode, int& trangHienTai)
{
	if (keyHit == INS) {
		char addMaVatTu[MAX_MA_VAT_TU];
		VatTu addVatTu;
		KhoiTaoVatTu(addMaVatTu, addVatTu);

		OptionThemVatTu optionThemVatTu;
		optionThemVatTu = OptionThemVatTu::ThemMaVatTu;

		bool flagThemThanhCong = false;

		ClearWorkFrame();

		int toaDoX = START_X_OF_MAIN_FRAME + 25 + 70; //toa do diem bat dau dong dau tien (Ma vat tu: )
		int toaDoY = START_Y_OF_MAIN_FRAME + 20;
		WriteForm_INS(toaDoX, toaDoY, addMaVatTu, addVatTu);

		keyHit = -1;
		while (true)
		{
			INS_Keyhit_Move_And_Enter(keyHit, optionThemVatTu);
			INS_Keyhit_F1_ThemVatTu(keyHit, addMaVatTu, addVatTu, listVatTu, root, flagThemThanhCong, toaDoX, toaDoY, firstNode, lastNode, currentNode, trangHienTai);

			//them thanh cong thi tro ve hien ds vat tu
			if (flagThemThanhCong) {
				ClearWorkFrame();
				DrawFormDSVatTu(toaDoXFormDSVatTu, toaDoYFormDSVatTu);
				return;
			}
			//nut ESCape
			if (keyHit == ESC) {

				string thongBao[3] = { "Ban co muon huy viec them vat tu?", "xxxxxxxxxxxxxxxx" };
				string options[3] = { "Co", "Khong" };
				ClearWorkFrame();
				int luaChon = XuatOThongBao(thongBao, options, 2);
				if (luaChon == 0) {
					ClearWorkFrame();
					DrawFormDSVatTu(toaDoXFormDSVatTu, toaDoYFormDSVatTu);
					return;
				}
				else {
					keyHit = -1;
					ClearWorkFrame();
					WriteForm_INS(toaDoX, toaDoY, addMaVatTu, addVatTu);
				}
			}

			WriteSectionGuide("F1: xac nhan them vat tu - KEY_UP_DOWN: di chuyen len xuong - ENTER: di chuyen xuong - ESC: thoat");

			INS_NhapThongTin(keyHit, optionThemVatTu, addMaVatTu, addVatTu, toaDoX, toaDoY); //ham nay se thay doi gia tri keyHit va xuat ra thong tin moi bang ham NhapThongTin()
		}
	}
}

void Keyhit_Enter(int keyHit, int toaDoXFormDSVatTu, int toaDoYFormDSVatTu, ListVatTu& listVatTu, PTRVatTu& root, PTRVatTu2& firstNode, PTRVatTu2& lastNode, PTRVatTu2& currentNode, int& trangHienTai, DSNhanVien dsNhanVien)
{
	if (listVatTu.first == NULL) {
		return;
	}
	if (keyHit == ENTER) {
		int toaDoX = START_X_OF_MAIN_FRAME + 25 + 70; //toa do diem bat dau dong dau tien (Ma vat tu: )
		int toaDoY = START_Y_OF_MAIN_FRAME + 20;

		ClearWorkFrame();
		WriteForm_INS(toaDoX, toaDoY, currentNode->maVatTu, currentNode->nodeTreeVatTu->infoVatTu);
		WriteTitle("XEM VAT TU");

		bool isSuaVatTuAndSucceed = false;

		keyHit = -1;
		while (true)
		{
			if (keyHit == 224)
				keyHit = _getch();
			if (keyHit == 0)
				keyHit = _getch();

			//cac nut
			ENTER_Keyhit_F1_SuaVatTu(keyHit, listVatTu,root, firstNode, lastNode, currentNode, trangHienTai, isSuaVatTuAndSucceed, dsNhanVien);

			if (isSuaVatTuAndSucceed) {
				ClearWorkFrame();
				DrawFormDSVatTu(toaDoXFormDSVatTu, toaDoYFormDSVatTu);
				return;
			}

			//nut ESCape
			if (keyHit == ESC) {
				ClearWorkFrame();
				DrawFormDSVatTu(toaDoXFormDSVatTu, toaDoYFormDSVatTu);
				return;
			}

			WriteSectionGuide("F1: sua vat tu - ESC: thoat");

			keyHit = _getch();
		}
	}
}

void Keyhit_Delete(int keyHit, int toaDoXFormDSVatTu, int toaDoYFormDSVatTu, ListVatTu& listVatTu, PTRVatTu& root, PTRVatTu2& firstNode, PTRVatTu2& lastNode, PTRVatTu2& currentNode, int& trangHienTai, DSNhanVien dsNhanVien)
{
	if (listVatTu.first == NULL) {
		return;
	}
	if (keyHit == DEL) {
		bool vatTuDaSuDung = false;
		for (int i = 0; i < dsNhanVien.soLuongNhanVien; i++) { //ktra tung nhan vien

			for (PTRHoaDon run = dsNhanVien.nodesNhanVien[i]->listHoaDon.first; run != NULL; run = run->next) { //kiem tra tung hoa don cua nhan vien do

				for (int j = 0; j < run->infoHoaDon.dsCTHD.soLuongVatTu; j++) {//kiem tra tung cthd cua hoa don do

					if (strcmp(currentNode->maVatTu, run->infoHoaDon.dsCTHD.nodesCTHD[j].maVatTu) == 0) { 
						vatTuDaSuDung = true;
						break;
					}
				}

				if (vatTuDaSuDung == true) { //break for hoa don
					break;
				}
			}

			if (vatTuDaSuDung == true) { //break for nhan vien
				break;
			}
		}

		if (vatTuDaSuDung == false) { //chua dc su dung -> cho xoa vat tu

			string thongBao[3] = { "Vat tu dang xoa chua duoc su dung!", "Ban co chac chan muon xoa vat tu nay?" };
			string options[3] = { "Dong y", "Huy" };
			ClearWorkFrame();
			int luaChon = XuatOThongBao(thongBao, options, 2);

			if (luaChon == 0) { //dong y xoa
				char deleteKey[MAX_MA_VAT_TU];
				strcpy(deleteKey, currentNode->maVatTu); //luu lai ma vat tu cua current node

				//cap nhat current lat nua in ds ra man hinh
				if (currentNode->right != NULL) { //neu co phan tu ben trai thi cap nhat thanh node trai
					currentNode = currentNode->right;
				}
				else if (currentNode->left != NULL) { //ko co trai thi se la phai
					currentNode = currentNode->left;
				}
				else {//neu khong co ca 2 thi day la ds co 1 phan tu, sau khi xoa se thanh ds rong
					currentNode = NULL;
				}

				char maVatTuThayDoiVungNho[MAX_MA_VAT_TU]; //boi vi double linked list phan gia tri la vung nho cua tree, khi xoa delete case 3, vung nho node bi xoa la node tan cung ben trai cua cay con ben phai cua node can xoa (copy gia tri tu node tan cung ben trai vo cho node can xoa, roi xoa node con tan cung ben trai do) chu khong phai la vung nho node can xoa, vay nen vung nho moi cua node tree tan cung ben trai do trong double linked list se la vung nho cua "node tree can xoa ban dau"
				maVatTuThayDoiVungNho[0] = '\0';

				DeleteTree(root, deleteKey, maVatTuThayDoiVungNho); //xoa o tree
				if (string(maVatTuThayDoiVungNho).length() != 0) { //neu nhu la delete case 3
					PTRVatTu2 run = listVatTu.first;
					while (strcmp(run->maVatTu, maVatTuThayDoiVungNho) != 0)
					{
						run = run->right;
					}
					run->nodeTreeVatTu = TimKiemVatTu(root, maVatTuThayDoiVungNho);
				}
				DeleteInfo(listVatTu, deleteKey); //xoa o double linked list

				//cap nhat firstNode và lastNode
				if (currentNode != NULL) {
					TimTrangChuaCurrentNode(listVatTu, firstNode, lastNode, currentNode, trangHienTai);
				}
				else {
					firstNode = lastNode = NULL;
					trangHienTai = 1;
				}

				//ve lai ds vat tu
				keyHit = -1;
				ClearWorkFrame();
				DrawFormDSVatTu(toaDoXFormDSVatTu, toaDoYFormDSVatTu);
			}
			else { //ko dong y xoa
				//ve lai ds vat tu
				keyHit = -1;
				ClearWorkFrame();
				DrawFormDSVatTu(toaDoXFormDSVatTu, toaDoYFormDSVatTu);
			}
		}
		else { //da duoc su dung -> ko cho xoa
			string thongBao[3] = { "Vat tu dang xoa da duoc su dung!", "Khong the xoa vat tu nay!" };
			string options[3] = { "OK" };
			ClearWorkFrame();
			XuatOThongBao(thongBao, options, 1);

			//ve lai ds vat tu
			keyHit = -1; 
			ClearWorkFrame();
			DrawFormDSVatTu(toaDoXFormDSVatTu, toaDoYFormDSVatTu);
		}
	}
}

void Output10Nodes(PTRVatTu2 firstNode, PTRVatTu2 lastNode, PTRVatTu2 currentNode, int trangHienTai, int toaDoX, int toaDoY)
{
	if (firstNode == NULL)
		return;

	int dem = 0;
	for (PTRVatTu2 run = firstNode; run != lastNode->right; run = run->right) {
		dem++;

		if (run == currentNode) {
			SetColor(Red);
		}

		gotoxy(toaDoX + 1, toaDoY + 1 + 2 * dem);
		cout << CenterTextInSpace(to_string(trangHienTai * 10 - 10 + dem), 32);

		gotoxy(toaDoX + 1 + 32 * 1, toaDoY + 1 + 2 * dem);
		cout << CenterTextInSpace(string(run->maVatTu), 32);

		gotoxy(toaDoX + 1 + 32 * 2, toaDoY + 1 + 2 * dem);
		cout << CenterTextInSpace(string(run->nodeTreeVatTu->infoVatTu.tenVatTu), 32);

		gotoxy(toaDoX + 1 + 32 * 3, toaDoY + 1 + 2 * dem);
		cout << CenterTextInSpace(string(run->nodeTreeVatTu->infoVatTu.donViTinh), 32);

		gotoxy(toaDoX + 1 + 32 * 4, toaDoY + 1 + 2 * dem);
		cout << CenterTextInSpace(FloatToString(run->nodeTreeVatTu->infoVatTu.soLuongTon), 32);

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

void DrawFormDSVatTu(int toaDoX, int toaDoY)
{
	int soDong = 11;
	int soCot = 5;
	int doDaiNgang1Cot = 32;
	int doDaiDoc1Hang = 1;

	DrawBorderList(toaDoX, toaDoY, soDong, soCot, doDaiNgang1Cot, doDaiDoc1Hang);
	WriteTitle("DANH SACH VAT TU");

	SetColor(Green);

	gotoxy(toaDoX + 1, toaDoY + 1);
	cout << CenterTextInSpace("STT", doDaiNgang1Cot);
	gotoxy(toaDoX + 1 + doDaiNgang1Cot * 1, toaDoY + 1);
	cout << CenterTextInSpace("MA VAT TU", doDaiNgang1Cot);
	gotoxy(toaDoX + 1 + doDaiNgang1Cot * 2, toaDoY + 1);
	cout << CenterTextInSpace("TEN VAT TU", doDaiNgang1Cot);
	gotoxy(toaDoX + 1 + doDaiNgang1Cot * 3, toaDoY + 1);
	cout << CenterTextInSpace("DON VI TINH", doDaiNgang1Cot);
	gotoxy(toaDoX + 1 + doDaiNgang1Cot * 4, toaDoY + 1);
	cout << CenterTextInSpace("SO LUONG TON", doDaiNgang1Cot);

	SetColor(Black);
}

void MainDanhSachVatTu(ListVatTu& listVatTu, PTRVatTu& root, DSNhanVien dsNhanVien)
{
	PTRVatTu2 firstNode, lastNode, currentNode;
	firstNode = currentNode = listVatTu.first;
	lastNode = endNode(firstNode);

	int trangHienTai = 1;

	int keyHit = -1;

	//toa do diem bat dau ve khung
	int toaDoX = START_X_OF_MAIN_FRAME + 25 + 8;
	int toaDoY = START_Y_OF_MAIN_FRAME + 18;
	DrawFormDSVatTu(toaDoX, toaDoY);

	while (true) {
		if (keyHit == 224)
			keyHit = _getch();
		if (keyHit == 0)
			keyHit = _getch();

		//cac nut 
		Keyhit_Move(listVatTu, firstNode, lastNode, currentNode, trangHienTai, keyHit);
		Keyhit_INS(keyHit, toaDoX, toaDoY, listVatTu, root, firstNode, lastNode, currentNode, trangHienTai);
		Keyhit_Enter(keyHit, toaDoX, toaDoY, listVatTu, root, firstNode, lastNode, currentNode, trangHienTai, dsNhanVien);
		Keyhit_F2_TimTheoMaVatTu(keyHit, listVatTu, root, firstNode, lastNode, currentNode, trangHienTai, toaDoX, toaDoY);
		Keyhit_Delete(keyHit, toaDoX, toaDoY, listVatTu, root, firstNode, lastNode, currentNode, trangHienTai, dsNhanVien);
		if (keyHit == ESC) {
			return;
		}
		//

		Output10Nodes(firstNode, lastNode, currentNode, trangHienTai, toaDoX, toaDoY);
		WriteSectionGuide("ENTER: chon vat tu - F2: tim kiem vat tu - INSERT: them vat tu - DELETE: xoa vat tu - KEY_UP_DOWN: di chuyen len, xuong - KEY_LEFT_RIGHT: lui trang, sang trang - ESC: thoat");

		keyHit = _getch();
	}
}

void WriteForm_F2_TimKiemVatTu(int toaDoX, int toaDoY, char tempMaVatTu[])
{
	int toaDoXNhapThongTin = toaDoX + 20;

	gotoxy(toaDoX, toaDoY);
	cout << "Ma vat tu: ";
	gotoxy(toaDoXNhapThongTin, toaDoY);
	cout << string(tempMaVatTu);

	WriteTitle("TIM KIEM VAT TU");
}

void Keyhit_F2_TimTheoMaVatTu(int keyHit,ListVatTu listVatTu,PTRVatTu root, PTRVatTu2& firstNode, PTRVatTu2& lastNode, PTRVatTu2& currentNode, int& trangHienTai, int toaDoXFormDSVatTu, int toaDoYFormDSVatTu)
{
	if (keyHit == F2) {
		char findMaVatTu[MAX_MA_VAT_TU];
		findMaVatTu[0] = '\0';
		string temp; // bien nay de nhap thong tin
		//ma vat tu thi co chu, co so, chu ghi hoa full, va khong co khoang trang
		CheDoNhap cheDoNhap;
		cheDoNhap.coGhiChu = true;
		cheDoNhap.coGhiHoaFull = true;
		cheDoNhap.coGhiSo = true;

		int toaDoX = START_X_OF_MAIN_FRAME + 25 + 70; //toa do diem bat dau dong dau tien (Ma vat tu: )
		int toaDoY = START_Y_OF_MAIN_FRAME + 20;
		int toaDoXNhapThongTin = toaDoX + 20;

		ClearWorkFrame();
		WriteForm_F2_TimKiemVatTu(toaDoX, toaDoY, findMaVatTu);

		keyHit = -1;
		while (true)
		{
			if (keyHit == ENTER) { //tim kiem
				PTRVatTu nodeTimKiem = TimKiemVatTu(root, findMaVatTu);

				if (nodeTimKiem != NULL) { //tim thay vat tu
					//cap nhat current node
					for (PTRVatTu2 run = listVatTu.first; run != NULL; run = run->right) { 
						if (strcmp(run->maVatTu, nodeTimKiem->maVatTu) == 0) {
							currentNode = run;
							break;
						}
					}
					//quay ve ds vat tu, current la cai vua tim duoc
					TimTrangChuaCurrentNode(listVatTu, firstNode, lastNode, currentNode, trangHienTai);
					ClearWorkFrame();
					DrawFormDSVatTu(toaDoXFormDSVatTu, toaDoYFormDSVatTu);
					return;
				}
				else { //ko tim thay vat tu
					string thongBao[3] = { "Vat tu tim kiem khong ton tai!", "xxxxxxxxxxxxxxxx" };
					string options[3] = { "Dong y"};
					ClearWorkFrame();
					XuatOThongBao(thongBao, options, 1);

					keyHit = -1;
					ClearWorkFrame();
					WriteForm_F2_TimKiemVatTu(toaDoX, toaDoY, findMaVatTu);
				}
			}

			//nut ESCape
			if (keyHit == ESC) {
				string thongBao[3] = { "Ban co muon huy viec tim kiem theo ma vat tu?", "xxxxxxxxxxxxxxxx" };
				string options[3] = { "Co", "Khong" };
				ClearWorkFrame();
				int luaChon = XuatOThongBao(thongBao, options, 2);
				if (luaChon == 0) { //thoat ra thi ve lai ds vat tu
					ClearWorkFrame();
					DrawFormDSVatTu(toaDoXFormDSVatTu, toaDoYFormDSVatTu);
					return;
				}
				else { //ko thoat ra thi ve lai form tim kiem
					keyHit = -1;
					ClearWorkFrame();
					WriteForm_F2_TimKiemVatTu(toaDoX, toaDoY, findMaVatTu);
				}
			}

			WriteSectionGuide("ENTER: tim kiem - ESC: thoat");

			temp = string(findMaVatTu);
			NhapThongTin(temp, MAX_MA_VAT_TU - 1, toaDoXNhapThongTin, toaDoY, keyHit, cheDoNhap);
			strcpy(findMaVatTu, temp.c_str());
		}
	}
}

PTRVatTu MainTimKiemVatTu(ListVatTu listVatTu, PTRVatTu root)
{
	PTRVatTu2 firstNode, lastNode, currentNode;
	firstNode = currentNode = listVatTu.first;
	lastNode = endNode(firstNode);

	int trangHienTai = 1;

	int keyHit = -1;

	//toa do diem bat dau ve khung
	int toaDoX = START_X_OF_MAIN_FRAME + 25 + 8;
	int toaDoY = START_Y_OF_MAIN_FRAME + 18;
	ClearWorkFrame();
	DrawFormDSVatTu(toaDoX, toaDoY);

	while (true) {
		if (keyHit == 224)
			keyHit = _getch();
		if (keyHit == 0)
			keyHit = _getch();

		//cac nut 
		Keyhit_Move(listVatTu, firstNode, lastNode, currentNode, trangHienTai, keyHit);
		Keyhit_F2_TimTheoMaVatTu(keyHit, listVatTu, root, firstNode, lastNode, currentNode, trangHienTai, toaDoX, toaDoY);

		if (keyHit == ENTER) { //chon vat tu
			if (listVatTu.first == NULL) { //truoc hau het nut bam la kiem tra xem ds co phan tu hay ko
				continue;
			}
			return currentNode->nodeTreeVatTu;
		}
		if (keyHit == ESC) { 
			string thongBao[3] = { "Ban co chac chan muon huy viec tim vat tu?", "xxxxxxxxxxxxxxx" };
			string options[3] = { "Co", "Khong" };
			ClearWorkFrame();

			int luaChon = XuatOThongBao(thongBao, options, 2);
			if (luaChon == 0) { //dong y huy viec kiem vat tu
				return NULL;
			}
			else { //khong dong huy viec kiem vat tu
				ClearWorkFrame();
				DrawFormDSVatTu(toaDoX, toaDoY);
			}
		}
		//----------------

		Output10Nodes(firstNode, lastNode, currentNode, trangHienTai, toaDoX, toaDoY);
		WriteSectionGuide("ENTER: chon vat tu - F2: tim kiem vat tu - KEY_UP_DOWN: di chuyen len, xuong - KEY_LEFT_RIGHT: lui trang, sang trang - ESC: thoat");

		keyHit = _getch();
	}
}

void CapNhatSoLuongTon(HoaDon addHoaDon, PTRVatTu& root)
{
	PTRVatTu temp;

	for (int i = 0; i < addHoaDon.dsCTHD.soLuongVatTu; i++) {
		temp = TimKiemVatTu(root, addHoaDon.dsCTHD.nodesCTHD[i].maVatTu); //con tro temp tro toi phan tu can xu ly

		if (addHoaDon.loai == 'X') {
			temp->infoVatTu.soLuongTon -= addHoaDon.dsCTHD.nodesCTHD[i].soLuong; //cap nhat
		}
		else {
			temp->infoVatTu.soLuongTon += addHoaDon.dsCTHD.nodesCTHD[i].soLuong; //cap nhat
		}	
	}
}

