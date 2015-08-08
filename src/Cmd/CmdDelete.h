#ifndef CMD_DELETE_H
#define CMD_DELETE_H

#include "CmdAbstract.h"
#include "CurvesGraphs.h"
#include <QHash>
#include <QStringList>

class QXmlStreamReader;

/// Command for deleting all selected Points.
class CmdDelete : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdDelete(MainWindow &mainWindow,
            Document &document,
            const QStringList &selectedPointIdentifiers);

  /// Constructor for parsing error report file xml
  CmdDelete(MainWindow &mainWindow,
            Document &document,
            const QString &cmdDescription,
            QXmlStreamReader &reader);

  virtual ~CmdDelete();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdDelete();

  bool m_transformIsDefined;
  QString m_csv;
  QString m_html;

  CurvesGraphs m_curvesGraphsRemoved;
};

#endif // CMD_DELETE_H
