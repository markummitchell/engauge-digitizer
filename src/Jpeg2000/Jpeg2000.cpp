#include "format_defs.h"
#include "Jpeg2000.h"
#include "Logger.h"
#include "openjpeg.h" // Before convert.h
#include <QImage>
#include <QString>

#include "convert.h" // Before lcms.h and lcms2.h
#ifdef OPJ_HAVE_LIBLCMS2
#include <lcms2.h>
#endif
#ifdef OPJ_HAVE_LIBLCMS1
#include <lcms.h>
#endif
#include "color.h" // After lcms.h and lcms2.h

Jpeg2000::Jpeg2000()
{
}

bool Jpeg2000::load (const QString &filename,
                     QImage &image) const
{
  opj_dparameters_t parameters;

  opj_set_default_decoder_parameters (&parameters);

  return false;
}

