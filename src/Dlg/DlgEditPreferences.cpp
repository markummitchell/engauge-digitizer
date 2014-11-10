#include "CmdMediator.h"
#include "DlgEditPreferences.h"
#include "DlgPreferencesPageCoords.h"
#include "DlgPreferencesPageCurves.h"
#include "DlgPreferencesPageCurveProperties.h"
#include "DlgPreferencesPageExport.h"
#include "DlgPreferencesPageFilter.h"
#include "DlgPreferencesPageGridDisplay.h"
#include "DlgPreferencesPageGridRemoval.h"
#include "DlgPreferencesPagePointMatch.h"
#include "DlgPreferencesPageSegments.h"
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>

const int MIN_DIALOG_HEIGHT = 550; // Big enough that preview window will not have scroll bar
const int MIN_DIALOG_WIDTH = 660; // Big enough that list widget will not have scroll bar

DlgEditPreferences::DlgEditPreferences(CmdMediator &cmdMediator) :
  m_cmdMediator (cmdMediator),
  m_listWidget (0)
{
  setWindowTitle (tr ("Edit Preferences"));
  setMinimumHeight (MIN_DIALOG_HEIGHT);
  setMinimumWidth (MIN_DIALOG_WIDTH);

  createListWidget();
  createStackedWidgets();

  m_btnClose = new QPushButton (tr ("Close"));
  connect (m_btnClose, SIGNAL (clicked ()), this, SLOT (close ()));

  QHBoxLayout *listLayout = new QHBoxLayout;
  listLayout->addWidget (m_listWidget);
  listLayout->addWidget (m_stackedWidget, 1);

  QHBoxLayout *buttonLayout = new QHBoxLayout;
  buttonLayout->addStretch (1);
  buttonLayout->addWidget (m_btnClose);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addLayout (listLayout);
  mainLayout->addLayout (buttonLayout);
  setLayout (mainLayout);
}

void DlgEditPreferences::changePage (QListWidgetItem *current,
                                     QListWidgetItem *previous)
{
  if (!current) {
    current = previous;
  }

  m_stackedWidget->setCurrentIndex (m_listWidget->row (current));
}

void DlgEditPreferences::createListWidget ()
{
  m_listWidget = new QListWidget;
  m_listWidget->setWhatsThis (tr ("Preferences page list"));
  m_listWidget->setViewMode (QListView::IconMode);
  m_listWidget->setIconSize (QSize (96, 84));
  m_listWidget->setMovement (QListView::Static);
  m_listWidget->setMinimumWidth (142);
  m_listWidget->setMaximumWidth (142);
  m_listWidget->setSpacing (12);

  m_listWidget->setCurrentRow (0);

  connect (m_listWidget, SIGNAL (currentItemChanged (QListWidgetItem *, QListWidgetItem *)),
           this, SLOT (changePage (QListWidgetItem *, QListWidgetItem *)));
}

void DlgEditPreferences::createStackedWidgetPage (QWidget *&widget,
                                                  const QString &imageFile,
                                                  const QString &title)
{
  m_stackedWidget->addWidget (widget);

  // Clickable icon/button
  QListWidgetItem *btn = new QListWidgetItem (m_listWidget);
  btn->setIcon (QIcon (imageFile));
  btn->setText (title);
  btn->setTextAlignment (Qt::AlignHCenter);
  btn->setFlags (Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}

void DlgEditPreferences::createStackedWidgets ()
{
  m_stackedWidget = new QStackedWidget;

  m_frameCoords = dynamic_cast<QWidget*> (new DlgPreferencesPageCoords (m_cmdMediator));
  createStackedWidgetPage (m_frameCoords,
                           ":/engauge6/img/settings_coords.png",
                           "Coordinates");

  m_frameCurves = dynamic_cast<QWidget*> (new DlgPreferencesPageCurves (m_cmdMediator));
  createStackedWidgetPage (m_frameCurves,
                           ":/engauge6/img/settings_curves.png",
                           "Curves");

  m_frameCurveProperties = dynamic_cast<QWidget*> (new DlgPreferencesPageCurveProperties (m_cmdMediator));
  createStackedWidgetPage (m_frameCurveProperties,
                           ":/engauge6/img/settings_curve_properties.png",
                           "Curve Properties");

  m_frameExport = dynamic_cast<QWidget*> (new DlgPreferencesPageExport (m_cmdMediator));
  createStackedWidgetPage (m_frameExport,
                           ":/engauge6/img/settings_export.png",
                           "Export");

  m_frameFilter = dynamic_cast<QWidget*> (new DlgPreferencesPageFilter (m_cmdMediator));
  createStackedWidgetPage (m_frameFilter,
                           ":/engauge6/img/settings_filter.png",
                           "Filter");

  m_frameGridDisplay = dynamic_cast<QWidget*> (new DlgPreferencesPageGridDisplay (m_cmdMediator));
  createStackedWidgetPage (m_frameGridDisplay,
                           ":/engauge6/img/settings_grid_display.png",
                           "Grid Display");

  m_frameGridRemoval = dynamic_cast<QWidget*> (new DlgPreferencesPageGridRemoval (m_cmdMediator));
  createStackedWidgetPage (m_frameGridRemoval,
                           ":/engauge6/img/settings_grid_removal.png",
                           "Grid Removal");

  m_framePointMatch = dynamic_cast<QWidget*> (new DlgPreferencesPagePointMatch (m_cmdMediator));
  createStackedWidgetPage (m_framePointMatch,
                           ":/engauge6/img/settings_point_match.png",
                           "Point Match");

  m_frameSegments = dynamic_cast<QWidget*> (new DlgPreferencesPageSegments (m_cmdMediator));
  createStackedWidgetPage (m_frameSegments,
                           ":/engauge6/img/settings_segments.png",
                           "Segments");
}
