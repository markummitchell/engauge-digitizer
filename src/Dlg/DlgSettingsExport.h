#ifndef DLG_SETTINGS_EXPORT_H
#define DLG_SETTINGS_EXPORT_H

#include "DlgSettingsAbstractBase.h"

class DocumentModelExport;
class QComboBox;
class QDoubleValidator;
class QGridLayout;
class QHBoxLayout;
class QLineEdit;
class QLabel;
class QListWidget;
class QPushButton;
class QRadioButton;
class QTabWidget;
class QTextEdit;
class QVBoxLayout;

/// Stacked widget page for editing exporting settings.
class DlgSettingsExport : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsExport(MainWindow &mainWindow);
  virtual ~DlgSettingsExport();

  virtual QWidget *createSubPanel ();
  virtual void load (CmdMediator &cmdMediator);

private slots:
  void slotDelimitersCommas();
  void slotDelimitersSpaces();
  void slotDelimitersTabs();
  void slotExclude();
  void slotFunctionsLayoutAllCurves();
  void slotFunctionsLayoutOneCurve();
  void slotFunctionsPointsAllCurves();
  void slotFunctionsPointsEvenlySpaced();
  void slotFunctionsPointsEvenlySpacedInterval(const QString  &);
  void slotFunctionsPointsEvenlySpacedIntervalUnits(const QString &);
  void slotFunctionsPointsFirstCurve();
  void slotFunctionsPointsRaw();
  void slotHeaderGnuplot();
  void slotHeaderNone();
  void slotHeaderSimple();
  void slotInclude();
  void slotListExcluded();
  void slotListIncluded();
  void slotRelationsPointsEvenlySpaced();
  void slotRelationsPointsEvenlySpacedInterval(const QString &);
  void slotRelationsPointsEvenlySpacedIntervalUnits(const QString &);
  void slotRelationsPointsRaw();
  void slotTabChanged (int);
  void slotXLabel (const QString &);

protected:
  virtual void handleOk ();

private:

  void createCurveSelection (QGridLayout *layout, int &row);
  void createDelimiters (QHBoxLayout *layoutMisc);
  void createFileLayout (QHBoxLayout *layoutMisc);
  void createFunctionsPointsSelection (QHBoxLayout *layout);
  void createHeader (QHBoxLayout *layoutMisc);
  void createPreview (QGridLayout *layout, int &row);
  void createRelationsPointsSelection (QHBoxLayout *layout);
  void createTabWidget (QGridLayout *layout,
                        int &row);
  void createXLabel (QGridLayout *layoutHeader,
                     int colLabel);
  bool goodIntervalFunctions() const;
  bool goodIntervalRelations() const;
  void updateControls();
  void updatePreview();

  QTabWidget *m_tabWidget;

  QListWidget *m_listIncluded;
  QListWidget *m_listExcluded;

  QPushButton *m_btnInclude;
  QPushButton *m_btnExclude;

  QRadioButton *m_btnFunctionsPointsAllCurves;
  QRadioButton *m_btnFunctionsPointsFirstCurve;
  QRadioButton *m_btnFunctionsPointsEvenlySpaced;
  QLineEdit *m_editFunctionsPointsEvenlySpacing;
  QDoubleValidator *m_validatorFunctionsPointsEvenlySpacing;
  QComboBox *m_cmbFunctionsPointsEvenlySpacingUnits;
  QRadioButton *m_btnFunctionsPointsRaw;

  QRadioButton *m_btnFunctionsLayoutAllCurves;
  QRadioButton *m_btnFunctionsLayoutOneCurve;

  QRadioButton *m_btnRelationsPointsEvenlySpaced;
  QLineEdit *m_editRelationsPointsEvenlySpacing;
  QDoubleValidator *m_validatorRelationsPointsEvenlySpacing;
  QComboBox *m_cmbRelationsPointsEvenlySpacingUnits;
  QRadioButton *m_btnRelationsPointsRaw;

  QRadioButton *m_btnDelimitersCommas;
  QRadioButton *m_btnDelimitersSpaces;
  QRadioButton *m_btnDelimitersTabs;

  QRadioButton *m_btnHeaderNone;
  QRadioButton *m_btnHeaderSimple;
  QRadioButton *m_btnHeaderGnuplot;

  QLineEdit *m_editXLabel;

  QTextEdit *m_editPreview;

  DocumentModelExport *m_modelExportBefore;
  DocumentModelExport *m_modelExportAfter;
};

#endif // DLG_SETTINGS_EXPORT_H
