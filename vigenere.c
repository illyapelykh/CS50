#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, string argv[])
{
    if (argc != 2)
    {
    printf("Usage: ./vigenere key-word\n");
    return 1;
    }
    
    int key [strlen(argv[1])];
    string keyword = argv[1];
    
    if (argc == 2)
    {
    
        for (int i = 0, nk = strlen(keyword); i < nk ; i++)
        {
            if (islower(keyword[i]))
            key[i] = (int)keyword[i] % 97;
            
            if (isupper(keyword[i]))
            key[i] = (int)keyword[i] % 65;
            
            if (isalpha(keyword[i]) == false)
            {
            printf("Use a valid key\n");
            return 1;
            }
        }
    }    
    
    string o_text = GetString();
    
    int count = 0;//Parallel index for key define
        
        for (int i = 0, nt = strlen(o_text) ; i < nt ; i++)
        {
            
            if (isalpha(o_text[i]) && islower(o_text[i]))
            {
                o_text[i] = (o_text[i] - 97 + key[count % strlen(keyword)]) % 26 + 97;
                printf("%c" , o_text[i]);
                count++;
            }
            else if (isalpha(o_text[i]) && isupper(o_text[i]))
            {
                o_text[i] = (o_text[i] - 65 + key[count % strlen(keyword)]) % 26 + 65;
                printf("%c" , o_text[i]);
                count++;
            }
            else
            printf("%c" , o_text[i]);
            
        }
        printf("\n");
     return 0;
}    
