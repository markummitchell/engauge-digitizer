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
  m_curveAxes (nullptr),
  m_curvesGraphs (nullptr)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdPointChangeBase::CmdPointChangeBase";
}

CmdPointChangeBase::~CmdPointChangeBase()
{
}

void CmdPointChangeBase::restoreDocumentState (Document &document) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdPointChangeBase::restoreDocumentState";

  ENGAUGE_CHECK_PTR (m_curveAxes);
  ENGAUGE_CHECK_PTR (m_curvesGraphs);

  document.setCurveAxes (*m_curveAxes);
  document.setCurvesGraphs (*m_curvesGraphs);
}

void CmdPointChangeBase::saveDocumentState (const Document &document)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdPointChangeBase::saveDocumentState";

  delete m_curveAxes;
  delete m_curvesGraphs;

  m_curveAxes = new Curve (document.curveAxes());
  m_curvesGraphs = new CurvesGraphs (document.curvesGraphs());
}
