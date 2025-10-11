#pragma once
#include <QColor>
#include <QDialog>
#include "../../app/handlers/Preferences.h"

class QPushButton;
class QComboBox;

class SettingsDialog final : public QDialog {
    Q_OBJECT
public:
    explicit SettingsDialog(const Preferences& initial, QWidget* parent = nullptr);
    [[nodiscard]] Preferences resultPreferences() const { return m_prefs; }

private slots:
    void chooseAccentColor();
    void accept() override;

private:
    void updateColorButton() const;

    Preferences m_prefs;
    QPushButton* m_colorBtn = nullptr;
    QComboBox* m_modeCombo = nullptr;
};
