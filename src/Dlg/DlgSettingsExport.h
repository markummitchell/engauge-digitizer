#ifndef DLG_SETTINGS_EXPORT_H
#define DLG_SETTINGS_EXPORT_H

#include "DlgSettingsAbstractBase.h"

class QGridLayout;
class QHBoxLayout;
class QLineEdit;
class QLabel;
class QListWidget;
class QPushButton;
class QRadioButton;
class QTextEdit;
class QVBoxLayout;

/// Stacked widget page for editing exporting settings.
class DlgSettingsExport : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsExport(QWidget *parent = 0);

  virtual QWidget *createSubPanel ();
  virtual void load (CmdMediator &cmdMediator);

private slots:
  void slotDelimitersCommas(bool);
  void slotDelimitersSpaces(bool);
  void slotDelimitersTabs(bool);
  void slotExclude();
  void slotFunctionsLayoutAllCurves(bool);
  void slotFunctionsLayoutOneCurve(bool);
  void slotFunctionsPointsAllCurves(bool);
  void slotFunctionsPointsEvenlySpaced(bool);
  void slotFunctionsPointsEvenlySpacedInterval();
  void slotFunctionsPointsFirstCurve(bool);
  void slotFunctionsPointsRaw(bool);
  void slotHeaderGnuplot(bool);
  void slotHeaderNone(bool);
  void slotHeaderSimple(bool);
  void slotInclude();
  void slotListExcluded();
  void slotListIncluded();
  void slotRelationsPointsEvenlySpaced(bool);
  void slotRelationsPointsEvenlySpacedInterval();
  void slotRelationsPointsRaw(bool);
  void slotXLabel ();

protected:
  virtual void handleOk ();

private:

  void createCurveSelection (QGridLayout *layout, int &row);
  void createDelimiters (QHBoxLayout *layoutMisc);
  void createFunctionsLayout (QHBoxLayout *layout);
  void createFunctionsPointsSelection (QHBoxLayout *layout);
  void createHeader (QHBoxLayout *layoutMisc);
  void createPreview (QGridLayout *layout, int &row);
  void createRelationsPointsSelection (QHBoxLayout *layout);
  void createTabWidget (QGridLayout *layout,
                        QHBoxLayout *&layoutFunctions,
                        QHBoxLayout *&layoutRelations,
                        int &row);
  void createXLabel (QHBoxLayout *layoutMisc);
  void updateControls();

  QListWidget *m_listIncluded;
  QListWidget *m_listExcluded;

  QPushButton *m_btnInclude;
  QPushButton *m_btnExclude;

  QRadioButton *m_btnFunctionsPointsAllCurves;
  QRadioButton *m_btnFunctionsPointsFirstCurve;
  QRadioButton *m_btnFunctionsPointsEvenlySpaced;
  QLineEdit *m_editFunctionsPointsEvenlySpacing;
  QRadioButton *m_btnFunctionsPointsRaw;

  QRadioButton *m_btnFunctionsLayoutAllCurves;
  QRadioButton *m_btnFunctionsLayoutOneCurve;

  QRadioButton *m_btnRelationsPointsEvenlySpaced;
  QLineEdit *m_editRelationsPointsEvenlySpacing;
  QRadioButton *m_btnRelationsPointsRaw;

  QRadioButton *m_btnDelimitersCommas;
  QRadioButton *m_btnDelimitersSpaces;
  QRadioButton *m_btnDelimitersTabs;

  QRadioButton *m_btnHeaderNone;
  QRadioButton *m_btnHeaderSimple;
  QRadioButton *m_btnHeaderGnuplot;

  QLineEdit *m_editXLabel;

  QTextEdit *m_editPreview;
};

#endif // DLG_SETTINGS_EXPORT_H
