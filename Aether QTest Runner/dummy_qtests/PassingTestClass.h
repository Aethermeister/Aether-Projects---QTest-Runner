#pragma once

#include <QtCore/QObject>

class PassingTestClass : public QObject
{
	Q_OBJECT

public:
	explicit PassingTestClass() = default;

private slots:
	void PassingTest1();
	void PassingTest2();
	void PassingTest3();
	void PassingTest4();
};
