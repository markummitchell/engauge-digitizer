/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CreateScene.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QGridLayout>
#include <QPushButton>

CreateScene::CreateScene()
{
}

void CreateScene::create(MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CreateScene::create";

  const QString NO_TEXT (""); // Keep skinny by leaving out bulky text
  
  mw.m_scene = new GraphicsScene (&mw);
  mw.m_view = new GraphicsView (mw.m_scene, mw);

  QString statusTipR (tr ("Create an R (range) guideline."));
  QString statusTipT (tr ("Create a T (theta) guideline."));
  QString statusTipX (tr ("Create an X guideline."));
  QString statusTipY (tr ("Create a Y guideline."));  

  QString whatsThisR (tr ("Create an R (Range) guideline\n\n"
                          "When pressed, a constant R (range) guideline is created. It can be moved by dragging"));
  QString whatsThisT (tr ("Create a T (Theta) guideline\n\n"
                          "When pressed, a constant T (theta) guideline is created. It can be moved by dragging"));
  QString whatsThisX (tr ("Create an X guideline\n\n"
                          "When pressed, a constant X guideline is created. It can be moved by dragging"));
  QString whatsThisY (tr ("Create a Y guideline\n\n"
                          "When pressed, a constant Y guideline is created. It can be moved by dragging"));
  
  mw.m_btnGuidelineBottomCartesian = new QPushButton (QIcon(":/engauge/img/icon_guidelinesx.png"), "");
  mw.m_btnGuidelineBottomCartesian->setSizePolicy (QSizePolicy::Maximum, QSizePolicy::Maximum);
  mw.m_btnGuidelineBottomCartesian->setEnabled (true);
  mw.m_btnGuidelineBottomCartesian->setAcceptDrops (false);  
  mw.m_btnGuidelineBottomCartesian->setStatusTip (statusTipX);
  mw.m_btnGuidelineBottomCartesian->setWhatsThis (whatsThisX);
  connect (mw.m_btnGuidelineBottomCartesian, SIGNAL (pressed ()), &mw, SLOT (slotBtnGuidelineBottomCartesian ()));

  mw.m_btnGuidelineBottomPolar = new QPushButton (QIcon(":/engauge/img/icon_guidelinest.png"), "");
  mw.m_btnGuidelineBottomPolar->setSizePolicy (QSizePolicy::Maximum, QSizePolicy::Maximum);  
  mw.m_btnGuidelineBottomPolar->setEnabled (true);
  mw.m_btnGuidelineBottomPolar->setAcceptDrops (false);  
  mw.m_btnGuidelineBottomPolar->setStatusTip (statusTipT);
  mw.m_btnGuidelineBottomPolar->setWhatsThis (whatsThisT);
  connect (mw.m_btnGuidelineBottomPolar, SIGNAL (pressed ()), &mw, SLOT (slotBtnGuidelineBottomPolar ()));

  mw.m_btnGuidelineLeftCartesian = new QPushButton (QIcon(":/engauge/img/icon_guidelinesy.png"), "");
  mw.m_btnGuidelineLeftCartesian->setSizePolicy (QSizePolicy::Maximum, QSizePolicy::Maximum);    
  mw.m_btnGuidelineLeftCartesian->setEnabled (true);
  mw.m_btnGuidelineLeftCartesian->setAcceptDrops (false);  
  mw.m_btnGuidelineLeftCartesian->setStatusTip (statusTipY);
  mw.m_btnGuidelineLeftCartesian->setWhatsThis (whatsThisY);
  connect (mw.m_btnGuidelineLeftCartesian, SIGNAL (pressed ()), &mw, SLOT (slotBtnGuidelineLeftCartesian ()));

  mw.m_btnGuidelineLeftPolar = new QPushButton (QIcon(":/engauge/img/icon_guidelinesr.png"), "");
  mw.m_btnGuidelineLeftPolar->setSizePolicy (QSizePolicy::Maximum, QSizePolicy::Maximum);      
  mw.m_btnGuidelineLeftPolar->setEnabled (true);
  mw.m_btnGuidelineLeftPolar->setAcceptDrops (false);  
  mw.m_btnGuidelineLeftPolar->setStatusTip (statusTipR);
  mw.m_btnGuidelineLeftPolar->setWhatsThis (whatsThisR);
  connect (mw.m_btnGuidelineLeftPolar, SIGNAL (pressed ()), &mw, SLOT (slotBtnGuidelineLeftPolar ()));

  mw.m_btnGuidelineRightCartesian = new QPushButton (QIcon(":/engauge/img/icon_guidelinesy.png"), "");
  mw.m_btnGuidelineRightCartesian->setSizePolicy (QSizePolicy::Maximum, QSizePolicy::Maximum);          
  mw.m_btnGuidelineRightCartesian->setEnabled (true);
  mw.m_btnGuidelineRightCartesian->setAcceptDrops (false);  
  mw.m_btnGuidelineRightCartesian->setStatusTip (statusTipY);
  mw.m_btnGuidelineRightCartesian->setWhatsThis (whatsThisY);
  connect (mw.m_btnGuidelineRightCartesian, SIGNAL (pressed ()), &mw, SLOT (slotBtnGuidelineRightCartesian ()));

  mw.m_btnGuidelineRightPolar = new QPushButton (QIcon(":/engauge/img/icon_guidelinesr.png"), "");
  mw.m_btnGuidelineRightPolar->setSizePolicy (QSizePolicy::Maximum, QSizePolicy::Maximum);        
  mw.m_btnGuidelineRightPolar->setEnabled (true);
  mw.m_btnGuidelineRightPolar->setAcceptDrops (false);  
  mw.m_btnGuidelineRightPolar->setStatusTip (statusTipR);
  mw.m_btnGuidelineRightPolar->setWhatsThis (whatsThisR);
  connect (mw.m_btnGuidelineRightPolar, SIGNAL (pressed ()), &mw, SLOT (slotBtnGuidelineRightPolar ()));

  mw.m_btnGuidelineTopCartesian = new QPushButton (QIcon(":/engauge/img/icon_guidelinesx.png"), "");
  mw.m_btnGuidelineTopCartesian->setSizePolicy (QSizePolicy::Maximum, QSizePolicy::Maximum);            
  mw.m_btnGuidelineTopCartesian->setEnabled (true);
  mw.m_btnGuidelineTopCartesian->setAcceptDrops (false);  
  mw.m_btnGuidelineTopCartesian->setStatusTip (statusTipX);
  mw.m_btnGuidelineTopCartesian->setWhatsThis (whatsThisX);
  connect (mw.m_btnGuidelineTopCartesian, SIGNAL (pressed ()), &mw, SLOT (slotBtnGuidelineTopCartesian ()));

  mw.m_btnGuidelineTopPolar = new QPushButton (QIcon(":/engauge/img/icon_guidelinest.png"), "");
  mw.m_btnGuidelineTopPolar->setSizePolicy (QSizePolicy::Maximum, QSizePolicy::Maximum);        
  mw.m_btnGuidelineTopPolar->setEnabled (true);
  mw.m_btnGuidelineTopPolar->setAcceptDrops (false);  
  mw.m_btnGuidelineTopPolar->setStatusTip (statusTipT);
  mw.m_btnGuidelineTopPolar->setWhatsThis (whatsThisT);
  connect (mw.m_btnGuidelineTopPolar, SIGNAL (pressed ()), &mw, SLOT (slotBtnGuidelineTopPolar ()));        

  int row = 0;

  // On each of the four sides there are two rows or columns that are mutually exclusive
  mw.m_layout->addWidget (mw.m_btnGuidelineTopCartesian, row++, 2, Qt::AlignHCenter);
  mw.m_layout->addWidget (mw.m_btnGuidelineTopPolar, row++, 2, Qt::AlignHCenter);
  mw.m_layout->addWidget (mw.m_btnGuidelineLeftCartesian, row, 0, Qt::AlignVCenter);
  mw.m_layout->addWidget (mw.m_btnGuidelineLeftPolar, row, 1, Qt::AlignVCenter);  
  mw.m_layout->addWidget (mw.m_view, row, 2);
  mw.m_layout->addWidget (mw.m_btnGuidelineRightCartesian, row, 3, Qt::AlignVCenter);
  mw.m_layout->addWidget (mw.m_btnGuidelineRightPolar, row++, 4, Qt::AlignVCenter);
  mw.m_layout->addWidget (mw.m_btnGuidelineBottomCartesian, row++, 2, Qt::AlignHCenter);
  mw.m_layout->addWidget (mw.m_btnGuidelineBottomPolar, row++, 2, Qt::AlignHCenter);  
}

