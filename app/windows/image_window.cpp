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

#include <QVBoxLayout>
#include <QLabel>

#include "image_window.hpp"
#include "data/parameter.hpp"
#include "conf/project_images.hpp"
#include "widgets/parameters_widget.hpp"

using namespace tdx::app::window;

void ImageWindow::initialize(){
    QVBoxLayout* main_layout = new QVBoxLayout(this);
    
    main_layout->addWidget(new QLabel(QString("Image: ") + imageNumber_, this));
    
    data::Parameter::ConfigContext context;
    context.levelUp(conf::ProjectImages().imageGroup(imageNumber_));
    context.levelUp(imageNumber_);
    
    parametersWidget_ = new widget::ParametersWidget(context, this);
    main_layout->addWidget(parametersWidget_);
    
    setLayout(main_layout);
}
