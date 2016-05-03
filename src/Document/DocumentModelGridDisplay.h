/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DOCUMENT_MODEL_GRID_DISPLAY
#define DOCUMENT_MODEL_GRID_DISPLAY

#include "DocumentModelAbstractBase.h"
#include "GridCoordDisable.h"

class Document;
class QTextStream;

/// Model for DlgSettingsGridDisplay and CmdSettingsGridDisplay.
class DocumentModelGridDisplay : public DocumentModelAbstractBase
{
public:
  /// Default constructor.
  DocumentModelGridDisplay();

  /// Initial constructor from Document.
  DocumentModelGridDisplay(const Document &document);

  /// Copy constructor.
  DocumentModelGridDisplay(const DocumentModelGridDisplay &other);

  /// Assignment constructor.
  DocumentModelGridDisplay &operator=(const DocumentModelGridDisplay &other);

  /// Get method for linear/log scale on x/theta.
  CoordScale coordScaleXTheta () const;

  /// Get method for initialized flag.
  bool initialized () const;

  virtual void loadXml(QXmlStreamReader &reader);

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  virtual void saveXml(QXmlStreamWriter &writer) const;

  /// Set method for initialized flag.
  void setInitialized (bool initialized);

  /// Set method for x grid line count.
  void setXCount (unsigned int xCount);

  /// Set method for x grid line disabled variable.
  void setXDisable (GridCoordDisable xDisable);

  /// Set method for x grid line lower bound (inclusive).
  void setXStart (double xStart);

  /// Set method for x grid line increment.
  void setXStep (double xStep);

  /// Set method for x grid line upper bound (inclusive).
  void setXStop (double xStop);

  /// Set method for y grid line count.
  void setYCount (unsigned int yCount);

  /// Set method for y grid line disabled variable.
  void setYDisable (GridCoordDisable yDisable);

  /// Set method for y grid line lower bound (inclusive).
  void setYStart (double yStart);

  /// Set method for y grid line increment.
  void setYStep (double yStep);

  /// Set method for y grid line upper bound (inclusive).
  void setYStop (double yStop);

  /// Get method for x grid line count.
  unsigned int xCount () const;

  /// Get method for x grid line disabled variable.
  GridCoordDisable xDisable () const;

  /// Get method for x grid line lower bound (inclusive).
  double xStart () const;

  /// Get method for x grid line increment.
  double xStep () const;

  /// Get method for x grid line upper bound (inclusive).
  double xStop () const;

  /// Get method for y grid line count.
  unsigned int yCount () const;

  /// Get method for y grid line disabled variable.
  GridCoordDisable yDisable () const;

  /// Get method for y grid line lower bound (inclusive).
  double yStart () const;

  /// Get method for y grid line increment.
  double yStep () const;

  /// Get method for y grid line upper bound (inclusive).
  double yStop () const;

private:

  bool m_initialized;

  GridCoordDisable m_xDisable;
  unsigned int m_xCount;
  double m_xStart;
  double m_xStep;
  double m_xStop;

  GridCoordDisable m_yDisable;
  unsigned int m_yCount;
  double m_yStart;
  double m_yStep;
  double m_yStop;
};

#endif // DOCUMENT_MODEL_GRID_DISPLAY
