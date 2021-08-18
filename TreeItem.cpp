#include <QStringList>
#include <QDateTime>
#include "TreeItem.h"

TreeItem::TreeItem(TreeItem *parent)
{
    mParentItem = parent;
    mLevel = 0;
    mRow = 0;
}

TreeItem::~TreeItem()
{
    removeChilds();
}

void TreeItem::appendChild(TreeItem *item)
{
    item->setRow(mChildItems.size());   //item���Լ��ǵڼ����������Ż�Ч��
    mChildItems.append(item);
    item->setLevel(mLevel + 1);
    if (item->mLevel == 1) {
        item->mTab = item->ItemData()[1].toString();
    } else {
        item->mTab = this->mTab;
    }
}

void TreeItem::removeChilds()
{
    qDeleteAll(mChildItems);
    mChildItems.clear();
}

TreeItem *TreeItem::child(int row)
{
    return mChildItems.value(row);
}

TreeItem *TreeItem::parentItem()
{
    return mParentItem;
}

int TreeItem::childCount() const
{
    return mChildItems.count();
}

int TreeItem::row() const
{
    return mRow;
}

QVariant TreeItem::data(int column) const
{
    if (column < mItemData.size()) {
        return mItemData[column];
    }
    //if (mLevel == 1)
    //{
    //    //һ���ڵ㣬�༶
    //    if (column == 0)
    //    {
    //        CLASS* c = (CLASS*)mPtr;
    //        return c->name;
    //    }
    //}
    //else if (mLevel == 2)
    //{
    //    //�����ڵ�ѧ����Ϣ
    //    STUDENT* s = (STUDENT*)mPtr;
    //    switch (column)
    //    {
    //    case 0: return s->name;
    //    case 1: return QString::number(s->score1);
    //    case 2: return QString::number(s->score2);
    //    case 3: return QString::number(s->score3);
    //    case 4: return QString::number(s->score1 + s->score2 + s->score3);
    //    case 5: return QString::number((s->score1 + s->score2 + s->score3) / 3);
    //    case 6:
    //    {
    //        if (s->score1 < 60 || s->score2 < 60 || s->score3 < 60)
    //        {
    //            //����һ�ſβ��ϸ��򲻺ϸ�
    //            return QStringLiteral("���ϸ�");
    //        }
    //        else
    //        {
    //            return QStringLiteral("�ϸ�");
    //        }
    //    }
    //    case 7:
    //    {
    //        if (s->score1 >= 90 && s->score2 >= 90 && s->score3 >= 90)
    //        {
    //            //ÿ�ſζ��ﵽ90����������
    //            return QStringLiteral("����");
    //        }
    //        else
    //        {
    //            return QStringLiteral("-");
    //        }
    //    }
    //    default:
    //        return QVariant();
    //    }
    //}
    return QVariant();
}

void TreeItem::setData(int column, QVariant value)
{
    if (column >= mItemData.size()) {
        return;
    }
    mItemData[column] = value;
}




