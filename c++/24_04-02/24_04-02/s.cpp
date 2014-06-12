#include <stdio.h>
#include <conio.h>
#include <string.h>

void Base64_code(char* strIn, char* strOut)
{
   static char base64ABC[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
   int len = strlen(strIn);
   int j=0;

   for(int i=0; i<len; i+=3) 
   {
      long l = ( ((long)strIn[i ])<<16 ) |
         (((i+1) < len) ? (((long)strIn[i+1])<<8 ) : 0 ) |
         (((i+2) < len) ? ( (long)strIn[i+2] ) : 0 );

      strOut[j++] = base64ABC[(l>>18) & 0x3F];
      strOut[j++] = base64ABC[(l>>12) & 0x3F];

      if (i+1 < len) strOut[j++] = base64ABC[(l>> 6) & 0x3F];
      if (i+2 < len) strOut[j++] = base64ABC[(l ) & 0x3F];
   }

   switch (len%3) 
   {
   case 1:
      strOut[j++] = '=';
   case 2:
      strOut[j++] = '=';
   }

   strOut[j]='\0';
}

void main()
{
   char StrIn[100], StrOut[100];

   printf( "Input string> " );
   gets( StrIn );
   Base64_code( StrIn, StrOut );
   printf ( "Source String \"%s\", destination string \"%s\"", StrIn, StrOut );
   _getch();
}