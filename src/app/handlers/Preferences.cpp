#include "Preferences.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>
#include <iostream>

#include "../../lib/json.hpp"


QString PreferencesIO::settingsFilePath() {
    auto dir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    if (dir.isEmpty()) {
        dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    }
    if (dir.isEmpty()) {
        dir = QDir::homePath() + "/.crossdev";
    }
    const QDir d(dir);
    if (!d.exists()) {
        if (!d.mkpath(".")) {
            qWarning() << "Failed to create config directory:" << d.path();
        }
    }
    return d.filePath("settings.json");
}

Preferences PreferencesIO::load() {
    Preferences prefs;
    QFile f(settingsFilePath());
    std::cout << "Loading settings from: " << f.fileName().toStdString() << std::endl;
    if (!f.exists()) return prefs;
    if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        const QByteArray data = f.readAll();
        f.close();
        try {
            auto j = nlohmann::json::parse(std::string(data.constData(), data.size()));
            if (j.contains("accentColor")) {
                const std::string s = j["accentColor"];
                if (QColor c(QString::fromStdString(s)); c.isValid()) prefs.accentColor = c;
            }
            if (j.contains("mode")) {
                if (const std::string s = j["mode"]; s == "normal" || s == "scientific") prefs.mode = QString::fromStdString(s);
            }
        } catch (const std::exception& e) {
            qWarning() << "Failed to parse settings.json:" << e.what();
        }
    }
    return prefs;
}

bool PreferencesIO::save(const Preferences& prefs) {
    nlohmann::json j;
    j["accentColor"] = prefs.accentColor.name(QColor::HexRgb).toStdString();
    j["mode"] = prefs.mode.toStdString();

    QFile f(settingsFilePath());
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) return false;
    const auto s = j.dump(2);
    f.write(s.c_str(), static_cast<qint64>(s.size()));
    f.close();
    return true;
}
