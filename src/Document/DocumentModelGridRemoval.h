/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DOCUMENT_MODEL_GRID_REMOVAL_H
#define DOCUMENT_MODEL_GRID_REMOVAL_H

#include "DocumentModelAbstractBase.h"
#include "GridCoordDisable.h"

class Document;
class QTextStream;

/// Model for DlgSettingsGridRemoval and CmdSettingsGridRemoval. The settings are unstable until the user approves
class DocumentModelGridRemoval : public DocumentModelAbstractBase
{
public:
  /// Default constructor.
  DocumentModelGridRemoval();

  /// Constructor fed by GridClassifier.
  DocumentModelGridRemoval (double startX,
                            double startY,
                            double stepX,
                            double stepY,
                            int countX,
                            int countY);

  /// Initial constructor from Document.
  DocumentModelGridRemoval(const Document &document);

  /// Copy constructor.
  DocumentModelGridRemoval(const DocumentModelGridRemoval &other);

  /// Assignment constructor.
  DocumentModelGridRemoval &operator=(const DocumentModelGridRemoval &other);

  /// Get method for close distance.
  double closeDistance() const;

  /// Get method for x count.
  int countX() const;

  /// Get method for y count.
  int countY() const;

  /// Get method for x coord parameter to disable.
  GridCoordDisable gridCoordDisableX () const;

  /// Get method for y coord parameter to disable.
  GridCoordDisable gridCoordDisableY () const;

  virtual void loadXml(QXmlStreamReader &reader);

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  /// Get method for removing defined grid lines.
  bool removeDefinedGridLines () const;

  virtual void saveXml(QXmlStreamWriter &writer) const;

  /// Set method for close distance.
  void setCloseDistance (double closeDistance);

  /// Set method for x count.
  void setCountX(int countX);

  /// Set method for y count.
  void setCountY(int countY);

  /// Set method for x coord parameter to disable.
  void setGridCoordDisableX (GridCoordDisable gridCoordDisable);

  /// Set method for y coord parameter to disable.
  void setGridCoordDisableY (GridCoordDisable gridCoordDisable);

  /// Set method for removing defined grid lines.
  void setRemoveDefinedGridLines (bool removeDefinedGridLines);

  /// Set the stable flag to true. This public version has no argument since it cannot be undone
  void setStable ();

  /// Set method for x start.
  void setStartX(double startX);

  /// Set method for y start.
  void setStartY(double startY);

  /// Set method for x step.
  void setStepX(double stepX);

  /// Set method for y step.
  void setStepY(double stepY);

  /// Set method for x stop.
  void setStopX(double stopX);

  /// Set method for y stop.
  void setStopY(double stopY);

  /// Get method for stable flag. The flag is false to let the settings get automatically updated, until the
  /// user selects settings - at which point the stable flag is set to true
  bool stable() const;

  /// Get method for x start.
  double startX() const;

  /// Get method for y start.
  double startY() const;

  /// Get method for x step.
  double stepX() const;

  /// Get method for y step.
  double stepY() const;

  /// Get method for x stop.
  double stopX() const;

  /// Get method for y stop.
  double stopY() const;

private:

  void setStable (bool stable); // Private version is for initialization

  bool m_stable;
  bool m_removeDefinedGridLines;
  double m_closeDistance;
  GridCoordDisable m_gridCoordDisableX;
  int m_countX;
  double m_startX;
  double m_stepX;
  double m_stopX;
  GridCoordDisable m_gridCoordDisableY;
  int m_countY;
  double m_startY;
  double m_stepY;
  double m_stopY;
};

#endif // DOCUMENT_MODEL_GRID_REMOVAL_H
