// quản lý trung tâm tin học.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm> // Thêm thư viện này để sử dụng hàm find_if

using namespace std;

// Định nghĩa lớp HocVien
class HocVien {
private:
    string hoTen;
    int maHocVien;

public:
    HocVien() : maHocVien(0) {}
    void setHoTen(const string& ten) { hoTen = ten; }
    void setMaHocVien(int ma) { maHocVien = ma; }
    string getHoTen() const { return hoTen; }
    int getMaHocVien() const { return maHocVien; }
};

// Khai báo các hàm
void themHocVien(vector<HocVien>& danhSachHocVien);
void hienThiDanhSachHocVien(const vector<HocVien>& danhSachHocVien);
void xoaHocVien(vector<HocVien>& danhSachHocVien);
void suaThongTinHocVien(vector<HocVien>& danhSachHocVien);
void luuFile(const vector<HocVien>& danhSachHocVien, const string& tenFile);
void docFile(vector<HocVien>& danhSachHocVien, const string& tenFile);

int main() {
    vector<HocVien> danhSachHocVien;

    // Đọc danh sách học viên từ file nếu có
    docFile(danhSachHocVien, "danh_sach_hoc_vien.txt");

    int luaChon;
    do {
        cout << "Menu Chinh\n";
        cout << "1. Them hoc vien\n";
        cout << "2. Hien thi danh sach hoc vien\n";
        cout << "3. Sua thong tin hoc vien\n";
        cout << "4. Xoa hoc vien\n";
        cout << "5. Luu danh sach hoc vien vao file\n";
        cout << "6. Thoat\n";
        cout << "Nhap lua chon cua ban: ";
        cin >> luaChon;

        switch (luaChon) {
        case 1:
            themHocVien(danhSachHocVien);
            break;
        case 2:
            hienThiDanhSachHocVien(danhSachHocVien);
            break;
        case 3:
            suaThongTinHocVien(danhSachHocVien);
            break;
        case 4:
            xoaHocVien(danhSachHocVien);
            break;
        case 5:
            luuFile(danhSachHocVien, "danh_sach_hoc_vien.txt");
            break;
        case 6:
            cout << "Thoat chuong trinh.\n";
            break;
        default:
            cout << "Lua chon khong hop le. Vui long thu lai.\n";
            break;
        }
    } while (luaChon != 6);

    return 0;
}

// Định nghĩa các hàm
void themHocVien(vector<HocVien>& danhSachHocVien) {
    HocVien hv;
    string ten;
    int ma;

    cout << "Nhap ten hoc vien: ";
    cin.ignore();
    getline(cin, ten);
    hv.setHoTen(ten);

    cout << "Nhap ma hoc vien: ";
    cin >> ma;
    hv.setMaHocVien(ma);

    danhSachHocVien.push_back(hv);
}

void hienThiDanhSachHocVien(const vector<HocVien>& danhSachHocVien) {
    cout << "Danh sach hoc vien:\n";
    for (const auto& hv : danhSachHocVien) {
        cout << "Ma hoc vien: " << hv.getMaHocVien() << ", Ten hoc vien: " << hv.getHoTen() << endl;
    }
}

void xoaHocVien(vector<HocVien>& danhSachHocVien) {
    int ma;
    cout << "Nhap ma hoc vien can xoa: ";
    cin >> ma;

    auto it = find_if(danhSachHocVien.begin(), danhSachHocVien.end(), [&](const HocVien& hv) {
        return hv.getMaHocVien() == ma;
        });

    if (it != danhSachHocVien.end()) {
        danhSachHocVien.erase(it);
        cout << "Da xoa hoc vien co ma so " << ma << endl;
    }
    else {
        cout << "Khong tim thay hoc vien co ma so " << ma << endl;
    }
}

void suaThongTinHocVien(vector<HocVien>& danhSachHocVien) {
    int ma;
    cout << "Nhap ma hoc vien can sua: ";
    cin >> ma;

    auto it = find_if(danhSachHocVien.begin(), danhSachHocVien.end(), [&](const HocVien& hv) {
        return hv.getMaHocVien() == ma;
        });

    if (it != danhSachHocVien.end()) {
        string tenMoi;
        cout << "Nhap ten moi: ";
        cin.ignore();
        getline(cin, tenMoi);

        it->setHoTen(tenMoi);
        cout << "Da sua thong tin thanh cong.\n";
    }
    else {
        cout << "Khong tim thay hoc vien co ma so " << ma << ".\n";
    }
}

void luuFile(const vector<HocVien>& danhSachHocVien, const string& tenFile) {
    ofstream fileOut(tenFile);

    if (!fileOut.is_open()) {
        cout << "Khong mo duoc file de ghi.\n";
        return;
    }

    for (const auto& hv : danhSachHocVien) {
        fileOut << hv.getMaHocVien() << "," << hv.getHoTen() << endl;
    }

    fileOut.close();
    cout << "Da ghi file thanh cong.\n";
}
void docFile(vector<HocVien>& danhSachHocVien, const string& tenFile) {
    ifstream fileIn(tenFile);
    if (!fileIn.is_open()) {
        cout << "Khong mo duoc file de doc.\n";
        return;
    }

    HocVien hv;
    string line;
    while (getline(fileIn, line)) {
        size_t pos = line.find(",");
        if (pos != string::npos) {
            int ma = stoi(line.substr(0, pos));
            string ten = line.substr(pos + 1);
            hv.setMaHocVien(ma);
            hv.setHoTen(ten);
            danhSachHocVien.push_back(hv);
        }
    }

    fileIn.close();
    cout << "Da doc file thanh cong.\n";
}
// Khai báo lớp KhoaHoc và LopHoc
class KhoaHoc {
private:
    string tenKhoaHoc;
    int maKhoaHoc;

public:
    KhoaHoc() : maKhoaHoc(0) {}
    void setTenKhoaHoc(const string& ten) { tenKhoaHoc = ten; }
    void setMaKhoaHoc(int ma) { maKhoaHoc = ma; }
    string getTenKhoaHoc() const { return tenKhoaHoc; }
    int getMaKhoaHoc() const { return maKhoaHoc; }
};

class LopHoc {
private:
    string tenLop;
    int maLop;
    KhoaHoc khoaHoc;

public:
    LopHoc() : maLop(0) {}
    void setTenLop(const string& ten) { tenLop = ten; }
    void setMaLop(int ma) { maLop = ma; }
    void setKhoaHoc(const KhoaHoc& kh) { khoaHoc = kh; }
    string getTenLop() const { return tenLop; }
    int getMaLop() const { return maLop; }
    KhoaHoc getKhoaHoc() const { return khoaHoc; }
};

// Khai báo hàm quản lý khoá học và lớp học
void themKhoaHoc(vector<KhoaHoc>& danhSachKhoaHoc);
void themLopHoc(vector<LopHoc>& danhSachLopHoc);
void hienThiDanhSachKhoaHoc(const vector<KhoaHoc>& danhSachKhoaHoc);
void hienThiDanhSachLopHoc(const vector<LopHoc>& danhSachLopHoc);

// Định nghĩa các hàm quản lý khoá học và lớp học
void themKhoaHoc(vector<KhoaHoc>& danhSachKhoaHoc) {
    KhoaHoc kh;
    string ten;
    int ma;

    cout << "Nhap ten khoa hoc: ";
    cin.ignore();
    getline(cin, ten);
    kh.setTenKhoaHoc(ten);

    cout << "Nhap ma khoa hoc: ";
    cin >> ma;
    kh.setMaKhoaHoc(ma);

    danhSachKhoaHoc.push_back(kh);
}

void themLopHoc(vector<LopHoc>& danhSachLopHoc) {
    LopHoc lh;
    string ten;
    int ma;
    KhoaHoc kh;

    cout << "Nhap ten lop hoc: ";
    cin.ignore();
    getline(cin, ten);
    lh.setTenLop(ten);

    cout << "Nhap ma lop hoc: ";
    cin >> ma;
    lh.setMaLop(ma);

    cout << "Nhap ten khoa hoc cua lop: ";
    cin.ignore();
    getline(cin, ten);
    kh.setTenKhoaHoc(ten);
    lh.setKhoaHoc(kh);

    danhSachLopHoc.push_back(lh);
}

void hienThiDanhSachKhoaHoc(const vector<KhoaHoc>& danhSachKhoaHoc) {
    cout << "Danh sach khoa hoc:\n";
    for (const auto& kh : danhSachKhoaHoc) {
        cout << "Ma khoa hoc: " << kh.getMaKhoaHoc() << ", Ten khoa hoc: " << kh.getTenKhoaHoc() << endl;
    }
}

void hienThiDanhSachLopHoc(const vector<LopHoc>& danhSachLopHoc) {
    cout << "Danh sach lop hoc:\n";
    for (const auto& lh : danhSachLopHoc) {
        cout << "Ma lop hoc: " << lh.getMaLop() << ", Ten lop hoc: " << lh.getTenLop() << ", Khoa hoc: " << lh.getKhoaHoc().getTenKhoaHoc() << endl;
    }
}
// Khai báo lớp GiaoVien và HoaDon
class GiaoVien {
private:
    string hoTen;
    int maGiaoVien;

public:
    GiaoVien() : maGiaoVien(0) {}
    void setHoTen(const string& ten) { hoTen = ten; }
    void setMaGiaoVien(int ma) { maGiaoVien = ma; }
    string getHoTen() const { return hoTen; }
    int getMaGiaoVien() const { return maGiaoVien; }
};

class HoaDon {
private:
    int maHoaDon;
    int maHocVien;
    double soTien;

public:
    HoaDon() : maHoaDon(0), maHocVien(0), soTien(0.0) {}
    void setMaHoaDon(int ma) { maHoaDon = ma; }
    void setMaHocVien(int ma) { maHocVien = ma; }
    void setSoTien(double tien) { soTien = tien; }
    int getMaHoaDon() const { return maHoaDon; }
    int getMaHocVien() const { return maHocVien; }
    double getSoTien() const { return soTien; }
};

// Khai báo hàm quản lý giáo viên và hóa đơn
void themGiaoVien(vector<GiaoVien>& danhSachGiaoVien);
void themHoaDon(vector<HoaDon>& danhSachHoaDon);
void hienThiDanhSachGiaoVien(const vector<GiaoVien>& danhSachGiaoVien);
void hienThiDanhSachHoaDon(const vector<HoaDon>& danhSachHoaDon);

// Định nghĩa các hàm quản lý giáo viên và hóa đơn
void themGiaoVien(vector<GiaoVien>& danhSachGiaoVien) {
    GiaoVien gv;
    string ten;
    int ma;

    cout << "Nhap ten giao vien: ";
    cin.ignore();
    getline(cin, ten);
    gv.setHoTen(ten);

    cout << "Nhap ma giao vien: ";
    cin >> ma;
    gv.setMaGiaoVien(ma);

    danhSachGiaoVien.push_back(gv);
}

void themHoaDon(vector<HoaDon>& danhSachHoaDon) {
    HoaDon hd;
    int maHD, maHV;
    double tien;

    cout << "Nhap ma hoa don: ";
    cin >> maHD;
    hd.setMaHoaDon(maHD);

    cout << "Nhap ma hoc vien: ";
    cin >> maHV;
    hd.setMaHocVien(maHV);

    cout << "Nhap so tien: ";
    cin >> tien;
    hd.setSoTien(tien);

    danhSachHoaDon.push_back(hd);
}

void hienThiDanhSachGiaoVien(const vector<GiaoVien>& danhSachGiaoVien) {
    cout << "Danh sach giao vien:\n";
    for (const auto& gv : danhSachGiaoVien) {
        cout << "Ma giao vien: " << gv.getMaGiaoVien() << ", Ten giao vien: " << gv.getHoTen() << endl;
    }
}

void hienThiDanhSachHoaDon(const vector<HoaDon>& danhSachHoaDon) {
    cout << "Danh sach hoa don:\n";
    for (const auto& hd : danhSachHoaDon) {
        cout << "Ma hoa don: " << hd.getMaHoaDon() << ", Ma hoc vien: " << hd.getMaHocVien() << ", So tien: " << hd.getSoTien() << endl;
    }
}