#include "UI.h"
#include <iostream>
#include <conio.h>

int UI::xuatMenu()
{
	system("CLS");
	cout << "\n*******************************************************";
	cout << "\n*  1. Danh sach sinh vien                             *";
	cout << "\n*                                                     *";
	cout << "\n*  2. Tim kiem theo so bao danh                       *";
	cout << "\n*  3. Tim kiem theo ten sinh vien                     *";
	cout << "\n*  4. Tim kiem theo tong diem                         *";
	cout << "\n*  5. Tim kiem theo diem tung mon                     *";
	cout << "\n*                                                     *";
	cout << "\n*  6. Sap xep danh sach theo alphabet                 *";
	cout << "\n*  7. Sap xep danh sach theo so bao danh              *";
	cout << "\n*  8. Sap xep danh sach theo tong diem                *";
	cout << "\n*                                                     *";
	cout << "\n*  9. Thay doi thong tin sinh vien                    *";
	cout << "\n*  10. Them sinh vien vao danh sach                   *";
	cout << "\n*  11. Thong ke                                       *";
	cout << "\n*  12. Thoat chuong trinh                             *";
	cout << "\n*                                                     *";
	cout << "\n*******************************************************";
	cout << "\nChon chuc nang: ";
	int i = 0;
	cin >> i;
	system("CLS");
	return i;
}
void UI::xuly(SVController *ds, HANDLE* ghSemaphore)
{
	int n, sosv, i = 0;
	char c;
	string dir;
	string temp;
	
	//cout << "Load du lieu phien lam viec truoc(y/n): ";
	//fflush(stdin);
	//getline(cin, temp);
	//while(1){
	//	if(temp.compare("y") == 0)
	//		if(ds->nhapFile("output.txt",0) != true){
	//			cout << "Load khong thanh cong\n";
	//			temp = "n";
	//		} else break;
	//	else{
	//		/*cout << "Chon phuong thuc nhap danh sach:\n1.Ban phim\t2.File\n";
	//		cin >> i;
	//		if (i == 1){
	//			cout << "Nhap so sinh vien: \n";
	//			cin >> sosv;
	//			ds->setSosv(sosv + ds->getSosv());
	//			cout << "Nhap danh sach sinh vien:\n";
	//			ds->nhapTay();
	//		}
	//		if(i == 2)*/
	//			fflush(stdin);
	//			sosv = ds->getSosv();
	//			cout << "Nhap duong dan: ";
	//			getline(cin, dir);
	//			sosv += ds->nhapFile(dir.c_str(), sosv);
	//			ds->setSosv(sosv);
	//			break;			
	//	}
	//}
	system("CLS");
	fflush(stdin);
	while (i = xuatMenu())
	{
		WaitForSingleObject(*ghSemaphore, INFINITE);
		switch (i)
		{
		case 1:
			ds->xuatDs();
			break;
		case 2:
			ds->timkiem("sbd");
			break;
		case 3:
			ds->timkiem("ten");
			break;
		case 4:
			ds->timkiem("tong");
			break;
		case 5:
			cout << "Chon mon:\n1.Toan\t2.Ly\t3.Hoa\n";
			cin >> i;
			if(i == 1)
				ds->timkiem("toan");
			if(i == 2)
				ds->timkiem("ly");
			if(i == 3)
				ds->timkiem("hoa");
			break;
		case 6:
			ds->sapxep("ten");
			cout << "Da sap xep\n";
			break;
		case 7:
			ds->sapxep("sbd");
			cout << "Da sap xep\n";
			break;
		case 8:
			ds->sapxep("tong");
			cout << "Da sap xep\n";
		case 9:
			cout << "Chon chuc nang:\n1.Cap nhat thong tin sinh vien\n2.Xoa thong tin sinh vien\n";
			cin >> i;
			if(i == 1){
				cout << "Chon sinh vien theo: 1.Ten\t2.So bao danh\n";
				cin >> i;
				if( i == 1) ds->capnhat("ten");
				if( i == 2) ds->capnhat("sbd");
			}else if(i == 2){
				cout << "Xoa theo: 1.Ten\t2.So bao danh\n";
				cin >> i;
				if( i == 1) ds->xoa("ten");
				if(i == 2) ds->xoa("sbd");
			}
			break;
		case 10:
			cout << "Nhap so sinh vien can them: ";
			cin >> n;
			for ( i = 0; i < n; i++){
				ds->ds[i+ds->getSosv()] = ds->nhapThongTin();
				cout << "***********\n";
				for( int j = 0; j < (ds->getSosv()+i) ; j++){
					if(ds->ds[j].getSbd() == ds->ds[i+ds->getSosv()].getSbd()){
						cout << "So bao danh bi trung, nhap lai thong tin\n";
						i--;
					}
				}
			}
			ds->setSosv(n + ds->getSosv());
			break;
		case 11:
			cout << "Nhap yeu cau thong ke:\n1. Sinh vien co diem nho hon 15\n2. Sinh vien co diem tu 15 den 20\n3. Sinh vien co diem tu 20 den 25\n4. Sinh vien co diem lon hon 25\n";
			cin >> i;
			if(i == 1)	ds->thongke("< 15");
			if(i == 2)	ds->thongke(">= 15 && < 20");
			if(i == 3)	ds->thongke(">= 20 && < 25");
			if(i == 4)	ds->thongke("> 25");
			break;
		case 12:
			if(!ds->luuDuLieu())
				cout << "Luu du lieu khong thanh cong\n";
			cout << "Luu du lieu thanh cong\n";
			return;
		default: 
			continue;
		}
		do{
			cout << "Quay tro lai menu(y/n): ";
			fflush(stdin);
			c = getchar();
			if (!ReleaseSemaphore( 
				*ghSemaphore,  // handle to semaphore
				1,            // increase count by one
				NULL) )       // not interested in previous count
			{
				printf("ReleaseSemaphore[2] error: %d\n", GetLastError());
			}
		}while(c != 'y');
	}

}