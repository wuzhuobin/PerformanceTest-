#include "CPlot3.h"
#include "CPlot3Buffer.h"

// qt
#include <QPaintEvent>
#include <QApplication>

// qwt
#include <qwt_plot_grid.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_directpainter.h>

class CPlot3Data
{
public:
  typedef double(*Function)(double);
  explicit CPlot3Data(double interval = 10.0, size_t numPoints = 1000)
  {
    this->fill(interval, numPoints);
  }

  void fill(double interval, size_t numPoints)
  {
    if ( interval <= 0.0 || numPoints < 2 )
        return;

    this->mValues.resize( numPoints );
    this->mValues.fill( 0.0 );

    if ( this->mfpY )
    {
        this->mStep = interval / ( numPoints - 1 );
        for ( size_t i = 0; i < numPoints; i++ )
        {
            this->mValues[i] = this->mfpY( i * this->mStep );
        }
    }

    this->mInterval = interval;
  }

  void setFunction(Function fpY)
  {
    this->mfpY = fpY;
  }

  void setReferenceTime(double timeStamp)
  {
    this->mReferenceTime = timeStamp;

    const double startTime = ::fmod( this->mReferenceTime, this->mValues.size() * this->mStep );

    this->mStartIndex = int( startTime / this->mStep ); // floor
    this->mOffset = ::fmod( startTime, this->mStep );
  }

  size_t GetSize() const
  {
    return this->mValues.size();
  }


private:
  double mReferenceTime = 0.0;
  double mInterval = 0.0;
  QVector<double> mValues;
  double mStep;
  int mStartIndex = 0;
  double mOffset = 0.0;
  Function mfpY = nullptr;
};

class CPlot3Canvas: public QFrame
{
  Q_OBJECT;
public:
  explicit CPlot3Canvas(QWidget *pParent = nullptr): QFrame(pParent) {}
  CPlot3Data *GetData() { return &this->mData; }
  Q_INVOKABLE void replot()
  {
    this->update();
  }

protected:
  virtual void paintEvent(QPaintEvent *pPaintEvent) override
  {
    QPainter painter(this);
    painter.setPen(Qt::black);
    return QFrame::paintEvent(pPaintEvent);
  }
  
  CPlot3Data mData;
};

#include "CPlot3.moc"

CPlot3::CPlot3(QWidget *pParent): Plot(pParent), mpDirectPainter(new QwtPlotDirectPainter(this))
{
  this->d_curve->setTitle(QStringLiteral("Normal Curve"));
  this->d_curve->setData(new CPlot3Buffer(this->d_interval, 10));

  this->setTitle(QString());
  this->setFooter(QString());
  this->enableAxis(xTop, false);
  this->enableAxis(xBottom, false);
  this->enableAxis(yLeft, false);
  this->enableAxis(yRight, false);

  this->setSettings(this->d_settings);
}

// void CPlot3::setSettings( const Settings &s )
// {
//     if ( d_timerId >= 0 )
//         killTimer( d_timerId );

//     d_timerId = startTimer( s.updateInterval );

//     this->d_grid->setPen( s.grid.pen );
//     this->d_grid->setVisible( s.grid.pen.style() != Qt::NoPen );

//     CPlot3Data *buffer = qobject_cast<CPlot3Canvas*>(this->canvas())->GetData();
//     if ( s.curve.numPoints != buffer->GetSize() ||
//             s.curve.functionType != d_settings.curve.functionType )
//     {
//         switch( s.curve.functionType )
//         {
//             case Settings::Wave:
//                 buffer->setFunction( wave );
//                 break;
//             case Settings::Noise:
//                 buffer->setFunction( noise );
//                 break;
//             default:
//                 buffer->setFunction( NULL );
//         }

//         buffer->fill( d_interval, s.curve.numPoints );
//     }

//     d_settings = s;
// }

void CPlot3::timerEvent(QTimerEvent *pEvent)
{
  CircularBuffer *buffer = static_cast<CircularBuffer *>( d_curve->data() );
  buffer->setReferenceTime( d_clock.elapsed() / 1000.0 );

  if (d_settings.updateType == Settings::RepaintCanvas)
  {
    // the axes in this example doesn't change. So all we need to do
    // is to repaint the canvas.
    this->DirectPaint();
  }
  else
  {
    bool doAutoReplot = autoReplot();
    this->setAutoReplot(false);

    this->updateAxes();

    /*
      Maybe the layout needs to be updated, because of changed
      axes labels. We need to process them here before painting
      to avoid that scales and canvas get out of sync.
     */
    QApplication::sendPostedEvents(this, QEvent::LayoutRequest);
    this->DirectPaint();

    this->setAutoReplot(doAutoReplot);
  }
}

void CPlot3::DirectPaint()
{
  this->mpDirectPainter->drawSeries(this->d_curve, 0, this->d_curve->dataSize() - 1);
  // QMetaObject::invokeMethod( canvas(), "replot", Qt::DirectConnection );
}