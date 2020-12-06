/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CENTIPEDE_PAIR_H
#define CENTIPEDE_PAIR_H

#include "CentipedeStateContext.h"
#include "DocumentModelGuideline.h"
#include <QPointF>

class CentipedeSegmentAbstract;
class CmdMediator;
class DocumentModelCoords;
class GraphicsScene;
class Transformation;

/// Show two Centipede graphics items that the user interacts with by moving the cursor. This unique approach
/// was chosen over conventional approaches for the following reasons:
/// - Does not require a hard-to-find button to toggle between X/T and Y/R guideline options
/// - Does not require two system states, with one state for creating X/T guidelines and another state for creating
///   Y/R guidelines
/// - Keeps focus on the screen region where the user clicked
/// - Does not require user to click on one of the two guideline options, which the user may not know to do,
///   or the user may accidentally miss the desired guideline when clicking which cause confusion. In some cases
///   trying to click on the narrow desired guideline may even be difficult
/// - This solution is conceptually simple "just move the cursor in the direction you want"
/// - This solution is fun
///
/// Two Centipedes are always shown. Initially they are in the form of two orthogonal line segments (straight
/// for cartesian and constant-theta polar cases, and curved for constant-radius polar case). Shown below are
/// the notional explanation in the first column (with the Centipede objects keeping constant lengths) and the
/// implemented solution in the second column (with the Centipede objects changing lengths). The implemented solution
/// uses two GraphicsItem subclasses, which is less complicateed than implementing the notional explanation
/// with four graphics items (one for each quadrant).
///
///       Notional Explanation          Implemented Solution
///                1                            1
///                1                            1
///                1                            1
///           2 2 2 1 1 1                  2 2 2 2 2 2
///                2                            1
///                2                            1
///                2                            1
///
/// As the cursor is moved, the Centipedes crawl the same amount correspondingly. As an example, if the cursor is
/// moved from the center to the right (within -45 to +45 degrees so the +x axis is closest to the cursor) then
/// the Guidelines move as
///
///       Notional Explanation          Implemented Solution
///                1                            1
///                1                            1
///         2 2 2 2 1 1 1 1              2 2 2 2 2 2 2 2
///                2                            1
///                2                            1
///
/// When the Centipede tails disappear the user's direction preference is noted and Centipede dragging ends.
///
///       Notional Explanation          Implemented Solution
///     2 2 2 2 2 2 1 1 1 1 1 1      2 2 2 2 2 2 2 2 2 2 2 2
///
/// [At least one blank comment line is required after the final indented section so it is recognized as a
/// code snippet like the code snippets before it]
class CentipedePair
{
public:
  /// Constructor with individual coordinates
  CentipedePair(CmdMediator &cmdMediator,
                GraphicsScene &scene,
                const Transformation &transformation,
                const DocumentModelGuideline &modelGuideline,
                const DocumentModelCoords &modelCoords,
                const QPointF &posScreen);
  virtual ~CentipedePair();

  /// True if cursor has moved far enough that the CentipedePair has finished and should be removed
  bool done (const QPointF &posScreen);

  /// Handle key press event
  void handleKeyPress (CmdMediator &cmdMediator,
                       Qt::Key key,
                       bool atLeastOneSelectedItem);

  /// Handle mouse move event
  void handleMouseMove (CmdMediator *cmdMediator,
                        QPointF posScreen);
  
  /// Handle mouse press event
  void handleMousePress (CmdMediator *cmdMediator,
                         QPointF posScreen);

  /// Handle mouse release event
  void handleMouseRelease (CmdMediator *cmdMediator,
                           QPointF posScreen);
  
  /// Follow cursor move
  void move (const QPointF &posScreen);  

  /// True if XT is final selection, otherwise false if YR is final selection
  bool selectedXTFinal () const;

  /// Final XT or YT (depending on selectedXTFinal) value
  double valueFinal () const;

private:
  CentipedePair();

  /// Updates final values. Also returns updated m_selectedXTFinal for convenience
  bool updateFinalValues (const QPointF &posScreen);

  DocumentModelGuideline m_modelGuideline;
  CentipedeSegmentAbstract *m_centipedeXT;
  CentipedeSegmentAbstract *m_centipedeYR;
  QPointF m_posScreenStart;
  QPointF m_posGraphStart;

  // Final values
  bool m_selectedXTFinal;
  double m_valueFinal;

  // State machine
  CentipedeStateContext m_context;
};

#endif // CENTIPEDE_PAIR_H
