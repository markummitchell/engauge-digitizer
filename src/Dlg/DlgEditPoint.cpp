#include "DigitizeStateAbstractBase.h"
#include "DlgEditPoint.h"
#include "DocumentModelCoords.h"
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
const QChar THETA (QChar(0x98, 0x03));

DlgEditPoint::DlgEditPoint (MainWindow &mainWindow,
                            DigitizeStateAbstractBase &digitizeState,
                            const DocumentModelCoords &modelCoords,
                            const QCursor &cursorShape,
                            QString xValue,
                            QString yValue) :
  QDialog (&mainWindow),
  m_cursorShape (cursorShape)
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

  createCoords (layout,
                modelCoords);
  createOkCancel (layout);

  m_editGraphX->setText (xValue);
  m_editGraphY->setText (yValue);

  updateControls ();
}

DlgEditPoint::~DlgEditPoint()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgEditPoint::~DlgEditPoint";

  emit signalSetOverrideCursor (m_cursorShape);
}

void DlgEditPoint::createCoords (QVBoxLayout *layoutOuter,
                                 const DocumentModelCoords &modelCoords)
{
  bool isCartesian = (modelCoords.coordsType() == COORDS_TYPE_CARTESIAN);
  QString description = QString ("Graph Coordinates (%1, %2):")
                        .arg (isCartesian ? QChar ('X') : THETA)
                        .arg (isCartesian ? QChar ('Y') : QChar ('R'));
  QGroupBox *panel = new QGroupBox (description, this);
  layoutOuter->addWidget (panel);

  QHBoxLayout *layout = new QHBoxLayout (panel);
  panel->setLayout (layout);

  // Row
  QLabel *labelGraphParLeft = new QLabel (tr ("("), this);
  layout->addWidget(labelGraphParLeft, 0);

  m_editGraphX = new QLineEdit;
  m_editGraphX->setAlignment (ALIGNMENT);
  m_validatorGraphX = new QDoubleValidator ();
  m_editGraphX->setValidator (m_validatorGraphX);
  // setStatusTip does not work for modal dialogs
  m_editGraphX->setWhatsThis (tr ("Enter the first graph coordinate of the axis point.\n\n"
                                  "For cartesian plots this is X. For polar plots this is the radius R."));
  layout->addWidget(m_editGraphX, 0);
  connect (m_editGraphX, SIGNAL (textChanged (const QString &)), this, SLOT (slotTextChanged (const QString &)));

  QLabel *labelGraphComma = new QLabel (tr (", "), this);
  layout->addWidget(labelGraphComma, 0);

  m_editGraphY = new QLineEdit;
  m_editGraphY->setAlignment (ALIGNMENT);
  m_validatorGraphY = new QDoubleValidator ();
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

QPointF DlgEditPoint::posGraph () const
{
  return QPointF (m_editGraphX->text().toDouble (),
                  m_editGraphY->text().toDouble ());
}

void DlgEditPoint::slotTextChanged (const QString &)
{
  updateControls ();
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

