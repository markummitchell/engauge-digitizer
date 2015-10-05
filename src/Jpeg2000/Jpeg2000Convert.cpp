/*
 * The copyright in this software is being made available under the 2-clauses 
 * BSD License, included below. This software may be subject to other third 
 * party and contributor rights, including patent rights, and no such rights
 * are granted under this license.
 *
 * Copyright (c) 2002-2014, Universite catholique de Louvain (UCL), Belgium
 * Copyright (c) 2002-2014, Professor Benoit Macq
 * Copyright (c) 2001-2003, David Janssens
 * Copyright (c) 2002-2003, Yannick Verschueren
 * Copyright (c) 2003-2007, Francois-Olivier Devaux 
 * Copyright (c) 2003-2014, Antonin Descampe
 * Copyright (c) 2005, Herve Drolon, FreeImage Team
 * Copyright (c) 2006-2007, Parvatha Elangovan
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS `AS IS'
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
//#include "opj_apps_config.h"

#include "Logger.h"
#include "openjpeg.h"
#include "Jpeg2000Convert.h"
#include <QBuffer>
#include <QDataStream>
#include <QDebug>
#include <string.h>

int imagetopnm(opj_image_t * image,
               QBuffer &buffer)
{
  int *red, *green, *blue, *alpha = NULL;
  int wr, hr, max;
  int i;
  unsigned int compno, ncomp;
  int adjustR, adjustG, adjustB, adjustA;
  int two, has_alpha, triple;
  int prec, v;
  char bufferLocal[1024];
  QDataStream str (&buffer);

  if((prec = (int)image->comps[0].prec) > 16)
  {
    fprintf(stderr,"%s:%d:imagetopnm\n\tprecision %d is larger than 16"
            "\n\t: refused.\n",__FILE__,__LINE__,prec);
    return 1;
  }
  two = has_alpha = 0;
  ncomp = image->numcomps;

  if (ncomp == 2 /* GRAYA */
      || (ncomp > 2 /* RGB, RGBA */
          && image->comps[0].dx == image->comps[1].dx
          && image->comps[1].dx == image->comps[2].dx
          && image->comps[0].dy == image->comps[1].dy
          && image->comps[1].dy == image->comps[2].dy
          && image->comps[0].prec == image->comps[1].prec
          && image->comps[1].prec == image->comps[2].prec
          ))
  {
    two = (prec > 8);
    triple = (ncomp > 2);
    wr = (int)image->comps[0].w; hr = (int)image->comps[0].h;
    max = (1<<prec) - 1; has_alpha = (ncomp == 4 || ncomp == 2);

    red = image->comps[0].data;

    if(triple)
    {
      green = image->comps[1].data;
      blue = image->comps[2].data;
    }
    else green = blue = NULL;

    if(has_alpha)
    {
      const char *tt = (triple?"RGB_ALPHA":"GRAYSCALE_ALPHA");

      sprintf(bufferLocal,
              "P7\n# OpenJPEG-%s\nWIDTH %d\nHEIGHT %d\nDEPTH %d\n"
              "MAXVAL %d\nTUPLTYPE %s\nENDHDR\n",
              opj_version(),
              wr,
              hr,
              ncomp,
              max,
              tt);
      str.writeRawData (bufferLocal,
                        strlen (bufferLocal));
      alpha = image->comps[ncomp - 1].data;
      adjustA = (image->comps[ncomp - 1].sgnd ?
                 1 << (image->comps[ncomp - 1].prec - 1) : 0);
    }
    else
    {
      sprintf(bufferLocal,
              "P6\n# OpenJPEG-%s\n%d %d\n%d\n",
              opj_version(),
              wr,
              hr,
              max);
      str.writeRawData (bufferLocal,
                        strlen (bufferLocal));
      adjustA = 0;
    }
    adjustR = (image->comps[0].sgnd ? 1 << (image->comps[0].prec - 1) : 0);

    if(triple)
    {
      adjustG = (image->comps[1].sgnd ? 1 << (image->comps[1].prec - 1) : 0);
      adjustB = (image->comps[2].sgnd ? 1 << (image->comps[2].prec - 1) : 0);
    }
    else adjustG = adjustB = 0;

    for(i = 0; i < wr * hr; ++i)
    {
      if(two)
      {
        v = *red + adjustR; ++red;
        if(v > 65535) v = 65535; else if(v < 0) v = 0;

        sprintf(bufferLocal,
                "%c%c",
                (unsigned char)(v>>8),
                (unsigned char)v);
        str.writeRawData (bufferLocal,
                          2);

        if(triple)
        {
          v = *green + adjustG; ++green;
          if(v > 65535) v = 65535; else if(v < 0) v = 0;

          sprintf(bufferLocal,
                  "%c%c",
                  (unsigned char)(v>>8),
                  (unsigned char)v);
          str.writeRawData  (bufferLocal,
                             2);

          v =  *blue + adjustB; ++blue;
          if(v > 65535) v = 65535; else if(v < 0) v = 0;

          sprintf(bufferLocal,
                  "%c%c",
                  (unsigned char)(v>>8),
                  (unsigned char)v);
          str.writeRawData (bufferLocal,
                            2);

        }/* if(triple) */

        if(has_alpha)
        {
          v = *alpha + adjustA; ++alpha;
          if(v > 65535) v = 65535; else if(v < 0) v = 0;

          sprintf(bufferLocal,
                  "%c%c",
                  (unsigned char)(v>>8),
                  (unsigned char)v);
          str.writeRawData (bufferLocal,
                            2);
        }
        continue;

      }	/* if(two) */

      /* prec <= 8: */
      v = *red++;
      if(v > 255) v = 255; else if(v < 0) v = 0;

      sprintf(bufferLocal,
              "%c",
              (unsigned char)v);
      str.writeRawData (bufferLocal,
                        1);
      if(triple)
      {
	v = *green++;
	if(v > 255) v = 255; else if(v < 0) v = 0;

        sprintf(bufferLocal,
                "%c",
                (unsigned char)v);
        str.writeRawData (bufferLocal,
                          1);
	v = *blue++;
	if(v > 255) v = 255; else if(v < 0) v = 0;

        sprintf(bufferLocal,
                "%c",
                (unsigned char)v);
        str.writeRawData (bufferLocal,
                          1);
      }
      if(has_alpha)
      {
	v = *alpha++;
	if(v > 255) v = 255; else if(v < 0) v = 0;

        sprintf(bufferLocal,
                "%c",
                (unsigned char)v);
        str.writeRawData (bufferLocal,
                          1);
      }
    }	/* for(i */

    return 0;
  }

  /* YUV or MONO: */

  if (image->numcomps > ncomp)
  {
    LOG4CPP_WARN_S ((*mainCat)) << "imagetopnm will only use the first component";
  }

  for (compno = 0; compno < ncomp; compno++)
  {
    wr = (int)image->comps[compno].w;
    hr = (int)image->comps[compno].h;
    prec = (int)image->comps[compno].prec;
    max = (1<<prec) - 1;

    sprintf(bufferLocal,
            "P5\n#OpenJPEG-%s\n%d %d\n%d\n",
            opj_version(),
            wr,
            hr,
            max);
    str.writeRawData (bufferLocal,
                      strlen (bufferLocal));

    red = image->comps[compno].data;
    adjustR =
    (image->comps[compno].sgnd ? 1 << (image->comps[compno].prec - 1) : 0);

    if(prec > 8)
    {
      for (i = 0; i < wr * hr; i++)
      {
        v = *red + adjustR; ++red;
        if(v > 65535) v = 65535; else if(v < 0) v = 0;

        sprintf(bufferLocal,
                "%c%c",
                (unsigned char)(v>>8), (unsigned char)v);
        str.writeRawData (bufferLocal,
                          2);

        if(has_alpha)
        {
          v = *alpha++;
          if(v > 65535) v = 65535; else if(v < 0) v = 0;

          sprintf(bufferLocal,
                  "%c%c",
                  (unsigned char)(v>>8), (unsigned char)v);
          str.writeRawData (bufferLocal,
                            2);
        }
      }/* for(i */
    }
    else /* prec <= 8 */
    {
      for(i = 0; i < wr * hr; ++i)
      {
	v = *red + adjustR; ++red;
	if(v > 255) v = 255; else if(v < 0) v = 0;

        sprintf(bufferLocal,
                "%c",
                (unsigned char)v);
        str.writeRawData (bufferLocal,
                          1);
      }
    }
  } /* for (compno */

  return 0;
}/* imagetopnm() */
