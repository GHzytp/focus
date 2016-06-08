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

#include <QStackedWidget>
#include <QToolBar>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QFileInfo>
#include <QFileDialog>
#include <QCloseEvent>
#include <QMessageBox>

#include "main_window.hpp"

#include "repositories/icon_repo.hpp"
#include "repositories/path_repo.hpp"
#include "repositories/project_repo.hpp"

#include "conf/user_preferences.hpp"
#include "conf/parameters_configuration.hpp"

using namespace tdx::app;

void MainWindow::initialize() {
    setupWindows();
    setupActions();
    setupMenubar();
    setupToolbar();

    setUnifiedTitleAndToolBarOnMac(true);
    
    conf::UserPreferences().loadAllFontSettings();
    conf::UserPreferences().loadWindowPreferences(this);
    
    conf::GlobalParameterConfiguration().syncGlobalParameters();
    
    preferencesDialog_ = new dialog::PreferencesDialog();
    parametersDialog_ = new dialog::ParametersDialog();
    
    showLibraryWindow();
}

void MainWindow::setupWindows() {
    centralWin_ = new QStackedWidget(this);
    libraryWin_ = new window::LibraryWindow(centralWin_);
    processWin_ = new window::ProcessWindow(centralWin_);
    mergeWin_ = new window::MergeWindow(centralWin_);

    centralWin_->addWidget(libraryWin_);
    centralWin_->addWidget(processWin_);
    centralWin_->addWidget(mergeWin_);
    setCentralWidget(centralWin_);
}

void MainWindow::setupActions() {
    showLibraryAct_ = new QAction(repo::IconRepository::get("library"), tr("Library"), this);
    showLibraryAct_->setShortcut(tr("Ctrl+L"));
    connect(showLibraryAct_, SIGNAL(triggered()), this, SLOT(showLibraryWindow()));

    showProcessAct_ = new QAction(repo::IconRepository::get("process"), tr("Process"), this);
    showProcessAct_->setShortcut(tr("Ctrl+P"));
    connect(showProcessAct_, SIGNAL(triggered()), this, SLOT(showProcessWindow()));

    showMergeAct_ = new QAction(repo::IconRepository::get("merge"), tr("Merge"), this);
    showMergeAct_->setShortcut(tr("Ctrl+M"));
    connect(showMergeAct_, SIGNAL(triggered()), this, SLOT(showMergeWindow()));

    openProjectAct_ = new QAction("Open Project", this);
    openProjectAct_->setShortcut(tr("Ctrl+O"));
    connect(openProjectAct_, SIGNAL(triggered()), this, SLOT(openProject()));

    newProjectAct_ = new QAction("New Project", this);
    newProjectAct_->setShortcut(tr("Ctrl+N"));
    connect(newProjectAct_, SIGNAL(triggered()), this, SLOT(newProject()));

    importImagesAct_ = new QAction("Import Images", this);
    importImagesAct_->setShortcut(tr("Ctrl+I"));
    connect(importImagesAct_, SIGNAL(triggered()), this, SLOT(importImages()));

    exitAct_ = new QAction("Quit", this);
    exitAct_->setShortcut(tr("Ctrl+Q"));
    connect(exitAct_, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

}

void MainWindow::setupMenubar() {
    QMenu *fileMenu = new QMenu("File");
    fileMenu->addAction(openProjectAct_);
    fileMenu->addAction(newProjectAct_);
    fileMenu->addAction(importImagesAct_);
    fileMenu->addAction(exitAct_);
    
    QMenu *optionsMenu = new QMenu("Options");
    
    QAction* preferencesAct = new QAction("Preferences", this);
    connect(preferencesAct, SIGNAL(triggered()), this, SLOT(showPreferences()));
    optionsMenu->addAction(preferencesAct);
    
    QAction* parametersAct = new QAction("Parameters", this);
    connect(parametersAct, SIGNAL(triggered()), this, SLOT(showParameters()));
    optionsMenu->addAction(parametersAct);
    
    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionsMenu);
    
}

void MainWindow::setupToolbar() {
    mainToolbar_ = new QToolBar(this);
    mainToolbar_->setIconSize(QSize(32, 32));
    mainToolbar_->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    mainToolbar_->addAction(showLibraryAct_);
    mainToolbar_->addAction(showProcessAct_);
    mainToolbar_->addAction(showMergeAct_);

    addToolBar(mainToolbar_);
}

void MainWindow::showLibraryWindow() {
    centralWin_->setCurrentWidget(libraryWin_);
}

void MainWindow::showProcessWindow() {
    centralWin_->setCurrentWidget(processWin_);
}

void MainWindow::showMergeWindow() {
    centralWin_->setCurrentWidget(mergeWin_);
}

void MainWindow::openProject() {
    
}

void MainWindow::newProject() {

}

void MainWindow::importImages() {

}

void MainWindow::loadProject(const QString& projectPath) {
    repo::ProjectRepo::Instance().setProjectPath(projectPath);
}

void MainWindow::showPreferences() {
    if(preferencesDialog_ == NULL) preferencesDialog_ = new dialog::PreferencesDialog();
    preferencesDialog_->showNormal();
}

void MainWindow::showParameters() {
    if(parametersDialog_ == NULL) parametersDialog_ = new dialog::ParametersDialog();
    parametersDialog_->showNormal();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (userReallyWantsToQuit()) {
        conf::UserPreferences().saveCurrentFontSettings();
        conf::UserPreferences().saveWindowPreferences(this);
        event->accept();
    } else {
        event->ignore();
    }
}

bool MainWindow::userReallyWantsToQuit()
{
    const QMessageBox::StandardButton ret
        = QMessageBox::warning(this, tr("Exit"),
                               tr("Are you sure you want to quit?"),
                               QMessageBox::Yes | QMessageBox::Discard | QMessageBox::Cancel);
    switch (ret) {
    case QMessageBox::Yes:
        return true;
    case QMessageBox::Cancel:
        return false;
    default:
        break;
    }
    return true;
}

