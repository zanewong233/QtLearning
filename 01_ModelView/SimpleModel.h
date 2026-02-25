#pragma once // VS 生成的头文件通常带这个，替代 #ifndef

#include <QAbstractTableModel>
#include <QList>
#include <QBrush>

// 定义一个简单的结构体来存储数据
struct Student {
	QString name;
	int score;
	bool passed; // 是否及格
};

class SimpleModel : public QAbstractTableModel
{
	Q_OBJECT // 核心宏：必须有，否则信号槽和 MOC 机制失效

public:
	explicit SimpleModel(QObject* parent = nullptr);

	// --- 必须重写的三个核心函数 ---
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	// --- 可选重写：表头 ---
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	// --- 自定义功能：添加数据 ---
	void addStudent(const QString& name, int score);

	// --- 进阶：实现编辑功能 ---
	// 1. 告诉 View 哪些单元格是可以编辑的
	Qt::ItemFlags flags(const QModelIndex& index) const override;

	// 2. 核心：View 把用户修改的值传回来，你负责更新底层数据
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

private:
	QList<Student> m_data; // 数据源
};