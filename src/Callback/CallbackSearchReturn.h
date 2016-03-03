/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

/**
 * \file CallbackSearchReturn.h
 * \brief
 * \copyright Copyright (c) 2012 Mark Mitchell. All rights reserved. Distribution requires prior written permission.
 */

#ifndef CALLBACK_SEARCH_RETURN_H
#define CALLBACK_SEARCH_RETURN_H

/**
 * \brief Return values for search callback methods. This lets each task-specific callback method control the generic search algorithm.
 *
 * Interrupting a search is useful when searching for the first node that meets some criteria that the callback method applies.
 *
 * Not recursing into a node's children is useful when trying to collect a list of subtrees, and the root node for each. This is
 * useful for TransformRecognizerManualBaseExponentExponent.
 */
enum CallbackSearchReturn {
  CALLBACK_SEARCH_RETURN_CONTINUE,  ///< Continue normal execution of the search
  CALLBACK_SEARCH_RETURN_INTERRUPT, ///< Immediately terminate the current search
  CALLBACK_SEARCH_RETURN_NO_RECURSE ///< Do not recurse into the current node's children, but continue current search
};

#endif // CALLBACK_SEARCH_RETURN_H
