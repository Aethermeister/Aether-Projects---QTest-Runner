#pragma once

#include <QtCore/QObject>

class MixingTestClass : public QObject
{
	Q_OBJECT

public:
	explicit MixingTestClass() = default;

private slots:
	void MixingTest1();
	void MixingTest2();
	void MixingTest3();
	void MixingTest4();
	void MixingTest5();
};
