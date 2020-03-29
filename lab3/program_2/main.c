#include <windows.h>
#include <processthreadsapi.h >
#include <stdio.h>
#include <time.h>

DWORD WINAPI ThreadProcAdd(LPVOID* lpParam)
{
    unsigned int i;
    for (i = 0; i < 100000000; i++)
        ((volatile long)*lpParam)++;

    ExitThread(0);
};

DWORD WINAPI ThreadProcSub(LPVOID* lpParam)
{
    unsigned int i;
    for (i = 0; i < 100000000; i++)
        ((volatile long)*lpParam)--;

    ExitThread(0);
};

void main()
{
	volatile long variable = 20;
    HANDLE  hThreadArray[20];
    int i;
    time_t start, end;

    printf("Variable = %d\n", variable);
    printf("Creating threads...\n");

    start = clock();

    for (i = 0; i < 10; i++)
    {
        hThreadArray[i] = CreateThread( NULL,                   // дескриптор защиты
                                        0,                      // начальный размер стека
                                        ThreadProcAdd,          // функция
                                        &variable,              // переменная
                                        0,                      // флаги
                                        NULL                    // ID потока
                                      );

        hThreadArray[i + 10] = CreateThread( NULL,                  // дескриптор защиты
                                        0,                      // начальный размер стека
                                        ThreadProcSub,          // функция
                                        &variable,              // переменная
                                        0,                      // флаги
                                        NULL                    // ID потока
                                      );    
        if (!hThreadArray[i])
        {
            printf("[ERROR] Thread %d wasn't created!", i);
            return;
        }

        if (!hThreadArray[i + 10])
        {
            printf("[ERROR] Thread %d wasn't created!", i);
            return;
        }

    }

    end = clock();

    if (WaitForMultipleObjects(20, hThreadArray, TRUE, INFINITE) == WAIT_FAILED)
    {
        printf("[ERROR] Wait failed!");
        return;
    }

    for (i = 0; i < 20; i++)
    {
        if (!CloseHandle(hThreadArray[i]))
        {
            printf("[ERROR] Closing process failed!");
            return;
        }
    }

    printf("Variable = %d\n", variable);
    printf("Time = %d\n", end - start);
}