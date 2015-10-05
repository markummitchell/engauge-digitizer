#ifndef JPEG2000_H
#define JPEG2000_H

#include "openjpeg.h" // Before Jpeg2000Convert.h

#include "Jpeg2000Convert.h" // Before lcms.h and lcms2.h
#ifdef OPJ_HAVE_LIBLCMS2
#include <lcms2.h>
#endif
#ifdef OPJ_HAVE_LIBLCMS1
#include <lcms.h>
#endif
#include "Jpeg2000Color.h" // After lcms.h and lcms2.h
#include <QStringList>

class QImage;
class QString;

/// Wrapper around OpenJPEG library, in C, for opening jpeg2000 files
class Jpeg2000
{
 public:
  /// Single constructor
  Jpeg2000();

  /// Load image from jpeg2000 file
  bool load (const QString &filename,
             QImage &image) const;

  /// List the supported jpeg2000 file extensions, for filtering import files
  QStringList supportedImageWildcards () const;

 private:

  void applyImageTweaks (opj_image_t *image) const;
  opj_codec_t *decode (int decodeFormat) const;
  int getFileFormat(const char *filename) const;
  void initializeParameters (opj_dparameters_t &parameters) const;
  int inputFormat(const char *filename) const;
  bool invalidFileExtension (const QString &filename) const;
  QStringList supportedFileExtensions () const;

};

#endif // JPEG2000_H
