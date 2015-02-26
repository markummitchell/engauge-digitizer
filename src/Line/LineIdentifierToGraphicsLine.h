#ifndef LINE_IDENTIFIER_TO_GRAPHICS_LINE_H
#define LINE_IDENTIFIER_TO_GRAPHICS_LINE_H

#include <QHash>
#include <QString>

class GraphicsLine;

typedef QHash<QString, GraphicsLine*> LineIdentifierToGraphicsLine;

#endif // LINE_IDENTIFIER_TO_GRAPHICS_LINE_H
