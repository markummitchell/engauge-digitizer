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
#include <qmath.h>
#include <QTableView>
#include <QTextStream>
#include "Transformation.h"

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

  m_coefficients.resize (MAX_POLYNOMIAL_ORDER + 1);

  createWidgets ();
  initializeOrder ();
}

FittingWindow::~FittingWindow()
{
}

void FittingWindow::calculateCurveFit (const PointsConvenient & /* pointsConvenient */)
{
  int order, row;

  for (order = 0; order <= MAX_POLYNOMIAL_ORDER; order++) {
    m_coefficients [order] = 0;
  }

  for (row = 0, order = m_model->rowCount () - 1; row < m_model->rowCount (); row++, order--) {

    QStandardItem *item = new QStandardItem (QString::number (m_coefficients [order]));
    m_model->setItem (row, COLUMN_COEFFICIENTS, item);
  }
}

void FittingWindow::calculateCurveFitAndStatistics (const Curve *curve,
                                                    const Transformation &transformation)
{
  // Copy points to convenient list
  PointsConvenient pointsConvenient;

  const Points points = curve->points();
  Points::const_iterator itr;
  for (itr = points.begin (); itr != points.end (); itr++) {

    const Point &point = *itr;
    QPointF posScreen = point.posScreen ();
    QPointF posGraph;
    transformation.transformScreenToRawGraph (posScreen,
                                              posGraph);
    pointsConvenient.append (posGraph);
  }

  calculateCurveFit (pointsConvenient);
  calculateStatistics (pointsConvenient);
}

void FittingWindow::calculateStatistics (const PointsConvenient &pointsConvenient)
{
  // First pass to get average y
  double ySum = 0;
  PointsConvenient::const_iterator itrC;
  for (itrC = pointsConvenient.begin (); itrC != pointsConvenient.end (); itrC++) {

    const QPointF &pointC = *itrC;
    ySum += pointC.y();
  }
  double yAverage = ySum / pointsConvenient.length();

  // Second pass to compute squared terms
  double mseSum = 0, rSquaredNumerator = 0, rSquaredDenominator = 0;
  for (itrC = pointsConvenient.begin(); itrC != pointsConvenient.end (); itrC++) {

    const QPointF &pointC = *itrC;
    double yActual = pointC.y();
    double yCurveFit = yFromXAndCoefficients (pointC.x());

    mseSum              += (yCurveFit - yActual ) * (yCurveFit - yActual );
    rSquaredNumerator   += (yCurveFit - yAverage) * (yCurveFit - yAverage);
    rSquaredDenominator += (yActual   - yAverage) * (yActual   - yAverage);
  }

  double mse = mseSum / pointsConvenient.count ();
  double rse = qSqrt (mse);
  double rSquared = (rSquaredDenominator > 0 ?
                       rSquaredNumerator / rSquaredDenominator :
                       0);

  m_lblMeanSquareError->setText (QString::number (mse / pointsConvenient.count ()));
  m_lblRootMeanSquare->setText (QString::number (rse));
  m_lblRSquared->setText (QString::number (rSquared));
}

void FittingWindow::clear ()
{
}

void FittingWindow::closeEvent(QCloseEvent * /* event */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "FittingWindow::closeEvent";

  emit signalFittingWindowClosed();
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
  for (int order = 0; order <= MAX_POLYNOMIAL_ORDER; order++) {
    m_cmbOrder->addItem (QString::number (order), QVariant (order));
  }
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
  m_lblRootMeanSquare->setWhatsThis (tr ("Calculated root mean square statistic. This is calculated as the square root of the mean square error"));
  layout->addWidget (m_lblRootMeanSquare, row++, 1, 1, 1);

  QLabel *lblRSquared = new QLabel (tr ("R squared:"));
  layout->addWidget (lblRSquared, row, 0, 1, 1);

  m_lblRSquared = new QLineEdit;
  m_lblRSquared->setReadOnly (true);
  m_lblRSquared->setWhatsThis (tr ("Calculated R squared statistic"));
  layout->addWidget (m_lblRSquared, row++, 1, 1, 1);
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

void FittingWindow::update (const CmdMediator &cmdMediator,
                            const QString &curveSelected,
                            const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "FittingWindow::update";

  // Save inputs
  m_isLogXTheta = (cmdMediator.document().modelCoords().coordScaleXTheta() == COORD_SCALE_LOG);
  m_isLogYRadius = (cmdMediator.document().modelCoords().coordScaleYRadius() == COORD_SCALE_LOG);

  int order = m_cmbOrder->currentData().toInt();

  // Table size may have to change
  resizeTable (order);

  if (transformation.transformIsDefined()) {

    // Gather and calculate geometry data
    const Curve *curve = cmdMediator.document().curveForCurveName (curveSelected);

    ENGAUGE_CHECK_PTR (curve);

    if (curve->numPoints() > 0) {

      calculateCurveFitAndStatistics (curve,
                                      transformation);
    }
  }
}

double FittingWindow::yFromXAndCoefficients (double x) const
{
  double sum = 0;

  for (int order = 0; order <= MAX_POLYNOMIAL_ORDER; order++) {
    sum += m_coefficients [order] * qPow (x, (double) order);
  }

  return sum;
}
