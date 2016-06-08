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

#include "library_window.hpp"

using namespace tdx::app::window;

LibraryWindow::LibraryWindow(QWidget* parent)
: QWidget(parent)
{
    library_widget_ = new widget::ImageLibraryWidget;

    createActions();
    setup_toolbar();
    
    main_layout_ = new QGridLayout(this);
    this->setLayout(main_layout_);
    main_layout_->addWidget(main_tool_bar_, 0, 1);
    main_layout_->addWidget(library_widget_, 0, 0);
}

void LibraryWindow::open()
{
    QString fileName =
            QFileDialog::getOpenFileName(this, tr("Open Bookmark File"),
                                         QDir::currentPath(),
                                         tr("XBEL Files (*.xbel *.xml)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("SAX Bookmarks"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    library_widget_->read(&file);
}

void LibraryWindow::saveAs()
{
    QString fileName =
            QFileDialog::getSaveFileName(this, tr("Save Bookmark File"),
                                         QDir::currentPath(),
                                         tr("XBEL Files (*.xbel *.xml)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("SAX Bookmarks"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    library_widget_->write(&file);
}

void LibraryWindow::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAsAct = new QAction(tr("&Save As..."), this);
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));
}

void LibraryWindow::setup_toolbar()
{
    main_tool_bar_ = new QToolBar(this);
    main_tool_bar_->setOrientation(Qt::Vertical);
    main_tool_bar_->addAction(openAct);
    main_tool_bar_->addAction(saveAsAct);
}
