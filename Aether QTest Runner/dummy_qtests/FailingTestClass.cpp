#include "FailingTestClass.h"

#include <QtTest/QTest>

void FailingTestClass::FailingTest1()
{
	QVERIFY(false);
}

void FailingTestClass::FailingTest2()
{
	QVERIFY2(false, "FailingTest2");
}

void FailingTestClass::FailingTest3()
{
	QCOMPARE(0, 1);
}

void FailingTestClass::FailingTest4()
{
	qDebug() << "FailingTest4 starting...";
	QVERIFY(false);
	qDebug() << "FailingTest4 finished...";
}

void FailingTestClass::FailingTest5()
{
	qDebug() << "FailingTest5 starting...";
	QCOMPARE(0, 1);
	qDebug() << "FailingTest5 finished...";
}
