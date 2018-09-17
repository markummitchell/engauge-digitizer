/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackDocumentScrub.h"
#include "CallbackSearchReturn.h"
#include "Document.h"
#include "DocumentScrub.h"
#include "Logger.h"
#include "MainWindow.h"
#include "Point.h"
#include <QMessageBox>
#include "Version.h"

DocumentScrub::DocumentScrub ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentScrub::DocumentScrub";
}

void DocumentScrub::check (MainWindow &mainWindow,
                           const Document &document) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentScrub::check";

  CallbackDocumentScrub ftor;

  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackDocumentScrub::callback);
  
  document.iterateThroughCurvePointsAxes (ftorWithCallback);
  document.iterateThroughCurvesPointsGraphs (ftorWithCallback);

  if (!ftor.success ()) {

    QMessageBox::critical (&mainWindow,
                           engaugeWindowTitle (),
                           QString ("%1: %2")
                           .arg (QObject::tr ("Point identifier error encountered. Please notify the Engauge "
                                              "developers along with any comments about the country and language locale. "
                                              "The invalid point name was"))
                           .arg (ftor.badPointName ().replace (POINT_IDENTIFIER_DELIMITER_SAFE, "<tab>")));
    exit (-1);
  }
}
