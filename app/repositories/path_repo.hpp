/* 
 * Author: Nikhil Biyani - nikhil(dot)biyani(at)gmail(dot)com
 *
 * This file is a part of 2dx.
 * 
 * 2dx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or any 
 * later version.
 * 
 * 2dx is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public 
 * License for more details <http://www.gnu.org/licenses/>.
 */

#ifndef REPO_PATH_MANAGER_HPP
#define REPO_PATH_MANAGER_HPP

#include <QDir>
#include <QString>
#include <QApplication>

namespace tdx {

    namespace app {

        namespace repo {

            class PathRepo {
                
            public:

                static QDir applicationDir() {
#ifdef Q_OS_MAC
                    return QDir(QApplication::applicationDirPath() + "/../../../");        
#else
                    return QDir(QApplication::applicationDirPath());
#endif
                }

                static QDir resourceDir() {
                    return QDir(applicationDir().absolutePath() + "/../Resource/");
                }
                
                static QDir iconsDir() {
                    return QDir(resourceDir().absolutePath() + "/icons/");
                }
                
                static QDir configDir() {
                    return QDir(resourceDir().absolutePath() + "/config/");
                }

                static QString userPreferencesConfFile() {
                    return QDir::homePath() + "/.2dx/user.preferences.conf";
                }
                
                static QString userProjectsConfFile() {
                    return QDir::homePath() + "/.2dx/user.projects.conf";
                }
                
                static QString globalParametersConfFile() {
                    return QDir::homePath() + "/.2dx/global.parameters.conf";
                }

            };
        }
    }
}

#endif 

