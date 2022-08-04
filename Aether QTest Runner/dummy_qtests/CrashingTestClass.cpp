#include "CrashingTestClass.h"

#include <QtTest/QTest>
#include <QtWidgets/QLabel>

void CrashingTestClass::CrashingTest()
{
	qInfo() << "Crashing Test starting...";

	QTest::qWait(10000);

	qInfo() << "I will crash";
	QLabel* label = nullptr;
	const auto text = label->text();
}
