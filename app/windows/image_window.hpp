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

#ifndef PROCESS_WINDOW_HPP
#define PROCESS_WINDOW_HPP

#include <QWidget>
#include <QString>

#include "widgets/parameters_widget.hpp"

namespace tdx {
    
    namespace app {
        
        namespace window {
            
            class ImageWindow : public QWidget {
                
                Q_OBJECT
            
            public:
                
                ImageWindow(const QString& imageNumber, QWidget* parent = NULL)
                : QWidget(parent), imageNumber_(imageNumber){
                    initialize();
                }
                
                
            private:
                void initialize();
                
                widget::ParametersWidget* parametersWidget_;
                
                QString imageNumber_;
                
            };
            
        }
    }
}

#endif

