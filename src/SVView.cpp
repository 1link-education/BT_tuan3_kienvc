#include "SVView.h"
#include <iostream>

void SVView::view(SinhVien sv)
{
	cout << "\tTen: " << sv.getTen() << '\n';
	cout << "\tSbd: " << sv.getSbd() << '\n';
	cout << "\tDia chi: " << sv.getDiachi() << '\n';
	cout << "\tGioi tinh: " << sv.getGioitinh() << '\n';
	cout << "\tDiem toan: " << sv.getToan() << '\n';
	cout << "\tDiem ly: " << sv.getLy() << '\n';
	cout << "\tDiem hoa: " << sv.getHoa() << '\n';
	cout << "\tTong diem: " << sv.getTong() << '\n'; 
}


