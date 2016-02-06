#ifndef GHOSTS_H
#define GHOSTS_H

/// Class for showing points and lines for all coordinate systems simultaneously, even though
/// the code normally only allows graphical items for once coordinate system to be visible at a time
class Ghosts
{
 public:
  /// Single constructor
  Ghosts(unsigned int coordSystemIndexToBeRestored);
  ~Ghosts();

  /// Coordinate system index that was active before the ghosts
  unsigned int coordSystemIndexToBeRestored() const;

 private:
  Ghosts();

  unsigned int m_coordSystemIndexToBeRestored;
};

#endif // GHOSTS_H
