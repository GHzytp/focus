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

#ifndef LIBRARY_WINDOW_HPP
#define LIBRARY_WINDOW_HPP

#include <QWidget>
#include <QToolBar>
#include <QGridLayout>

#include "widgets/library_widget.hpp"

namespace tdx {

    namespace app {

        namespace window {

            class LibraryWindow : public QWidget {

                Q_OBJECT

            public:
                LibraryWindow(QWidget* parent = NULL);

            public slots:
                void open();
                void saveAs();

            private:
                void createActions();
                void setup_toolbar();

                widget::ImageLibraryWidget* library_widget_;

                QAction *openAct;
                QAction *saveAsAct;

                QGridLayout* main_layout_;
                QToolBar* main_tool_bar_;

            };

        }
    }
}

#endif /* LIBRARY_WINDOW_HPP */

