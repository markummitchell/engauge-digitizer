#ifndef DLG_MODEL_EXPORT_H
#define DLG_MODEL_EXPORT_H

class CmdMediator;

/// Model for DlgSettingsExport and CmdSettingsExport.
class DlgModelExport
{
public:
  /// Default constructor.
  DlgModelExport();

  /// Initial constructor from Document.
  DlgModelExport(const CmdMediator &cmdMediator);

  /// Copy constructor.
  DlgModelExport(const DlgModelExport &other);

  /// Assignment constructor.
  DlgModelExport &operator=(const DlgModelExport &other);

private:

};

#endif // DLG_MODEL_EXPORT_H
