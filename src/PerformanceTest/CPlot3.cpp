#include "CPlot3.h"

// qt
#include <QPaintEvent>

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

class CPlot3Canvas: public QWidget
{
  Q_OBJECT;
public:
  explicit CPlot3Canvas(QWidget *pParent = nullptr): QWidget(pParent) {}
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
    return QWidget::paintEvent(pPaintEvent);
  }
  
  CPlot3Data mData;
};

#include "CPlot3.moc"

CPlot3::CPlot3(QWidget *pParent): Plot(pParent)
{
  this->setTitle(QString());
  this->setFooter(QString());
  this->enableAxis(xTop, false);
  this->enableAxis(xBottom, false);
  this->enableAxis(yLeft, false);
  this->enableAxis(yRight, false);

  CPlot3Canvas *pCanvas =  new CPlot3Canvas(this);
  this->setCanvas(pCanvas);

  this->setSettings(this->d_settings);
}

void CPlot3::setSettings( const Settings &s )
{
    if ( d_timerId >= 0 )
        killTimer( d_timerId );

    d_timerId = startTimer( s.updateInterval );
    CPlot3Data *buffer = qobject_cast<CPlot3Canvas*>(this->canvas())->GetData();
    if ( s.curve.numPoints != buffer->GetSize() ||
            s.curve.functionType != d_settings.curve.functionType )
    {
        switch( s.curve.functionType )
        {
            case Settings::Wave:
                buffer->setFunction( wave );
                break;
            case Settings::Noise:
                buffer->setFunction( noise );
                break;
            default:
                buffer->setFunction( NULL );
        }

        buffer->fill( d_interval, s.curve.numPoints );
    }

    d_settings = s;
}

void CPlot3::timerEvent(QTimerEvent *pEvent)
{
    CPlot3Canvas *pCanvas = static_cast<CPlot3Canvas*>(this->canvas());
    pCanvas->GetData()->setReferenceTime( d_clock.elapsed() / 1000.0 );
    Plot::timerEvent(pEvent);
}