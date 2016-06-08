/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   user_projects.hpp
 * Author: biyanin
 *
 * Created on June 7, 2016, 1:04 PM
 */

#ifndef USER_PROJECTS_HPP
#define USER_PROJECTS_HPP

#include <QSettings>
#include <QApplication>
#include <QFont>
#include <QString>
#include <QStringList>

namespace tdx {

    namespace app {

        namespace conf {

            class UserProjects : public QSettings {

            public:
                UserProjects()
                : QSettings(repo::PathRepo::userProjectsConfFile, QSettings::Format::IniFormat) {
                }

                void addProjectPath(const QString& path) {
                    QStringList paths = projectPaths();
                    paths.push_front(path);
                    clear();
                    beginWriteArray("recents");
                    for (int i = 0; i < paths.size(); ++i) {
                        setArrayIndex(i);
                        setValue("userName", paths.at(i));
                    }
                    endArray();
                }

                QStringList projectPaths() {
                    QStringList paths;
                    int size = beginReadArray("recents");
                    for (int i = 0; i < size; ++i) {
                        setArrayIndex(i);
                        paths << value("path").toString();
                    }
                    endArray();
                    return paths;
                }


            };
        }
    }
}

#endif /* USER_PROJECTS_HPP */

