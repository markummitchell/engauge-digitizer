/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Logger.h"
#include "MainCreateNetwork.h"
#include "MainWindow.h"
#ifdef NETWORKING
#include "NetworkClient.h"
#endif

MainCreateNetwork::MainCreateNetwork()
{
}

void MainCreateNetwork::create(MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainCreateNetwork::create";
  
#ifdef NETWORKING
  mw.m_networkClient = new NetworkClient (&mw);
#endif
}
