/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gui_properties.hpp
 * Author: biyanin
 *
 * Created on June 1, 2016, 1:38 PM
 */

#ifndef CONF_USER_PREFERENCES_HPP
#define CONF_USER_PREFERENCES_HPP

#include <QSettings>
#include <QApplication>
#include <QFont>
#include <QString>
#include <QStringList>
#include <QSize>
#include <QPoint>
#include <QMainWindow>

#include "repositories/path_repo.hpp"

namespace tdx {

    namespace app {

        namespace conf {

            class UserPreferences : public QSettings {
                
                Q_OBJECT

            public:
                UserPreferences()
                : QSettings(repo::PathRepo::userPreferencesConfFile(), QSettings::Format::IniFormat) {
                }
                
            public slots:
                void setFontSize(const QString& value) {
                    beginGroup("appearance");
                    beginGroup("font");
                    setValue("size", value.toInt());
                    endGroup();
                    endGroup();
                    loadAllFontSettings();
                }
                
                void setFontWeight(const QString& value) {
                    beginGroup("appearance");
                    beginGroup("font");
                    setValue("weight", value.toInt());
                    endGroup();
                    endGroup();
                    loadAllFontSettings();
                }
                
                void setFontFamily(const QString& value) {
                    beginGroup("appearance");
                    beginGroup("font");
                    setValue("family", value);
                    endGroup();
                    endGroup();
                    loadAllFontSettings();
                }
                
                void saveCurrentFontSettings() {
                    beginGroup("appearance");
                    beginGroup("font");
                    QFont font = QApplication::font();
                    setValue("size", font.pointSize());
                    setValue("family", font.family());
                    setValue("weight", font.weight());
                    endGroup();
                    endGroup();
                }
                
                void loadAllFontSettings() {
                    QFont font = QApplication::font();
                    beginGroup("appearance");
                    beginGroup("font");
                    font.setPointSize(value("size", font.pointSize()).toInt());
                    font.setFamily(value("family", font.family()).toString());
                    font.setWeight(value("weight", font.weight()).toInt());
                    endGroup();
                    endGroup();
                    QApplication::setFont(font);
                }
                
                void saveWindowPreferences(QMainWindow* window) {
                    beginGroup("window");
                    setValue("size", window->size());
                    setValue("position", window->pos());
                    endGroup();
                }
                
                void loadWindowPreferences(QMainWindow* window) {
                    beginGroup("window");
                    window->resize(value("size", QSize(896, 504)).toSize());
                    window->move(value("position", QPoint(200, 200)).toPoint());
                    endGroup();
                }

            };
        }
    }
}

#endif /* GUI_PROPERTIES_HPP */

