#ifndef WIDGETSTYLE_H
#define WIDGETSTYLE_H

#include "assistant/common.h"
#include "assistant/graphicswidget.h"
#include "assistant/coreEditor/coreeditor.h"
#include <QWidget>
#include <algorithm>
#include <functional>

#include <QtWidgets>

namespace Ui {
class WidgetStyle;
}

class WidgetStyle : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetStyle(QWidget* parent = nullptr);
    ~WidgetStyle() override;

    void setFocusLineEdit();
    QGraphicsScene* getScene() const;
    void setScene(QGraphicsScene* scene);

private slots:
    void filterListWidget();
    void selectWidget();
    void deleteWidget();
    void clearScene();
    void setStyleSheetWidget(const QString& style);

private:
    class WidgetScene : public QGraphicsScene
    {
    public:
        WidgetScene(qreal x, qreal y, qreal widht, qreal height, WidgetStyle* parent = nullptr);
        ~WidgetScene() override = default;

    private:
        WidgetStyle         *m_wgtStyle = nullptr;
        QGraphicsRectItem   *m_rectItem = nullptr;
        QPointF             m_topLeftRect;
        Qt::MouseButton     m_mouseButton = Qt::NoButton;

        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    };

    Ui::WidgetStyle             *ui             = nullptr;
    WidgetScene                 *m_scene        = nullptr;
    CoreEditor                  *m_editor       = nullptr;
    QVector<GraphicsWidget*>    m_graphicsWgt_;
    QVector<GraphicsWidget*>    m_deleteGraphicsWgt_;

    QWidget* createWidget(const QString& name);
    QWidget* setLayoutWidget(const QVector<QWidget*>& vecWgt, const QSize& size);
    void distinguishRect(const QRectF& rect);
    bool containsWidget(const QPointF& point);
};

#endif // WIDGETSTYLE_H
