/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DlgEditScale.h"
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

DlgEditScale::DlgEditScale (MainWindow &mainWindow,
                            const DocumentModelCoords &modelCoords,
                            const DocumentModelGeneral &modelGeneral,
                            const MainWindowModel &modelMainWindow,
                            const double *scaleLength) :
  QDialog (&mainWindow),
  m_modelCoords (modelCoords),
  m_modelGeneral (modelGeneral),
  m_modelMainWindow (modelMainWindow)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgEditScale::DlgEditScale";

  QVBoxLayout *layout = new QVBoxLayout;
  setLayout (layout);

  setCursor  (QCursor (Qt::ArrowCursor));
  setModal(true);
  setWindowTitle (tr ("Edit Axis Point"));

  createScaleLength (layout);
  createHint (layout);
  createOkCancel (layout);

  initializeScaleLength (scaleLength);
  
  updateControls ();
}

DlgEditScale::~DlgEditScale()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgEditScale::~DlgEditScale";
}

void DlgEditScale::createHint (QVBoxLayout *layoutOuter)
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

void DlgEditScale::createOkCancel (QVBoxLayout *layoutOuter)
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

void DlgEditScale::createScaleLength (QVBoxLayout *layoutOuter)
{
  // Simple validation strategy
  DlgValidatorFactory dlgValidatorFactory;
  m_validatorScaleLength = dlgValidatorFactory.createAboveZero (m_modelMainWindow.locale());

  // Label, with guidance in terms of legal ranges and units
  QGroupBox *panel = new QGroupBox (tr ("Scale Length"), this);
  layoutOuter->addWidget (panel);

  QHBoxLayout *layout = new QHBoxLayout (panel);
  panel->setLayout (layout);

  // Row
  m_editScaleLength = new QLineEdit;
  m_editScaleLength->setMinimumWidth(MIN_WIDTH_TO_FIT_STRANGE_UNITS);
  m_editScaleLength->setAlignment (ALIGNMENT);
  m_editScaleLength->setValidator (m_validatorScaleLength);
  // setStatusTip does not work for modal dialogs
  m_editScaleLength->setWhatsThis (tr ("Enter the scale bar length"));
  layout->addWidget(m_editScaleLength, 0);
  connect (m_editScaleLength, SIGNAL (textChanged (const QString &)), this, SLOT (slotTextChanged (const QString &)));
}

void DlgEditScale::initializeScaleLength (const double *scaleLength)
{
  if (scaleLength != 0) {
    m_editScaleLength->setText (QString::number (*scaleLength));
  }
}

double DlgEditScale::scaleLength () const
{
  double xTheta, yRadius;
  const QString DUMMY_Y ("0");

  FormatCoordsUnits format;

  // Format conversion is done using x coordinate. Y coordinate is given a dummy value and the result is ignored
  format.formattedToUnformatted (m_editScaleLength->text(),
                                 DUMMY_Y,
                                 m_modelCoords,
                                 m_modelMainWindow,
                                 xTheta,
                                 yRadius);

  return xTheta;
}

void DlgEditScale::slotTextChanged (const QString &)
{
  updateControls ();
}

void DlgEditScale::updateControls ()
{
  QString textScaleLength = m_editScaleLength->text();

  int posScaleLength;

  // Check for not empty (which allows single minus sign) and for valid number (which prevents single minus sign)
  m_btnOk->setEnabled (!textScaleLength.isEmpty () &&
                       (m_validatorScaleLength->validate(textScaleLength, posScaleLength) == QValidator::Acceptable));
}
