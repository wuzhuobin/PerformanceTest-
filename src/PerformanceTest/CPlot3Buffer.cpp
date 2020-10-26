#include "CPlot3Buffer.h"


static const double EMPTY_PERCENT = 0.1;
CPlot3Buffer::CPlot3Buffer(double interval, size_t numPoints):
  CircularBuffer(interval, numPoints)
{}

size_t CPlot3Buffer::size() const
{
  return 10;
}

QPointF CPlot3Buffer::sample(size_t i) const
{
  const int size = d_values.size();

  int index = d_startIndex + i;
  if (index >= size)
  {
    index -= size;
  }
  const double x = (i + this->d_startIndex) * this->d_step - d_interval;
  const double y = this->d_values.data()[index];
  return QPointF(x, y);

}