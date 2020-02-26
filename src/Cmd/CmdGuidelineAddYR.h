/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_GUIDELINE_ADD_Y_R_H
#define CMD_GUIDELINE_ADD_Y_R_H

#include "CmdAbstract.h"
#include "GuidelineValues.h"

class QXmlStreamReader;

/// Command for adding one Y/R Guideline value
class CmdGuidelineAddYR : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdGuidelineAddYR(MainWindow &mainWindow,
                    Document &document,
                    double value);

  /// Constructor for parsing error report file xml
  CmdGuidelineAddYR(MainWindow &mainWindow,
                    Document &document,
                    const QString &cmdDescription,
                    QXmlStreamReader &reader);

  virtual ~CmdGuidelineAddYR();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdGuidelineAddYR();

  // Value
  QString m_identifier;
  double m_value;

};

#endif // CMD_GUIDELINE_ADD_Y_R_H
