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

#ifndef CONF_PROJECT_PREFERENCES_HPP
#define CONF_PROJECT_PREFERENCES_HPP

#include <QSettings>
#include <QApplication>
#include <QFont>
#include <QString>
#include <QStringList>
#include <QSize>
#include <QPoint>
#include <QMainWindow>

#include "repositories/path_repo.hpp"
#include "repositories/project_repo.hpp"

namespace tdx {

    namespace app {

        namespace conf {

            class ProjectPreferences : public QSettings {

            public:
                ProjectPreferences()
                : QSettings(repo::ProjectRepo::Instance().preferencesConfFilePath(), QSettings::Format::IniFormat) {
                }
                
                void setProjectName(const QString& name) {
                    beginGroup("properties");
                    setValue("name", name);
                    endGroup();
                }
                
                QString projectName() {
                    beginGroup("properties");
                    QString name = value("name").toString();
                    endGroup();
                    return name;
                }
                

            };
        }
    }
}

#endif /* GUI_PROPERTIES_HPP */

