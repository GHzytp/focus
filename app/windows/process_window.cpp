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

#include <QGridLayout>
#include <QLabel>

#include "process_window.hpp"

using namespace tdx::app::window;

void ProcessWindow::initialize(){
    QGridLayout* main_layout = new QGridLayout(this);
    this->setLayout(main_layout);
    main_layout->addWidget(new QLabel(QString("I'm a Process window processing image: ") + imageNumber_, this));
    //TODO Add widgets and stuff
}
