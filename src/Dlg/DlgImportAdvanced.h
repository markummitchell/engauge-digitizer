#ifndef DLG_IMPORT_ADVANCED_H
#define DLG_IMPORT_ADVANCED_H

#include "DlgSettingsAbstractBase.h"
#include "DocumentAxesPointsRequired.h"
#include <QObject>

class QRadioButton;
class QSpinBox;
class QString;

/// Dialog for setting the advanced parameters in a newly imported Document
class DlgImportAdvanced : public DlgSettingsAbstractBase {
  Q_OBJECT;

public:
  /// Single constructor
  DlgImportAdvanced(MainWindow &mainWindow);

  virtual void createOptionalSaveDefault(QHBoxLayout *layout);
  virtual QWidget *createSubPanel();

  /// Number of axes points selected by user
  DocumentAxesPointsRequired documentAxesPointsRequired() const;

  virtual void handleOk();
  virtual void load(CmdMediator &cmdMediator);

  /// Number of coordinate systems selected by user
  unsigned int numberCoordSystem() const;

private slots:
  void slotAxesPointCount(bool);
  void slotCoordSystemCount(const QString &);

private:
  DlgImportAdvanced();

  QSpinBox *m_spinCoordSystemCount;
  QRadioButton *m_btnAxesPointCount3;
  QRadioButton *m_btnAxesPointCount4;
};

#endif // DLG_IMPORT_ADVANCED_H
