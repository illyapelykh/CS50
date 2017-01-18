/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include<stdint.h>
#include<stdio.h>
 
int main(void)
{
    // open the card.raw
    FILE* inpf = fopen("card.raw", "r");
    
    // check if open correctly
    if (inpf == NULL)
    {
        fclose(inpf);
        printf("Unable to recover...\n");
        return 1;
    }
    
    // set the buffer
    uint8_t buff[512];
    
    // set the "output file name" counter
    int counter = 0;
    
    // name of the output file
    char name[10]; 
    
    // temporary output file
    FILE* outf = NULL;
    
    // read the "card.raw" till the end
    while (!feof(inpf))
    {
        // chek if read file is JPEG
        if (buff[0] == 0xff && buff[1] == 0xd8 && buff[2] == 0xff && (buff[3] == 0xe0 || buff[3] == 0xe1))
        {
            // close if already exist
            if (outf != NULL)
            fclose(outf);
        
        // set the name of first JPEG
        sprintf(name, "%03d.jpg", counter);
        
        // next file
        outf = fopen(name, "w");
            
        // increase the counter
        counter++;
            
        // new file with buffer
        fwrite(buff, sizeof(buff), 1, outf);
        
        }
        
        else if (counter > 0)
        {
            // put jpg into temporary output file
            fwrite(buff, sizeof(buff), 1, outf);  
        }
        
        // start/end to read buffer
        fread(buff, sizeof(buff), 1, inpf);
    }
    
    // close the file
    fclose(inpf);

    return 0;
}
