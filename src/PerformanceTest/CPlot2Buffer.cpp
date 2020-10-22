#include "CPlot2Buffer.h"

// std
#include <math.h>
static const double EMPTY_PERCENT = 0.1;
CPlo2Buffer::CPlo2Buffer(double interval, size_t numPoints, bool left):
  CircularBuffer(interval, numPoints),
  mLeft(left)
{}

size_t CPlo2Buffer::size() const
{
  size_t size = 0;
  if (this->mLeft)
  {
    size = this->d_startIndex <= this->d_values.size() * (1 - EMPTY_PERCENT) ? this->d_startIndex : 0;
  }
  else
  {
    int size_ = this->d_values.size() * ( 1 - EMPTY_PERCENT);
    size = this->d_startIndex > size_ ? size_ : size_ - this->d_startIndex;
  }
  return size;
}

QPointF CPlo2Buffer::sample( size_t i ) const
{
  double x;
  double y;
  if (this->mLeft)
  {
    x = i * d_step - d_interval;
    y = d_values.data()[i];
  }
  else
  {
    int index = this->d_startIndex - this->d_values.size() * (1 - EMPTY_PERCENT);
    index = index > 0 ? index : this->d_startIndex + this->d_values.size() * EMPTY_PERCENT;
    x = (index + i) * d_step - d_interval;
    y = d_values.data()[static_cast<int>(index + i)];
  }
  return QPointF(x, y);
}
