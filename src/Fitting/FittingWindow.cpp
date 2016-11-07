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
#include "FittingModel.h"
#include "GeometryModel.h"
#include "FittingWindow.h"
#include "Logger.h"
#include <QApplication>
#include <QClipboard>
#include <QComboBox>
#include <QGridLayout>
#include <QHeaderView>
#include <QItemSelectionModel>
#include <QLabel>
#include <QLineEdit>
#include <QTableView>
#include <QTextStream>

const int COLUMN_COEFFICIENTS = 0;
const int COLUMN_POLYNOMIAL_TERMS = 1;

FittingWindow::FittingWindow (QWidget *parent) :
  QDockWidget (parent),
  m_isLogXTheta (false),
  m_isLogYRadius (false)
{
  setVisible (false);
  setAllowedAreas (Qt::AllDockWidgetAreas);
  setWindowTitle (tr ("Curve Fitting Window")); // Appears in title bar when undocked
  setStatusTip (tr ("Curve Fitting Window"));
  setWhatsThis (tr ("Curve Fitting Window\n\n"
                    "This window applies a curve fit to the currently selected curve"));

  createWidgets ();
  initializeOrder ();
}

void FittingWindow::createWidgets ()
{
  QWidget *widget = new QWidget;
  setWidget (widget);

  QGridLayout *layout = new QGridLayout;
  widget->setLayout (layout);
  int row = 0;

  // Order row
  QLabel *labelOrder = new QLabel (tr ("Order:"));
  layout->addWidget (labelOrder, row, 0, 1, 1);

  m_cmbOrder = new QComboBox;
  m_cmbOrder->addItem ("0", QVariant (0));
  m_cmbOrder->addItem ("1", QVariant (1));
  m_cmbOrder->addItem ("2", QVariant (2));
  m_cmbOrder->addItem ("3", QVariant (3));
  m_cmbOrder->addItem ("4", QVariant (4));
  m_cmbOrder->addItem ("5", QVariant (5));
  m_cmbOrder->addItem ("6", QVariant (6));
  connect (m_cmbOrder, SIGNAL (currentIndexChanged (int)), this, SLOT (slotCmbOrder (int)));
  layout->addWidget (m_cmbOrder, row++, 1, 1, 1);

  // Y= row
  m_labelY = new QLabel; // The text will be set in resizeTable
  layout->addWidget (m_labelY, row++, 0, 1, 1);

  // Table row
  m_model = new FittingModel;
  m_model->setColumnCount (2);

  m_view = new QTableView;
  m_view->horizontalHeader()->setStretchLastSection (true);
  m_view->setModel (m_model); // Call before setSelectionModel since this also overrides the selection model
  m_view->setSelectionMode (QAbstractItemView::ContiguousSelection);
  m_view->setDragEnabled (true);
  m_view->horizontalHeader()->hide();
  m_view->verticalHeader()->hide();
  m_view->setEditTriggers(QAbstractItemView::NoEditTriggers); // Control is read only

  layout->addWidget (m_view, row++, 0, 1, 2);

  // Statistics rows
  QLabel *lblMeanSquareError = new QLabel (tr ("Mean square error:"));
  layout->addWidget (lblMeanSquareError, row, 0, 1, 1);

  m_lblMeanSquareError = new QLineEdit;
  m_lblMeanSquareError->setReadOnly (true);
  m_lblMeanSquareError->setWhatsThis (tr ("Calculated mean square error statistic"));
  layout->addWidget (m_lblMeanSquareError, row++, 1, 1, 1);

  QLabel *lblRootMeanSquare = new QLabel (tr ("Root mean square:"));
  layout->addWidget (lblRootMeanSquare, row, 0, 1, 1);

  m_lblRootMeanSquare = new QLineEdit;
  m_lblRootMeanSquare->setReadOnly (true);
  m_lblRootMeanSquare->setWhatsThis (tr ("Calculated root mean square statistic"));
  layout->addWidget (m_lblRootMeanSquare, row++, 1, 1, 1);

  QLabel *lblRSquared = new QLabel (tr ("R squared:"));
  layout->addWidget (lblRSquared, row, 0, 1, 1);

  m_lblRSquared = new QLineEdit;
  m_lblRSquared->setReadOnly (true);
  m_lblRSquared->setWhatsThis (tr ("Calculated R squared statistic"));
  layout->addWidget (m_lblRSquared, row++, 1, 1, 1);
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

void FittingWindow::initializeOrder ()
{
  const int SECOND_ORDER = 2;

  int index = m_cmbOrder->findData (QVariant (SECOND_ORDER));
  m_cmbOrder->setCurrentIndex (index);
}

void FittingWindow::resizeTable (int order)
{
  LOG4CPP_INFO_S ((*mainCat)) << "FittingWindow::resizeTable";

  m_model->setRowCount (order + 1);

  // Populate the Y= row
  m_labelY->setText (m_isLogYRadius ?
                       tr ("log(Y)=") :
                       tr ("Y="));

  // Populate polynomial terms
  QString xString = (m_isLogXTheta ?
                       tr ("log(X)") :
                       tr ("X"));
  for (int row = 0, term = order; term >= 0; row++, term--) {

    // Entries are x^order, ..., x^2, x, 1
    QString termString = QString ("%1%2%3%4")
        .arg ((term > 0) ? xString : "")
        .arg ((term > 1) ? "^" : "")
        .arg ((term > 1) ? QString::number (term) : "")
        .arg ((term > 0) ? "+" : "");

    QStandardItem *item = new QStandardItem (termString);
    m_model->setItem (row, COLUMN_POLYNOMIAL_TERMS, item);
  }
}

void FittingWindow::slotCmbOrder(int /* index  */)
{
  int order = m_cmbOrder->currentData().toInt();

  resizeTable (order);
}

void FittingWindow::update (const CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "FittingWindow::update";

  m_isLogXTheta = (cmdMediator.document().modelCoords().coordScaleXTheta() == COORD_SCALE_LOG);
  m_isLogYRadius = (cmdMediator.document().modelCoords().coordScaleYRadius() == COORD_SCALE_LOG);

  int order = m_cmbOrder->currentData().toInt();

  resizeTable (order);
}

