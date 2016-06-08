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

#ifndef LIBRARY_WIDGET_HPP
#define LIBRARY_WIDGET_HPP

#include <QSortFilterProxyModel>
#include <QDir>
#include <QDomDocument>
#include <QHash>
#include <QIcon>
#include <QTreeWidget>

namespace tdx {

    namespace app {

        namespace widget {

            class ImageLibraryWidget : public QTreeWidget {
                Q_OBJECT

            public:
                ImageLibraryWidget(QWidget *parent = NULL);

                bool read(QIODevice *device);
                bool write(QIODevice *device);

            private slots:
                void updateDomElement(QTreeWidgetItem *item, int column);

            private:
                void parseFolderElement(const QDomElement &element,
                        QTreeWidgetItem *parentItem = 0);
                QTreeWidgetItem *createItem(const QDomElement &element,
                        QTreeWidgetItem *parentItem = 0);

                QDomDocument domDocument;
                QHash<QTreeWidgetItem *, QDomElement> domElementForItem;
                QIcon folderIcon;
                QIcon bookmarkIcon;
            };
        }
    }
}


#endif /* LIBRARY_WIDGET_HPP */

