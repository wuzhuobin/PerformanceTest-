#include "CPlot2.h"
#include "CPlot2Buffer.h"

// qwt
#include <qwt_text_label.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_canvas.h>

// qt
#include <QDateTime>

CPlot2::CPlot2(QWidget *pParent):
  Plot(pParent),
  mpCurve(new QwtPlotCurve)
{
  this->d_curve->setTitle(QStringLiteral("Normal Curve"));
  this->d_curve->setData(new CPlo2Buffer(this->d_interval, 10, false));

  this->mpCurve->setTitle("Normal Curve");
  this->mpCurve->setPen(Qt::black);
  this->mpCurve->setData(new CPlo2Buffer(this->d_interval, 10, true));
  this->mpCurve->attach(this);

  this->setTitle(QString());
  this->setFooter(QString());
  this->enableAxis(xTop, false);
  this->enableAxis(xBottom, false);
  this->enableAxis(yLeft, false);
  this->enableAxis(yRight, false);
  this->plotLayout()->setCanvasMargin(0);
  this->plotLayout()->setSpacing(0);

  this->setSettings(this->d_settings);
}

void CPlot2::setSettings(const Settings & s)
{
    CircularBuffer *buffer2 = static_cast<CircularBuffer *>( this->mpCurve->data() );
    if ( s.curve.numPoints != buffer2->size() ||
            s.curve.functionType != d_settings.curve.functionType )
    {
        switch( s.curve.functionType )
        {
            case Settings::Wave:
                buffer2->setFunction( wave );
                break;
            case Settings::Noise:
                buffer2->setFunction( noise );
                break;
            default:
                buffer2->setFunction( NULL );
        }

        buffer2->fill( d_interval, s.curve.numPoints );
    }

    this->mpCurve->setPen( s.curve.pen );
    this->mpCurve->setBrush( s.curve.brush );

    this->mpCurve->setPaintAttribute( QwtPlotCurve::ClipPolygons,
        s.curve.paintAttributes & QwtPlotCurve::ClipPolygons );
    this->mpCurve->setPaintAttribute( QwtPlotCurve::FilterPoints,
        s.curve.paintAttributes & QwtPlotCurve::FilterPoints );

    this->mpCurve->setRenderHint( QwtPlotItem::RenderAntialiased,
        s.curve.renderHint & QwtPlotItem::RenderAntialiased );
  Plot::setSettings(s);
}

void CPlot2::timerEvent(QTimerEvent *pEvent)
{
  CPlo2Buffer *pBuffer = static_cast<CPlo2Buffer*>(this->mpCurve->data());
  pBuffer->setReferenceTime(this->d_clock.elapsed() / 1000.0);
  Plot::timerEvent(pEvent);
  QwtPlotCanvas *plotCanvas = qobject_cast<QwtPlotCanvas *>( canvas() );
  // qDebug() << plotCanvas;
  // qDebug() << plotCanvas->backingStore();
  // if (plotCanvas && plotCanvas->backingStore())
  // {
  //   plotCanvas->backingStore()->save(QDateTime::currentDateTime().toString() + ".png");
  // }
}