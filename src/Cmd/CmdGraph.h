#ifndef CMD_GRAPH_H
#define CMD_GRAPH_H

#include "CmdAbstract.h"
#include "CurvesGraphs.h"
#include <QHash>
#include <QStringList>

class QXmlStreamReader;

/// Command for changing the currently selected Graph
class CmdGraph : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdGraph(MainWindow &mainWindow);

  /// Constructor for parsing error report file xml
  CmdGraph(MainWindow &mainWindow,
           Document &document,
           const QString &cmdDescription,
           QXmlStreamReader &reader);
  
  virtual ~CmdGraph();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdGraph();

  int m_graphBefore;
  int m_graphAfter;
};

#endif // CMD_GRAPH_H
