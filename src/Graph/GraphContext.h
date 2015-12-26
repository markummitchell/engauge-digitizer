#ifndef GRAPH_CONTEXT_H
#define GRAPH_CONTEXT_H

class Graph;

/// This class plays the role of context class in a state machine, although the 'states' are actually different
/// instantiations of the Graph class. At any point in time, one Graph is active (as selected by the user)
class GraphContext
{
 public:
  /// Single constructor
  GraphContext();

 private:
};

#endif // GRAPH_CONTEXT_H
