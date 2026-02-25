#include "SimpleModel.h"
#include <QColor>

SimpleModel::SimpleModel(QObject* parent)
	: QAbstractTableModel(parent)
{
	// 初始化一些默认数据
	addStudent("Zane", 85); // 稍微改了个名字以示区分
	addStudent("Li Si", 58);
	addStudent("Wang Wu", 92);
}

int SimpleModel::rowCount(const QModelIndex& parent) const
{
	if (parent.isValid()) return 0;
	return m_data.count();
}

int SimpleModel::columnCount(const QModelIndex& parent) const
{
	if (parent.isValid()) return 0;
	return 3;
}

QVariant SimpleModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid() || index.row() >= m_data.size())
		return QVariant();

	const Student& s = m_data.at(index.row());

	if (role == Qt::DisplayRole) {
		switch (index.column()) {
		case 0: return s.name;
		case 1: return s.score;
		case 2: return s.passed ? "Pass" : "Fail";
		}
	}
	else if (role == Qt::ForegroundRole) {
		// 分数不及格标红
		if ((index.column() == 1 || index.column() == 2) && !s.passed)
			return QBrush(Qt::red);
	}
	else if (role == Qt::TextAlignmentRole) {
		if (index.column() == 1)
			return Qt::AlignCenter;
	}

	return QVariant();
}

QVariant SimpleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
		switch (section) {
		case 0: return "Name";
		case 1: return "Score";
		case 2: return "Status";
		}
	}
	return QVariant();
}

void SimpleModel::addStudent(const QString& name, int score)
{
	// begin的作用：1. 保护现场，防止渲染不一致; 2. 坐标偏移，比如修改选中索引
	// (parentIndex, first, last)
	beginInsertRows(QModelIndex(), m_data.count(), m_data.count()); 
	m_data.append({ name, score, score >= 60 });
	// 刷新数据
	endInsertRows();
}