/* See LICENSE file for copyright and license details
 *
 * ipp is a photo manager for IOS.  It provides functions such as copying favourite photos.
 * It assumes the IOS file systems is already mounted using a tool such as ifuse.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   if (argc !=3) {
       printf("Usage %s -cp FAVOURITES <ios mount point> <destination>\n", argv[0]); 
       exit(1);
   }
   if (argv[1] != "-cp") {
       printf("Usage %s -cp FAVOURITES <ios mount point> <destination>\n", argv[0]); 
       exit(2);
   }
   if (argv[2] != "FAVOURITES") {
       printf("Usage %s -cp FAVOURITES <ios mount point> <destination>\n", argv[0]); 
       exit(3);
   }

   
   exit (0);
}
