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

	if (role == Qt::DisplayRole || role == Qt::EditRole) {
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

Qt::ItemFlags SimpleModel::flags(const QModelIndex& index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	// 获取父类的默认属性 (通常包含 Enabled | Selectable)
	Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);

	// 只有“分数”列 (第1列) 允许编辑
	if (index.column() == 1) {
		return defaultFlags | Qt::ItemIsEditable; // 加上“可编辑”属性
	}

	return defaultFlags;
}

bool SimpleModel::setData(const QModelIndex& index, const QVariant& value, int role /*= Qt::EditRole*/)
{
	// 基本校验
	if (index.isValid() && role == Qt::EditRole) {

		// 获取底层数据的引用 (注意不是 const 引用，因为我们要改它)
		// m_data 是 QList<Student>
		Student& s = m_data[index.row()];

		// 根据列号修改对应字段
		if (index.column() == 1) {
			bool ok;
			int newScore = value.toInt(&ok);

			if (ok) {
				s.score = newScore;
				s.passed = (newScore >= 60); // 自动联动更新“状态”

				// === 关键点 ===
				// 数据改完了，必须发射 dataChanged 信号！
				// 否则 View 虽然看似改了，但可能会立刻变回去，或者其他 View 不会同步。
				// 参数：左上角索引，右下角索引，改变的角色
				emit dataChanged(index, index, { Qt::DisplayRole, Qt::ForegroundRole });

				// 还要通知“状态”那一列也刷新（因为及格状态变了）
				QModelIndex statusIndex = this->index(index.row(), 2);
				emit dataChanged(statusIndex, statusIndex, { Qt::DisplayRole, Qt::ForegroundRole });

				return true; // 修改成功
			}
		}
	}
	return false; // 修改失败
}
