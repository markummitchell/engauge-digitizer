#include "CmdMediator.h"
#include "CmdSettingsPointMatch.h"
#include "DlgSettingsPointMatch.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QComboBox>
#include <QIntValidator>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QLabel>
#include <QLineEdit>
#include "ViewPreview.h"

const int POINT_SEPARATION_MAX = 1024;
const int POINT_SEPARATION_MIN = 1;
const int POINT_SIZE_MAX = 1024;
const int POINT_SIZE_MIN = 1;

DlgSettingsPointMatch::DlgSettingsPointMatch(MainWindow &mainWindow) :
  DlgSettingsAbstractBase ("Point Match", mainWindow),
  m_modelPointMatchBefore (0),
  m_modelPointMatchAfter (0)
{
  QWidget *subPanel = createSubPanel ();
  finishPanel (subPanel);
}

void DlgSettingsPointMatch::createControls (QGridLayout *layout,
                                            int &row)
{
  QLabel *labelPointSeparation = new QLabel ("Point separation (pixels):");
  layout->addWidget (labelPointSeparation, row, 1);

  m_editPointSeparation = new QLineEdit;
  m_editPointSeparation->setWhatsThis (tr ("Select a point separation in pixels.\n\n"
                                           "Matched points must be separated from existing points by at least this number of pixels.\n\n"
                                           "This value has a lower limit"));
  m_editPointSeparation->setValidator (new QIntValidator (POINT_SEPARATION_MIN, POINT_SEPARATION_MAX));
  connect (m_editPointSeparation, SIGNAL (textChanged (const QString &)), this, SLOT (slotPointSeparation (const QString &)));
  layout->addWidget (m_editPointSeparation, row++, 2);

  QLabel *labelPointSize = new QLabel ("Maximum point size (pixels):");
  layout->addWidget (labelPointSize, row, 1);

  m_editPointSize = new QLineEdit;
  m_editPointSize->setWhatsThis (tr ("Select a maximum point size in pixels.\n\n"
                                     "Sample match points must fit within a square box, around the cursor, having width and height "
                                     "equal to this maximum.\n\n"
                                     "This size is also used to determine if a region of pixels that are on, in the processed image, "
                                     "should be ignored since that region is wider or taller than this limit.\n\n"
                                     "This value has a lower limit"));
  m_editPointSize->setValidator (new QIntValidator (POINT_SIZE_MIN, POINT_SIZE_MAX));
  connect (m_editPointSize, SIGNAL (textChanged (const QString &)), this, SLOT (slotPointSize (const QString &)));
  layout->addWidget (m_editPointSize, row++, 2);

  QLabel *labelAcceptedPointColor = new QLabel ("Accepted point color:");
  layout->addWidget (labelAcceptedPointColor, row, 1);

  m_cmbAcceptedPointColor = new QComboBox;
  m_cmbAcceptedPointColor->setWhatsThis (tr ("Select a color for matched points that are accepted"));
  m_cmbAcceptedPointColor->addItem ("Blue", QVariant (COLOR_PALETTE_BLUE));
  m_cmbAcceptedPointColor->addItem ("Red", QVariant (COLOR_PALETTE_RED));
  m_cmbAcceptedPointColor->addItem ("Black", QVariant (COLOR_PALETTE_BLACK));
  m_cmbAcceptedPointColor->addItem ("Cyan", QVariant (COLOR_PALETTE_CYAN));
  m_cmbAcceptedPointColor->addItem ("Gold", QVariant (COLOR_PALETTE_GOLD));
  m_cmbAcceptedPointColor->addItem ("Green", QVariant (COLOR_PALETTE_GREEN));
  m_cmbAcceptedPointColor->addItem ("Magenta", QVariant (COLOR_PALETTE_MAGENTA));
  m_cmbAcceptedPointColor->addItem ("Red", QVariant (COLOR_PALETTE_RED));
  m_cmbAcceptedPointColor->addItem ("Yellow", QVariant (COLOR_PALETTE_YELLOW));
  m_cmbAcceptedPointColor->addItem ("Transparent", QVariant (COLOR_PALETTE_TRANSPARENT));
  connect (m_cmbAcceptedPointColor, SIGNAL (currentTextChanged (const QString &)), this, SLOT (slotAcceptedPointColor (const QString &)));
  layout->addWidget (m_cmbAcceptedPointColor, row++, 2);

  QLabel *labelRejectedPointColor = new QLabel ("Rejected point color:");
  layout->addWidget (labelRejectedPointColor, row, 1);

  m_cmbRejectedPointColor = new QComboBox;
  m_cmbRejectedPointColor->setWhatsThis (tr ("Select a color for matched points that are rejected"));
  m_cmbRejectedPointColor->addItem ("Blue", QVariant (COLOR_PALETTE_BLUE));
  m_cmbRejectedPointColor->addItem ("Red", QVariant (COLOR_PALETTE_RED));
  m_cmbRejectedPointColor->addItem ("Black", QVariant (COLOR_PALETTE_BLACK));
  m_cmbRejectedPointColor->addItem ("Cyan", QVariant (COLOR_PALETTE_CYAN));
  m_cmbRejectedPointColor->addItem ("Gold", QVariant (COLOR_PALETTE_GOLD));
  m_cmbRejectedPointColor->addItem ("Green", QVariant (COLOR_PALETTE_GREEN));
  m_cmbRejectedPointColor->addItem ("Magenta", QVariant (COLOR_PALETTE_MAGENTA));
  m_cmbRejectedPointColor->addItem ("Red", QVariant (COLOR_PALETTE_RED));
  m_cmbRejectedPointColor->addItem ("Yellow", QVariant (COLOR_PALETTE_YELLOW));
  m_cmbRejectedPointColor->addItem ("Transparent", QVariant (COLOR_PALETTE_TRANSPARENT));
  connect (m_cmbRejectedPointColor, SIGNAL (currentTextChanged (const QString &)), this, SLOT (slotRejectedPointColor (const QString &)));
  layout->addWidget (m_cmbRejectedPointColor, row++, 2);

  QLabel *labelCandidatePointColor = new QLabel ("Candidate point color:");
  layout->addWidget (labelCandidatePointColor, row, 1);

  m_cmbCandidatePointColor = new QComboBox;
  m_cmbCandidatePointColor->setWhatsThis (tr ("Select a color for the point being decided upon"));
  m_cmbCandidatePointColor->addItem ("Blue", QVariant (COLOR_PALETTE_BLUE));
  m_cmbCandidatePointColor->addItem ("Red", QVariant (COLOR_PALETTE_RED));
  m_cmbCandidatePointColor->addItem ("Black", QVariant (COLOR_PALETTE_BLACK));
  m_cmbCandidatePointColor->addItem ("Cyan", QVariant (COLOR_PALETTE_CYAN));
  m_cmbCandidatePointColor->addItem ("Gold", QVariant (COLOR_PALETTE_GOLD));
  m_cmbCandidatePointColor->addItem ("Green", QVariant (COLOR_PALETTE_GREEN));
  m_cmbCandidatePointColor->addItem ("Magenta", QVariant (COLOR_PALETTE_MAGENTA));
  m_cmbCandidatePointColor->addItem ("Red", QVariant (COLOR_PALETTE_RED));
  m_cmbCandidatePointColor->addItem ("Yellow", QVariant (COLOR_PALETTE_YELLOW));
  m_cmbCandidatePointColor->addItem ("Transparent", QVariant (COLOR_PALETTE_TRANSPARENT));
  connect (m_cmbCandidatePointColor, SIGNAL (currentTextChanged (const QString &)), this, SLOT (slotCandidatePointColor (const QString &)));
  layout->addWidget (m_cmbCandidatePointColor, row++, 2);
}

void DlgSettingsPointMatch::createPreview (QGridLayout *layout,
                                           int &row)
{
  QLabel *labelPreview = new QLabel ("Preview");
  layout->addWidget (labelPreview, row++, 0, 1, 4);

  m_scenePreview = new QGraphicsScene (this);
  m_viewPreview = new ViewPreview (m_scenePreview, this);
  m_viewPreview->setWhatsThis (tr ("Preview window shows how current settings affect "
                                   "point matching, and how the marked and candidate points are displayed.\n\nThe points are separated "
                                   "by the point separation value, and the maximum point size is shown as a box in the center"));
  m_viewPreview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setMinimumHeight (MINIMUM_PREVIEW_HEIGHT);

  layout->addWidget (m_viewPreview, row++, 0, 1, 4);
}

QWidget *DlgSettingsPointMatch::createSubPanel ()
{
  QWidget *subPanel = new QWidget ();
  QGridLayout *layout = new QGridLayout (subPanel);
  subPanel->setLayout (layout);

  layout->setColumnStretch(0, 1); // Empty column
  layout->setColumnStretch(1, 0); // Labels
  layout->setColumnStretch(2, 0); // Controls
  layout->setColumnStretch(3, 1); // Empty column

  int row = 0;
  createControls (layout, row);
  createPreview (layout, row);

  return subPanel;
}

void DlgSettingsPointMatch::handleOk ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsPointMatch::handleOk";

  CmdSettingsPointMatch *cmd = new CmdSettingsPointMatch (mainWindow (),
                                                          cmdMediator ().document(),
                                                          *m_modelPointMatchBefore,
                                                          *m_modelPointMatchAfter);
  cmdMediator ().push (cmd);

  hide ();
}

void DlgSettingsPointMatch::load (CmdMediator &cmdMediator)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsPointMatch::load";

  setCmdMediator (cmdMediator);

  m_modelPointMatchBefore = new DocumentModelPointMatch (cmdMediator.document());
  m_modelPointMatchAfter = new DocumentModelPointMatch (cmdMediator.document());

  m_editPointSeparation->setText(QString::number(m_modelPointMatchAfter->pointSeparation()));
  m_editPointSize->setText(QString::number(m_modelPointMatchAfter->maxPointSize()));

  int indexAccepted = m_cmbAcceptedPointColor->findData(QVariant(m_modelPointMatchAfter->paletteColorAccepted()));
  Q_ASSERT (indexAccepted >= 0);
  m_cmbAcceptedPointColor->setCurrentIndex(indexAccepted);

  int indexCandidate = m_cmbCandidatePointColor->findData(QVariant(m_modelPointMatchAfter->paletteColorCandidate()));
  Q_ASSERT (indexCandidate >= 0);
  m_cmbCandidatePointColor->setCurrentIndex(indexCandidate);

  int indexRejected = m_cmbRejectedPointColor->findData(QVariant(m_modelPointMatchAfter->paletteColorRejected()));
  Q_ASSERT (indexRejected >= 0);
  m_cmbRejectedPointColor->setCurrentIndex(indexRejected);

}

void DlgSettingsPointMatch::slotAcceptedPointColor (const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsPointMatch::slotAcceptedPointColor";

  enableOk (true);

  m_modelPointMatchAfter->setPaletteColorAccepted((ColorPalette) m_cmbAcceptedPointColor->currentData().toInt());
}

void DlgSettingsPointMatch::slotCandidatePointColor (const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsPointMatch::slotCandidatePointColor";

  enableOk (true);

  m_modelPointMatchAfter->setPaletteColorCandidate((ColorPalette) m_cmbCandidatePointColor->currentData().toInt());
}

void DlgSettingsPointMatch::slotPointSeparation (const QString &pointSeparation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsPointMatch::slotPointSeparation";

  enableOk (true);

  m_modelPointMatchAfter->setPointSeparation(pointSeparation.toDouble());
}

void DlgSettingsPointMatch::slotPointSize (const QString &pointSize)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsPointMatch::slotPointSize";

  enableOk (true);

  m_modelPointMatchAfter->setMaxPointSize(pointSize.toDouble());
}

void DlgSettingsPointMatch::slotRejectedPointColor (const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgSettingsPointMatch::slotRejectedPointColor";

  enableOk (true);

  m_modelPointMatchAfter->setPaletteColorRejected((ColorPalette) m_cmbRejectedPointColor->currentData().toInt());
}
