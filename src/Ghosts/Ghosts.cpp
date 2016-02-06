#include "Ghosts.h"

Ghosts::Ghosts (unsigned int coordSystemIndexToBeRestored) :
  m_coordSystemIndexToBeRestored (coordSystemIndexToBeRestored)
{
}

Ghosts::~Ghosts ()
{
}

unsigned int Ghosts::coordSystemIndexToBeRestored () const
{
  return m_coordSystemIndexToBeRestored;
}
