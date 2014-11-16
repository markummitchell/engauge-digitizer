#include "CmdMediator.h"
#include "DlgPreferencesPagePointMatch.h"
#include "Logger.h"
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

DlgPreferencesPagePointMatch::DlgPreferencesPagePointMatch(CmdMediator &cmdMediator,
                                                   QWidget *parent) :
  DlgPreferencesPageAbstractBase (cmdMediator,
                                  parent)
{
  QGridLayout *layout = new QGridLayout (this);
  setLayout (layout);

  layout->setColumnStretch(0, 1); // Empty column
  layout->setColumnStretch(1, 0); // Labels
  layout->setColumnStretch(2, 0); // Controls
  layout->setColumnStretch(3, 1); // Empty column

  int row = 0;
  createControls (layout, row);
  createPreview (layout, row);
}

void DlgPreferencesPagePointMatch::createControls (QGridLayout *layout,
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
  connect (m_cmbAcceptedPointColor, SIGNAL (currentTextChanged (const QString &)), this, SLOT (slotAcceptedPointColor (const QString &)));
  layout->addWidget (m_cmbAcceptedPointColor, row++, 2);

  QLabel *labelRejectedPointColor = new QLabel ("Rejected point color:");
  layout->addWidget (labelRejectedPointColor, row, 1);

  m_cmbRejectedPointColor = new QComboBox;
  m_cmbRejectedPointColor->setWhatsThis (tr ("Select a color for matched points that are rejected"));
  connect (m_cmbRejectedPointColor, SIGNAL (currentTextChanged (const QString &)), this, SLOT (slotRejectedPointColor (const QString &)));
  layout->addWidget (m_cmbRejectedPointColor, row++, 2);

  QLabel *labelCandidatePointColor = new QLabel ("Candidate point color:");
  layout->addWidget (labelCandidatePointColor, row, 1);

  m_cmbCandidatePointColor = new QComboBox;
  m_cmbCandidatePointColor->setWhatsThis (tr ("Select a color for the point being decided upon"));
  connect (m_cmbCandidatePointColor, SIGNAL (currentTextChanged (const QString &)), this, SLOT (slotCandidatePointColor (const QString &)));
  layout->addWidget (m_cmbCandidatePointColor, row++, 2);
}

void DlgPreferencesPagePointMatch::createPreview (QGridLayout *layout,
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

  layout->addWidget (m_viewPreview, row++, 0, 1, 4);
}

void DlgPreferencesPagePointMatch::load ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPagePointMatch::load";
}

void DlgPreferencesPagePointMatch::slotAcceptedPointColor (const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPagePointMatch::slotAcceptedPointColor";
}

void DlgPreferencesPagePointMatch::slotCandidatePointColor (const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPagePointMatch::slotCandidatePointColor";
}

void DlgPreferencesPagePointMatch::slotPointSeparation (const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPagePointMatch::slotPointSeparation";
}

void DlgPreferencesPagePointMatch::slotPointSize (const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPagePointMatch::slotPointSize";
}

void DlgPreferencesPagePointMatch::slotRejectedPointColor (const QString &)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPagePointMatch::slotRejectedPointColor";
}
