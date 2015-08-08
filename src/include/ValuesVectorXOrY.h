#ifndef VALUES_VECTOR_X_OR_Y_H
#define VALUES_VECTOR_X_OR_Y_H

#include <QMap>

// Save values into container that preserves order by key (QMap). These are common to all included curves
// QMap is for fast random access
typedef QMap<double, bool> ValuesVectorXOrY;

#endif // VALUES_VECTOR_X_OR_Y_H
