// Copyright (c) 1999-2012 OPEN CASCADE SAS
//
// The content of this file is subject to the Open CASCADE Technology Public
// License Version 6.5 (the "License"). You may not use the content of this file
// except in compliance with the License. Please obtain a copy of the License
// at http://www.opencascade.org and read it completely before using this file.
//
// The Initial Developer of the Original Code is Open CASCADE S.A.S., having its
// main offices at: 1, place des Freres Montgolfier, 78280 Guyancourt, France.
//
// The Original Code and all software distributed under the License is
// distributed on an "AS IS" basis, without warranty of any kind, and the
// Initial Developer hereby disclaims all such warranties, including without
// limitation, any warranties of merchantability, fitness for a particular
// purpose or non-infringement. Please see the License for the specific terms
// and conditions governing the rights and limitations under the License.

/*
* Fonction
* ~~~~~~~~
*   Gestion des images sous OpenGL
*
*
* Attention:
* ~~~~~~~~~~~
*  Ce package a ete teste sur SGI, OSF, SUN, HP et WNT.
*
*
* Historique des modifications
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*   22-05-97: PCT ; creation
*   10-07-98: FGU ; Ajout : ReadScaledImage 
*                   Mise a jour des dimensions de l image
*    02.15.100 JR : Implicit convertion
*/
/*----------------------------------------------------------------------*/

/*----------------------------------------------------------------------*/
/*
* Includes
*/

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include <OpenGl_ImageBox.hxx>

/*----------------------------------------------------------------------*/
/*
* Types definis
*/

typedef struct _ImageRec {
  unsigned short imagic;
  unsigned short type;
  unsigned short dim;
  unsigned short xsize, ysize, zsize;
  unsigned int min, max;
  unsigned int wasteBytes;
  char name[80];
  unsigned long colorMap;
  FILE *file;
  unsigned char *tmp, *tmpR, *tmpG, *tmpB;
  unsigned long rleEnd;
  unsigned int *rowStart;
  int *rowSize;
} ImageRec;

/*----------------------------------------------------------------------*/
/*
* Fonctions privees
*/

static void
ConvertShort(unsigned short *array, long length) {
  unsigned long b1, b2;
  unsigned char *ptr;

  ptr = (unsigned char *)array;
  while (length--) {
    b1 = *ptr++;
    b2 = *ptr++;
    *array++ = (unsigned short )((b1 << 8) | (b2));
  }
}
/*----------------------------------------------------------------------*/

static void
ConvertLong(unsigned *array, long length) {
  unsigned long b1, b2, b3, b4;
  unsigned char *ptr;

  ptr = (unsigned char *)array;
  while (length--) {
    b1 = *ptr++;
    b2 = *ptr++;
    b3 = *ptr++;
    b4 = *ptr++;
    *array++ = (b1 << 24) | (b2 << 16) | (b3 << 8) | (b4);
  }
}
/*----------------------------------------------------------------------*/

static ImageRec *ImageOpen(char *fileName)
{
  union {
    int testWord;
    char testByte[4];
  } endianTest;
  ImageRec *image;
  int swapFlag;
  int x;

  endianTest.testWord = 1;
  if (endianTest.testByte[0] == 1) {
    swapFlag = 1;
  } else {
    swapFlag = 0;
  }

  image = new ImageRec();
  if (image == NULL) {
    fprintf(stderr, "Out of memory!\n");
    exit(1);
  }
  if ((image->file = fopen(fileName, "rb")) == NULL) {
    perror(fileName);
    exit(1);
  }

  fread(image, 1, 12, image->file);

  if (swapFlag) {
    ConvertShort(&image->imagic, 6);
  }

  image->tmp = new unsigned char[image->xsize*256];
  image->tmpR = new unsigned char[image->xsize*256];
  image->tmpG = new unsigned char[image->xsize*256];
  image->tmpB = new unsigned char[image->xsize*256];
  if (image->tmp == NULL || image->tmpR == NULL || image->tmpG == NULL ||
    image->tmpB == NULL) {
      fprintf(stderr, "Out of memory!\n");
      exit(1);
    }

    if ((image->type & 0xFF00) == 0x0100) {
      x = image->ysize * image->zsize * sizeof(unsigned);
      image->rowStart = new unsigned[x];
      image->rowSize = new int[x];
      if (image->rowStart == NULL || image->rowSize == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(1);
      }
      image->rleEnd = 512 + (2 * x);
      fseek(image->file, 512, SEEK_SET);
      fread(image->rowStart, 1, x, image->file);
      fread(image->rowSize, 1, x, image->file);
      if (swapFlag) {
        ConvertLong(image->rowStart, x/sizeof(unsigned));
        ConvertLong((unsigned *)image->rowSize, x/sizeof(int));
      }
    }
    return image;
}
/*----------------------------------------------------------------------*/

static void
ImageClose(ImageRec *image) {
  fclose(image->file);
  delete [] image->tmp;
  delete [] image->tmpR;
  delete [] image->tmpG;
  delete [] image->tmpB;
  delete [] image->rowStart;
  delete [] image->rowSize;
  delete image;
}
/*----------------------------------------------------------------------*/

static void
ImageGetRow(ImageRec *image, unsigned char *buf, int y, int z) {
  unsigned char *iPtr, *oPtr, pixel;
  int count;

  if ((image->type & 0xFF00) == 0x0100) {
    fseek(image->file, image->rowStart[y+z*image->ysize], SEEK_SET);
    fread(image->tmp, 1, (unsigned int)image->rowSize[y+z*image->ysize],
      image->file);

    iPtr = image->tmp;
    oPtr = buf;
    while (1) {
      pixel = *iPtr++;
      count = (int)(pixel & 0x7F);
      if (!count) {
        return;
      }
      if (pixel & 0x80) {
        while (count--) {
          *oPtr++ = *iPtr++;
        }
      } else {
        pixel = *iPtr++;
        while (count--) {
          *oPtr++ = pixel;
        }
      }
    }
  } else {
    fseek(image->file, 512+(y*image->xsize)+(z*image->xsize*image->ysize),
      SEEK_SET);
    fread(buf, 1, image->xsize, image->file);
  }
}

/*----------------------------------------------------------------------*/
/*
* Fonctions publiques 
*/

/*----------------------------------------------------------------------*/
void ReadScaledImage(char *file, int xsize, int ysize, char *buf, unsigned short *zsize)
{    
  ImageRec *image = ImageOpen(file);
  unsigned char *rbuf, *gbuf=NULL, *bbuf=NULL;    
  int row, rrow, i, ri;
  char *p = buf;

  *zsize = image->zsize;

  /* Allocation memoire */
  rbuf = new unsigned char[image->xsize];

  if (image->zsize > 2) {
    gbuf = new unsigned char[image->xsize];
    bbuf = new unsigned char[image->xsize];
  }

  /* Lecture image rang apres rang */    
  for (row = 0; row < ysize; row++) {
    /* rang a lire */
    rrow = (row*image->ysize)/ysize;

    if (*zsize > 2) {
      ImageGetRow(image, rbuf, rrow, 0);
      ImageGetRow(image, gbuf, rrow, 1);
      ImageGetRow(image, bbuf, rrow, 2);
    }
    else
      ImageGetRow(image, rbuf, rrow, 0);

    /* stockage au format RGB */
    for (i=0; i < xsize; i++) {
      ri = (i*image->xsize)/xsize;
      if (*zsize > 2) {
        *p++ = rbuf[ri];
        *p++ = gbuf[ri];
        *p++ = bbuf[ri];
      }
      else {
        *p++ = rbuf[ri];
        *p++ = rbuf[ri];
        *p++ = rbuf[ri];
      }
    }
  }

  /* delete image buffers */
  delete [] rbuf;
  if (*zsize > 2) {
    delete [] gbuf;
    delete [] bbuf;
  }

  ImageClose(image);    
}

/*----------------------------------------------------------------------*/
void ReadSizeImage(char *file, int *xsize, int *ysize)
{
  /* Lecture image */
  ImageRec *image = ImageOpen(file);

  /* Affectation taille */
  *xsize = image->xsize;
  *ysize = image->ysize;
}

/*----------------------------------------------------------------------*/
void bwtorgba(unsigned char *b,unsigned char *l,int n) {
  while(n--) {
    l[0] = *b;
    l[1] = *b;
    l[2] = *b;
    l[3] = 0xff;
    l += 4; b++;
  }
}

/*----------------------------------------------------------------------*/

void rgbtorgba(unsigned char *r,unsigned char *g,unsigned char *b,unsigned char *l,int n) {
  while(n--) {
    l[0] = r[0];
    l[1] = g[0];
    l[2] = b[0];
    l[3] = 0xff;
    l += 4; r++; g++; b++;
  }
}

/*----------------------------------------------------------------------*/

void rgbatorgba(unsigned char *r,unsigned char *g,unsigned char *b,unsigned char *a,unsigned char *l,int n) {
  while(n--) {
    l[0] = r[0];
    l[1] = g[0];
    l[2] = b[0];
    l[3] = a[0];
    l += 4; r++; g++; b++; a++;
  }
}

/*----------------------------------------------------------------------*/

unsigned *
read_texture(char *name, int *width, int *height, int *components) {
  unsigned *base, *lptr;
  unsigned char *rbuf, *gbuf, *bbuf, *abuf;
  ImageRec *image;
  int y;

  image = ImageOpen(name);

  if(!image)
    return NULL;
  (*width)=image->xsize;
  (*height)=image->ysize;
  (*components)=image->zsize;
  base = new unsigned[image->xsize*image->ysize];
  rbuf = new unsigned char[image->xsize];
  gbuf = new unsigned char[image->xsize];
  bbuf = new unsigned char[image->xsize];
  abuf = new unsigned char[image->xsize];
  if(!base || !rbuf || !gbuf || !bbuf)
  {  
    delete [] base;
    delete [] rbuf;
    delete [] gbuf;
    delete [] bbuf;
    delete [] abuf;
    return NULL;
  }
  lptr = base;
  for(y=0; y<image->ysize; y++) {
    if(image->zsize>=4) {
      ImageGetRow(image,rbuf,y,0);
      ImageGetRow(image,gbuf,y,1);
      ImageGetRow(image,bbuf,y,2);
      ImageGetRow(image,abuf,y,3);
      rgbatorgba(rbuf,gbuf,bbuf,abuf,(unsigned char *)lptr,image->xsize);
      lptr += image->xsize;
    } else if(image->zsize==3) {
      ImageGetRow(image,rbuf,y,0);
      ImageGetRow(image,gbuf,y,1);
      ImageGetRow(image,bbuf,y,2);
      rgbtorgba(rbuf,gbuf,bbuf,(unsigned char *)lptr,image->xsize);
      lptr += image->xsize;
    } else {
      ImageGetRow(image,rbuf,y,0);
      bwtorgba(rbuf,(unsigned char *)lptr,image->xsize);
      lptr += image->xsize;
    }
  }
  ImageClose(image);
  delete [] rbuf;
  delete [] gbuf;
  delete [] bbuf;
  delete [] abuf;

  return (unsigned *) base;
}

/*----------------------------------------------------------------------*/
