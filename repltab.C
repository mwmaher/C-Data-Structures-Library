/* ReplcTab.C

   By Michael W. Maher
   9/13/91

   Replace the TAB character with a space.
*/
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAB_CHARACTER 9

void main(int argc, char **argv);

void main(int argc, char **argv)
  {
  FILE *infile,
       *outfile;
  char buf[201],
       in_buf[2];
  int  i,
       tab_stops;

  if (argc > 3)
    {
    for (i=0; i < sizeof(buf); i++)
       buf[i] = ' ';
    buf[i] = '\0';
    tab_stops = atoi(argv[3]);
    infile = fopen(argv[1], "rt");
    outfile = fopen(argv[2], "wt");
    while(fread(in_buf, sizeof(char), 1, infile) == 1)
      {
      if (in_buf[0] == TAB_CHARACTER)
	fwrite(buf, sizeof(char), tab_stops, outfile);
      else
	fwrite(in_buf, sizeof(char), 1, outfile);
      }
    fclose(infile);
    fclose(outfile);
    }
  else
    {
    printf("\nReplTab by Michael W. Maher 9/13/91");
    printf("\nThis program will replace the TAB character with space(s).");
    printf("\nUSAGE: REPLTAB infilespec outfilespec tab_stops\n");
    }
  return;
  }

