#include "CPlot3Buffer.h"


static const double EMPTY_PERCENT = 0.1;
static const double EXTENDED_WAVE = 0.005;
CPlot3Buffer::CPlot3Buffer(double interval, size_t numPoints):
  CircularBuffer(interval, numPoints)
{}

void CPlot3Buffer::setReferenceTime(double time)
{
  this->mOldStartIndex = this->d_startIndex;
  CircularBuffer::setReferenceTime(time);
}

size_t CPlot3Buffer::size() const
{
  size_t size_ = this->d_startIndex - this->mOldStartIndex;
  size_ = size_ > 0 ? size_ : this->d_startIndex - this->mOldStartIndex + this->d_interval;
  size_ = size_ > 1 ? size_ : 1;
  size_ += this->d_values.size() * EXTENDED_WAVE * 2;
  return size_;
}

QPointF CPlot3Buffer::sample(size_t i) const
{
  const int size = d_values.size();

  int index = this->d_startIndex + i - this->d_values.size() * EXTENDED_WAVE;
  if (index >= size)
  {
    index -= size;
  }
  const double x = (i + this->d_startIndex - this->d_values.size() * EXTENDED_WAVE) * this->d_step - d_interval;
  const double y = this->d_values.data()[index];
  // if (i == 0)
  // {
  //   qDebug() << (x + this->d_interval ) * 106.5;
  // }
  return QPointF(x, y);
}

QRectF CPlot3Buffer::boundingRect() const
{
  return qwtBoundingRect(*this);
}