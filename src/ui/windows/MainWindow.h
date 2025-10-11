#pragma once
#include <QMainWindow>
#include <QPointer>
#include <QVector>
#include "../../app/handlers/Preferences.h"

class QPushButton;
class QStackedWidget;
class QComboBox;
class DisplayWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void openSettings();
    void setModeNormal();
    void setModeScientific();

    void digitClicked();
    void pointClicked();
    void clearClicked();
    void backspaceClicked() const;
    void changeSignClicked();

    void binaryOperatorClicked();
    void equalsClicked();

    void functionClicked(); // sin, cos, tan, sqrt, ln, log10, inv, sqr, pi, e

private:
    void buildUi();
    QWidget* buildNormalPad();
    QWidget* buildScientificPad();
    QPushButton* makeButton(const QString& text, const char* slot, bool accent=false);
    void applyAccentColor();
    void applyPreferences(const Preferences& p);

    double displayValue() const;
    void setDisplayValue(double v);

    void abortOperation();
    bool calculate(double rightOperand, const QString& op);

private:
    Preferences m_prefs;
    DisplayWidget* m_display = nullptr;
    QStackedWidget* m_stack = nullptr;
    QComboBox* m_modeBox = nullptr;

    QString m_pendingOp;
    double m_accumulator = 0.0;
    bool m_waitingForOperand = true;
};
