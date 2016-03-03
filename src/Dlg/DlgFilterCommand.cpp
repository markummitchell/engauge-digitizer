#include "DlgFilterCommand.h"

DlgFilterCommand::DlgFilterCommand(ColorFilterMode colorFilterMode,
                                   double low0To1, double high0To1)
    : m_colorFilterMode(colorFilterMode), m_low0To1(low0To1),
      m_high0To1(high0To1) {}

DlgFilterCommand::DlgFilterCommand(const DlgFilterCommand &other)
    : m_colorFilterMode(other.colorFilterMode()), m_low0To1(other.low0To1()),
      m_high0To1(other.high0To1()) {}

DlgFilterCommand &DlgFilterCommand::operator=(const DlgFilterCommand &other) {
  m_colorFilterMode = other.colorFilterMode();
  m_low0To1 = other.low0To1();
  m_high0To1 = other.high0To1();

  return *this;
}

ColorFilterMode DlgFilterCommand::colorFilterMode() const {
  return m_colorFilterMode;
}

double DlgFilterCommand::high0To1() const { return m_high0To1; }

double DlgFilterCommand::low0To1() const { return m_low0To1; }
