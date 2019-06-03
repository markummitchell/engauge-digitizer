

Windows Installation Options
----------------------------
Option 1) Windows release WITH INSTALLER (digit-exe-windows-32-bit-installer-X_Y.msi): 
          The Windows MSI installer included in this release has been tested in Windows XP and Windows 8, and in 32 and 64
          bit operating systems. This installer is recommended when installing in a user account with administrative rights,
          since it creates helpful shortcuts and can be managed through the Control Panel.

Option 2) Windows release WITHOUT INSTALLER (digit-exe-windows-32-bit-without-installer-X_Y.msi): 
          The Windows ZIP file included in this release has been tested in Windows XP and Windows 7, with 32 and 64
          bit operating systems. After unzipping the files into a directory, clicking on the engauge.exe executable file 
          runs Engauge Digitizer. Installing from this zip file is the only option when working in a user account without
          administrative rights (since the MSI installer cannot be used).

Option 3) Cygwin release for Windows using the cygwin installer:
          Install cygwin from https://cygwin.com/install.html, with the engauge-digitizer package selected.
	  
Option 4) Engauge can be built from source code. This requires a lot of effort and is not recommended.


Windows Issues
--------------
          |-----------------------------------------------------------------------------------------------------------------|
          |                                              Known Windows Issues                                               |
          |-----------------------------------------------------------------------------------------------------------------|
          |Error Message:   'The program was unable to start correctly (0xc0150002). Click OK to close the application'     |
          |Description:     The Microsoft Visual C++ 2005 Service Pack 1 Redistributable Package MFC Security Update        |
          |                 should probably be installed.                                                                   |
          |Solution:        The steps to install the Service Pack package on Windows are:                                   |
          |                     >https://www.microsoft.com/en-us/download/details.aspx?id=26347                             |
          |                     >download the x86 version even when the current operating system is 64 bit                  |
          |                     >run the installer                                                                          |
          |-----------------------------------------------------------------------------------------------------------------|

Mac OSX Installation Options
----------------------------
Option 1) Download Engauge Digitizer from the Apple App Store. This option involves familiar steps that rarely have
          problems with security software such as Gatekeeper.

Option 2) Engauge can be built from source code. This requires a lot of time and effort and is not recommended.


Linux Distributions Installation Options
----------------------------------------
Option 1) Many Linux distributions already offer Engauge Digitizer as packages. For these distributions, Engauge Digitizer
          can be installed by using the distribution's package manager (yum, apt-get, ...).

Option 2) The AppImage release file can be downloaded and executed on all 32 and 64 bit Linux distributions. No installation
          step is required before executing the AppImage. Some known issues with this approach are listed below.

Option 3) The Flathub project is working on an installation system that can target all Linux distributions. The flatpak
          package must be installed, and then the Flatpak release of Engauge Digitizer can be installed. 

Linux Distribution Issues
-------------------------
          |----------------------------------------------------------------------------------------------------------------|
          |                                             Known Linux Issues                                                 |
          |----------------------------------------------------------------------------------------------------------------|
	  |Error Indication:          './engauge: No such file or directory'                                               |
	  |Description:               The operating system is configured to support only 64 bit applications               |
	  |Solution (Ubuntu/Kubuntu): Install libraries to support 32 bit applications                                     |
	  |                             >sudo dpkg --add-architecture i386                                                 |
	  |                             >sudo apt-get update                                                               |
	  |                             >sudo apt-get install libc6:i386 libncurses5:i386 libstdc++6:i386                  |
          |----------------------------------------------------------------------------------------------------------------|
          |Error Indication:          'Fuse is not installed'                                                              |
          |Description:               The fuse package must be installed                                                   |
          |Solution (Ubuntu/Kubuntu): The commands to install the fuse package on Ubuntu/Kubuntu are:                      |
          |                             >sudo apt-get install fuse                                                         |
          |                             >sudo modprobe fuse                                                                |
          |                             >sudo usermod -a -G fuse $USER                                                     |
          |                             (log out and log back in so your account is immediately able to use fuse)          |
          |Solution (openSUSE):       The command to install the fuse package on openSUSE is:                              |
          |                             >sudo zypper install fuse                                                          |
          |----------------------------------------------------------------------------------------------------------------|
	  |Error Indication:          'qt.network.ssl: Incompatible version of OpenSSL'                                    |
	  |Description:               An compatible version of libssl-dev is installed (e.g. 1.1.0 versus 1.0.2)           |
	  |Solution (Ubuntu/Kubuntu)  Try a different version of the libssl-dev package                                    |
          |----------------------------------------------------------------------------------------------------------------|
          |Error Indication:          'D-Bus library appears to be incorrectly set up; failed to read machine uuid'        |
          |Description:               D-Bus is has not been configured yet                                                 |
          |Solution (Fedora):         The commands to configure D-Bus are:                                                 |
          |                             >sudo su                                                                           |
          |                             >dbus-uuidgen >/var/lib/dbus/machine-id                                            |
          |----------------------------------------------------------------------------------------------------------------|
          |Error Indication:          'QCommon::drawComplexControl: Control 1 not handled'                                 |
          |Description:               Qt does not support the GTK style in the AppImage build                              |
	  |Solution (Fedora):         Execute the AppImage with a different style specified                                |
	  |                             >./digit-exe-universal-linux-#-bit-without-installer_#_#.AppImage -style=plastique |
          |----------------------------------------------------------------------------------------------------------------|
          |Error Indication:          Crash after selecting File / Import or File / Open                                   |
          |Description:               Fedora 25 (Wayland) requires the qgnomeplatform package for file dialogs to appear   |
	  |Solution (Fedora):         Install the qgnomeplatform package using                                             |
	  |                             >sudo dnf install qgnomeplatform                                                   |
          |----------------------------------------------------------------------------------------------------------------|	  
	  
Option 3) The Debian installer (digit-exe-debian-linux-32-bit-installer-X_Y.run) is released for installing into Debian systems. 
          The Debian installer included in this release has been tested in 32 and 64 bit Kubuntu and Knoppix.

Option 4) Engauge can be built from source code. This requires a lot of effort and is not recommended.
