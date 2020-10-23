#ifndef C_PLOT2_BUFFER_H
#define C_PLOT2_BUFFER_H

#include "circularbuffer.h"

class CPlo2Buffer : public CircularBuffer
{

public:
  explicit CPlo2Buffer(double interval = 10.0, size_t numPoints = 1000, bool left = true);

  virtual size_t size() const override;
  virtual QPointF sample(size_t i) const override;

protected:
  bool mLeft;
};

#endif //!C_PLOT2_BUFFER_H
