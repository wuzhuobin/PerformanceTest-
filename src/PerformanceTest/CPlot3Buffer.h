#ifndef C_PLOT3_BUFFER_H
#define C_PLOT3_BUFFER_H

#include "circularbuffer.h"

class CPlot3Buffer: public CircularBuffer
{
public:
  explicit CPlot3Buffer(double interval = 10.0, size_t numPoints = 1000);
  virtual void setReferenceTime(double time) override;
  virtual size_t size() const override;
  virtual QPointF sample(size_t i) const override;
  virtual QRectF boundingRect() const override;
protected:
  int mOldStartIndex = 0;
};


#endif //!C_PLOT3_BUFFER_H