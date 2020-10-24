/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CRC32_H
#define CRC32_H

#include <QString>

/// Compute crc checksum that linux cksum would produce for specified bytes. Based on IEEE Std 1003.1 - 2017
class Crc32
{
 public:
  /// Single default constructor
  Crc32 ();

  /// Compute the checksum using data in file
  unsigned filecrc (const QString &filename) const;

  /// Compute the checksum using data in memory
  unsigned memcrc (const unsigned char *b,
                   unsigned int n) const;
  
 private:

  /// Encoding polynomial table for
  /// G(x) = x^32 + x^26 + x^23 + x^22 + x^16 + x^12 +x^11 + x^10 + x^8 + x^6 + x^5 + x^4 + x^2 + x + 1
  static unsigned long m_crctab[];
};

#endif // CRC32_H
