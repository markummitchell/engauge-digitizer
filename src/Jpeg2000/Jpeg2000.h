#ifndef JPEG2000_H
#define JPEG2000_H

class QImage;
class QString;

/// Wrapper around OpenJPEG library for opening jpeg2000 files
class Jpeg2000
{
 public:
  /// Single constructor
  Jpeg2000();

  /// Load image from jpeg2000 file
  bool load (const QString &filename,
             QImage &image) const;
};

#endif // JPEG2000_H
