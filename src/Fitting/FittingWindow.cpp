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
#include "FittingStatistics.h"
#include "FittingWindow.h"
#include "GeometryModel.h"
#include "Logger.h"
#include "MainWindow.h"
#include "MainWindowModel.h"
#include <QApplication>
#include <QClipboard>
#include <QComboBox>
#include <QGridLayout>
#include <QItemSelectionModel>
#include <QLabel>
#include <QLineEdit>
#include <qmath.h>
#include "Transformation.h"
#include "WindowTable.h"

const int COLUMN_COEFFICIENTS = 0;
const int COLUMN_POLYNOMIAL_TERMS = 1;

FittingWindow::FittingWindow (MainWindow *mainWindow) :
  WindowAbstractBase (mainWindow),
  m_isLogXTheta (false),
  m_isLogYRadius (false),
  m_significantDigits (mainWindow->modelMainWindow().significantDigits ())
{
  setVisible (false);
  setAllowedAreas (Qt::AllDockWidgetAreas);
  setWindowTitle (tr ("Curve Fitting Window")); // Appears in title bar when undocked
  setStatusTip (tr ("Curve Fitting Window"));
  setWhatsThis (tr ("Curve Fitting Window\n\n"
                    "This window applies a curve fit to the currently selected curve.\n\n"
                    "If drag-and-drop is disabled, a rectangular set of cells may be selected by clicking and dragging. Otherwise, if "
                    "drag-and-drop is enabled, a rectangular set of cells may be selected using Click then Shift+Click, since click and drag "
                    "starts the dragging operation. Drag-and-drop mode is set in the Main Window settings"));

  m_coefficients.resize (MAX_POLYNOMIAL_ORDER + 1);

  createWidgets (mainWindow);
  initializeOrder ();
  clear ();
}

FittingWindow::~FittingWindow()
{
}

void FittingWindow::calculateCurveFitAndStatistics ()
{
  FittingStatistics fittingStatistics;

  double mse = 0, rms = 0, rSquared = 0;
  fittingStatistics.calculateCurveFitAndStatistics (unsigned (maxOrder ()),
                                                    m_pointsConvenient,
                                                    m_coefficients,
                                                    mse,
                                                    rms,
                                                    rSquared,
                                                    qFloor (m_significantDigits));

  m_lblMeanSquareError->setText (QString::number (mse));
  m_lblRootMeanSquare->setText (QString::number (rms));
  m_lblRSquared->setText (QString::number (rSquared));

  // Send coefficients to connected classes. Also send the first and last x values
  if (m_pointsConvenient.size () > 0) {
    int last = m_pointsConvenient.size () - 1;
    emit signalCurveFit (m_coefficients,
                         m_pointsConvenient [0].x(),
                         m_pointsConvenient [last].x (),
                         m_isLogXTheta,
                         m_isLogYRadius);
  } else {
    emit signalCurveFit (m_coefficients,
                         0,
                         0,
                         false,
                         false);
  }

  // Copy into displayed control
  for (int row = 0, order = m_model->rowCount () - 1; row < m_model->rowCount (); row++, order--) {

    QStandardItem *item = new QStandardItem (QString::number (m_coefficients [order]));
    m_model->setItem (row, COLUMN_COEFFICIENTS, item);
  }
}

void FittingWindow::clear ()
{
  m_labelY->setText ("");
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

void FittingWindow::createWidgets (MainWindow *mainWindow)
{
  QWidget *widget = new QWidget;
  setWidget (widget);

  QGridLayout *layout = new QGridLayout;
  widget->setLayout (layout);
  int row = 0;

  // Order row
  QLabel *labelOrder = new QLabel (QString ("%1:").arg (tr ("Order")));
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

  m_view = new WindowTable (*m_model);
  connect (m_view, SIGNAL (signalTableStatusChange ()),
           mainWindow, SLOT (slotTableStatusChange ()));

  layout->addWidget (m_view, row++, 0, 1, 2);

  // Statistics rows
  QLabel *lblMeanSquareError = new QLabel (QString ("%1:").arg (tr ("Mean square error")));
  layout->addWidget (lblMeanSquareError, row, 0, 1, 1);

  m_lblMeanSquareError = new QLineEdit;
  m_lblMeanSquareError->setReadOnly (true);
  m_lblMeanSquareError->setWhatsThis (tr ("Calculated mean square error statistic"));
  layout->addWidget (m_lblMeanSquareError, row++, 1, 1, 1);

  QLabel *lblRootMeanSquare = new QLabel (QString ("%1:").arg (tr ("Root mean square")));
  layout->addWidget (lblRootMeanSquare, row, 0, 1, 1);

  m_lblRootMeanSquare = new QLineEdit;
  m_lblRootMeanSquare->setReadOnly (true);
  m_lblRootMeanSquare->setWhatsThis (tr ("Calculated root mean square statistic. This is calculated as the square root of the mean square error"));
  layout->addWidget (m_lblRootMeanSquare, row++, 1, 1, 1);

  QLabel *lblRSquared = new QLabel (QString ("%1:").arg (tr ("R squared")));
  layout->addWidget (lblRSquared, row, 0, 1, 1);

  m_lblRSquared = new QLineEdit;
  m_lblRSquared->setReadOnly (true);
  m_lblRSquared->setWhatsThis (tr ("Calculated R squared statistic"));
  layout->addWidget (m_lblRSquared, row++, 1, 1, 1);
}

void FittingWindow::doCopy ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "FittingWindow::doCopy";

  QString text = m_model->selectionAsText (m_modelExport.delimiter());

  if (!text.isEmpty ()) {

    // Save to clipboard
    QApplication::clipboard ()->setText (text);

  }
}

void FittingWindow::initializeOrder ()
{
  const int SECOND_ORDER = 2;

  int index = m_cmbOrder->findData (QVariant (SECOND_ORDER));
  m_cmbOrder->setCurrentIndex (index);
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
  QString yTerm = QString ("%1%2%3")
      .arg (m_curveSelected)
      .arg (m_curveSelected.isEmpty () ?
              "" :
              ": ")
      .arg (m_isLogYRadius ?
              tr ("log10(Y)=") :
              tr ("Y="));
  m_labelY->setText (yTerm);

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

void FittingWindow::update (const CmdMediator &cmdMediator,
                            const MainWindowModel &modelMainWindow,
                            const QString &curveSelected,
                            const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "FittingWindow::update";

  // Save inputs
  m_curveSelected = curveSelected;
  m_modelExport = cmdMediator.document().modelExport();
  m_model->setDelimiter (m_modelExport.delimiter());
  m_isLogXTheta = (cmdMediator.document().modelCoords().coordScaleXTheta() == COORD_SCALE_LOG);
  m_isLogYRadius = (cmdMediator.document().modelCoords().coordScaleYRadius() == COORD_SCALE_LOG);
  m_view->setDragEnabled (modelMainWindow.dragDropExport());
  m_significantDigits = modelMainWindow.significantDigits();

  m_pointsConvenient.clear ();

  if (transformation.transformIsDefined()) {

    // Gather and calculate geometry data
    const Curve *curve = cmdMediator.document().curveForCurveName (curveSelected);

    ENGAUGE_CHECK_PTR (curve);

    if (curve->numPoints() > 0) {

      // Copy points to convenient list
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

QTableView *FittingWindow::view () const
{
  return dynamic_cast<QTableView*> (m_view);
}
