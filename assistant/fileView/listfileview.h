#ifndef LISTFILEVIEW_H
#define LISTFILEVIEW_H

#include "assistant/common.h"
#include <QWidget>
#include <QListView>
#include <QMenu>
#include <QContextMenuEvent>
#include <QModelIndex>
#include <QAction>

class ListFileView : public QListView
{
    Q_OBJECT
public:
    explicit ListFileView(QWidget* parent = nullptr);
    ~ListFileView() override = default;

signals:
    void clickedCloseFile(int row);

private:
    QMenu       *m_menu     = new QMenu(this);

    void contextMenuEvent(QContextMenuEvent* event) override;
};

#endif // LISTFILEVIEW_H
