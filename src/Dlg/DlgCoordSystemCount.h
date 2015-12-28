#ifndef DLG_COORD_SYSTEM_COUNT_H
#define DLG_COORD_SYSTEM_COUNT_H

#include "DlgSettingsAbstractBase.h"
#include <QObject>
#include <QSpinBox>

class QSpinBox;
class QString;

/// Dialog for setting the number of coordinates systems in a newly imported Document
class DlgCoordSystemCount : public DlgSettingsAbstractBase
{
  Q_OBJECT;

 public:
  /// Single constructor
  DlgCoordSystemCount(MainWindow &mainWindow);

  virtual void createOptionalSaveDefault (QHBoxLayout *layout);
  virtual QWidget *createSubPanel ();
  virtual void handleOk();
  virtual void load(CmdMediator &cmdMediator);

  /// Number of coordinate systems selected by user
  unsigned int numberCoordSystem () const;

 private slots:
  /// Number of coordinate systems has changed
  void slotCount(const QString &);

 private:
  DlgCoordSystemCount();

  QSpinBox *m_spinCount;
};

#endif // DLG_COORD_SYSTEM_COUNT_H
