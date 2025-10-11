#include "MainWindow.h"
#include <QAction>
#include <QComboBox>
#include <QGridLayout>
#include <QMenuBar>
#include <QPushButton>
#include <QStackedWidget>
#include <QStatusBar>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>
#include <QtMath>
#include "../../app/handlers/Preferences.h"
#include "../dialogs/SettingsDialog.h"
#include "../widgets/DisplayWidget.h"


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    m_prefs = PreferencesIO::load();
    buildUi();
    applyPreferences(m_prefs);
}

void MainWindow::buildUi() {
    auto* central = new QWidget(this);
    auto* vbox = new QVBoxLayout(central);
    vbox->setContentsMargins(8,8,8,8);
    vbox->setSpacing(8);

    m_display = new DisplayWidget(central);
    m_display->setText("0");
    vbox->addWidget(m_display);

    m_stack = new QStackedWidget(central);
    m_stack->addWidget(buildNormalPad());
    m_stack->addWidget(buildScientificPad());
    vbox->addWidget(m_stack, 1);

    setCentralWidget(central);

    // Toolbar for mode and settings
    auto* tb = addToolBar("Main");
    m_modeBox = new QComboBox(tb);
    m_modeBox->addItem("Normal");
    m_modeBox->addItem("Scientific");
    connect(m_modeBox, &QComboBox::currentIndexChanged, this, [this](int idx){
        if (idx == 0) setModeNormal(); else setModeScientific();
    });
    tb->addWidget(m_modeBox);

    tb->addSeparator();
    auto* settingsAct = tb->addAction("Settings");
    connect(settingsAct, &QAction::triggered, this, &MainWindow::openSettings);

    // Menu
    auto* settingsMenu = menuBar()->addMenu("&Settings");
    settingsMenu->addAction(settingsAct);

    // statusBar()->showMessage("Ready");
}

QWidget* MainWindow::buildNormalPad() {
    auto* w = new QWidget(this);
    auto* grid = new QGridLayout(w);
    grid->setSpacing(6);

    // Row 0: Clear, Backspace, Divide, Multiply
    grid->addWidget(makeButton("C", SLOT(clearClicked()), true), 0, 0);
    grid->addWidget(makeButton("⌫", SLOT(backspaceClicked()), true), 0, 1);
    grid->addWidget(makeButton("/", SLOT(binaryOperatorClicked()), true), 0, 2);
    grid->addWidget(makeButton("*", SLOT(binaryOperatorClicked()), true), 0, 3);

    // Row 1: 7 8 9 -
    grid->addWidget(makeButton("7", SLOT(digitClicked())), 1, 0);
    grid->addWidget(makeButton("8", SLOT(digitClicked())), 1, 1);
    grid->addWidget(makeButton("9", SLOT(digitClicked())), 1, 2);
    grid->addWidget(makeButton("-", SLOT(binaryOperatorClicked()), true), 1, 3);

    // Row 2: 4 5 6 +
    grid->addWidget(makeButton("4", SLOT(digitClicked())), 2, 0);
    grid->addWidget(makeButton("5", SLOT(digitClicked())), 2, 1);
    grid->addWidget(makeButton("6", SLOT(digitClicked())), 2, 2);
    grid->addWidget(makeButton("+", SLOT(binaryOperatorClicked()), true), 2, 3);

    // Row 3: 1 2 3 =
    grid->addWidget(makeButton("1", SLOT(digitClicked())), 3, 0);
    grid->addWidget(makeButton("2", SLOT(digitClicked())), 3, 1);
    grid->addWidget(makeButton("3", SLOT(digitClicked())), 3, 2);
    grid->addWidget(makeButton("=", SLOT(equalsClicked()), true), 3, 3);

    // Row 4: +/- 0 .
    grid->addWidget(makeButton("±", SLOT(changeSignClicked()), true), 4, 0);
    grid->addWidget(makeButton("0", SLOT(digitClicked())), 4, 1);
    grid->addWidget(makeButton(".", SLOT(pointClicked())), 4, 2);

    return w;
}

QWidget* MainWindow::buildScientificPad() {
    auto* w = new QWidget(this);
    auto* grid = new QGridLayout(w);
    grid->setSpacing(6);

    // Functions row
    grid->addWidget(makeButton("sin", SLOT(functionClicked()), true), 0, 0);
    grid->addWidget(makeButton("cos", SLOT(functionClicked()), true), 0, 1);
    grid->addWidget(makeButton("tan", SLOT(functionClicked()), true), 0, 2);
    grid->addWidget(makeButton("√", SLOT(functionClicked()), true), 0, 3);

    // Second row of functions
    grid->addWidget(makeButton("x²", SLOT(functionClicked()), true), 1, 0);
    grid->addWidget(makeButton("1/x", SLOT(functionClicked()), true), 1, 1);
    grid->addWidget(makeButton("ln", SLOT(functionClicked()), true), 1, 2);
    grid->addWidget(makeButton("log10", SLOT(functionClicked()), true), 1, 3);

    // Constants
    grid->addWidget(makeButton("π", SLOT(functionClicked()), true), 2, 0);
    grid->addWidget(makeButton("e", SLOT(functionClicked()), true), 2, 1);

    // Basic pad similar to normal
    grid->addWidget(makeButton("C", SLOT(clearClicked()), true), 3, 0);
    grid->addWidget(makeButton("⌫", SLOT(backspaceClicked()), true), 3, 1);
    grid->addWidget(makeButton("/", SLOT(binaryOperatorClicked()), true), 3, 2);
    grid->addWidget(makeButton("*", SLOT(binaryOperatorClicked()), true), 3, 3);

    grid->addWidget(makeButton("7", SLOT(digitClicked())), 4, 0);
    grid->addWidget(makeButton("8", SLOT(digitClicked())), 4, 1);
    grid->addWidget(makeButton("9", SLOT(digitClicked())), 4, 2);
    grid->addWidget(makeButton("-", SLOT(binaryOperatorClicked()), true), 4, 3);

    grid->addWidget(makeButton("4", SLOT(digitClicked())), 5, 0);
    grid->addWidget(makeButton("5", SLOT(digitClicked())), 5, 1);
    grid->addWidget(makeButton("6", SLOT(digitClicked())), 5, 2);
    grid->addWidget(makeButton("+", SLOT(binaryOperatorClicked()), true), 5, 3);

    grid->addWidget(makeButton("1", SLOT(digitClicked())), 6, 0);
    grid->addWidget(makeButton("2", SLOT(digitClicked())), 6, 1);
    grid->addWidget(makeButton("3", SLOT(digitClicked())), 6, 2);
    grid->addWidget(makeButton("=", SLOT(equalsClicked()), true), 6, 3);

    grid->addWidget(makeButton("±", SLOT(changeSignClicked()), true), 7, 0);
    grid->addWidget(makeButton("0", SLOT(digitClicked())), 7, 1);
    grid->addWidget(makeButton(".", SLOT(pointClicked())), 7, 2);

    return w;
}

QPushButton* MainWindow::makeButton(const QString& text, const char* slot, bool accent) {
    auto* b = new QPushButton(text, this);
    b->setMinimumSize(48, 40);
    b->setProperty("accent", accent);
    connect(b, SIGNAL(clicked()), this, slot);
    return b;
}

void MainWindow::applyAccentColor() {
    const QString accent = m_prefs.accentColor.name(QColor::HexRgb);
    const QString css = QString(
        "QPushButton[accent='true'] {"
        "  background-color: %1; color: white; border: none; border-radius: 6px;"
        "  padding: 6px;"
        "}"
        "QPushButton { padding: 6px; }"
    ).arg(accent);
    this->setStyleSheet(css);
}

void MainWindow::applyPreferences(const Preferences& p) {
    m_prefs = p;
    if (m_prefs.mode == "scientific") {
        m_stack->setCurrentIndex(1);
        if (m_modeBox) m_modeBox->setCurrentIndex(1);
    } else {
        m_stack->setCurrentIndex(0);
        if (m_modeBox) m_modeBox->setCurrentIndex(0);
    }
    applyAccentColor();
}

void MainWindow::openSettings() {
    if (SettingsDialog dlg(m_prefs, this); dlg.exec() == QDialog::Accepted) {
        const auto newPrefs = dlg.resultPreferences();
        applyPreferences(newPrefs);
        PreferencesIO::save(newPrefs);
    }
}

void MainWindow::setModeNormal() {
    m_prefs.mode = "normal";
    m_stack->setCurrentIndex(0);
    PreferencesIO::save(m_prefs);
}

void MainWindow::setModeScientific() {
    m_prefs.mode = "scientific";
    m_stack->setCurrentIndex(1);
    PreferencesIO::save(m_prefs);
}

// Calculator logic

double MainWindow::displayValue() const {
    bool ok=false;
    const double v = m_display->text().toDouble(&ok);
    return ok ? v : 0.0;
}

void MainWindow::setDisplayValue(const double v) {
    m_display->setText(QString::number(v, 'g', 12));
    m_waitingForOperand = true;
}

void MainWindow::abortOperation() {
    m_accumulator = 0.0;
    m_pendingOp.clear();
    m_display->setText("Error");
    m_waitingForOperand = true;
}

bool MainWindow::calculate(const double rightOperand, const QString& op) {
    if (op == "+") {
        m_accumulator += rightOperand;
    } else if (op == "-") {
        m_accumulator -= rightOperand;
    } else if (op == "*") {
        m_accumulator *= rightOperand;
    } else if (op == "/") {
        if (qFuzzyIsNull(rightOperand)) return false;
        m_accumulator /= rightOperand;
    } else {
        return false;
    }
    return true;
}

void MainWindow::digitClicked() {
    const auto* b = qobject_cast<QPushButton*>(sender());
    if (!b) return;
    const QString d = b->text();

    if (m_display->text() == "0" && d == "0") return;

    if (m_waitingForOperand) {
        m_display->setText(d);
        m_waitingForOperand = false;
    } else {
        m_display->setText(m_display->text() + d);
    }
}

void MainWindow::pointClicked() {
    if (m_waitingForOperand) {
        m_display->setText("0.");
        m_waitingForOperand = false;
    } else if (!m_display->text().contains('.')) {
        m_display->setText(m_display->text() + ".");
    }
}

void MainWindow::clearClicked() {
    m_accumulator = 0.0;
    m_pendingOp.clear();
    m_display->setText("0");
    m_waitingForOperand = true;
}

void MainWindow::backspaceClicked() const
{
    if (m_waitingForOperand) return;
    QString t = m_display->text();
    if (t.size() > 1) t.chop(1); else t = "0";
    m_display->setText(t);
}

void MainWindow::changeSignClicked() {
    double v = displayValue();
    v = -v;
    setDisplayValue(v);
}

void MainWindow::binaryOperatorClicked() {
    const auto* b = qobject_cast<QPushButton*>(sender());
    if (!b) return;
    const QString op = b->text();

    const double operand = displayValue();

    if (!m_pendingOp.isEmpty()) {
        if (!calculate(operand, m_pendingOp)) {
            abortOperation();
            return;
        }
        setDisplayValue(m_accumulator);
    } else {
        m_accumulator = operand;
    }

    m_pendingOp = op;
    m_waitingForOperand = true;
}

void MainWindow::equalsClicked() {
    const double operand = displayValue();
    if (!m_pendingOp.isEmpty()) {
        if (!calculate(operand, m_pendingOp)) {
            abortOperation();
            return;
        }
        setDisplayValue(m_accumulator);
        m_pendingOp.clear();
    } else {
        setDisplayValue(operand);
    }
}

void MainWindow::functionClicked() {
    const auto* b = qobject_cast<QPushButton*>(sender());
    if (!b) return;
    const QString f = b->text();

    double v = displayValue();

    if (f == "sin") v = qSin(v);
    else if (f == "cos") v = qCos(v);
    else if (f == "tan") v = qTan(v);
    else if (f == "√") v = qSqrt(v);
    else if (f == "ln") v = qLn(v);
    else if (f == "log10") v = qLn(v) / qLn(10);
    else if (f == "1/x") { if (!qFuzzyIsNull(v)) v = 1.0 / v; else { abortOperation(); return; } }
    else if (f == "x²") v = v * v;
    else if (f == "π") v = M_PI;
    else if (f == "e") v = M_E;

    setDisplayValue(v);
}
