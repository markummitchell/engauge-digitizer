#ifndef CMD_COPY_H
#define CMD_COPY_H

#include "CmdAbstract.h"
#include "CurvesGraphs.h"
#include <QHash>
#include <QStringList>

/// Command for moving all selected Points by a specified translation.
class CmdCopy : public CmdAbstract
{
public:
  /// Single constructor.
  CmdCopy(MainWindow &mainWindow,
          Document &document,
          const QStringList &selectedPointIdentifiers);

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdCopy();

  bool m_transformIsDefined;
  QString m_csv;
  QString m_html;

  CurvesGraphs m_curvesGraphs;
};

#endif // CMD_COPY_H
