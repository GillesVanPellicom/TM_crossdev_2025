#pragma once
#include <QWidget>
#include <QString>

class DisplayWidget final : public QWidget {
    Q_OBJECT
public:
    explicit DisplayWidget(QWidget* parent = nullptr);
    void setText(const QString& text);
    QString text() const { return m_text; }

protected:
    void paintEvent(QPaintEvent* event) override;
    QSize minimumSizeHint() const override { return {200, 60}; }
    QSize sizeHint() const override { return {300, 80}; }

private:
    QString m_text;
};
