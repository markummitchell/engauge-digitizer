#include "Jpeg2000.h"
#include "Jpeg2000Callbacks.h"
#include "Jpeg2000Color.h"
#include "Jpeg2000FormatDefs.h"
#include "Logger.h"
#include <QBuffer>
#include <QFile>
#include <QImage>
#include <QString>

#define JP2_RFC3745_MAGIC "\x00\x00\x00\x0c\x6a\x50\x20\x20\x0d\x0a\x87\x0a"
#define JP2_MAGIC "\x0d\x0a\x87\x0a"
#define J2K_CODESTREAM_MAGIC "\xff\x4f\xff\x51"

Jpeg2000::Jpeg2000()
{
}

void Jpeg2000::applyImageTweaks (opj_image_t *image) const
{
  if (image->color_space == OPJ_CLRSPC_SYCC) {
    color_sycc_to_rgb (image);
  }

  if (image->color_space != OPJ_CLRSPC_SYCC &&
      image->numcomps == 3 &&
      image->comps[0].dx == image->comps[0].dy &&
      image->comps[1].dx != 1) {
    image->color_space = OPJ_CLRSPC_SYCC;
  } else if (image->numcomps <= 2) {
    image->color_space = OPJ_CLRSPC_GRAY;
  }

  if (image->icc_profile_buf) {
#if defined(OPJ_HAVE_LIBLCMS1) || defined(OPJ_HAVE_LIBLCMS2)
    color_apply_icc_profile (image);
#endif
    free (image->icc_profile_buf);
    image->icc_profile_buf = 0;
    image->icc_profile_len = 0;
  }
}

opj_codec_t *Jpeg2000::decode (int decodeFormat) const
{
  switch(decodeFormat)
  {
    case J2K_CFMT: /* JPEG-2000 codestream */
      return opj_create_decompress(OPJ_CODEC_J2K);

    case JP2_CFMT: /* JPEG 2000 compressed image data */
      return opj_create_decompress(OPJ_CODEC_JP2);

    case JPT_CFMT: /* JPEG 2000, JPIP */
      return opj_create_decompress(OPJ_CODEC_JPT);

    default:
      break;
  }

  return 0;
}

int Jpeg2000::getFileFormat(const char *filename) const
{
  static const char *extension[] = {"pgx", "pnm", "pgm", "ppm", "bmp",
                                    "tif", "raw", "rawl", "tga", "png",
                                    "j2k", "jp2", "jpt", "j2c", "jpc"};
  static const int format[] = {PGX_DFMT, PXM_DFMT, PXM_DFMT, PXM_DFMT, BMP_DFMT,
                               TIF_DFMT, RAW_DFMT, RAWL_DFMT, TGA_DFMT, PNG_DFMT,
                               J2K_CFMT, JP2_CFMT, JPT_CFMT, J2K_CFMT, J2K_CFMT};
  const char * ext = strrchr(filename, '.');
  if (ext == NULL) {
    return -1;
  }
  ext++;
  if (*ext) {
    for (unsigned int i = 0; i < sizeof(format)/sizeof(*format); i++) {
      if(strcasecmp(ext, extension[i]) == 0) {
        return format[i];
      }
    }
  }

  return -1;
}

void Jpeg2000::initializeParameters (opj_dparameters_t &parameters) const
{
  parameters.cp_reduce = 0;
  parameters.cp_layer = 0;
  parameters.cod_format = 10;
  parameters.decod_format = 1;
  parameters.DA_x0 = 0;
  parameters.DA_x1 = 0;
  parameters.DA_y0 = 0;
  parameters.DA_y1 = 0;
  parameters.m_verbose = 0;
  parameters.tile_index = 0;
  parameters.nb_tile_to_decode = 0;
  parameters.jpwl_correct = 0;
  parameters.jpwl_exp_comps = 0;
  parameters.jpwl_max_tiles = 0;
  parameters.flags = 0;
}

int Jpeg2000::inputFormat(const char *filename) const
{
  FILE *reader;
  const char *s, *magic_s;
  int ext_format, magic_format;
  unsigned char buf[12];
  OPJ_SIZE_T l_nb_read;

  reader = fopen(filename,
                 "rb");

  if (reader == NULL) {
    return -2;
  }

  memset(buf, 0, 12);
  l_nb_read = fread(buf, 1, 12, reader);
  fclose(reader);
  if (l_nb_read != 12) {
    return -1;
  }

  ext_format = getFileFormat(filename);

  if (ext_format == JPT_CFMT) {
    return JPT_CFMT;
  }

  if (memcmp(buf, JP2_RFC3745_MAGIC, 12) == 0 || memcmp(buf, JP2_MAGIC, 4) == 0) {
    magic_format = JP2_CFMT;
    magic_s = ".jp2";
  } else if (memcmp(buf, J2K_CODESTREAM_MAGIC, 4) == 0) {
    magic_format = J2K_CFMT;
    magic_s = ".j2k or .jpc or .j2c";
  } else {
    return -1;
  }

  if (magic_format == ext_format) {
    return ext_format;
  }

  s = filename + strlen(filename) - 4;

  LOG4CPP_ERROR_S ((*mainCat)) << "Jpeg2000::inputFormat"
                               << "The extension of this file is incorrect. Found " << s
                               << ". Should be " << magic_s;

  return magic_format;
}

bool Jpeg2000::invalidFileExtension (const QString &filename) const
{
  const int CHARACTER_IN_EXTENSION = 3;

  bool invalid = true;

  // Look for file extension in approved list. A complication is that we probably want this
  // comparison to be case insensitive
  QString extensionGot = filename.right (CHARACTER_IN_EXTENSION);

  QStringList extensions = supportedFileExtensions();
  QStringList::iterator itr;
  for (itr = extensions.begin(); itr != extensions.end(); itr++) {

    QString extensionWanted = *itr;
    if (QString::compare (extensionGot,
                          extensionWanted,
                          Qt::CaseInsensitive)) {

      // Found it
      invalid = false;
      break;
    }
  }

  return invalid;
}

bool Jpeg2000::load (const QString &filename,
                     QImage &imageResult) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Jpeg2000::load"
                              << " filename=" << filename.toLatin1().data();

  if (invalidFileExtension (filename)) {
    return false;
  }

  opj_dparameters_t parameters;
  initializeParameters (parameters);

  parameters.decod_format = inputFormat (filename.toLatin1().data());

  opj_stream_t *inStream = opj_stream_create_default_file_stream (filename.toLatin1().data(), 1);
  if (!inStream) {
    LOG4CPP_ERROR_S ((*mainCat)) << "Jpeg2000::load encountered error opening stream";
    return false;
  }

  // Create decoder
  opj_codec_t *inCodec = decode (parameters.decod_format);
  if (!inCodec) {
    LOG4CPP_ERROR_S ((*mainCat)) << "Jpeg2000::load encountered error creating decoding stream";
    opj_stream_destroy (inStream);
    return false;
  }

  // Callbacks for local handling of errors
  opj_set_info_handler (inCodec, infoCallback, 0);
  opj_set_warning_handler (inCodec, warningCallback, 0);
  opj_set_error_handler (inCodec, errorCallback, 0);

  if (!opj_setup_decoder (inCodec,
                          &parameters)) {
    LOG4CPP_ERROR_S ((*mainCat)) << "Jpeg2000::load encountered error decoding stream";
    opj_stream_destroy (inStream);
    opj_destroy_codec (inCodec);
    return false;
  }

  // Read header and, if necessary, the JP2 boxes
  opj_image_t *image;
  if (!opj_read_header (inStream,
                        inCodec,
                        &image)) {
    LOG4CPP_ERROR_S ((*mainCat)) << "Jpeg2000::load encountered error reading header";
    opj_stream_destroy (inStream);
    opj_destroy_codec (inCodec);
    opj_image_destroy (image);
    return false;
  }

  // Get the decoded image
  if (!(opj_decode (inCodec,
                    inStream,
                    image) &&
       opj_end_decompress (inCodec,
                           inStream))) {
    LOG4CPP_ERROR_S ((*mainCat)) << "Jpeg2000::load failed to decode image";
    opj_destroy_codec (inCodec);
    opj_stream_destroy (inStream);
    opj_image_destroy (image);
    return false;
  }

  // Close the byte stream
  opj_stream_destroy (inStream);

  applyImageTweaks (image);

  // Transform into ppm image in memory
  bool success = true;
  QBuffer buffer;
  buffer.open (QBuffer::WriteOnly);
  if (imagetopnm (image,
                  buffer)) {
    LOG4CPP_ERROR_S ((*mainCat)) << "Jpeg2000::load failed to generate new image";
    success = false;

  } else {

    // Intermediate file for debugging
//    QFile file ("jpeg2000.ppm");
//    file.open (QIODevice::WriteOnly);
//    file.write (buffer.data());
//    file.close ();

    // Create output
    imageResult.loadFromData(buffer.data());

  }

  // Deallocate
  if (inCodec) {
    opj_destroy_codec (inCodec);
  }
  opj_image_destroy (image);

  return success;
}

QStringList Jpeg2000::supportedFileExtensions () const
{
  QStringList extensions;

  // Entries from openjpeg source code, and may not be correct. Order is unimportant since they are sorted later
  extensions << "j2k" << "jp2" << "jpc" << "jpt";

  return extensions;
}

QStringList Jpeg2000::supportedImageWildcards () const
{
  QStringList extensions = supportedFileExtensions();
  QStringList wildcards;

  QStringList::iterator itr;
  for (itr = extensions.begin(); itr != extensions.end(); itr++) {
    QString extension = *itr;
    QString wildcard = QString ("*.%1").arg (extension);
    wildcards << wildcard;
  }

  return wildcards;
}
