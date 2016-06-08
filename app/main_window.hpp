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

#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QSettings>

#include "windows/library_window.hpp"
#include "windows/merge_window.hpp"
#include "windows/process_window.hpp"

#include "dialogs/preferences.hpp"
#include "dialogs/parameters.hpp"

class QStackedWidget;
class QToolBar;
class QAction;
class QCloseEvent;

namespace tdx {

    namespace app {

        class MainWindow : public QMainWindow {
            Q_OBJECT

        public:
            MainWindow(QString projectPath, QWidget *parent = NULL)
            : QMainWindow(parent) {
                loadProject(projectPath);
                initialize();
            }

        public slots:
            void showLibraryWindow();
            void showProcessWindow();
            void showMergeWindow();
            
            void showPreferences();
            void showParameters();
            
            void openProject();
            void newProject();
            void importImages();
            
            void loadProject(const QString& projectDirPath);
            
            void closeEvent(QCloseEvent* event);
            
        private:

            void initialize();
            void setupWindows();
            void setupActions();
            void setupMenubar();
            void setupToolbar();
            
            bool userReallyWantsToQuit();
            
            bool projectLoaded_;
            
            //Main Windows
            QStackedWidget* centralWin_;
            window::LibraryWindow* libraryWin_;
            window::ProcessWindow* processWin_;
            window::MergeWindow* mergeWin_;
            
            //Dialogs
            dialog::PreferencesDialog* preferencesDialog_;
            dialog::ParametersDialog* parametersDialog_;
            
            QToolBar* mainToolbar_;
            QAction* showLibraryAct_;
            QAction* showProcessAct_;
            QAction* showMergeAct_;
            
            QAction* openProjectAct_;
            QAction* newProjectAct_;
            QAction* importImagesAct_;
            QAction* exitAct_;
            

        };

    }
}

#endif /* MAIN_WINDOW_HPP */

