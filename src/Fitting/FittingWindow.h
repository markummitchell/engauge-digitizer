/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef FITTING_WINDOW_H
#define FITTING_WINDOW_H

#include "DocumentModelExportFormat.h"
#include "FittingCurveCoefficients.h"
#include "FittingPointsConvenient.h"
#include <QVector>
#include "WindowAbstractBase.h"

class CmdMediator;
class Curve;
class FittingModel;
class MainWindow;
class MainWindowModel;
class Matrix;
class QComboBox;
class QItemSelection;
class QLabel;
class QLineEdit;
class QString;
class QTableView;
class Transformation;

/// Window that displays curve fitting as applied to the currently selected curve
///
/// The strategy used assumes no changes to the DIG file format will be made for the original implementation.
/// Since settings cannot be saved for the Document or Curves, this keeps the implementation simple
class FittingWindow : public WindowAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor. Parent is needed or else this widget cannot be redocked after being undocked
  FittingWindow (MainWindow *mainWindow);
  virtual ~FittingWindow ();

  virtual void clear ();
  virtual void closeEvent(QCloseEvent *event);
  virtual void doCopy ();
  virtual void update (const CmdMediator &cmdMediator,
                       const MainWindowModel &modelMainWindow,
                       const QString &curveSelected,
                       const Transformation &transformation);
  virtual QTableView *view () const;

private slots:

  /// Update after change in the selected curve fit order
  void slotCmbOrder(int index);

signals:

  /// Signal containing coefficients from curve fit
  void signalCurveFit(FittingCurveCoefficients, double, double, bool, bool);

  /// Signal that this QDockWidget was just closed
  void signalFittingWindowClosed();

private:
  FittingWindow();

  void calculateCurveFitAndStatistics ();
  void createWidgets(MainWindow *mainWindow);
  void initializeOrder ();
  int maxOrder () const;
  void refreshTable ();
  void resizeTable (int order);

  QComboBox *m_cmbOrder;
  QLabel *m_labelY;
  QTableView *m_view;
  FittingModel *m_model;
  QLineEdit *m_lblMeanSquareError;
  QLineEdit *m_lblRootMeanSquare;
  QLineEdit *m_lblRSquared;

  QString m_curveSelected; // Save selected curve name so it can be displayed. Let user know what data this fit applies to
  bool m_isLogXTheta;
  bool m_isLogYRadius;
  FittingPointsConvenient m_pointsConvenient;

  // Calculated curve fit coefficients, with 0th for constant term, 1st for linear term, ...
  QVector<double> m_coefficients;

  // Export format and coordinate scale are updated after every CmdAbstractBase gets redone/undone
  DocumentModelExportFormat m_modelExport;

  double m_significantDigits;
};

#endif // FITTING_WINDOW_H
