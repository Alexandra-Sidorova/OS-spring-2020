#include <windows.h>
#include <stdio.h>

void main()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Запустим дочерний процесс.
    if (!CreateProcess( NULL, // модуль.
        (LPSTR)"notepad.exe", // Командная строка не используется.
        NULL,                 // Дескриптор процесса не наследуемый.
        NULL,                 // Дескриптор потока не наследуемый.
        FALSE,                // Установим наследование дескриптора в FALSE.
        0,                    // Флажков создания нет.
        NULL,                 // Используйте блок конфигурации родителя.
        NULL,                 // Используйте стартовый каталог родителя.
        &si,                  // Указатель на структуру STARTUPINFO.
        &pi)                 // Указатель на структуру PROCESS_INFORMATION.
        )
    {
        printf("[ERROR] Process wasn't created!");
        return;
    }
    

    // Ждать до тех пор, пока дочерний процесс не выйдет из работы.
    if (WaitForSingleObject(pi.hProcess, INFINITE) == WAIT_FAILED)
    {
        printf("[ERROR] Wait failed!");
        return;
    }

    // Закроем дескрипторы процесса и потока.
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
