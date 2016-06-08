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

#include <QApplication>
#include <QCommandLineParser>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QString>

#include "main_window.hpp"

using namespace tdx::app;

void checkCentralConfiguration() {
    
}

void initializeProject(const QString &workingDir) {
    
}

int main(int argc, char** argv) {

    //Load the application
    QApplication application(argc, argv);
    QCoreApplication::setApplicationName("2dx");
    QCoreApplication::setOrganizationName("C-CINA");
    QCoreApplication::setOrganizationDomain("c-cina.org");
    
    //Check if the central configuration is up to date;
    checkCentralConfiguration();   
    
    QCommandLineParser parser;
    parser.setApplicationDescription(QApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("project_dir", "Path of the 2dx Project to be opened.");
    parser.process(application);

    MainWindow *win;
    if (!parser.positionalArguments().isEmpty()) {
        win = new MainWindow(parser.positionalArguments().first());
    } else {
        QString workingDir = QFileDialog::getExistingDirectory(0,"Select a Project Directory", "~");
        if(workingDir.isEmpty() || !QDir(workingDir).exists()) std::exit(0);    
        win = new MainWindow(workingDir);
    }
        
    win->show();
    win->raise(); // raises the window on top of the parent widget stack
    win->activateWindow(); // activates the window an thereby putting it on top-level

    return application.exec();
}

