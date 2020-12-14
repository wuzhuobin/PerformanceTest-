#include "CPlot3.h"
#include "CPlot3Buffer.h"

// qt
#include <QPaintEvent>
#include <QApplication>

// qwt
#include <qwt_plot_curve.h>
// #include <qwt_plot_directpainter.h>
#include <qwt_plot_canvas.h>

class CPlot3Canvas: public QwtPlotCanvas
{
  Q_OBJECT;
public:
  explicit CPlot3Canvas(QwtPlot *pPlot = nullptr) : QwtPlotCanvas(pPlot) {}
public Q_SLOTS:
  void replot(const QRect &rect)
  {
    this->invalidateBackingStore();
    if (this->testPaintAttribute(QwtPlotCanvas::ImmediatePaint))
    {
      this->repaint(rect);
    }
    else
    {
      this->update(rect);
    }
  }
};

#include "CPlot3.moc"


CPlot3::CPlot3(QWidget *pParent): Plot(pParent)
{

  QwtPlotCanvas *canvas = new CPlot3Canvas();
  canvas->setFrameStyle(QFrame::Box | QFrame::Plain);
  canvas->setLineWidth(1);
  canvas->setPalette(Qt::white);
  this->setCanvas(canvas);

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

void CPlot3::timerEvent(QTimerEvent *pEvent)
{
  CircularBuffer *buffer = static_cast<CircularBuffer *>( d_curve->data() );
  double elapsed = this->d_clock.elapsed();
  buffer->setReferenceTime( elapsed / 1000.0 );
  QwtPlotCanvas *plotCanvas = qobject_cast<QwtPlotCanvas *>(canvas());
  QRect rect = plotCanvas->contentsRect();
  double moveLeft = 1 + rect.width() * fmod(elapsed / 1000.0, this->d_interval) / this->d_interval; 
  double width = rect.width() * 0.1;
  rect.moveLeft(moveLeft);
  rect.setWidth(width);

  if (d_settings.updateType == Settings::RepaintCanvas)
  {
    // the axes in this example doesn't change. So all we need to do
    // is to repaint the canvas.
    QMetaObject::invokeMethod(canvas(), "replot", Qt::DirectConnection, Q_ARG(QRect, rect));
  }
  else
  {
    this->replot();
  }
}
