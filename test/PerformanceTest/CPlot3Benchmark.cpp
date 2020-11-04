#include "CPlot3.h"

// qt
#include <QtTest/QtTest>
// qwt
#include <qwt_plot_canvas.h>

class CPlot3CanvasBenchmark: public QwtPlotCanvas
{
  Q_OBJECT;
public Q_SLOTS:
  void replot(const QRect &rect)
  {
    this->invalidateBackingStore();
    QBENCHMARK
    {
      this->repaint(rect);
    }
  }
};

class CPlot3Benchmark: public QObject
{
  Q_OBJECT;
private Q_SLOTS:
  void initTestCase() {}
  void init() {}
  void cleanup() {}
  void cleanupTestCase() {}
  void show()
  {
    CPlot3CanvasBenchmark *canvas = new CPlot3CanvasBenchmark;
    canvas->setFrameStyle(QFrame::Box | QFrame::Plain);
    canvas->setLineWidth(1);
    canvas->setPalette(Qt::white);

    CPlot3 w;
    w.setCanvas(canvas);
    w.showMaximized();

    QTest::qWait(1000);
  }
};

#include "CPlot3Benchmark.moc"

QTEST_MAIN(CPlot3Benchmark)