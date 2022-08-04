#include "MixingTestClass.h"

#include <QtTest/QTest>

void MixingTestClass::MixingTest1()
{
	QVERIFY(true);
}

void MixingTestClass::MixingTest2()
{
	QVERIFY2(false, "FailingTest2");
}

void MixingTestClass::MixingTest3()
{
	QCOMPARE(0, 1);
}

void MixingTestClass::MixingTest4()
{
	qDebug() << "MixingTest4 starting...";
	QVERIFY(true);
	qDebug() << "MixingTest4 finished...";
}

void MixingTestClass::MixingTest5()
{
	qDebug() << "MixingTest5 starting...";
	QCOMPARE(0, 1);
	qDebug() << "MixingTest5 finished...";
}
