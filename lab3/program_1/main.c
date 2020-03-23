#include <windows.h>
#include <stdio.h>

void main()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// �������� �������� �������.
	if (!CreateProcess( NULL, // ������.
		(LPSTR)"notepad.exe", // ��������� ������ �� ������������.
		NULL,                 // ���������� �������� �� �����������.
		NULL,                 // ���������� ������ �� �����������.
		FALSE,                // ��������� ������������ ����������� � FALSE.
		0,                    // ������� �������� ���.
		NULL,                 // ����������� ���� ������������ ��������.
		NULL,                 // ����������� ��������� ������� ��������.
		&si,                  // ��������� �� ��������� STARTUPINFO.
		&pi)                 // ��������� �� ��������� PROCESS_INFORMATION.
		)
	{
		printf("[ERROR] Process wasn't created!");
		return;
	}
	

	// ����� �� ��� ���, ���� �������� ������� �� ������ �� ������.
	if (WaitForSingleObject(pi.hProcess, INFINITE) == WAIT_FAILED)
	{
		printf("[ERROR] Wait failed!");
		return;
	}

	// ������� ����������� �������� � ������.
	if (!CloseHandle(pi.hProcess))
	{
		printf("[ERROR] Closing process failed!");
		return;
	}
	
	if( !CloseHandle(pi.hThread))
	{
		printf("[ERROR] Closing thread failed!");
		return;
	}
}
