#include "CWaveBuffer.h"

// std
#include <math.h>
static const double EMPTY_PERCENT = 0.1;
CWaveBuffer::CWaveBuffer(double interval, size_t numPoints, bool left):
  CircularBuffer(interval, numPoints),
  mLeft(left)
{}

size_t CWaveBuffer::size() const
{
  /// @todo NOT CORRECT
  size_t size = 0;
  if (this->mLeft)
  {
    size = this->d_startIndex;
  }
  else
  {
    int size_ = static_cast<int>(this->d_values.size() * ( 1 - EMPTY_PERCENT) - this->d_startIndex);
    size = size_ < 0 ? 0 : size_;
  }
  return size;
}

QPointF CWaveBuffer::sample( size_t i ) const
{
  /// @todo NOT CORRECT
  double x;
  double y;
  if (this->mLeft)
  {
    x = i * d_step - d_interval;
    y = d_values.data()[i];
  }
  else
  {
    x = (this->d_startIndex + this->d_values.size() * EMPTY_PERCENT + i) * d_step - d_interval;
    y = d_values.data()[
      static_cast<int>(this->d_startIndex + this->d_values.size() * EMPTY_PERCENT + i)
      ];
  }
  return QPointF(x, y);
}
