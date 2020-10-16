#include "CWaveBuffer.h"

// std
#include <math.h>
static const double EMPTY_PERCENT = 0.1;
CWaveBuffer::CWaveBuffer(double interval, size_t numPoints, bool left):
  CircularBuffer(interval, numPoints),
  mLeft(left)
{}
// CWaveBuffer::CWaveBuffer( double interval, size_t numPoints ):
//   d_y( NULL ),
//   d_referenceTime( 0.0 ),
//   d_startIndex( 0 ),
//   d_offset( 0.0 )
// {
//     fill( interval, numPoints );
// }

// void CWaveBuffer::fill( double interval, size_t numPoints )
// {
//     if ( interval <= 0.0 || numPoints < 2 )
//         return;

//     d_values.resize( numPoints );
//     d_values.fill( 0.0 );

//     if ( d_y )
//     {
//         d_step = interval / ( numPoints - 1 );
//         for ( size_t i = 0; i < numPoints; i++ )
//             d_values[i] = d_y( i * d_step );
//     }

//     d_interval = interval;
// }

// void CWaveBuffer::setFunction( double( *y )( double ) )
// {
//     d_y = y;
// }

// void CWaveBuffer::setReferenceTime( double timeStamp )
// {
//     d_referenceTime = timeStamp;

//     const double startTime = ::fmod( d_referenceTime, d_values.size() * d_step );

//     d_startIndex = static_cast<int>(::floor( startTime / d_step )); // floor
//     d_offset = ::fmod( startTime, d_step );
// }

// double CWaveBuffer::referenceTime() const
// {
//     return d_referenceTime;
// }

size_t CWaveBuffer::size() const
{
  size_t size = 0;
  if (this->mLeft)
  {
    size = this->d_startIndex;
  }
  else
  {
    size = static_cast<int>(this->d_values.size() * ( 1 - EMPTY_PERCENT) - this->d_startIndex);
  }
  return size;
}

QPointF CWaveBuffer::sample( size_t i ) const
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
    x = (this->d_startIndex + this->d_values.size() * EMPTY_PERCENT + i) * d_step - d_interval;
    y = d_values.data()[
      static_cast<int>(this->d_startIndex + this->d_values.size() * EMPTY_PERCENT + i)
      ];
  }
  return QPointF(x, y);
}

// QRectF CWaveBuffer::boundingRect() const
// {
//     return QRectF( -1.0, -d_interval, 2.0, d_interval );
// }
