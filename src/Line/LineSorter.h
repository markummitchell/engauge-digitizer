#ifndef LINE_SORTER_H
#define LINE_SORTER_H

/// Sort points in a curve line according to the independent variable if connected as a function, by updating
/// the ordinals correspondingly. This class is a noop if curve is connected as a relation since the ordinals
/// are already sorted elsewhere
class LineSorter
{
public:
  /// Single constructor
  LineSorter();
};

#endif // LINE_SORTER_H
