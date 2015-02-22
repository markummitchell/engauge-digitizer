#ifndef CMD_SETTINGS_SEGMENTS_H
#define CMD_SETTINGS_SEGMENTS_H

#include "CmdAbstract.h"
#include "DocumentModelSegments.h"

class QXmlStreamReader;

/// Command for DlgSettingsSegments
class CmdSettingsSegments : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdSettingsSegments(MainWindow &mainWindow,
                      Document &document,
                      const DocumentModelSegments &modelSegmentsBefore,
                      const DocumentModelSegments &modelSegmentsAfter);

  /// Constructor for parsing error report file xml
  CmdSettingsSegments(MainWindow &mainWindow,
                      Document &document,
                      const QString &cmdDescription,
                      QXmlStreamReader &reader);

  virtual ~CmdSettingsSegments();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdSettingsSegments();

  DocumentModelSegments m_modelSegmentsBefore;
  DocumentModelSegments m_modelSegmentsAfter;
};

#endif // CMD_SETTINGS_SEGMENTS_H
