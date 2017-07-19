/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_SETTINGS_EXPORT_FORMAT_H
#define DLG_SETTINGS_EXPORT_FORMAT_H

#include "DlgSettingsAbstractBase.h"

class DocumentModelExportFormat;
class QCheckBox;
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

/// Dialog for editing exporting settings.
class DlgSettingsExportFormat : public DlgSettingsAbstractBase
{
  Q_OBJECT;

public:
  /// Single constructor.
  DlgSettingsExportFormat(MainWindow &mainWindow);
  virtual ~DlgSettingsExportFormat();

  virtual void createOptionalSaveDefault (QHBoxLayout *layout);
  virtual QWidget *createSubPanel ();
  virtual void load (CmdMediator &cmdMediator);
  virtual void setSmallDialogs (bool smallDialogs);

private slots:
  void slotDelimitersCommas();
  void slotDelimitersSemicolons();
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
  void slotOverrideCsvTsv(int);
  void slotRelationsPointsEvenlySpaced();
  void slotRelationsPointsEvenlySpacedInterval(const QString &);
  void slotRelationsPointsEvenlySpacedIntervalUnits(const QString &);
  void slotRelationsPointsRaw();
  void slotSaveDefault();
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
  QString exportedTextToExportedHtml (const QString &text,
                                      const QString &color) const;
  bool goodIntervalFunctions() const;
  bool goodIntervalRelations() const;
  void initializeIntervalConstraints ();
  void updateControls();
  void updateControlsUponLoad();
  void updateIntervalConstraints(); // Update constraints on intervals to prevent overflows downstream (especially when value is temporarily 0)
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

  QRadioButton *m_btnCurvesLayoutAllCurves;
  QRadioButton *m_btnCurvesLayoutOneCurve;

  QRadioButton *m_btnRelationsPointsEvenlySpaced;
  QLineEdit *m_editRelationsPointsEvenlySpacing;
  QDoubleValidator *m_validatorRelationsPointsEvenlySpacing;
  QComboBox *m_cmbRelationsPointsEvenlySpacingUnits;
  QRadioButton *m_btnRelationsPointsRaw;

  QRadioButton *m_btnDelimitersCommas;
  QRadioButton *m_btnDelimitersSemicolons;
  QRadioButton *m_btnDelimitersSpaces;
  QRadioButton *m_btnDelimitersTabs;
  QCheckBox *m_chkOverrideCsvTsv;

  QRadioButton *m_btnHeaderNone;
  QRadioButton *m_btnHeaderSimple;
  QRadioButton *m_btnHeaderGnuplot;

  QLineEdit *m_editXLabel;

  QTextEdit *m_editPreview;

  QPushButton *m_btnSaveDefault;

  DocumentModelExportFormat *m_modelExportBefore;
  DocumentModelExportFormat *m_modelExportAfter;

  // Safe values are computed for intervals and then applied according to the current settings. This prevents
  // accidentally generating exports with thousands of points. That causes delays and can even overflow resources
  // with a resulting crash
  double m_minIntervalGraph;
  double m_minIntervalScreen;

  bool m_haveFunction;
  bool m_haveRelation;
};

#endif // DLG_SETTINGS_EXPORT_FORMAT_H
