#include <stdio.h>
#include <stdlib.h>

typedef unsigned char BYTE;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    BYTE buffer[512];
    int counter = 0;
    char *filename = malloc(10);
    sprintf(filename, "%03i.jpg", counter);
    FILE *img = fopen(filename,"w");
    int jpegOn = 0;
    while(fread(buffer,512,1,f)==1)
    {

       if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
       {
           if(jpegOn==1)
           {
               fclose(img);
               printf("Started a new jpeg\n");
             jpegOn=1;
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename,"w");
            counter++;
             fwrite(buffer,512,1,img);


           }else{
             printf("Started a new jpeg\n");
             jpegOn=1;
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename,"w");
            counter++;
             fwrite(buffer,512,1,img);
           }

       }
       else if(jpegOn==1)
       {
           fwrite(buffer,512,1,img);
       }


    }
    printf("counter: %i\n", counter);





}
