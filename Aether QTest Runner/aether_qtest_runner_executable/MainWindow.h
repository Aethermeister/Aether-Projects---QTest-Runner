#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	virtual ~MainWindow() = default;

private:
	Ui::MainWindowClass ui;

	void InitializeConnections() const;

private slots:
	void ShowTestRunConfigurationWidget();
};
