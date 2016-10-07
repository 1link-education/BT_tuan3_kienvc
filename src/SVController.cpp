#include "SVController.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <io.h>
#include <conio.h>


SVController::SVController()
{
	sosv = 0;
	//ds = new SinhVien;
}

SVController::SVController(SVView view)
{
	//this->ds = ds;
	this->view = view;
	sosv = 0;
}

void SVController::setSosv(int n)
{
	sosv = n;
}
int SVController::getSosv()
{
	return sosv;
}
SinhVien SVController::nhapThongTin()
{
	SinhVien sv;
	string ten, diachi, sbd, gioitinh, temp;
	float toan, ly, hoa;
	fflush(stdin);
	cout << "\tTen: ";
	getline(cin, ten);
	cout << "\tSbd: ";
	getline(cin, sbd);
	cout << "\tDia chi: ";
	getline(cin, diachi);
	cout << "\tGioi tinh: ";
	getline(cin, gioitinh);
	do{
		fflush(stdin);
		cout << "\tDiem toan: ";
		getline(cin, temp);
		stringstream myStream(temp);
		myStream >> toan;
	}while(toan < 0 || toan > 10);
	do{
		fflush(stdin);
		cout << "\tDiem ly: ";
		getline(cin, temp);
		stringstream myStream(temp);
		myStream >> ly;
	}while(ly < 0 || ly > 10);
	do{
		cout << "\tDiem hoa: ";
		fflush(stdin);
		getline(cin, temp);
		stringstream myStream(temp);
		myStream >> hoa;
	}while(hoa < 0 || hoa > 10);
	sv = SinhVien(ten, sbd, diachi, gioitinh, toan, ly, hoa);
	return sv;
}

void SVController::nhapTay(int tmp, int index)
{
	fflush(stdin);
	for(int i = 0; i < tmp; i++){
		cout << "Sinh vien thu " << i+ index + 1 << ":\n";
		ds[i+index] = nhapThongTin();
		for( int j = 0; j <= i ; j++){
			if(ds[j].getSbd() == ds[i + index].getSbd() && j != (i+index)){
				cout << "So bao danh bi trung, nhap lai thong tin\n";
				cout << "Sinh vien thu " << i+1 << ":\n";
				ds[i+index]= nhapThongTin();
				j--;
			}
		}
	}
	sosv = tmp + index;
}

int SVController::nhapFile(const char *dir,int index)
{
	char *ten_c, *sbd_c, *diachi_c, *gioitinh_c, *toan_s, *ly_s, *hoa_s;
	const char *tmp3;
	char tmp2[100];
	string tmp;
	int i = 0, tmp_sosv;
	char *next_token = NULL;
	char *seps = "-";
	
	if (_access(dir, 00) == -1)
		return 0;
	
	ifstream file;
	file.open(dir);
	if(file.is_open()){
		file >> tmp_sosv;
		getline(file,tmp);
		while(!file.eof() && i != tmp_sosv){
			getline(file,tmp);

			tmp3 = tmp.c_str();
			strcpy_s(tmp2, tmp3);
			ten_c = strtok_s(tmp2, seps, &next_token);
			string ten(ten_c);
			sbd_c = strtok_s(NULL, seps, &next_token);
			string sbd(sbd_c);
			diachi_c = strtok_s(NULL, seps, &next_token);
			string diachi(diachi_c);
			gioitinh_c = strtok_s(NULL, seps, &next_token);
			string gioitinh(gioitinh_c);
			toan_s = strtok_s(NULL, seps, &next_token);
			ly_s = strtok_s(NULL, seps, &next_token);
			hoa_s = strtok_s(NULL, seps, &next_token);
			next_token = NULL;

			ds[i+index] = SinhVien(ten, sbd, diachi, gioitinh, atof(toan_s), atof(ly_s), atof(hoa_s));
			
			for( int j = 0; j < sosv; j++)
				if(ds[j].getSbd() == sbd){
					i--;
					tmp_sosv--;
					break;
				}
			i++;
		}
		file.close();
		return tmp_sosv;
	}
	return 0;
}

void SVController::nhapFiles(const char *dir)
{
	string line[1000];
	ifstream file;
	int i = 0, tmp = 0;

	file.open(dir);
	if (file.is_open())
	{
		while (! file.eof() )
		{
			getline (file,line[i]);
			i++;
		}
		file.close();
	}
	for(int y = 0; y <= i-2; y++)
	{
		
		sosv += nhapFile(line[y].c_str(), sosv);
	}
	//sosv = tmp;
}
void SVController::timkiem(string yeucau)
{
	fflush(stdin);
	ofstream file;
	file.open("result.txt");

	SinhVien ds2[1000];
	int count = 0,temp;

	if(yeucau.compare("ten") == 0){
		string tmp;
		cout << "Nhap ten sinh vien: ";
		getline(cin, tmp);
		for(int i = 0; i < sosv; i++){
			if(ds[i].getTen().compare(tmp) == 0){
				ds2[count] = ds[i];
				count ++;
			}
		}
	}
	if(yeucau.compare("sbd") == 0){
		string tmp;
		cout << "Nhap sbd sinh vien: ";
		getline(cin, tmp);
		for(int i = 0; i < sosv; i++){
			if(ds[i].getSbd().compare(tmp) == 0){
				ds2[count] = ds[i];
				count ++;
			}
		}
	}
	if(yeucau.compare("tong") == 0){
		float tong;
		cout << "Nhap tong diem cua sinh vien: ";
		cin >> tong;
		for(int i = 0; i < sosv; i++){
			if(ds[i].getTong() == tong){
				ds2[count] = ds[i];
				count ++;
			}
		}
	}
	if(yeucau.compare("toan") == 0){
		float toan;
		cout << "Nhap diem toan cua sinh vien: ";
		cin >> toan;
		for(int i = 0; i < sosv; i++){
			if(ds[i].getToan() == toan){
				ds2[count] = ds[i];
				count ++;
			}
		}
	}
	if(yeucau.compare("ly") == 0){
		float ly;
		cout << "Nhap diem ly cua sinh vien: ";
		cin >> ly;
		for(int i = 0; i < sosv; i++){
			if(ds[i].getLy() == ly){
				ds2[count] = ds[i];
				count ++;
			}
		}
	}
	if(yeucau.compare("hoa") == 0){
		float hoa;
		cout << "Nhap diem hoa cua sinh vien: ";
		cin >> hoa;
		for(int i = 0; i < sosv; i++){
			if(ds[i].getHoa() == hoa){
				ds2[count] = ds[i];
				count ++;
			}
		}
	}
	if( count == 0){
		cout << "Khong tim thay sinh vien\n";
		return;
	}
	fflush(stdin);
	cout << "Lua chon sap xep dau ra:\n1.Mac dinh( theo so bao danh)\n2.Theo ten\n3.Theo tong diem\n";
	cin >> temp;
	if(temp == 1){
		for (int i = 0; i < count-1; i++)
			for(int j = i+1; j < count; j++)
				if (ds2[i].getSbd().compare(ds2[j].getSbd()) > 0)
					swap(ds2[i], ds2[j]);
	}
	if(temp == 2){
		for (int i = 0; i < count-1; i++)
			for(int j = i+1; j < count; j++)
				if (ds2[i].getTen().compare(ds2[j].getTen()) > 0)
					swap(ds2[i], ds2[j]);
	}
	if(temp == 3){
		for (int i = 0; i < count-1; i++)
			for(int j = i+1; j < count; j++)
				if (ds2[i].getTong() > ds2[j].getTong())
					swap(ds2[i], ds2[j]);
	}
	for(int i = 0; i < count;i++){
		cout << "*************\n";
		view.view(ds2[i]);
		file << "*************\n";
		file << "Ten: " << ds[i].getTen() << "\n";
		file << "Sbd: " << ds[i].getSbd() << "\n";
		file << "Dia chi: " << ds[i].getDiachi() << "\n";
		file << "Gioi tinh: " << ds[i].getGioitinh() << "\n";
		file << "Diem toan: " << ds[i].getToan() << "\n";
		file << "Diem hoa: " << ds[i].getHoa() << "\n";
		file << "Diem ly: " << ds[i].getLy() << "\n";
		file << "Tong diem: " << ds[i].getTong() << "\n";
	}
	file.close();
}

void SVController::sapxep(string yeucau)
{
	fflush(stdin);

	if(yeucau.compare("sbd")){
		for (int i = 0; i < sosv-1; i++)
			for(int j = i+1; j < sosv; j++)
				if (ds[i].getSbd().compare(ds[j].getSbd()) > 0)
					swap(ds[i], ds[j]);
	}
	if(yeucau.compare("ten")){
		for (int i = 0; i < sosv-1; i++)
			for(int j = i+1; j < sosv; j++)
				if (ds[i].getTen().compare(ds[j].getTen()) > 0)
					swap(ds[i], ds[j]);
	}
	if(yeucau.compare("diem")){
		for (int i = 0; i < sosv-1; i++)
			for(int j = i+1; j < sosv; j++)
				if (ds[i].getTong() > ds[j].getTong())
					swap(ds[i], ds[j]);
	}
}
void SVController::xoa(string yeucau)
{
	//
	//
	// 
	fflush(stdin);
	if(yeucau.compare("ten") == 0){
		string tmp;
		cout << "Nhap ten sinh vien: ";
		getline(cin, tmp);
		for(int i = 0; i < sosv; i++){
			if(ds[i].getTen().compare(tmp) == 0){
				for(i; i < sosv - 1; i++)
					ds[i] = ds[i+1];
				sosv--;
				cout <<"Da xoa\n";
				return;
			}
		}
	}
	if(yeucau.compare("sbd") == 0){
		string tmp;
		cout << "Nhap so bao danh sinh vien: ";
		getline(cin, tmp);
		for(int i = 0; i < sosv; i++){
			if(ds[i].getSbd().compare(tmp) == 0){
				for(i; i < sosv - 1; i++)
					ds[i] = ds[i+1];
				sosv--;
				cout <<"Da xoa\n";
				return;
			}
		}
	}
	cout << "Khong ton tai sinh vien\n";
}

void SVController::capnhat(string yeucau)
{
	fflush(stdin);
	if(yeucau.compare("ten") == 0){
		string tmp;
		cout << "Nhap ten sinh vien: ";
		getline(cin, tmp);
		for(int i = 0; i < sosv; i++){
			if(ds[i].getTen().compare(tmp) == 0){
				ds[i] = nhapThongTin();
				return;
			}
		}
	}
	if(yeucau.compare("sbd") == 0){
		string tmp;
		cout << "Nhap so bao danh sinh vien: ";
		getline(cin, tmp);
		for(int i = 0; i < sosv; i++){
			if(ds[i].getSbd().compare(tmp) == 0){
				ds[i] = nhapThongTin();
				return;
			}
		}
	}
}
void SVController::xuatDs()
{
	cout << "Tong so sinh vien: " << sosv << "\n";
	for(int i = 0; i < sosv; i++){
		cout << "-------------------------\nSinh vien thu " << i+1 << ":\n";
		view.view(ds[i]);
	}
}

void SVController::thongke(string yeucau)
{
	int count = 0;
	if(!yeucau.compare("< 15")){
		for(int i = 0; i < sosv; i++)
			if(ds[i].getTong() < 15){
				cout << "***************\n";
				view.view(ds[i]);
				count++;
			};
	}
	if(!yeucau.compare(">= 15 && < 20")){
		for(int i = 0; i < sosv; i++)
			if(ds[i].getTong() >= 15 && ds[i].getTong() < 20){
				cout << "***************\n";
				view.view(ds[i]);
				count++;
			};
	}
	if(!yeucau.compare(">= 20 && < 25")){
		for(int i = 0; i < sosv; i++)
			if(ds[i].getTong() >= 20 && ds[i].getTong() < 25){
				cout << "***************\n";
				view.view(ds[i]);
				count++;
			};
	}
	if(!yeucau.compare("> 25")){
		for(int i = 0; i < sosv; i++)
			if(ds[i].getTong() > 25){
				cout << "***************\n";
				view.view(ds[i]);
				count++;
			};
	}
	cout << "So sinh vien thong ke duoc: " << count << "\n";
}

bool SVController::luuDuLieu()
{
	ofstream file;
	file.open("output1.txt");
	if(file.is_open()){
		file << sosv << '\n';
		for (int index = 0; index < sosv; index++)
		{
			file << ds[index].getTen() << '-' << ds[index].getSbd() << '-' << ds[index].getDiachi() << '-' << ds[index].getGioitinh();
			file << '-' << ds[index].getToan() << '-' << ds[index].getLy() << '-' << ds[index].getHoa() << '-' << ds[index].getTong();
			file << '\n';
		}
		file.close();
		return true;
	}
	return false;
}