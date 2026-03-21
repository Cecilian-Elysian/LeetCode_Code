#include<stdio.h>
#include<string.h>
#include<stdlib.h>





char* longestCommonPrefix(char** strs, int strsSize)
{


    if (strsSize == 0)
    {
        char* result = (char*)malloc(1);
        result[0] = '\0';
        return result;
    }

    int len = strlen(strs[0]);
   
    char* Returnchar = (char*)malloc(len + 1);

    strcpy(Returnchar, strs[0]);

    for (int i = 1; i < strsSize; i++)
    {
        int count = 0;
        while (Returnchar[count] != '\0' && strs[i][count] != '\0' && Returnchar[count] == strs[i][count])
        {
            count++;
        }
        Returnchar[count] = '\0';

        
        if (Returnchar[0] == '\0')
        {
            return Returnchar;
        }
    }
    return Returnchar;
}

int main()
{
    return 0;
}
    
