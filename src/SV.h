#pragma once
#include <string>

using namespace std;

class SinhVien
{
private:
	string ten;
	string sbd;
	string diachi;
	string gioitinh;
	float toan;
	float ly;
	float hoa;
	float tong;
public:
	//constructor
	SinhVien();
	SinhVien(string ten, string sbd, string diachi, string gioitinh, float toan, float hoa, float ly);

	//set information
	void setTen(string);
	void setSbd(string);
	void setDiachi(string);
	void setGioitinh(string);
	void setToan(float);
	void setLy(float);
	void setHoa(float);
	void setTong(float toan, float ly, float hoa);

	//get information
	string getTen();
	string getSbd();
	string getDiachi();
	string getGioitinh();
	float getToan();
	float getLy();
	float getHoa();
	float getTong();
};