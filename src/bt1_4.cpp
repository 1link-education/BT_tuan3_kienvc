// bt1_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "UI.h"
#include <Windows.h>
#include <iostream>
#include <process.h>
#include <fstream>
#include <conio.h>

using namespace std;
CRITICAL_SECTION critical;
HANDLE ghSemaphore[3];
static SVController ds;


unsigned __stdcall FolderFilesWatchThread(LPVOID lpParam) // thread procedure
{
	WIN32_FIND_DATA file_data;
	ofstream file;

	HANDLE hFileChange = FindFirstChangeNotification((LPTSTR)lpParam, // folder path
		FALSE,            // don't look in subfolders
		FILE_NOTIFY_CHANGE_FILE_NAME); 

	if(INVALID_HANDLE_VALUE == hFileChange)
	{
		cout << "\n ERROR: FindFirstChangeNotification function failed.\n";
		DWORD dwError = GetLastError();
		// handle error (see this FAQ)
		return dwError;
	}

	WaitForSingleObject(hFileChange, INFINITE);

	while(TRUE)
	{
		int i = 0;
		//WaitForSingleObject(hFileChange, INFINITE);

		//while(!TryEnterCriticalSection(&critical)){}
		HANDLE listFile = FindFirstFile(L"C:\\Users\\vuchi\\Documents\\Visual Studio 2008\\Projects\\bt1_4\\bt1_4\\Diem_thi\\*", &file_data);
		file.open("output.txt");
		while(listFile != INVALID_HANDLE_VALUE)
		{
			i++;
			if(i > 2){
				wstring tmp = L"C:\\Users\\vuchi\\Documents\\Visual Studio 2008\\Projects\\bt1_4\\bt1_4\\Diem_thi\\";
				wstring dir1(file_data.cFileName);
				tmp += dir1;
				string dir2(tmp.begin(), tmp.end());
				file << dir2 << "\n";
			}
			if(FindNextFile(listFile, &file_data) == FALSE)
				break;
		}
		file.close();
		if (!ReleaseSemaphore( 
			ghSemaphore[0],  // handle to semaphore
			1,            // increase count by one
			NULL) )       // not interested in previous count
		{
			printf("ReleaseSemaphore error: %d\n", GetLastError());
		}
		FindNextChangeNotification(hFileChange);
		//LeaveCriticalSection(&critical);
		WaitForSingleObject(hFileChange, INFINITE);
		WaitForSingleObject(ghSemaphore[1], INFINITE);


	}
	return 0;
}
unsigned __stdcall readData(void* Param) // thread procedure
{	
	ifstream file;
	//SVController ds = *(SVController*) Param;

	while(1)
	{
		WaitForSingleObject( ghSemaphore[0],   // handle to semaphore
			INFINITE);           // zero-second 
		//while(!TryEnterCriticalSection(&critical)){}
		ds.nhapFiles("output.txt");
		//LeaveCriticalSection(&critical);
		if (!ReleaseSemaphore( 
			ghSemaphore[1],  // handle to semaphore
			1,            // increase count by one
			NULL) )       // not interested in previous count
		{
			printf("ReleaseSemaphore error: %d\n", GetLastError());
		}
	}
	return 0;
}


int main(int argc, char argv[])
{
	
	SVView view;
	ds = SVController(view);
	UI ui;

	for(int i = 0; i < 2; i++)
	{
		ghSemaphore[i] = CreateSemaphore( 
			NULL,           // default security attributes
			0,  // initial count
			1,  // maximum count
			NULL);          // unnamed semaphore

		if (ghSemaphore[i] == NULL) 
		{
			printf("CreateSemaphore error: %d\n", GetLastError());
			return 1;
		}
	}
	_beginthreadex(0, 0, FolderFilesWatchThread, _T("C:\\Users\\vuchi\\Documents\\Visual Studio 2008\\Projects\\bt1_4\\bt1_4\\Diem_thi") , 0, 0);
	_beginthreadex(0, 0 ,readData, NULL , 0, 0);
	
	ui.xuly(&ds);

	CloseHandle(ghSemaphore[0]);
	CloseHandle(ghSemaphore[1]);

	return 0;
}

