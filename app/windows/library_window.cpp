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

void LibraryWindow::load() {
    library_widget_->load();
}

void LibraryWindow::createActions()
{
    loadAct = new QAction(tr("&Reload"), this);
    connect(loadAct, SIGNAL(triggered()), this, SLOT(load()));
}

void LibraryWindow::setup_toolbar()
{
    main_tool_bar_ = new QToolBar(this);
    main_tool_bar_->setOrientation(Qt::Vertical);
    main_tool_bar_->addAction(loadAct);
}
