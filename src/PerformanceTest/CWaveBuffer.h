#ifndef C_WAVE_BUFFER_H
#define C_WAVE_BUFFER_H

#include "circularbuffer.h"

class CWaveBuffer : public CircularBuffer
{

public:
  CWaveBuffer(double interval = 10.0, size_t numPoints = 1000, bool left = true);
  // void fill(double interval, size_t numPoints);

  // void setReferenceTime(double);
  // double referenceTime() const;

  virtual size_t size() const override;
  virtual QPointF sample(size_t i) const override;

  // virtual QRectF boundingRect() const override;

  // void setFunction(double (*y)(double));

protected:
  bool mLeft;
// private:
//   double (*d_y)(double);

//   double d_referenceTime;
//   double d_interval;
//   QVector<double> d_values;

//   double d_step;
//   int d_startIndex;
//   double d_offset;
};

#endif //!C_WAVE_BUFFER_H
