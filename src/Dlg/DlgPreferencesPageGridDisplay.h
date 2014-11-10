#ifndef DLG_PREFERENCES_PAGE_GRID_DISPLAY_H
#define DLG_PREFERENCES_PAGE_GRID_DISPLAY_H

#include <QWidget>

class CmdMediator;
class QComboBox;
class QGraphicsScene;
class QGridLayout;
class QLineEdit;
class ViewPreview;

/// Stacked widget page for editing grid display preferences.
class DlgPreferencesPageGridDisplay : public QWidget
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgPreferencesPageGridDisplay(CmdMediator &cmdMediator,
                                QWidget *parent = 0);

private slots:
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

private:
  DlgPreferencesPageGridDisplay(QWidget *parent = 0);

  void createX (QGridLayout *layout, int &row);
  void createY (QGridLayout *layout, int &row);
  void createPreview (QGridLayout *layout, int &row);

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

  QGraphicsScene *m_scenePreview;
  ViewPreview *m_viewPreview;
};

#endif // DLG_PREFERENCES_PAGE_GRID_DISPLAY_H
