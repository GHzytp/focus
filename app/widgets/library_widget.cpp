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

#include <QtWidgets>

#include "library_widget.hpp"

using namespace tdx::app::widget;

ImageLibraryWidget::ImageLibraryWidget(QWidget *parent)
    : QTreeWidget(parent)
{
    QStringList labels;
    labels << tr("Title") << tr("Location");

    header()->setSectionResizeMode(QHeaderView::Stretch);
    setHeaderLabels(labels);

    folderIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirClosedIcon),
                         QIcon::Normal, QIcon::Off);
    folderIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirOpenIcon),
                         QIcon::Normal, QIcon::On);
    bookmarkIcon.addPixmap(style()->standardPixmap(QStyle::SP_FileIcon));
}

bool ImageLibraryWidget::read(QIODevice *device)
{
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!domDocument.setContent(device, true, &errorStr, &errorLine,
                                &errorColumn)) {
        QMessageBox::information(window(), tr("DOM Bookmarks"),
                                 tr("Parse error at line %1, column %2:\n%3")
                                 .arg(errorLine)
                                 .arg(errorColumn)
                                 .arg(errorStr));
        return false;
    }

    QDomElement root = domDocument.documentElement();
    if (root.tagName() != "xbel") {
        QMessageBox::information(window(), tr("DOM Bookmarks"),
                                 tr("The file is not an XBEL file."));
        return false;
    } else if (root.hasAttribute("version")
               && root.attribute("version") != "1.0") {
        QMessageBox::information(window(), tr("DOM Bookmarks"),
                                 tr("The file is not an XBEL version 1.0 "
                                    "file."));
        return false;
    }

    clear();

    disconnect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)),
               this, SLOT(updateDomElement(QTreeWidgetItem*,int)));

    QDomElement child = root.firstChildElement("folder");
    while (!child.isNull()) {
        parseFolderElement(child);
        child = child.nextSiblingElement("folder");
    }

    connect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)),
            this, SLOT(updateDomElement(QTreeWidgetItem*,int)));

    return true;
}

bool ImageLibraryWidget::write(QIODevice *device)
{
    const int IndentSize = 4;

    QTextStream out(device);
    domDocument.save(out, IndentSize);
    return true;
}

void ImageLibraryWidget::updateDomElement(QTreeWidgetItem *item, int column)
{
    QDomElement element = domElementForItem.value(item);
    if (!element.isNull()) {
        if (column == 0) {
            QDomElement oldTitleElement = element.firstChildElement("title");
            QDomElement newTitleElement = domDocument.createElement("title");

            QDomText newTitleText = domDocument.createTextNode(item->text(0));
            newTitleElement.appendChild(newTitleText);

            element.replaceChild(newTitleElement, oldTitleElement);
        } else {
            if (element.tagName() == "bookmark")
                element.setAttribute("href", item->text(1));
        }
    }
}

void ImageLibraryWidget::parseFolderElement(const QDomElement &element,
                                  QTreeWidgetItem *parentItem)
{
    QTreeWidgetItem *item = createItem(element, parentItem);

    QString title = element.firstChildElement("title").text();
    if (title.isEmpty())
        title = QObject::tr("Folder");

    item->setFlags(item->flags() | Qt::ItemIsEditable);
    item->setIcon(0, folderIcon);
    item->setText(0, title);

    bool folded = (element.attribute("folded") != "no");
    setItemExpanded(item, !folded);

    QDomElement child = element.firstChildElement();
    while (!child.isNull()) {
        if (child.tagName() == "folder") {
            parseFolderElement(child, item);
        } else if (child.tagName() == "bookmark") {
            QTreeWidgetItem *childItem = createItem(child, item);

            QString title = child.firstChildElement("title").text();
            if (title.isEmpty())
                title = QObject::tr("Folder");

            childItem->setFlags(item->flags() | Qt::ItemIsEditable);
            childItem->setIcon(0, bookmarkIcon);
            childItem->setText(0, title);
            childItem->setText(1, child.attribute("href"));
        } else if (child.tagName() == "separator") {
            QTreeWidgetItem *childItem = createItem(child, item);
            childItem->setFlags(item->flags() & ~(Qt::ItemIsSelectable | Qt::ItemIsEditable));
            childItem->setText(0, QString(30, 0xB7));
        }
        child = child.nextSiblingElement();
    }
}

QTreeWidgetItem *ImageLibraryWidget::createItem(const QDomElement &element,
                                      QTreeWidgetItem *parentItem)
{
    QTreeWidgetItem *item;
    if (parentItem) {
        item = new QTreeWidgetItem(parentItem);
    } else {
        item = new QTreeWidgetItem(this);
    }
    domElementForItem.insert(item, element);
    return item;
}
