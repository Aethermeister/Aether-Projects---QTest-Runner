#pragma once

#include <QtCore/QObject>

class CrashingTestClass : public QObject
{
	Q_OBJECT

public:
	explicit CrashingTestClass() = default;

private slots:
	void CrashingTest();
};
