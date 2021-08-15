#ifndef TREEMODEL_H
#define TREEMODEL_H

#include "TreeItem.h"
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QSortFilterProxyModel>

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit TreeModel(QStringList headers, QObject *parent = 0);
    ~TreeModel();

    //����Ϊ�Զ���model��Ҫʵ�ֵ�һЩ�麯�������ᱻQt�ڲ�ѯmodel����ʱ����
    //headerData: ��ȡ��ͷ��section�е�����
    //data: ���ĺ�������ȡĳ������index��Ԫ�صĸ�������
    //      role������ȡ�������ݣ����������漸�֣�
    //      DisplayRole��Ĭ�ϣ������ǽ�����ʾ���ı�����
    //      TextAlignmentRole������Ԫ�ص��ı���������
    //      TextColorRole��BackgroundRole���ֱ�ָ�ı���ɫ����Ԫ�񱳾�ɫ
    //flags: ��ȡindex��һЩ��־��һ�㲻��ô��
    //index: Qt�����model����һ������Ϊparent�Ľڵ������row��column���ӽڵ��Ԫ�أ��ڱ�����������Ҫ���ظ�Ԫ�ص���ȷ����
    //parent����ȡָ��Ԫ�صĸ�Ԫ��
    //rowCount: ��ȡָ��Ԫ�ص��ӽڵ��������һ��������
    //columnCount: ��ȡָ��Ԫ�ص�����
    //setData: �޸Ľڵ�����
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

public:
    TreeItem *itemFromIndex(const QModelIndex &index) const;
    QModelIndex indexFromItem(TreeItem *item);
    TreeItem *root();

private:
    QStringList mHeaders;   // ��ͷ����
    TreeItem *mRootItem;    // ���ڵ�
};

class MyFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    MyFilterModel(QObject *parent = nullptr);
    virtual ~MyFilterModel();
    bool filterAcceptsRow(int source_row,
        const QModelIndex & source_parent) const override;
};
#endif // TREEMODEL_H
