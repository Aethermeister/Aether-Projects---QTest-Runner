#pragma once

#include <QtCore/QObject>

class FailingTestClass : public QObject
{
	Q_OBJECT

public:
	explicit FailingTestClass() = default;

private slots:
	void FailingTest1();
	void FailingTest2();
	void FailingTest3();
	void FailingTest4();
	void FailingTest5();
};
