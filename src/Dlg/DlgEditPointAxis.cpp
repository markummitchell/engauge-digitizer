/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DlgEditPointAxis.h"
#include "DlgValidatorAbstract.h"
#include "DlgValidatorFactory.h"
#include "DocumentAxesPointsRequired.h"
#include "DocumentModelCoords.h"
#include "DocumentModelGeneral.h"
#include "EngaugeAssert.h"
#include "FormatCoordsUnits.h"
#include "FormatDateTime.h"
#include "FormatDegreesMinutesSecondsNonPolarTheta.h"
#include "FormatDegreesMinutesSecondsPolarTheta.h"
#include "Logger.h"
#include "MainWindow.h"
#include "MainWindowModel.h"
#include <QDoubleValidator>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QRect>
#include "QtToString.h"
#include <QVBoxLayout>
#include "Transformation.h"

const Qt::Alignment ALIGNMENT = Qt::AlignCenter;

const int MIN_WIDTH_TO_FIT_STRANGE_UNITS = 200;

const bool IS_X_THETA = true;
const bool IS_NOT_X_THETA = false;

DlgEditPointAxis::DlgEditPointAxis (MainWindow &mainWindow,
                                    const DocumentModelCoords &modelCoords,
                                    const DocumentModelGeneral &modelGeneral,
                                    const MainWindowModel &modelMainWindow,
                                    const Transformation &transformation,
                                    DocumentAxesPointsRequired documentAxesPointsRequired,
                                    bool isXOnly,
                                    const double *xInitialValue,
                                    const double *yInitialValue) :
  QDialog (&mainWindow),
  m_documentAxesPointsRequired (documentAxesPointsRequired),
  m_modelCoords (modelCoords),
  m_modelGeneral (modelGeneral),
  m_modelMainWindow (modelMainWindow)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgEditPointAxis::DlgEditPointAxis";

  // Either one or two coordinates are desired
  bool isX = (documentAxesPointsRequired == DOCUMENT_AXES_POINTS_REQUIRED_3) || isXOnly;
  bool isY = (documentAxesPointsRequired == DOCUMENT_AXES_POINTS_REQUIRED_3) || !isXOnly;

  QVBoxLayout *layout = new QVBoxLayout;
  setLayout (layout);

  setCursor  (QCursor (Qt::ArrowCursor));
  setModal(true);
  setWindowTitle (tr ("Edit Axis Point"));

  createCoords (layout);
  createHint (layout);
  createOkCancel (layout);

  initializeGraphCoordinates (xInitialValue,
                              yInitialValue,
                              transformation,
                              isX,
                              isY);

  updateControls ();
}

DlgEditPointAxis::~DlgEditPointAxis()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgEditPointAxis::~DlgEditPointAxis";
}

void DlgEditPointAxis::createCoords (QVBoxLayout *layoutOuter)
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
                                                                                m_modelCoords.coordUnitsTime(),
                                                                                m_modelMainWindow.locale());
  m_validatorGraphY = dlgValidatorFactory.createCartesianOrPolarWithNonPolarPolar (m_modelCoords.coordScaleYRadius(),
                                                                                   isCartesian (),
                                                                                   m_modelCoords.coordUnitsY(),
                                                                                   m_modelCoords.coordUnitsRadius(),
                                                                                   m_modelCoords.coordUnitsDate(),
                                                                                   m_modelCoords.coordUnitsTime(),
                                                                                   m_modelMainWindow.locale());

  // Label, with guidance in terms of legal ranges and units
  QString description = QString ("%1 (%2, %3)%4%5%6%7%8%9 %10 (%11, %12):")
                        .arg (tr ("Graph Coordinates"))
                        .arg (nameXTheta ())
                        .arg (nameYRadius ())
                        .arg (isConstraintX || isConstraintY ? " with " : "")
                        .arg (isConstraintX                  ? QString (nameXTheta ()) : "")
                        .arg (isConstraintX                  ? " > 0" : "")
                        .arg (isConstraintX && isConstraintY ? " and " : "")
                        .arg (                 isConstraintY ? QString (nameYRadius ()) : "")
                        .arg (                 isConstraintY ? " > 0" : "")
                        .arg (tr ("as"))
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
                                  "For cartesian plots this is X. For polar plots this is the radius R.\n\n"
                                  "The expected format of the coordinate value is determined by the locale setting. If "
                                  "typed values are not recognized as expected, check the locale setting in Settings / Main Window..."));
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
                                  "For cartesian plots this is Y. For plot plots this is the angle Theta.\n\n"
                                  "The expected format of the coordinate value is determined by the locale setting. If "
                                  "typed values are not recognized as expected, check the locale setting in Settings / Main Window..."));
  layout->addWidget(m_editGraphY, 0);
  connect (m_editGraphY, SIGNAL (textChanged (const QString &)), this, SLOT (slotTextChanged (const QString &)));

  QLabel *labelGraphParRight = new QLabel (tr (")"), this);
  layout->addWidget(labelGraphParRight, 0);
}

void DlgEditPointAxis::createHint (QVBoxLayout *layoutOuter)
{
  // Insert a hint explaining why decimal points may not be accepted. Very confusing for user to figure out the problem at first, and
  // then figure out which setting should change to fix it. The hint is centered so it is slightly less intrusive

  QWidget *widget = new QWidget;
  layoutOuter->addWidget (widget, 0, Qt::AlignCenter);

  QHBoxLayout *layout = new QHBoxLayout;
  widget->setLayout (layout);

  QString locale = QLocaleToString (m_modelMainWindow.locale ());
  QString hint = QString ("%1: %2")
                 .arg (tr ("Number format"))
                 .arg (locale);
  QLabel *label = new QLabel (hint);
  layout->addWidget (label);
}

void DlgEditPointAxis::createOkCancel (QVBoxLayout *layoutOuter)
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

void DlgEditPointAxis::initializeGraphCoordinates (const double *xInitialValue,
                                                   const double *yInitialValue,
                                                   const Transformation &transformation,
                                                   bool isX,
                                                   bool isY)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgEditPointAxis::initializeGraphCoordinates";

  QString xTheta, yRadius;
  if ((xInitialValue != 0) &&
      (yInitialValue != 0)) {

    FormatCoordsUnits format;
    format.unformattedToFormatted (*xInitialValue,
                                   *yInitialValue,
                                   m_modelCoords,
                                   m_modelGeneral,
                                   m_modelMainWindow,
                                   xTheta,
                                   yRadius,
                                   transformation);
  }

  if (isX) {
    m_editGraphX->setText (xTheta);
  } else {
    m_editGraphX->setText ("");
  }

  if (isY) {
    m_editGraphY->setText (yRadius);
  } else {
    m_editGraphY->setText ("");
  }
}

bool DlgEditPointAxis::isCartesian () const
{
  return (m_modelCoords.coordsType() == COORDS_TYPE_CARTESIAN);
}

QChar DlgEditPointAxis::nameXTheta () const
{
  return (isCartesian () ? QChar ('X') : THETA);
}

QChar DlgEditPointAxis::nameYRadius () const
{
  return (isCartesian () ? QChar ('Y') : QChar ('R'));
}

QPointF DlgEditPointAxis::posGraph (bool &isXOnly) const
{
  double xTheta, yRadius;

  FormatCoordsUnits format;

  format.formattedToUnformatted (m_editGraphX->text(),
                                 m_editGraphY->text(),
                                 m_modelCoords,
                                 m_modelMainWindow,
                                 xTheta,
                                 yRadius);

  // If yRadius value is empty then this is the xTheta value only
  isXOnly = m_editGraphY->text().isEmpty();

  return QPointF (xTheta,
                  yRadius);
}

void DlgEditPointAxis::slotTextChanged (const QString &)
{
  updateControls ();
}

QString DlgEditPointAxis::unitsType (bool isXTheta) const
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

void DlgEditPointAxis::updateControls ()
{
  QString textX = m_editGraphX->text();
  QString textY = m_editGraphY->text();

  int posX, posY;

  if (m_documentAxesPointsRequired == DOCUMENT_AXES_POINTS_REQUIRED_4) {

    bool gotX = (!textX.isEmpty() &&
                 (m_validatorGraphX->validate(textX, posX) == QValidator::Acceptable));
    bool gotY = (!textY.isEmpty() &&
                 (m_validatorGraphY->validate(textY, posY) == QValidator::Acceptable));

    // Check for not empty in one coordinate and for valid number in the other coordinate
    m_btnOk->setEnabled ((textX.isEmpty() && gotY) ||
                         (textY.isEmpty() && gotX));

  } else {

    // Check for not empty (which allows single minus sign) and for valid number (which prevents single minus sign)
    m_btnOk->setEnabled (!textX.isEmpty () &&
                         !textY.isEmpty () &&
                         (m_validatorGraphX->validate(textX, posX) == QValidator::Acceptable) &&
                         (m_validatorGraphY->validate(textY, posY) == QValidator::Acceptable));

  }
}
