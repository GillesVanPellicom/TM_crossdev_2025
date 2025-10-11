#pragma once
#include <QColor>
#include <QString>

struct Preferences {
    QColor accentColor = QColor(76, 110, 245); // default blue
    QString mode = "normal"; // "normal" or "scientific"
};

class PreferencesIO {
public:
    static Preferences load();
    static bool save(const Preferences& prefs);
    static QString settingsFilePath();
};
