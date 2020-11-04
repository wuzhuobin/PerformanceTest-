#include "CPlot1.h"

// qt
#include <QtTest/QtTest>

class CPlot1Test: public QObject
{
  Q_OBJECT;
private Q_SLOTS:
  void initTestCase() {}
  void init() {}
  void cleanup() {}
  void cleanupTestCase() {}
};

#include "CPlot1Test.moc"

QTEST_MAIN(CPlot1Test)