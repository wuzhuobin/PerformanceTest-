#ifndef C_WAVE_BUFFER_H
#define C_WAVE_BUFFER_H

#include "circularbuffer.h"

class CWaveBuffer : public CircularBuffer
{

public:
  CWaveBuffer(double interval = 10.0, size_t numPoints = 1000, bool left = true);

  virtual size_t size() const override;
  virtual QPointF sample(size_t i) const override;

protected:
  bool mLeft;
};

#endif //!C_WAVE_BUFFER_H
