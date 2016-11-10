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
#include "FittingCurveCoefficients.h"
#include "FittingModel.h"
#include "FittingWindow.h"
#include "GeometryModel.h"
#include "Logger.h"
#include "Matrix.h"
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

void FittingWindow::calculateCurveFit ()
{
  int order, row;

  // Calculate X and y arrays in y = X a
  Matrix X (m_pointsConvenient.size (), maxOrder () + 1);
  QVector<double> Y (m_pointsConvenient.size ());
  loadXAndYArrays (X, Y);

  // Solve for the coefficients a in y = X a + epsilon using a = (Xtranpose X)^(-1) Xtranspose y
  Matrix denominator = X.transpose () * X;
  QVector<double> a = denominator.inverse () * X.transpose () * Y;

  // Copy coefficients into member variable and into list for sending as a signal
  FittingCurveCoefficients fittingCurveCoef;
  for (order = 0; order <= MAX_POLYNOMIAL_ORDER; order++) {
    if (order <= maxOrder ()) {

      // Copy from polynomial regression vector
      m_coefficients [order] = a [order];
      fittingCurveCoef.append (a [order]);

    } else {

      // Set to zero in case value gets used somewhere
      m_coefficients [order] = 0;

    }
  }

  // Send to connected classes
  emit signalCurveFit (fittingCurveCoef);

  // Copy into displayed control
  for (row = 0, order = m_model->rowCount () - 1; row < m_model->rowCount (); row++, order--) {

    QStandardItem *item = new QStandardItem (QString::number (m_coefficients [order]));
    m_model->setItem (row, COLUMN_COEFFICIENTS, item);
  }
}

void FittingWindow::calculateCurveFitAndStatistics ()
{
  calculateCurveFit ();
  calculateStatistics ();
}

void FittingWindow::calculateStatistics ()
{
  // First pass to get average y
  double ySum = 0;
  PointsConvenient::const_iterator itrC;
  for (itrC = m_pointsConvenient.begin (); itrC != m_pointsConvenient.end (); itrC++) {

    const QPointF &pointC = *itrC;
    ySum += pointC.y();
  }
  double yAverage = ySum / m_pointsConvenient.length();

  // Second pass to compute squared terms
  double mseSum = 0, rSquaredNumerator = 0, rSquaredDenominator = 0;
  for (itrC = m_pointsConvenient.begin(); itrC != m_pointsConvenient.end (); itrC++) {

    const QPointF &pointC = *itrC;
    double yActual = pointC.y();
    double yCurveFit = yFromXAndCoefficients (pointC.x());

    mseSum              += (yCurveFit - yActual ) * (yCurveFit - yActual );
    rSquaredNumerator   += (yCurveFit - yAverage) * (yCurveFit - yAverage);
    rSquaredDenominator += (yActual   - yAverage) * (yActual   - yAverage);
  }

  double mse = mseSum / m_pointsConvenient.count ();
  double rse = qSqrt (mse);
  double rSquared = (rSquaredDenominator > 0 ?
                       rSquaredNumerator / rSquaredDenominator :
                       0);

  m_lblMeanSquareError->setText (QString::number (mse));
  m_lblRootMeanSquare->setText (QString::number (rse));
  m_lblRSquared->setText (QString::number (rSquared));
}

void FittingWindow::clear ()
{
  m_model->setRowCount (0);
  m_lblMeanSquareError->setText ("");
  m_lblRootMeanSquare->setText ("");
  m_lblRSquared->setText ("");
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
  connect (m_view->selectionModel(), SIGNAL (selectionChanged (const QItemSelection &, const QItemSelection &)),
           this, SLOT (slotSelectionChanged (const QItemSelection &, const QItemSelection &)));


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

int FittingWindow::fold2dIndexes (int row,
                                  int col,
                                  int rowLow,
                                  int colLow,
                                  int colHigh) const
{
  return (row - rowLow) * (colHigh - colLow + 1) + (col - colLow);
}

void FittingWindow::initializeOrder ()
{
  const int SECOND_ORDER = 2;

  int index = m_cmbOrder->findData (QVariant (SECOND_ORDER));
  m_cmbOrder->setCurrentIndex (index);
}

void FittingWindow::loadXAndYArrays (Matrix &X,
                                     QVector<double> &Y) const
{
  ENGAUGE_ASSERT (Y.size () == X.rows ());

  int row;
  PointsConvenient::const_iterator itr;
  for (row = 0, itr = m_pointsConvenient.begin(); itr != m_pointsConvenient.end(); itr++, row++) {

    const QPointF &p = *itr;
    double x = p.x ();
    double y = p.y ();

    for (int order = 0; order <= maxOrder (); order++) {

      X.set (row, order, qPow (x, order));
    }

    Y [row] = y;
  }
}

int FittingWindow::maxOrder () const
{
  return m_cmbOrder->currentData().toInt();
}

void FittingWindow::refreshTable ()
{
  int order = m_cmbOrder->currentData().toInt();

  // Table size may have to change
  resizeTable (order);

  calculateCurveFitAndStatistics ();
}

void FittingWindow::resizeTable (int order)
{
  LOG4CPP_INFO_S ((*mainCat)) << "FittingWindow::resizeTable";

  m_model->setRowCount (order + 1);

  // Populate the Y= row. Base for log must be consistent with base used in update()
  m_labelY->setText (m_isLogYRadius ?
                       tr ("log10(Y)=") :
                       tr ("Y="));

  // Populate polynomial terms. Base for log must be consistent with base used in update()
  QString xString = (m_isLogXTheta ?
                       tr ("log10(X)") :
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
  refreshTable ();
}

void FittingWindow::slotSelectionChanged (const QItemSelection & /* selected */,
                                          const QItemSelection & /* deselected */)
{
  const bool NOT_GNUPLOT = false;

  QItemSelectionModel *selectionModel = m_view->selectionModel ();
  QModelIndexList selection = selectionModel->selectedIndexes ();

  if (selection.size () > 0) {

    // Gather input. A rectangular grid that encompasses all selected indexes will be copied
    int rowLow = 0, rowHigh = 0, colLow = 0, colHigh = 0;
    bool isFirst = true;
    for (QModelIndexList::const_iterator itr = selection.begin(); itr != selection.end(); itr++) {
      QModelIndex index = *itr;
      if (isFirst || index.row ()    < rowLow ) rowLow  = index.row ();
      if (isFirst || index.row ()    > rowHigh) rowHigh = index.row ();
      if (isFirst || index.column () < colLow ) colLow  = index.column ();
      if (isFirst || index.column () > colHigh) colHigh = index.column ();
      isFirst = false;
    }

    int numRows = rowHigh - rowLow + 1;
    int numCols = colHigh - colLow + 1;

    // Put data into two dimensional rowXcolumn table is handled as a flattened vector. Table is initialized
    // with empty strings
    QVector<QString> table (numRows * numCols);

    for (int i = 0; i < selection.size (); i++) {
      QModelIndex index = selection [i];
      QVariant data = m_model->data (index);
      QString text = data.toString ();
      table [fold2dIndexes (index.row(), index.column(), rowLow, colLow, colHigh)] = text;
    }

    // Concatenate table into output string
    QString output;
    QTextStream str (&output);
    for (int row = rowLow; row <= rowHigh; row++) {
      QString delimiter;
      for (int col = colLow; col <= colHigh; col++) {
        str << delimiter << table [fold2dIndexes (row, col, rowLow, colLow, colHigh)];
        delimiter = exportDelimiterToText (m_modelExport.delimiter(),
                                           NOT_GNUPLOT);
      }
      str << "\n";
    }

    // Save to clipboard
    QApplication::clipboard ()->setText (output);
  }
}

void FittingWindow::update (const CmdMediator &cmdMediator,
                            const QString &curveSelected,
                            const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "FittingWindow::update";

  // Save inputs
  m_modelExport = cmdMediator.document().modelExport();
  m_isLogXTheta = (cmdMediator.document().modelCoords().coordScaleXTheta() == COORD_SCALE_LOG);
  m_isLogYRadius = (cmdMediator.document().modelCoords().coordScaleYRadius() == COORD_SCALE_LOG);

  m_pointsConvenient.clear ();

  if (transformation.transformIsDefined()) {

    // Gather and calculate geometry data
    const Curve *curve = cmdMediator.document().curveForCurveName (curveSelected);

    ENGAUGE_CHECK_PTR (curve);

    if (curve->numPoints() > 0) {

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

        // Adjust for log coordinates
        if (m_isLogXTheta) {
          double x = qLn (posGraph.x()) / qLn (10.0); // Use base 10 consistent with text in resizeTable
          posGraph.setX (x);
        }
        if (m_isLogYRadius) {
          double y = qLn (posGraph.y()) / qLn (10.0); // Use base 10 consistent with text in resizeTable
          posGraph.setY (y);
        }

        m_pointsConvenient.append (posGraph);
      }
    }
  }

  refreshTable ();
}

double FittingWindow::yFromXAndCoefficients (double x) const
{
  double sum = 0;

  for (int order = 0; order <= MAX_POLYNOMIAL_ORDER; order++) {
    sum += m_coefficients [order] * qPow (x, (double) order);
  }

  return sum;
}
