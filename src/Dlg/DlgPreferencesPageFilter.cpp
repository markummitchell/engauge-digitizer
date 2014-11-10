#include "CmdMediator.h"
#include "DlgPreferencesPageFilter.h"
#include "Logger.h"
#include <QComboBox>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QLabel>
#include <QRadioButton>
#include "ViewPreview.h"
#include "ViewProfile.h"

const int PROFILE_HEIGHT_IN_ROWS = 6;

DlgPreferencesPageFilter::DlgPreferencesPageFilter(CmdMediator &,
                                                   QWidget *parent) :
  QWidget (parent)
{
  const int EMPTY_COLUMN_WIDTH = 40;

  QGridLayout *layout = new QGridLayout (this);
  setLayout (layout);

  layout->setColumnStretch(0, 0); // Empty column
  layout->setColumnMinimumWidth(0, EMPTY_COLUMN_WIDTH);
  layout->setColumnStretch(1, 0); // Radio buttons
  layout->setColumnStretch(2, 0); // Empty column to put some space between previous and next columns, so they are not too close
  layout->setColumnMinimumWidth(2, 15);
  layout->setColumnStretch(3, 1); // Profile
  layout->setColumnMinimumWidth(4, EMPTY_COLUMN_WIDTH); // Empty column

  int rowLeft = 0, rowRight = 0;
  createControls (layout, rowLeft);
  createProfileAndScale (layout, rowRight);

  int row = qMax (rowLeft, rowRight);
  createPreview (layout, row);
}

void DlgPreferencesPageFilter::createControls (QGridLayout *layout, int &row)
{
  QLabel *labelProfile = new QLabel ("Filter parameter:");
  layout->addWidget (labelProfile, row++, 1);

  m_btnIntensity = new QRadioButton ("Intensity");
  m_btnIntensity->setWhatsThis (tr ("Filter the original image into black and white pixels using the Intensity parameter, "
                                    "to hide unimportant information and emphasize important information.\n\n"
                                    "The Intensity value of a pixel is computed from the red, green "
                                    "and blue components as I = (R + G + B) / 3"));
  connect (m_btnIntensity, SIGNAL (pressed ()), this, SLOT (slotIntensity ()));
  layout->addWidget (m_btnIntensity, row++, 1);

  m_btnForeground = new QRadioButton ("Foreground");
  m_btnForeground->setWhatsThis (tr ("Filter the original image into black and white pixels by isolating the foreground from the background, "
                                     "to hide unimportant information and emphasize important information.\n\n"
                                     "The background color is shown on the left side of the scale bar. All pixels with approximately "
                                     "the background color are considered part of the background, and all other pixels are considered "
                                     "part of the foreground"));
  connect (m_btnForeground, SIGNAL (pressed ()), this, SLOT (slotForeground ()));
  layout->addWidget (m_btnForeground, row++, 1);

  m_btnHue = new QRadioButton ("Hue");
  m_btnHue->setWhatsThis (tr ("Filter the original image into black and white pixels using the Hue component of the "
                              "Hue, Saturation and Value (HSV) color components, "
                              "to hide unimportant information and emphasize important information."));
  connect (m_btnHue, SIGNAL (pressed ()), this, SLOT (slotHue ()));
  layout->addWidget (m_btnHue, row++, 1);

  m_btnSaturation = new QRadioButton ("Saturation");
  m_btnSaturation->setWhatsThis (tr ("Filter the original image into black and white pixels using the Saturation component of the "
                                     "Hue, Saturation and Value (HSV) color components, "
                                     "to hide unimportant information and emphasize important information."));
  connect (m_btnSaturation, SIGNAL (pressed ()), this, SLOT (slotSaturation ()));
  layout->addWidget (m_btnSaturation, row++, 1);

  m_btnValue = new QRadioButton ("Value");
  m_btnValue->setWhatsThis (tr ("Filter the original image into black and white pixels using the Value component of the "
                                "Hue, Saturation and Value (HSV) color components, "
                                "to hide unimportant information and emphasize important information.\n\n"
                                "The Value component is also called the Lightness."));
  connect (m_btnValue, SIGNAL (pressed ()), this, SLOT (slotValue ()));
  layout->addWidget (m_btnValue, row++, 1);
}

void DlgPreferencesPageFilter::createPreview (QGridLayout *layout, int &row)
{
  QLabel *labelPreview = new QLabel ("Preview");
  layout->addWidget (labelPreview, row++, 0, 1, 5);

  m_scenePreview = new QGraphicsScene (this);
  m_viewPreview = new ViewPreview (m_scenePreview, this);
  m_viewPreview->setWhatsThis (tr ("Preview window that shows how current settings affect the filtering of the original image."));
  m_viewPreview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_viewPreview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  layout->addWidget (m_viewPreview, row++, 0, 1, 5);
}

void DlgPreferencesPageFilter::createProfileAndScale (QGridLayout *layout, int &row)
{
  QLabel *labelProfile = new QLabel ("Filter Parameter Histogram Profile");
  layout->addWidget (labelProfile, row++, 3);

  m_sceneProfile = new QGraphicsScene;
  m_viewProfile = new ViewProfile (m_sceneProfile);
  m_viewProfile->setWhatsThis (tr ("Histogram profile of the selected filter parameter. The two Dividers can be moved back and forth to adjust "
                                   "the range of filter parameter values that will be included in the filtered image. The clear portion will "
                                   "be included, and the shaded portion will be excluded."));

  layout->addWidget (m_viewProfile, row, 3, PROFILE_HEIGHT_IN_ROWS, 1);
  row += PROFILE_HEIGHT_IN_ROWS;

  m_scale = new QLabel;
  m_scale->setWhatsThis (tr ("This read-only box displays a graphical representation of the horizontal axis in the histogram profile above."));
  m_scale->setAutoFillBackground(true);
  m_scale->setPalette (QPalette (Qt::red));
  layout->addWidget (m_scale, row++, 3);
}

void DlgPreferencesPageFilter::slotForeground ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPageFilter::slotForeground";
}

void DlgPreferencesPageFilter::slotHue ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPageFilter::slotHue";
}

void DlgPreferencesPageFilter::slotIntensity ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPageFilter::slotIntensity";
}

void DlgPreferencesPageFilter::slotSaturation ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPageFilter::slotSaturation";
}

void DlgPreferencesPageFilter::slotValue ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgPreferencesPageFilter::slotValue";
}
