#include "SettingsDialog.h"
#include <QColorDialog>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

SettingsDialog::SettingsDialog(const Preferences& initial, QWidget* parent)
    : QDialog(parent), m_prefs(initial) {
    setWindowTitle("Settings");

    auto* v = new QVBoxLayout(this);

    // Accent color row
    {
        auto* h = new QHBoxLayout();
        h->addWidget(new QLabel("Accent color:", this));
        m_colorBtn = new QPushButton(this);
        m_colorBtn->setFixedSize(48, 24);
        updateColorButton();
        connect(m_colorBtn, &QPushButton::clicked, this, &SettingsDialog::chooseAccentColor);
        h->addWidget(m_colorBtn);
        h->addStretch();
        v->addLayout(h);
    }

    // Mode row
    {
        auto* h = new QHBoxLayout();
        h->addWidget(new QLabel("Mode:", this));
        m_modeCombo = new QComboBox(this);
        m_modeCombo->addItem("Normal", "normal");
        m_modeCombo->addItem("Scientific", "scientific");
        const int idx = m_prefs.mode == "scientific" ? 1 : 0;
        m_modeCombo->setCurrentIndex(idx);
        h->addWidget(m_modeCombo);
        h->addStretch();
        v->addLayout(h);
    }

    auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttons, &QDialogButtonBox::accepted, this, &SettingsDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &SettingsDialog::reject);
    v->addWidget(buttons);
}

void SettingsDialog::updateColorButton() const
{
    if (!m_colorBtn) return;
    const QString css = QString("background:%1; border:1px solid #666; border-radius:4px;")
            .arg(m_prefs.accentColor.name(QColor::HexRgb));
    m_colorBtn->setStyleSheet(css);
}

void SettingsDialog::chooseAccentColor() {
    if (const QColor c = QColorDialog::getColor(m_prefs.accentColor, this, "Choose accent color"); c.isValid()) {
        m_prefs.accentColor = c;
        updateColorButton();
    }
}

void SettingsDialog::accept() {
    if (m_modeCombo) {
        m_prefs.mode = m_modeCombo->currentData().toString();
    }
    QDialog::accept();
}
