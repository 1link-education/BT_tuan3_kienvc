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
		HANDLE listFile = FindFirstFile(L"DIEM_THI_2016\\*", &file_data);
		file.open("output.txt");
		while(listFile != INVALID_HANDLE_VALUE)
		{
			i++;
			if(i > 2){
				wstring tmp = L"DIEM_THI_2016\\";
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
			printf("ReleaseSemaphore[0] error: %d\n", GetLastError());
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
		WaitForSingleObject(ghSemaphore[2], INFINITE);
		
		ds.nhapFiles("output.txt");
		
		//LeaveCriticalSection(&critical);
		if (!ReleaseSemaphore( 
			ghSemaphore[2],  // handle to semaphore
			1,            // increase count by one
			NULL) )       // not interested in previous count
		{
			printf("ReleaseSemaphore[2] error: %d\n", GetLastError());
		}
		if (!ReleaseSemaphore( 
			ghSemaphore[1],  // handle to semaphore
			1,            // increase count by one
			NULL) )       // not interested in previous count
		{
			printf("ReleaseSemaphore error[1]: %d\n", GetLastError());
		}
	}
	return 0;
}


int main(int argc, char argv[])
{
	
	SVView view;
	ds = SVController(view);
	UI ui;

	ghSemaphore[0] = CreateSemaphore( NULL, 0, 1, NULL);
	ghSemaphore[1] = CreateSemaphore( NULL, 0, 1, NULL);
	ghSemaphore[2] = CreateSemaphore( NULL, 1, 1, NULL);

	_beginthreadex(0, 0, FolderFilesWatchThread, _T("DIEM_THI_2016") , 0, 0);
	_beginthreadex(0, 0 ,readData, NULL , 0, 0);
	
	ui.xuly(&ds,&ghSemaphore[2]);

	CloseHandle(ghSemaphore[0]);
	CloseHandle(ghSemaphore[1]);
	CloseHandle(ghSemaphore[2]);


	return 0;
}

