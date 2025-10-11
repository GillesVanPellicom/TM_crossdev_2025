#include "DisplayWidget.h"
#include <QFontMetrics>
#include <QPaintEvent>
#include <QPainter>

DisplayWidget::DisplayWidget(QWidget* parent)
    : QWidget(parent) {
    setAttribute(Qt::WA_OpaquePaintEvent);
}

void DisplayWidget::setText(const QString& text) {
    if (m_text == text) return;
    m_text = text;
    update();
}

void DisplayWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    // Background rounded rect
    const QRectF r = rect().adjusted(4, 4, -4, -4);
    QPen pen(QColor(0,0,0,40));
    pen.setWidthF(1.0);
    p.setPen(pen);
    p.setBrush(QColor(240, 240, 245));
    p.drawRoundedRect(r, 10, 10);

    // Text (right-aligned)
    QFont f = font();
    f.setPointSizeF(f.pointSizeF() + 4);
    p.setFont(f);
    p.setPen(QPen(Qt::black));

    const QFontMetrics fm(f);
    const QString elided = fm.elidedText(m_text, Qt::ElideLeft, static_cast<int>(r.width() - 16));
    p.drawText(r.adjusted(8, 0, -8, 0), Qt::AlignVCenter | Qt::AlignRight, elided);
}
