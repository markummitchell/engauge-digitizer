#ifndef DOCUMENT_MODEL_GRID_REMOVAL_H
#define DOCUMENT_MODEL_GRID_REMOVAL_H

#include "DocumentModelAbstractBase.h"
#include "GridCoordDisable.h"

class Document;
class QTextStream;

/// Model for DlgSettingsGridRemoval and CmdSettingsGridRemoval.
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
  void printStream (QTextStream &str) const;

  /// Get method for removing defined grid lines.
  bool removeDefinedGridLines () const;

  /// Get method for removing lines parallel to axes.
  bool removeParallelToAxes () const;

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

  /// Set method for removing lines parallel to axes.
  void setRemoveParallelToAxes (bool removeParallelToAxes);

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

  bool m_removeParallelToAxes;
};

#endif // DOCUMENT_MODEL_GRID_REMOVAL_H
