#ifndef CHECKLIST_GUIDE_PAGE_CURVES_H
#define CHECKLIST_GUIDE_PAGE_CURVES_H

#include "ChecklistGuidePage.h"
#include <QStringList>

class QRadioButton;
class QTableWidget;
class QTableWidgetItem;

/// This class adds validation to the Curves page
class ChecklistGuidePageCurves : public ChecklistGuidePage
{
  Q_OBJECT;

 public:
  /// Single constructor
  ChecklistGuidePageCurves ();

  /// Wizard selection for curve names
  QStringList curveNames () const;

  /// Validate the contents of this page
  virtual bool isComplete () const;

  /// Wizard selection of lines versus points
  bool withLines () const;

 public slots:
  /// Update after curve table update
  void slotTableChanged (QTableWidgetItem *);

 private:

  QTableWidget *m_tableCurves;
  QRadioButton *m_btnLines;
  QRadioButton *m_btnPoints;

};

#endif // CHECKLIST_GUIDE_PAGE_CURVES_H
