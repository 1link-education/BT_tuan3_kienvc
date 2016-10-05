#include <iostream>
#include "SV.h"

//using namespace std;

SinhVien::SinhVien()
{
	ten = '\0';
	sbd = '\0';
	diachi = '\0';
	gioitinh = '\0';
	toan = 0;
	ly = 0;
	hoa = 0;
}
SinhVien::SinhVien(string ten, string sbd, string diachi, string gioitinh, float toan, float ly, float hoa)
{
	this->ten = ten;
	this->sbd = sbd;
	this->diachi = diachi;
	this->gioitinh = gioitinh;
	this->toan = toan;
	this->ly = ly;
	this->hoa = hoa;
	this->tong = toan + ly + hoa;
}
void SinhVien::setTen(string str)
{
	ten = str;
}
void SinhVien::setSbd(string str)
{
	sbd = str;
}
void SinhVien::setDiachi(string str)
{
	diachi = str;
}
void SinhVien::setGioitinh(string str)
{
	gioitinh = str;
}
void SinhVien::setToan(float diem)
{
	toan = diem;
}
void SinhVien::setLy(float diem)
{
	ly = diem;
}
void SinhVien::setHoa(float diem)
{
	hoa = diem;
}
void SinhVien::setTong(float toan, float ly, float hoa)
{
	this->tong = toan + ly + hoa;
}
string SinhVien::getTen()
{
	return ten;
}
string SinhVien::getDiachi()
{
	return diachi;
}
string SinhVien::getSbd()
{
	return sbd;
}
string SinhVien::getGioitinh()
{
	return gioitinh;
}
float SinhVien::getToan()
{
	return toan;
}
float SinhVien::getLy()
{
	return ly;
}
float SinhVien::getHoa()
{
	return hoa;
}
float SinhVien::getTong()
{
	tong = toan + ly +hoa;
	return tong;
}
