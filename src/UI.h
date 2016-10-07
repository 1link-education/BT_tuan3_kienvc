#pragma once
#include "SVController.h"
#include <Windows.h>

class UI
{
public:
	int xuatMenu();
	void xuly(SVController *ds, HANDLE* ghSemaphore);
};