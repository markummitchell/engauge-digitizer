/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_POINT_CHANGE_BASE_H
#define CMD_POINT_CHANGE_BASE_H

#include "CmdAbstract.h"

class Curve;
class CurvesGraphs;
class Document;

/// Base class for CmdBase leaf subclasses that involve point additions, deletions and/or modifications.
/// This class uses a strategy of taking a snapshot of all points before the redo, and then applying that
/// snapshot to the Document to (later) perform the undo. Before this strategy, the strategy was to just do
/// the opposite steps of the redo, but that strategy was too fragile since it implicity assumed no point
/// changes occurred after the redo of this command and before the redo of the next command. However, point
/// updates like "ordinal maintenance" do occur during that time period
class CmdPointChangeBase : public CmdAbstract
{
public:
  /// Single constructor
  CmdPointChangeBase(MainWindow &mainWindow,
                     Document &document,
                     const QString &cmdDescription);

  virtual ~CmdPointChangeBase();

protected:

  /// Restore the document previously saved by saveDocumentState
  void restoreDocumentState (Document &document) const;

  /// Save the document state for restoration by restoreDocumentState
  void saveDocumentState (const Document &document);

private:
  CmdPointChangeBase();

  Curve *m_curveAxes;
  CurvesGraphs *m_curvesGraphs;
};

#endif // CMD_POINT_CHANGE_BASE_H
