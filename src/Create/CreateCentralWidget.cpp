/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CreateCentralWidget.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QVBoxLayout>
#include <QWidget>

CreateCentralWidget::CreateCentralWidget()
{
}

void CreateCentralWidget::create(MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CreateCentralWidget::create";

  QWidget *widget = new QWidget;
  mw.setCentralWidget (widget);
  mw.m_layout = new QVBoxLayout;
  widget->setLayout (mw.m_layout);
}
