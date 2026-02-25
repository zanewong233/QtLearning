#include <QtWidgets/QApplication> // VS通常包含完整的路径，或者配置好include路径后直接 <QApplication>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHeaderView>
#include "SimpleModel.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	// 创建主窗口
	QWidget window;
	window.setWindowTitle("VS + Qt Model/View Demo");
	window.resize(600, 400);

	QVBoxLayout* layout = new QVBoxLayout(&window);

	// 1. View
	QTableView* tableView = new QTableView();

	// 2. Model
	SimpleModel* model = new SimpleModel(&window);

	// 3. Bind
	tableView->setModel(model);

	// 设置
	tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableView->setAlternatingRowColors(true);

	layout->addWidget(tableView);

	// 按钮
	QPushButton* btn = new QPushButton("Add Random Student");
	layout->addWidget(btn);

	QObject::connect(btn, &QPushButton::clicked, [model]() {
		int score = rand() % 100;
		QString name = QString("Student %1").arg(rand() % 1000);
		model->addStudent(name, score);
		});

	window.show();
	return a.exec();
}