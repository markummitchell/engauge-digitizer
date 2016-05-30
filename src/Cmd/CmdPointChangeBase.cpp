/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdPointChangeBase.h"
#include "Curve.h"
#include "CurvesGraphs.h"
#include "Document.h"
#include "EngaugeAssert.h"
#include "Logger.h"

CmdPointChangeBase::CmdPointChangeBase(MainWindow &mainWindow,
                                       Document &document,
                                       const QString &cmdDescription) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription),
  m_curveAxes (0),
  m_curvesGraphs (0)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdPointChangeBase::CmdPointChangeBase";
}

CmdPointChangeBase::~CmdPointChangeBase()
{
}

void CmdPointChangeBase::restoreDocumentState (Document &document) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdPointChangeBase::restoreDocumentState";

  ENGAUGE_ASSERT (m_curveAxes != 0);
  ENGAUGE_ASSERT (m_curvesGraphs != 0);

  document.setCurveAxes (*m_curveAxes);
  document.setCurvesGraphs (*m_curvesGraphs);
}

void CmdPointChangeBase::saveDocumentState (const Document &document)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdPointChangeBase::saveDocumentState";

  if (m_curveAxes != 0) {
    delete m_curveAxes;
    m_curveAxes = 0;
  }

  if (m_curvesGraphs != 0) {
    delete m_curvesGraphs;
    m_curvesGraphs = 0;
  }

  m_curveAxes = new Curve (document.curveAxes());
  m_curvesGraphs = new CurvesGraphs (document.curvesGraphs());
}
