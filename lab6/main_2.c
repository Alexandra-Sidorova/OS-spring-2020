#include <stdio.h>
#include <stdlib.h>

int main()
{
    char* param1 = getenv("PARAM1");
    char* param2 = getenv("PARAM2");
    
    if (param1 == NULL)
    {
        printf("Error. PARAM1 is not found!");
        return -1;
    }
    
    if (param2 == NULL)
    {
        printf("Error. PARAM2 is not found!");
        return -1;
    }
    
    printf("Child. PARAM1 = %s, PARAM2 = %s\n", param1, param2);
    
    return 0;
}