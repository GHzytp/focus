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

#ifndef ICON_MANAGER_HPP
#define ICON_MANAGER_HPP

#include <iostream>
#include <QString>
#include <QStringList>
#include <QIcon>

#include "path_repo.hpp"

namespace tdx {

    namespace app {

        namespace repo {

            class IconRepository {
            public:

                static QIcon get(const QString& name) {
                    QDir directory(PathRepo::iconsDir());
                    if (!directory.exists()) {
                        std::cerr << "CRITICAL! Icons directory does not exist!!\n";
                        std::cerr << "Tried to locate:\n\t" << directory.absolutePath().toStdString() << std::endl;
                    }

                    QIcon icon = QIcon();
                    QString entry, type;

                    foreach(entry, directory.entryList(QStringList() << name+QString("*"), QDir::Files | QDir::NoDotAndDotDot, QDir::Unsorted)) {
                        if (entry.contains(QRegExp(".*\\-..\\.png$"))) {
                            type = entry.section(".png", 0, 0).section("-", 1, 1).trimmed().toLower();
                            if (type == "ad") icon.addPixmap(directory.canonicalPath() + "/" + entry, QIcon::Active, QIcon::On);
                            if (type == "id") icon.addPixmap(directory.canonicalPath() + "/" + entry, QIcon::Normal, QIcon::On);
                            if (type == "au") icon.addPixmap(directory.canonicalPath() + "/" + entry, QIcon::Active, QIcon::Off);
                            if (type == "iu") icon.addPixmap(directory.canonicalPath() + "/" + entry, QIcon::Normal, QIcon::Off);
                        } else if (entry.contains(".png", Qt::CaseInsensitive)) {
                            icon.addPixmap(directory.canonicalPath() + "/" + entry);
                        }
                    }

                    if(icon.isNull()) {
                        std::cerr << "No icon present with requested name: " << name.toStdString() << std::endl;
                    }
                    
                    return icon;
                };
            };
        }
    }
}

#endif 

