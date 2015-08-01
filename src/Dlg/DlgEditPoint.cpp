#include "DigitizeStateAbstractBase.h"
#include "DlgEditPoint.h"
#include "DlgValidatorAbstract.h"
#include "DlgValidatorFactory.h"
#include "DocumentModelCoords.h"
#include "EngaugeAssert.h"
#include "FormatCoordsUnitsNonPolarTheta.h"
#include "FormatCoordsUnitsPolarTheta.h"
#include "FormatDateTime.h"
#include "FormatDegreesMinutesSecondsNonPolarTheta.h"
#include "FormatDegreesMinutesSecondsPolarTheta.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QDoubleValidator>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QRect>
#include <QVBoxLayout>

const Qt::Alignment ALIGNMENT = Qt::AlignCenter;

const int MIN_WIDTH_TO_FIT_STRANGE_UNITS = 200;

const bool IS_X_THETA = true;
const bool IS_NOT_X_THETA = false;

DlgEditPoint::DlgEditPoint (MainWindow &mainWindow,
                            DigitizeStateAbstractBase &digitizeState,
                            const DocumentModelCoords &modelCoords,
                            const QCursor &cursorShape,
                            const double *xInitialValue,
                            const double *yInitialValue) :
  QDialog (&mainWindow),
  m_cursorShape (cursorShape),
  m_modelCoords (modelCoords)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgEditPoint::DlgEditPoint";

  // To guarantee the override cursor is always removed, we call removeOverrideCursor here rather than in the code that
  // allocates this DlgEditPoint. The digitizeState argument is otherwise unused.
  digitizeState.removeOverrideCursor();

  connect (this, SIGNAL (signalSetOverrideCursor (QCursor)), &mainWindow, SLOT (slotSetOverrideCursor (QCursor)));

  QVBoxLayout *layout = new QVBoxLayout;
  setLayout (layout);

  setCursor  (QCursor (Qt::ArrowCursor));
  setModal(true);
  setWindowTitle (tr ("Edit Axis Point"));

  createCoords (layout);
  createOkCancel (layout);

  FormatCoordsUnitsNonPolarTheta formatNonPolarTheta;
  FormatCoordsUnitsPolarTheta formatPolarTheta;

  if (m_modelCoords.coordsType() == COORDS_TYPE_CARTESIAN) {
    m_editGraphX->setText (formatNonPolarTheta.unformattedToFormatted (xInitialValue,
                                                                       m_modelCoords.coordUnitsX(),
                                                                       m_modelCoords.coordUnitsDate(),
                                                                       m_modelCoords.coordUnitsTime(),
                                                                       IS_X_THETA));
    m_editGraphY->setText (formatNonPolarTheta.unformattedToFormatted (yInitialValue,
                                                                       m_modelCoords.coordUnitsY(),
                                                                       m_modelCoords.coordUnitsDate(),
                                                                       m_modelCoords.coordUnitsTime(),
                                                                       IS_NOT_X_THETA));
  } else {
    m_editGraphX->setText (formatPolarTheta.unformattedToFormatted (xInitialValue,
                                                                    modelCoords.coordUnitsTheta()));
    m_editGraphY->setText (formatNonPolarTheta.unformattedToFormatted (yInitialValue,
                                                                       m_modelCoords.coordUnitsRadius(),
                                                                       m_modelCoords.coordUnitsDate(),
                                                                       m_modelCoords.coordUnitsTime(),
                                                                       IS_NOT_X_THETA));
  }

  updateControls ();
}

DlgEditPoint::~DlgEditPoint()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgEditPoint::~DlgEditPoint";

  emit signalSetOverrideCursor (m_cursorShape);
}

void DlgEditPoint::createCoords (QVBoxLayout *layoutOuter)
{
  // Constraints on x and y are needed for log scaling
  bool isConstraintX = (m_modelCoords.coordScaleXTheta() == COORD_SCALE_LOG);
  bool isConstraintY = (m_modelCoords.coordScaleYRadius() == COORD_SCALE_LOG);
  DlgValidatorFactory dlgValidatorFactory;
  m_validatorGraphX = dlgValidatorFactory.createCartesianOrPolarWithPolarPolar (m_modelCoords.coordScaleXTheta(),
                                                                                isCartesian (),
                                                                                m_modelCoords.coordUnitsX(),
                                                                                m_modelCoords.coordUnitsTheta(),
                                                                                m_modelCoords.coordUnitsDate(),
                                                                                m_modelCoords.coordUnitsTime());
  m_validatorGraphY = dlgValidatorFactory.createCartesianOrPolarWithNonPolarPolar (m_modelCoords.coordScaleYRadius(),
                                                                                   isCartesian (),
                                                                                   m_modelCoords.coordUnitsY(),
                                                                                   m_modelCoords.coordUnitsRadius(),
                                                                                   m_modelCoords.coordUnitsDate(),
                                                                                   m_modelCoords.coordUnitsTime());

  // Label, with guidance in terms of legal ranges and units
  QString description = QString ("Graph Coordinates (%1, %2)%3%4%5%6%7%8 as (%9, %10):")
                        .arg (nameXTheta ())
                        .arg (nameYRadius ())
                        .arg (isConstraintX || isConstraintY ? " with " : "")
                        .arg (isConstraintX                  ? QString (nameXTheta ()) : "")
                        .arg (isConstraintX                  ? " > 0" : "")
                        .arg (isConstraintX && isConstraintY ? " and " : "")
                        .arg (                 isConstraintY ? QString (nameYRadius ()) : "")
                        .arg (                 isConstraintY ? " > 0" : "")
                        .arg (unitsType (IS_X_THETA))
                        .arg (unitsType (IS_NOT_X_THETA));
  QGroupBox *panel = new QGroupBox (description, this);
  layoutOuter->addWidget (panel);

  QHBoxLayout *layout = new QHBoxLayout (panel);
  panel->setLayout (layout);

  // Row
  QLabel *labelGraphParLeft = new QLabel (tr ("("), this);
  layout->addWidget(labelGraphParLeft, 0);

  m_editGraphX = new QLineEdit;
  m_editGraphX->setMinimumWidth(MIN_WIDTH_TO_FIT_STRANGE_UNITS);
  m_editGraphX->setAlignment (ALIGNMENT);
  m_editGraphX->setValidator (m_validatorGraphX);
  // setStatusTip does not work for modal dialogs
  m_editGraphX->setWhatsThis (tr ("Enter the first graph coordinate of the axis point.\n\n"
                                  "For cartesian plots this is X. For polar plots this is the radius R."));
  layout->addWidget(m_editGraphX, 0);
  connect (m_editGraphX, SIGNAL (textChanged (const QString &)), this, SLOT (slotTextChanged (const QString &)));

  QLabel *labelGraphComma = new QLabel (tr (", "), this);
  layout->addWidget(labelGraphComma, 0);

  m_editGraphY = new QLineEdit;
  m_editGraphY->setMinimumWidth(MIN_WIDTH_TO_FIT_STRANGE_UNITS);
  m_editGraphY->setAlignment (ALIGNMENT);
  m_editGraphY->setValidator (m_validatorGraphY);
  // setStatusTip does not work for modal dialogs
  m_editGraphY->setWhatsThis (tr ("Enter the second graph coordinate of the axis point.\n\n"
                                  "For cartesian plots this is Y. For plot plots this is the angle Theta."));
  layout->addWidget(m_editGraphY, 0);
  connect (m_editGraphY, SIGNAL (textChanged (const QString &)), this, SLOT (slotTextChanged (const QString &)));

  QLabel *labelGraphParRight = new QLabel (tr (")"), this);
  layout->addWidget(labelGraphParRight, 0);
}

void DlgEditPoint::createOkCancel (QVBoxLayout *layoutOuter)
{
  QWidget *panel = new QWidget (this);
  layoutOuter->addWidget (panel, 0, Qt::AlignCenter);

  QHBoxLayout *layout = new QHBoxLayout (panel);
  panel->setLayout (layout);

  m_btnOk = new QPushButton (tr ("Ok"), this);
  layout->addWidget(m_btnOk);
  connect (m_btnOk, SIGNAL (released ()), this, SLOT (accept ()));

  m_btnCancel = new QPushButton (tr ("Cancel"), this);
  layout->addWidget(m_btnCancel);
  connect (m_btnCancel, SIGNAL (released ()), this, SLOT (reject ()));
}

bool DlgEditPoint::isCartesian () const
{
  return (m_modelCoords.coordsType() == COORDS_TYPE_CARTESIAN);
}

QChar DlgEditPoint::nameXTheta () const
{
  return (isCartesian () ? QChar ('X') : THETA);
}

QChar DlgEditPoint::nameYRadius () const
{
  return (isCartesian () ? QChar ('Y') : QChar ('R'));
}

QPointF DlgEditPoint::posGraph () const
{
  double xTheta, yRadius;

  FormatCoordsUnitsNonPolarTheta formatNonPolarTheta;
  FormatCoordsUnitsPolarTheta formatPolarTheta;

  if (m_modelCoords.coordsType() == COORDS_TYPE_CARTESIAN) {
    xTheta = formatNonPolarTheta.formattedToUnformatted (m_editGraphX->text(),
                                                         m_modelCoords.coordUnitsX(),
                                                         m_modelCoords.coordUnitsDate(),
                                                         m_modelCoords.coordUnitsTime(),
                                                         IS_X_THETA);
    yRadius = formatNonPolarTheta.formattedToUnformatted (m_editGraphY->text(),
                                                          m_modelCoords.coordUnitsY(),
                                                          m_modelCoords.coordUnitsDate(),
                                                          m_modelCoords.coordUnitsTime(),
                                                          IS_NOT_X_THETA);
  } else {
    xTheta = formatPolarTheta.formattedToUnformatted (m_editGraphX->text(),
                                                      m_modelCoords.coordUnitsTheta());
    yRadius = formatNonPolarTheta.formattedToUnformatted (m_editGraphY->text(),
                                                          m_modelCoords.coordUnitsRadius(),
                                                          m_modelCoords.coordUnitsDate(),
                                                          m_modelCoords.coordUnitsTime(),
                                                          IS_NOT_X_THETA);
  }

  return QPointF (xTheta,
                  yRadius);



  return QPointF (m_editGraphX->text().toDouble (),
                  m_editGraphY->text().toDouble ());
}

void DlgEditPoint::slotTextChanged (const QString &)
{
  updateControls ();
}

QString DlgEditPoint::unitsType (bool isXTheta) const
{
  if (isCartesian ()) {
    if (isXTheta) {
      return coordUnitsNonPolarThetaToBriefType (m_modelCoords.coordUnitsX());
    } else {
      return coordUnitsNonPolarThetaToBriefType (m_modelCoords.coordUnitsY());
    }
  } else {
    if (isXTheta) {
      return coordUnitsPolarThetaToBriefType (m_modelCoords.coordUnitsTheta());
    } else {
      return coordUnitsNonPolarThetaToBriefType (m_modelCoords.coordUnitsRadius());
    }
  }
}

void DlgEditPoint::updateControls ()
{
  // Check for not empty (which allows single minus sign) and for valid number (which prevents single minus sign)
  QString textX = m_editGraphX->text();
  QString textY = m_editGraphY->text();
  int posX, posY;
  m_btnOk->setEnabled (!textX.isEmpty () &&
                       !textY.isEmpty () &&
                       (m_validatorGraphX->validate(textX, posX) == QValidator::Acceptable) &&
                       (m_validatorGraphY->validate(textY, posY) == QValidator::Acceptable));
}

