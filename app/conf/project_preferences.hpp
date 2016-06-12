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
                    setValue("name", name);
                }
                
                QString projectName() {
                    return value("name").toString();
                }
                
                void setImportImageDir(const QString& path) {
                    beginGroup("import");
                    setValue("image", path);
                    endGroup();
                }
                
                QString importImageDir() {
                    beginGroup("import");
                    QString val = value("image").toString();
                    endGroup();
                    return val;
                }
                
                void setImportMoiveDir(const QString& path) {
                    beginGroup("import");
                    setValue("movie", path);
                    endGroup();
                }
                
                QString importMovieDir() {
                    beginGroup("import");
                    QString val = value("movie").toString();
                    endGroup();
                    return val;
                }
                
                void setImportGroup(const QString& group) {
                    beginGroup("import");
                    setValue("group", group);
                    endGroup();
                }

                QString importGroup() {
                    beginGroup("import");
                    QString val = value("group").toString();
                    endGroup();
                    return val;
                }
                
                void setImportIgnorePattern(const QString& ignore) {
                    beginGroup("import");
                    setValue("ignore", ignore);
                    endGroup();
                }
                
                QString importIgnorePattern() {
                    beginGroup("import");
                    QString val = value("ignore").toString();
                    endGroup();
                    return val;
                }
                
                void setImportImageLength(int length) {
                    beginGroup("import");
                    setValue("length", length);
                    endGroup();
                }
                
                int importImageLength() {
                    beginGroup("import");
                    int val = value("length").toInt();
                    endGroup();
                    return val;
                }

            };
        }
    }
}

#endif /* GUI_PROPERTIES_HPP */

