#ifndef MAIN_WINDOW_MODEL_H
#define MAIN_WINDOW_MODEL_H

#include "DocumentModelAbstractBase.h"
#include <QString>
#include "ZoomControl.h"

class QTextStream;

/// Model for DlgSettingsMainWindow and CmdSettingsMainWindow. Unlike the other models (DocumentModel*) this
/// data is not saved and loaded within the document, so no xml or working with the Document class is involved. Instead,
/// the settings are saved using QSettings. Method involving xml/Document (from DocumentModelAbstractBase) are stubbed out
class MainWindowModel : public DocumentModelAbstractBase
{
public:
  /// Default constructor.
  MainWindowModel();

  /// Copy constructor.
  MainWindowModel(const MainWindowModel &other);

  /// Assignment constructor.
  MainWindowModel &operator=(const MainWindowModel &other);

  virtual void loadXml(QXmlStreamReader &reader);

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  virtual void saveXml(QXmlStreamWriter &writer) const;

  /// Set method for zoom control
  void setZoomControl (ZoomControl zoomControl);

  /// Get method for zoom control
  ZoomControl zoomControl () const;

private:

  ZoomControl m_zoomControl;
};

#endif // MAIN_WINDOW_MODEL_H
