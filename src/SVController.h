#pragma once
#include "SVView.h"
#include "SV.h"


class SVController
{
private:
	int sosv;
	SVView view;
public:
	SinhVien ds[1000];

	//constructor
	SVController();
	SVController(SVView view);

	void setSosv(int n);
	int getSosv();
	SinhVien nhapThongTin();
	void nhapTay();
	int nhapFile(const char *dir,int index);
	void nhapFiles(const char *dir);
	bool luuDuLieu();
	void timkiem(string yeucau);
	void sapxep(string yeucau);
	void xuatDs();
	void capnhat(string yeucau);
	void xoa(string yeucau);
	void thongke(string yeucau);
};
