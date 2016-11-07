/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "Curve.h"
#include "CurveConnectAs.h"
#include "CurveStyle.h"
#include "EngaugeAssert.h"
#include "GeometryModel.h"
#include "FittingWindow.h"
#include "Logger.h"
#include <QApplication>
#include <QClipboard>
#include <QHeaderView>
#include <QItemSelectionModel>
#include <QTableView>
#include <QTextStream>

FittingWindow::FittingWindow (QWidget *parent) :
  QDockWidget (parent)
{
  setVisible (false);
  setAllowedAreas (Qt::AllDockWidgetAreas);
  setWindowTitle (tr ("Curve Fitting Window")); // Appears in title bar when undocked
  setStatusTip (tr ("Curve Fitting Window"));
  setWhatsThis (tr ("Curve Fitting Window\n\n"
                    "This window applies a curve fit to the currently selected curve"));
}

FittingWindow::~FittingWindow()
{
}

void FittingWindow::clear ()
{
}

void FittingWindow::closeEvent(QCloseEvent * /* event */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "FittingWindow::closeEvent";

  emit signalFittingWindowClosed();
}

void FittingWindow::update (const CmdMediator &cmdMediator,
                            const MainWindowModel &modelMainWindow,
                            const QString &curveSelected,
                            const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "FittingWindow::update";
}

