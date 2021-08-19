#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>

// �ڵ��Ƿ�����༭
#define TREE_ITEM_CAN_MODIFY    1


class TreeItem
{
public:
    explicit TreeItem(TreeItem *parentItem = 0);
    ~TreeItem();

    void appendChild(TreeItem *child);      // �ڱ��ڵ��������ӽڵ�
    void removeChilds();                    // ������нڵ�

    TreeItem *child(int row);               // ��ȡ��row���ӽڵ�ָ��
    TreeItem *parentItem();                 // ��ȡ���ڵ�ָ��
    int childCount() const;                 // �ӽڵ����
    int row() const;                        // ��ȡ�ýڵ��Ǹ��ڵ�ĵڼ����ӽڵ�

    //���ĺ�������ȡ�ڵ��column�е�����
    QVariant data(int column) const;

    //���á���ȡ�ڵ��Ǽ����ڵ㣨�������Ĳ㼶��
    int level() { return mLevel; }

    //���á���ȡ�ڵ�������ָ��
    void setItemData(QVector<QVariant> data) { mItemData = data; };
    QVector<QVariant> ItemData() { return mItemData; };

    //����ýڵ����丸�ڵ�ĵڼ����ӽڵ㣬��ѯ�Ż�����
    void setRow(int row) {
        mRow = row;
    }

    //�޸Ľڵ�����(ֻ�������ݵĽڵ���޸ģ��������������ſΣ������Ǹ�����Щ�����Զ����ģ����Զ�ˢ�£���������û����)
    void setData(int column, QVariant value);

    QString mTab; // ��¼��һ����Ϣ��������

private:
    void setLevel(int level) { mLevel = level; }
    QList<TreeItem*> mChildItems;   //�ӽڵ�
    TreeItem *mParentItem;          //���ڵ�
    int mLevel;     //�ýڵ��ǵڼ����ڵ�
    int mRow;       //��¼��item�ǵڼ��������Ż���ѯЧ��
    QVector<QVariant> mItemData;
};
Q_DECLARE_METATYPE(TreeItem *)
#endif
