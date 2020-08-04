#include "WorkWithFile.h"

void DocFileVatTu(PTRVatTu& root, string nameFile)
{
	fstream f;
	f.open(nameFile, ios::in);

	if (f.fail()) {
		cout << "DOC FILE THAT BAI!";
		return;
	}

	string line;
	VatTu addVatTu;
	char addKey[MAX_MA_VAT_TU];

	while (!f.eof()) {
		getline(f, line); //doc 1 dong va cho vao line

		if (line == "") { //neu rong thi ko xet 
			continue;
		}

		LineToVatTu(line, addKey, addVatTu);
		InsertTree(root, addKey, addVatTu);
	}

	f.close();
}

void GhiFileVatTu(PTRVatTu root, string nameFile)
{
	fstream f;
	f.open(nameFile, ios::out);
	if (f.fail()) {
		cout << "GHI FILE THAT BAI!";
		return;
	}

	/*for (ListVatTu temp = this->dsVatTuChinh.GetFirstListVatTu(); temp != NULL; temp = temp->right)
	{
		write << temp->maVT;
		write << "+";
		write << temp->info.tenVT;
		write << "+";
		write << temp->info.soLuongTon;
		write << "+";
		write << temp->info.donViTinh;
		write << "+" << endl;
	}*/
	GhiFile_NLR(root, f);
}

void GhiFile_NLR(PTRVatTu p, fstream& f)
{
	
	if (p != NULL)
	{
		//phan xu ly
		f << p->maVatTu;
		f << "+";
		f << p->infoVatTu.tenVatTu;
		f << "+";
		f << p->infoVatTu.donViTinh;
		f << "+";
		f << FloatToString(p->infoVatTu.soLuongTon);
		//f << p->infoVatTu.soLuongTon;
		f << "+" << endl;
		//

		GhiFile_NLR(p->left, f);
		GhiFile_NLR(p->right, f);		
	}
}

void LineToVatTu(string line, char addKey[], VatTu& addVatTu)
{
	//ma+ten+sl+dvt+
	//line = maVatTu+tenVatTu+donViTinh+soLuongTon+
	string temp = "";
	int i = 0;

	//doc maVatTu
	while (line[i] != '+')
	{
		temp += line[i];	
		i++;
	}
	strcpy(addKey ,temp.c_str()); 

	i++;
	temp = "";

	//doc tenVatTu
	while (line[i] != '+')
	{
		temp += line[i];
		i++;
	}
	//addVatTu.tenVatTu = temp;
	strcpy(addVatTu.tenVatTu, temp.c_str());

	i++;
	temp = "";

	//doc donViTinh
	while (line[i] != '+')
	{
		temp += line[i];
		i++;
	}

	//addVatTu.donViTinh = temp;
	strcpy(addVatTu.donViTinh, temp.c_str());

	i++;
	temp = "";

	//doc soLuongTon
	while (line[i] != '+')
	{
		temp += line[i];
		i++;
	}
	addVatTu.soLuongTon = stof(temp);
}

void DocFileNhanVien(DSNhanVien& dsNhanVien, string nameFile)
{
	fstream f;
	f.open(nameFile, ios::in);

	if (f.fail()) {
		cout << "DOC FILE THAT BAI!";
		return;
	}

	string line;
	NhanVien addNhanVien;

	while (!f.eof()) {
		getline(f, line); //doc 1 dong va cho vao line

		if (line == "") { //neu rong thi ko xet 
			continue;
		}

		LineToNhanVien(line, addNhanVien);
		InsertLast(dsNhanVien, addNhanVien);
	}

	f.close();
}

void GhiFileNhanVien(DSNhanVien dsNhanVien, string nameFile)
{
	fstream f;
	f.open(nameFile, ios::out);
	if (f.fail()) {
		cout << "GHI FILE THAT BAI!";
		return;
	}

	//duyet tung nhan vien
	for (int i = 0; i < dsNhanVien.soLuongNhanVien; i++) { 
		f << dsNhanVien.nodesNhanVien[i]->maNhanVien;
		f << "+";
		f << dsNhanVien.nodesNhanVien[i]->name.ho;
		f << "+";
		f << dsNhanVien.nodesNhanVien[i]->name.ten;
		f << "+";
		f << dsNhanVien.nodesNhanVien[i]->phai;
		f << "+";
		f << dsNhanVien.nodesNhanVien[i]->soCMND;
		f << "+";

		if (!Empty(dsNhanVien.nodesNhanVien[i]->listHoaDon)) {
			//duyet tung hoa don
			for (PTRHoaDon run = dsNhanVien.nodesNhanVien[i]->listHoaDon.first; run != NULL; run = run->next) {
				f << run->infoHoaDon.soHoaDon;
				f << "*";
				f << DateToString(run->infoHoaDon.ngayLap);
				f << "*";
				f << run->infoHoaDon.loai;
				f << "*";

				//duyet tung chi tiet hoa don
				for (int i = 0; i < run->infoHoaDon.dsCTHD.soLuongVatTu; i++) {
					f << run->infoHoaDon.dsCTHD.nodesCTHD[i].maVatTu;
					f << "/";
					f << FloatToString(run->infoHoaDon.dsCTHD.nodesCTHD[i].soLuong);
					f << "/";
					f << to_string(run->infoHoaDon.dsCTHD.nodesCTHD[i].donGia);
					f << "/";
					f << FloatToString(run->infoHoaDon.dsCTHD.nodesCTHD[i].VAT);
					f << "/";
					f << run->infoHoaDon.dsCTHD.nodesCTHD[i].trangThai;
					f << "/";
				}
				f << "#";
			}
		}
		f << "@" << endl;
	}
}

void LineToNhanVien(string line, NhanVien& addNhanVien)
{
	string temp = "";
	int i = 0;

	//doc maNhanVien
	while (line[i] != '+')
	{
		temp += line[i];
		i++;
	}
	addNhanVien.maNhanVien = stoi(temp);

	i++;
	temp = "";

	//doc ho NhanVien
	while (line[i] != '+')
	{
		temp += line[i];
		i++;
	}
	strcpy(addNhanVien.name.ho, temp.c_str());

	i++;
	temp = "";

	//doc ten NhanVien
	while (line[i] != '+')
	{
		temp += line[i];
		i++;
	}
	strcpy(addNhanVien.name.ten, temp.c_str());

	i++;
	temp = "";

	//doc phai NhanVien
	while (line[i] != '+')
	{
		temp += line[i];
		i++;
	}
	addNhanVien.phai = (int)temp[0] - '0'; //phai tru di ky tu 0 vi so kia la ma ascii

	i++;
	temp = "";

	//doc soCMND NhanVien
	while (line[i] != '+')
	{
		temp += line[i];
		i++;
	}
	strcpy(addNhanVien.soCMND, temp.c_str());

	i++;
	temp = "";

	CreateList(addNhanVien.listHoaDon); //khoi tao DS Hoa Don

	//vong while duyet tat ca cac hoa don cho den khi gap @ la het hoa don
	while (line[i] != '@')
	{
		HoaDon addHoaDon;
		CreateMangTuyenTinh(addHoaDon.dsCTHD);

		//doc soHoaDon
		while (line[i] != '*')
		{
			temp += line[i];
			i++;
		}
		strcpy(addHoaDon.soHoaDon, temp.c_str());

		i++;
		temp = "";

		//doc Date HoaDon
		while (line[i] != '*')
		{
			temp += line[i];
			i++;
		}
		addHoaDon.ngayLap = StringToDate(temp);

		temp = "";
		i++;

		//doc loai HoaDon
		while (line[i] != '*')
		{
			temp += line[i];
			i++;
		}
		//strcpy(addHoaDon.loai, temp.c_str());
		addHoaDon.loai = temp[0];

		i++;
		temp = "";

		//vong while duyet tat ca cac chi tiet hoa don cua 1 hoa don cho den khi gap # la het chi tiet hoa don cua 1 hoa don
		while (line[i] != '#')
		{
			ChiTietHoaDon addCTHD;
			//doc maVatTu
			while (line[i] != '/')
			{
				temp += line[i];
				i++;
			}
			strcpy(addCTHD.maVatTu, temp.c_str());

			i++;
			temp = "";

			//doc soLuong
			while (line[i] != '/')
			{
				temp += line[i];
				i++;
			}
			addCTHD.soLuong = stof(temp);

			i++;
			temp = "";

			//doc donGia
			while (line[i] != '/')
			{
				temp += line[i];
				i++;
			}
			addCTHD.donGia = stoi(temp);

			i++;
			temp = "";

			//doc VAT
			while (line[i] != '/')
			{
				temp += line[i];
				i++;
			}
			addCTHD.VAT = stof(temp);

			i++;
			temp = "";

			//doc  trangThai
			while (line[i] != '/')
			{
				temp += line[i];
				i++;
			}
			addCTHD.trangThai= stoi(temp);

			InsertLast(addHoaDon.dsCTHD, addCTHD);

			i++;
			temp = "";
		}

		InsertLast(addNhanVien.listHoaDon, addHoaDon);

		i++;
		temp = "";
	}
}

void LoadTreeToDoubleLinkedList_RNL(PTRVatTu& p, ListVatTu& listVatTu) {
	if (p != NULL)
	{
		LoadTreeToDoubleLinkedList_RNL(p->right, listVatTu);

		//phan xu ly
		InsertLast(listVatTu, p);
		//

		LoadTreeToDoubleLinkedList_RNL(p->left, listVatTu);
	}
}
