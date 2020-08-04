#include "XuLyChuoi.h"

char KyTuCuoi(char s[]) {
    return s[strlen(s) - 1];
}

void ThemVaoCuoiChuoi(char s[], char addChar) {
    int i = strlen(s);
    s[i] = addChar;
    s[i + 1] = '\0';
}

bool isFullString(char s[], int maxChuoi) {
    if (maxChuoi == strlen(s) + 1) { //strlen tra ve la da co bao nhieu ky tu, phan tu cuoi la phan tu '\0' nen ko dc phep cho gia tri khac vao
        return true;
    }
    return false;
}

int NameCmp(Name name1, Name name2) {
    if (strcmp(name1.ten, name2.ten) > 0) {
        return 1;
    }
    else if (strcmp(name1.ten, name2.ten) < 0) {
        return -1;
    }
    else {
        if (strcmp(name1.ho, name2.ho) > 0) {
            return 1;
        }
        else if (strcmp(name1.ho, name2.ho) < 0) {
            return -1;
        }
        else {
            return 0;
        }
    }
}

string FloatToString(float a)
{
    if (a == 0) {
        return "0.00";
    }

    int temp_int = a * 100.0; //lay sau dau phay 2 so

    if (a < 0.1) { //vi du: 0.02 -> temp_int = 2
        return "0.0" + to_string(temp_int);

    }
    else if (a < 1) { //vi du 0.22 -> temp_int = 22
        return "0." + to_string(temp_int);
    }
    else {
        char soThapPhan1, soThapPhan2;
        string s = to_string(temp_int);
        soThapPhan1 = s[(s.length() - 1) - 1]; //so gan cuoi
        soThapPhan2 = s[(s.length() - 1)]; //so cuoi

        //xoa 2 so cuoi roi them dau cham, sau do them 2 so do vao lai
        s.erase(s.length() - 1, 1);
        s.erase(s.length() - 1, 1);

        s.insert(s.length(), 1, '.');
        s.insert(s.length(), 1, soThapPhan1);
        s.insert(s.length(), 1, soThapPhan2);
        return s;
    }
}
//
//float StringToFloat(string s)
//{
//    char soThapPhan1, soThapPhan2;
//    soThapPhan1 = s[(s.length() - 1) - 1];
//    soThapPhan2 = s[(s.length() - 1)];
//
//    float phanNguyen = stoi(s);
//
//    string s_phanThapPhan;
//    s_phanThapPhan += soThapPhan1;
//    s_phanThapPhan += soThapPhan2;
//    float phanThapPhan = stoi(s_phanThapPhan);
//
//    return phanNguyen + phanThapPhan * 0.01;
//}

Date StringToDate(string s)
{
    Date result;
    result.ngay = 0;
    result.thang = 0;
    result.nam = 0;

    result.ngay = (int)(s[0] - '0') * 10 + (int)(s[1] - '0');
    result.thang = (int)(s[2] - '0') * 10 + (int)(s[3] - '0');
    for (int i = 4; i < s.length(); i++)
        result.nam = result.nam * 10 + (int)(s[i] - '0');

    return result;
}

string DateToString(Date date)
{
    string s = "";

    s += (int)date.ngay / 10 + '0';
    s += date.ngay % 10 + '0';
    s += (int)date.thang / 10 + '0';
    s += date.thang % 10 + '0';

    int reverse = 0;

    do
    {
        reverse = reverse * 10 + date.nam % 10;
        date.nam /= 10;
    } while (date.nam != 0);
    int i = 4;
    do
    {
        s += (int)(reverse % 10) + '0';
        reverse /= 10;
    } while (reverse != 0);
    return s;
}

string OutputDate(Date date)
{
    string s = to_string(date.ngay) + "/" + to_string(date.thang) + "/" + to_string(date.nam);
    return s;
}

int KiemTraDate(Date date) //1 -> sai ngay, 2 -> sai thang, 3 -> sai nam, 4 -> ngay lap hoa don lon hon ngay gio he thong, 0 -> ngay thang nam hop le
{
    //kiem tra so co qua nho hoac qua lon hay ko
    if (date.ngay <= 0 || date.ngay > 31) {
        return 1;
    }
    if (date.thang <= 0 || date.thang > 12) {
        return 2;
    }
    if (date.nam <= 0) {
        return 3;
    }

    //ktra tinh dung dan cua ngay
    if (date.thang == 4 || date.thang == 6 || date.thang == 9 || date.thang == 11) { //cac thang ko dc co ngay 31
        if (date.ngay > 30) {
            return 1;
        }
    }
    if (date.thang == 2) {
        if ((date.nam % 4 == 0 && date.nam % 100 != 0) || (date.nam % 400 == 0)) { //neu la nam nhuan
            if (date.ngay > 29) { //chi co 29 ngay
                return 1;
            }
        }
        else { //nam bth thang 2 chi co 28 ngay
            if (date.ngay > 28) {
                return 1;
            }
        }
    }

    //loi cuoi cung la ktra co lon hon ngay gio cua he thong hay ko
    time_t hientai = time(0);
    tm* now = localtime(&hientai);

    Date dateHienTai;
    dateHienTai.ngay = now->tm_mday;
    dateHienTai.thang = now->tm_mon + 1;
    dateHienTai.nam = now->tm_year + 1900;
    
    if (DateCmp(date, dateHienTai) > 0) {
        return 4;
    }

    //neu vuot qua het thi ngay/thang/nam hop le
    return 0;
}

int DateCmp(Date date1, Date date2) //ktra theo thu tu: nam -> thang -> ngay
{
    if (date1.nam > date2.nam) {
        return 1;
    }
    else if (date1.nam < date2.nam) {
        return -1;
    }
    else {
        if (date1.thang > date2.thang) {
            return 1;
        }
        else if (date1.thang < date2.thang) {
            return -1;
        }
        else {
            if (date1.ngay > date2.ngay) {
                return 1;
            }
            else if (date1.ngay < date2.ngay) {
                return -1;
            }
            else {
                return 0;
            }
        }
    }
}

int MaxNgayCuaThangTrongNam(int thang, int nam)
{
    switch (thang)
    {
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 2:
        if ((nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0)) {
            return 29;
        }
        else {
            return 28;
        }
    default:
        return -1;
        break;
    }
}

int SoNgayDaDatHang(Date dateDatHang) //thuat toan chi dung khi ngay dat hang < ngay he thong -> cai nay da kiem tra khi lap hoa don
{
    time_t hientai = time(0);
    tm* now = localtime(&hientai);

    Date dateHienTai;
    dateHienTai.ngay = now->tm_mday;
    dateHienTai.thang = now->tm_mon + 1;
    dateHienTai.nam = now->tm_year + 1900;

    int ketQua = 0;
    //y tuong thuat toan la cu ngay++ va thang++ va nam++, cho ket qua chay tung ngay 1 tu ngay dat hang cho toi ngay hien tai
    while (true) {
        //day la dieu kien dung vong lap
        //truong hop ca 3 cai bang nhau thi return luon
        if (dateDatHang.nam == dateHienTai.nam && dateDatHang.thang == dateHienTai.thang && dateDatHang.ngay == dateHienTai.ngay) {
            return ketQua;
        }

        ketQua++;
        dateDatHang.ngay++;

        if (dateDatHang.ngay > MaxNgayCuaThangTrongNam(dateDatHang.thang, dateDatHang.nam)) { //neu het ngay cua thang hien tai thi reset ngay, thang++
            dateDatHang.ngay = 1;
            dateDatHang.thang++;

            if (dateDatHang.thang > 12) { //neu het 12 thang thi reset thang, nam++
                dateDatHang.nam++;
                dateDatHang.thang = 1;
            }
        }
    }
}

string NameToString(Name name)
{
    return string(name.ho) +" "+ string(name.ten);
}

string CenterTextInSpace(string s, int wide) //cho s va do dai muon string s nam giua
{
    string result;
    result.resize(wide - 2, ' ');//wide la khoang cach tu duong thang gioi han 2 ben cua 1 o trong DrawBorderList, chi can viet giua 2 duong thang nen -2

    int tongDoDaiKhoangTrang = (wide - 2) - s.length(); 
    int diemBatDau = tongDoDaiKhoangTrang/2;

    for (int i = 0; i < s.length(); i++)
    {
        result[diemBatDau + i] = s[i];
    }
    
    return result;
}

void OutputString(string s, int maxChuoi, int toaDoX, int toaDoY)
{
    gotoxy(toaDoX, toaDoY);
    cout << CenterTextInSpace(" ", maxChuoi + 2);
    gotoxy(toaDoX, toaDoY);
    cout << s;
}

void NhapThongTin(string& s, int maxChuoi, int toaDoX, int toaDoY, int& keyHit, CheDoNhap cheDoNhap)
{
    keyHit = -1;
    while (true) {
        if (keyHit == 224 || keyHit == 0) {
            keyHit = _getch();
            if (keyHit == KEY_DOWN || keyHit == KEY_UP || keyHit == F1 || keyHit == F2) {
                if (s.length() != 0) {
                    if (s[s.length() - 1] == ' ') { //neu phan tu cuoi cung la khoang trang thi xoa, day la loi con lai duy nhat cua ham nhap thong tin
                        s.erase(s.length() - 1, 1);
                        OutputString(s, maxChuoi, toaDoX, toaDoY);
                    }
                }
                return;
            }
                
        }
        else if(keyHit == ENTER || keyHit == ESC)
        {
            if (s.length() != 0) {
                if (s[s.length() - 1] == ' ') { //neu phan tu cuoi cung la khoang trang thi xoa, day la loi con lai duy nhat cua ham nhap thong tin
                    s.erase(s.length() - 1, 1);
                    OutputString(s, maxChuoi, toaDoX, toaDoY);
                }
            }
            return;
        }
        else { //phai bo trong day vi cac nut bam kia co so sau so 224 la mot so thuoc cac ky tu ma ascii
            //cac nut bam
            if (s.length() < maxChuoi) {//neu chua max chuoi

                if (keyHit >= 'a' && keyHit <= 'z' && cheDoNhap.coGhiChu == true) {
                    if (cheDoNhap.coGhiHoaFull == true) { //neu che do ghi hoa full thi ghi hoa het
                        keyHit = keyHit - ('a' - 'A');
                    }
                    else { //che do ghi hoa chu cai dau
                        if (s.length() == 0) {//ky tu dau chuoi duong nhien ghi hoa
                            keyHit = keyHit - ('a' - 'A');
                        }
                        else { //co it nhat 1 ky tu
                            if (s[s.length() - 1] == ' ') {   //neu truoc no co khoang trang
                                keyHit = keyHit - ('a' - 'A');
                            }
                        }
                    }
                    s.insert(s.length(), 1, keyHit);
                }
                else if (keyHit >= 'A' && keyHit <= 'Z' && cheDoNhap.coGhiChu == true) {
                    if (cheDoNhap.coGhiHoaFull == false) { //neu chi ghi hoa chu cai dau 
                        if (s.length() != 0) { //neu no ko phai ki tu dau
                            if (s[s.length() - 1] != ' ') {//va truoc no ko phai ki tu khoang trang thi phai ghi thuong
                                keyHit = keyHit + ('a' - 'A');
                            }
                        }
                    }
                    s.insert(s.length(), 1, keyHit);
                }
                else if (keyHit >= '0' && keyHit <= '9' && cheDoNhap.coGhiSo == true) {
                    s.insert(s.length(), 1, keyHit);
                }
                else if (keyHit == SPACEBAR && cheDoNhap.coKhoangTrang == true) {
                    if (s.length() != 0) { //ko cho nhap khoang trang khi no la phan tu dau hoac trc no da co khoang trang
                        if (s[s.length() - 1] != ' ') {
                            s.insert(s.length(), 1, ' ');
                        }
                    }
                }
            }
        }
            
        if (keyHit == BACKSPACE) {
            if (s.length() != 0) {
                s.erase(s.length() - 1, 1);
            }
        }

        //xuat ra string
        OutputString(s, maxChuoi, toaDoX, toaDoY);

        keyHit = _getch();
    }
}

bool DaCoDauCham(string s)
{
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '.') {
            return true;
        }
    }
    return false;
}

void NhapSoThuc(string& s, int maxChuoi, int toaDoX, int toaDoY, int& keyHit)
{
    keyHit = -1;
    while (true) {
        if (keyHit == 224 || keyHit == 0) {
            keyHit = _getch();
            if (keyHit == KEY_DOWN || keyHit == KEY_UP || keyHit == F1 || keyHit == F2) {
                if (s.length() != 0) {
                    if (s[s.length() - 1] == '.') { //neu phan tu cuoi cung la dau cham thi xoa, day la loi con lai duy nhat cua ham nhap so thuc
                        s.erase(s.length() - 1, 1);
                        OutputString(s, maxChuoi, toaDoX, toaDoY);
                    }
                }
                return;
            }
        }
        else if (keyHit == ENTER || keyHit == ESC)
        {
            if (s.length() != 0) {
                if (s[s.length() - 1] == '.') { //neu phan tu cuoi cung la dau cham thi xoa, day la loi con lai duy nhat cua ham nhap so thuc
                    s.erase(s.length() - 1, 1);
                    OutputString(s, maxChuoi, toaDoX, toaDoY);
                }
            }
            return;
        }
        else { //phai bo trong day vi cac nut bam kia co so sau so 224 la mot so thuoc cac ky tu ma ascii
            //cac nut bam
            if (s.length() < maxChuoi) {//neu chua max chuoi
                if (keyHit >= '0' && keyHit <= '9') {

                    if (DaCoDauCham(s)) { //toi da sau dau phay chi dc 2 so
                        int dem = 0;
                        int i = s.length() - 1;
                        while (s[i] != '.') { //dem xem sau dau phay co may so
                            dem++;
                            i--;
                        }
                        if (dem < 2) { //neu chua du 2 so thi co the tiep tuc them
                            s.insert(s.length(), 1, keyHit);
                        }
                    }
                    else
                        s.insert(s.length(), 1, keyHit);
                }
                else if (keyHit == DOT) {
                    if (s.length() != 0) { //cho nhap dau cham khi no ko la phan tu dau
                        if (!DaCoDauCham(s)) { //va khi no chua co dau cham
                            s.insert(s.length(), 1, '.');
                        }
                    }
                }
            }
        }

        if (keyHit == BACKSPACE) {
            if (s.length() != 0) {
                s.erase(s.length() - 1, 1);
            }
        }

        //xuat ra string
        OutputString(s, maxChuoi, toaDoX, toaDoY);

        keyHit = _getch();
    }
}
