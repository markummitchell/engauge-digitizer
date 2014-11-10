#ifndef DLG_PREFERENCES_PAGE_GRID_REMOVAL_H
#define DLG_PREFERENCES_PAGE_GRID_REMOVAL_H

#include <QWidget>

class CmdMediator;
class ViewPreview;
class QCheckBox;
class QComboBox;
class QGraphicsScene;
class QGridLayout;
class QHBoxLayout;
class QLineEdit;

/// Stacked widget page for editing grid removal preferences.
class DlgPreferencesPageGridRemoval : public QWidget
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgPreferencesPageGridRemoval(CmdMediator &cmdMediator,
                                QWidget *parent = 0);

private slots:
  void slotRemoveGridLines (int);
  void slotCloseDistance(const QString &);

  void slotDisableX(const QString &);
  void slotCountX(const QString &);
  void slotStartX(const QString &);
  void slotStepX(const QString &);
  void slotStopX(const QString &);

  void slotDisableY(const QString &);
  void slotCountY(const QString &);
  void slotStartY(const QString &);
  void slotStepY(const QString &);
  void slotStopY(const QString &);

  void slotRemoveParallel (int);

private:
  DlgPreferencesPageGridRemoval(QWidget *parent = 0);

  void createRemoveGridLines (QGridLayout *layout, int &row);
  void createRemoveGridLinesX (QGridLayout *layoutGridLines, int &row);
  void createRemoveGridLinesY (QGridLayout *layoutGridLines, int &row);
  void createRemoveParallel (QGridLayout *layout, int &row);
  void createPreview (QGridLayout *layout, int &row);
  void updateControls ();

  QCheckBox *m_chkRemoveGridLines;
  QLineEdit *m_editCloseDistance;

  QComboBox *m_cmbDisableX;
  QLineEdit *m_editCountX;
  QLineEdit *m_editStartX;
  QLineEdit *m_editStepX;
  QLineEdit *m_editStopX;

  QComboBox *m_cmbDisableY;
  QLineEdit *m_editCountY;
  QLineEdit *m_editStartY;
  QLineEdit *m_editStepY;
  QLineEdit *m_editStopY;

  QCheckBox *m_chkRemoveParallel;

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;
};

#endif // DLG_PREFERENCES_PAGE_GRID_REMOVAL_H
