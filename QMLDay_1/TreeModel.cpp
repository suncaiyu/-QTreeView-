
#include "TreeItem.h"
#include "TreeModel.h"
#include <QColor>
#include <QDateTime>
#include <QStringList>
#include <QDebug>


TreeModel::TreeModel(QStringList headers, QObject *parent)
    : QAbstractItemModel(parent)
{
    mHeaders = headers;
    mRootItem = new TreeItem;
    int role = Qt::UserRole;
    role++;
    mRoleNames[Qt::DisplayRole] = "display";
//    role++;
//    mRoleNames[role] = "api";
//    role++;
//    mRoleNames[role] = "dur";
}

QHash<int,QByteArray> TreeModel::roleNames() const
{
    return mRoleNames;
}

TreeModel::~TreeModel()
{
    delete mRootItem;
}

TreeItem *TreeModel::itemFromIndex(const QModelIndex &index) const
{
    if (!index.isValid())
        return NULL;
    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    return item;
}

QModelIndex TreeModel::indexFromItem(TreeItem *item)
{
    TreeItem *tmp = item;
    QVector<TreeItem *>itemVector;
    while (tmp->parentItem() != nullptr) {
        itemVector.push_back(item->parentItem());
        tmp = tmp->parentItem();
    }
    itemVector.push_back(item);
    QModelIndex tmpIndex;
    itemVector.erase(itemVector.begin());
    for (int i = 0; i < itemVector.size(); ++i) {
        tmpIndex = index(itemVector[i]->row(), 0, tmpIndex);
    }
    return tmpIndex;
}

TreeItem *TreeModel::root()
{
    return mRootItem;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole)
        {
            return mHeaders.at(section);
        }
    }
    return QVariant();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    qDebug() << role;

    if (!index.isValid()) {
        return QVariant();
    }
    TreeItem *item = static_cast<TreeItem *>(index.internalPointer());
    if (role == Qt::UserRole) {
        return QVariant::fromValue<TreeItem *>(item);
    }
    //TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    else if (role == Qt::DisplayRole) {
        return item->data(index.column());
    }
    else if (role == Qt::EditRole)
    {
        //Ԫ�ش򿪱༭��ʱ����ʾ�����ݣ����û�����У��༭�����ʱĬ��Ϊ�հ�
        return item->data(index.column());
    }/* else {
        return item->ItemData().at(role - Qt::UserRole - 1);
    }*/
    //else if (role == Qt::TextAlignmentRole)
    //{
    //    if (index.column() == 0)
    //    {
    //        //��1�������
    //        return QVariant(Qt::AlignVCenter | Qt::AlignLeft);
    //    }
    //    else if (index.column() > 0 && index.column() < 6)
    //    {
    //        //��2~6���Ҷ���
    //        return QVariant(Qt::AlignVCenter | Qt::AlignRight);
    //    }
    //    else
    //    {
    //        //�����о��ж���
    //        return QVariant(Qt::AlignCenter);
    //    }
    //}
    //else if (role == Qt::TextColorRole)
    //{
    //    if (index.column() == 6)
    //    {
    //        QString str = item->data(6).toString();
    //        if (str == QStringLiteral("���ϸ�"))
    //        {
    //            //��7�У��Ƿ�ϸ�������ϸ�����ı�Ϊ��ɫ
    //            return QVariant(QColor("#FF0000"));
    //        }
    //    }
    //    return QVariant();
    //}
    return QVariant();
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    //TreeModel::setData ����д�ĸ��ຯ�������ڱ༭���ᱻ�Զ����õĺ���
    //TreeItem::setData �����Լ�д�ĺ������������޸�����
    if (index.isValid() && role == Qt::EditRole)
    {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        item->setData(index.column(), value);

        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    ////�ڵ��Ƿ�����༭
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    flags |= Qt::ItemIsEditable;

    return flags;
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = mRootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if (parentItem == mRootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = mRootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    return mHeaders.size();
}

MyFilterModel::MyFilterModel(QObject *parent) : QSortFilterProxyModel(parent)
{

}

MyFilterModel::~MyFilterModel()
{
}

bool MyFilterModel::filterAcceptsRow(int source_row, const QModelIndex & source_parent) const
{
    return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
    //> ���ÿ��������ӽڵ�
//    bool filter = QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);

//    if (filter) {
//        return true;
//    } else {
//        // check all decendant's
//        QModelIndex source_index = sourceModel()->index(source_row, 0, source_parent);
//        for (int k = 0; k < sourceModel()->rowCount(source_index); k++) {
//            if (filterAcceptsRow(k, source_index)) {
//                return true;
//            }
//        }
//    }
//    return false;


    // >���ÿ�����������
//    QString str = this->filterRegExp().pattern();
//    // ������1�͵�2��
//    for (int i = 1; i < 3; ++i) {
//        QModelIndex idx = sourceModel()->index(source_row, i, source_parent);
//        QString origin = sourceModel()->data(idx).toString();
//        if (origin.contains(str)) {
//            return true;
//        } else {
//            QModelIndex source_index = sourceModel()->index(source_row, 0, source_parent);
//            for (int k = 0; k < sourceModel()->rowCount(source_index); k++) {
//                if (filterAcceptsRow(k, source_index)) {
//                    return true;
//                }
//            }
//        }
//    }
//    return  false;

    //>ֻ֧��������һ�㣬����Ҫչʾ���Ͻڵ��ȫ���ӽڵ�
    // ����ѭ�����������ǱȽϵ������ǵĵ�һ�㸸�ڵ�
//    QString str = this->filterRegExp().pattern();
//    // ����������һ��
//    TreeItem *it = source_parent.data(Qt::UserRole).value<TreeItem *>();
//    if (it == nullptr) {
//        QModelIndex idx = sourceModel()->index(source_row, 0, source_parent);
//        return filterAcceptsRow(source_row, idx);
//    }
//    QString origin = it->mTab;
//    if (origin.contains(str)) {
//        QModelIndex source_index = sourceModel()->index(source_row, 0, source_parent);
//        for (int k = 0; k < sourceModel()->rowCount(source_index); k++) {
//            if (filterAcceptsRow(k, source_index)) {
//                return true;
//            }
//        }
//        return true;
//    }
//    return false;
}
