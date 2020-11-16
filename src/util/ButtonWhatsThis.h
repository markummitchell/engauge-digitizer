/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef BUTTON_WHATS_THIS_H
#define BUTTON_WHATS_THIS_H

#include <QPushButton>

/// Unobtrusive button to trigger QWhatsThis since some operating systems (Linux Mint) do not show
/// WhatsThis button in title bar. A complication is that the size must be minimized explicitly to
/// remove a large amount of padding, but in a manner that reliably works with various system font sizes
class ButtonWhatsThis : public QPushButton
{
public:
  /// Single constructor.
  ButtonWhatsThis(QWidget *parent = 0);

};

#endif // BUTTON_WHATS_THIS_H
