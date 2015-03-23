#ifndef CMD_ADD_POINT_GRAPH_H
#define CMD_ADD_POINT_GRAPH_H

#include "CmdAbstract.h"
#include <QPointF>

class QXmlStreamReader;
class Transformation;

/// Command for adding one graph point.
class CmdAddPointGraph : public CmdAbstract
{
 public:
  /// Constructor for normal creation
  CmdAddPointGraph(MainWindow &mainWindow,
                   Document &document,
                   const QString &curveName,
                   const QPointF &posScreen);

  /// Constructor for parsing error report file xml
  CmdAddPointGraph(MainWindow &mainWindow,
                   Document &document,
                   const QString &cmdDescription,
                   QXmlStreamReader &reader);

  virtual ~CmdAddPointGraph();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdAddPointGraph();

  // Depending on CurveStyle settings, determine where in its Curve it will be inserted. This is specified as the ordinal.
  // This is static so it is available during construction
  static double ordinalForNewPoint (const Document &document,
                                    const Transformation &transformation,
                                    const QPointF &posScreen,
                                    const QString &curveName);

  QString m_curveName;
  QPointF m_posScreen;
  QString m_identifierAdded; // Point that got added
  double m_ordinal;
};

#endif // CMD_ADD_POINT_GRAPH_H
