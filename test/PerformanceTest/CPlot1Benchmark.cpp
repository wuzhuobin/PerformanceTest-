#include "CPlot1.h"

// qt
#include <QtTest/QtTest>
// qwt
#include <qwt_plot_canvas.h>

class CPlot1CanvasBenchmark: public QwtPlotCanvas
{
  Q_OBJECT;
public Q_SLOTS:
  void replot()
  {
    this->invalidateBackingStore();
    QBENCHMARK
    {
      this->repaint();
    }
  }
};

class CPlot1Benchmark: public QObject
{
  Q_OBJECT;
private Q_SLOTS:
  void initTestCase() {}
  void init() {}
  void cleanup() {}
  void cleanupTestCase() {}
  void show()
  {
    CPlot1CanvasBenchmark *canvas = new CPlot1CanvasBenchmark;
    canvas->setFrameStyle(QFrame::Box | QFrame::Plain);
    canvas->setLineWidth(1);
    canvas->setPalette(Qt::white);

    CPlot1 w;
    w.setCanvas(canvas);
    w.showMaximized();

    QTest::qWait(1000);
  }
};

#include "CPlot1Benchmark.moc"

QTEST_MAIN(CPlot1Benchmark)