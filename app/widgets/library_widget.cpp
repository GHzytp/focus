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

#include <QList>
#include <QMap>
#include <QTreeWidgetItem>
#include <QString>
#include <QStringList>

#include "library_widget.hpp"
#include "conf/project_images.hpp"
#include "data/parameter.hpp"

using namespace tdx::app::widget;

ImageLibraryWidget::ImageLibraryWidget(QWidget *parent)
: QTreeWidget(parent) {
    setColumnCount(2);
    
    setHeaderLabels(QStringList() << "Image Numbers" << "Original Path");
    
    load();
}

QString ImageLibraryWidget::imageNumberForItem(QTreeWidgetItem* item) {
    if(itemToImageNumbers_.contains(item)) return itemToImageNumbers_[item];
    else return QString();
}

void ImageLibraryWidget::load() {
    
    clear();
    setHeaderLabels(QStringList() << "Image Numbers" << "Original Path");
    
    QMap<QString, QStringList> groupToImages;
    QStringList images = conf::ProjectImages().images();
    for(QString image : images) {
        QString group = conf::ProjectImages().imageGroup(image);
        if(!groupToImages.contains(group)) groupToImages.insert(group, QStringList());
        groupToImages[group].append(image);
    }
      
    QList<QTreeWidgetItem *> items;
    QStringList groups = groupToImages.keys();
    for(int i=0; i<groups.size(); ++i) {
        QTreeWidgetItem* groupItem = new QTreeWidgetItem((QTreeWidget*) 0, QStringList(groups.at(i)));
        items.append(groupItem);
        for(QString image : groupToImages[groups.at(i)]) {
            QTreeWidgetItem* imageItem = new QTreeWidgetItem(groupItem);
            imageItem->setData(0, Qt::DisplayRole, image);
            
            data::Parameter::ConfigContext context;
            context.levelUp(groups.at(i));
            context.levelUp(image);
            QString imagePath = data::Parameter("imagename_original", context).value().toString();
            imageItem->setData(1, Qt::DisplayRole, imagePath);
            
            itemToImageNumbers_.insert(imageItem, image);
        }
    }
    
    insertTopLevelItems(0, items);
    expandAll();
}
