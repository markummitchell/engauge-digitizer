#ifndef CHECKLIST_GUIDE_PAGE_CURVES_H
#define CHECKLIST_GUIDE_PAGE_CURVES_H

#include "ChecklistGuidePage.h"
#include <QStringList>

class ChecklistLineEdit;
class QRadioButton;

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

 public slots:
  /// Update after curve table update
  void slotTableChanged ();

  /// Drawn with lines, else points
  bool withLines() const;

 private:

  bool curveNamesAreAllUnique() const;
  int NUM_CURVE_NAMES () const { return 6; }

  ChecklistLineEdit **m_edit; // Vector array of editors
  QRadioButton *m_btnLines;
  QRadioButton *m_btnPoints;

};

#endif // CHECKLIST_GUIDE_PAGE_CURVES_H
