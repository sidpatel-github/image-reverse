#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
int main(int argc, char *argv[])
{
    char str[MAX];
    char readStrTop[MAX],readStrBottom[MAX];
    FILE * fp;
    int i = 0, j = 0, end, writenBytes ;
    int nblines, nbcols;
    long int fileSize, headerBytes, lineFromTop, lineFromBottom;
    fp = fopen ("m1.pgm", "r+");
   
    fgets(str, MAX, fp);
    fscanf(fp,"%d %d", &nblines, &nbcols);
    fgets(str, MAX, fp);
    fgets(str, MAX, fp);//this is extra one due to fseek

    headerBytes = ftell(fp);
   // printf("header bytes %ld ", headerBytes);
	
    fseek(fp, 0L, SEEK_END);
    fileSize = ftell(fp);
    fseek(fp, headerBytes, SEEK_SET);
   // printf("\nseek %ld ", fileSize);

    lineFromTop = ftell(fp);
    lineFromBottom = fileSize;
  //  printf("before %d",nblines / 2);
    for(i = 0; i < nblines / 2 ; i++)
    {
// set pointer to the beginning of the first line and read line
	fseek(fp, lineFromTop, SEEK_SET);
        fread(readStrTop,sizeof(char), nbcols, fp);
        lineFromTop = ftell(fp);

// set pointer to the beginning of the last line and read line
        fseek(fp, lineFromBottom - nbcols, SEEK_SET);
        fread(readStrBottom,sizeof(char), nbcols, fp);
	lineFromBottom = ftell(fp);

//swap pointers and write lines
	fseek(fp, lineFromTop - nbcols, SEEK_SET);
        fwrite(readStrBottom, sizeof(char), nbcols, fp);
        lineFromTop = ftell(fp);
        fseek(fp, lineFromBottom - nbcols, SEEK_SET);
        fwrite(readStrTop, sizeof(char), nbcols, fp);
	lineFromBottom = ftell(fp) - nbcols;
	}
    fclose(fp);
}
