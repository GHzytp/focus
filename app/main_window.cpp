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
#include <QProcess>

#include "main_window.hpp"

#include "repositories/icon_repo.hpp"
#include "repositories/path_repo.hpp"
#include "repositories/project_repo.hpp"

#include "conf/user_preferences.hpp"
#include "conf/parameters_configuration.hpp"
#include "conf/user_projects.hpp"

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

}

void MainWindow::setupMenubar() {
    QMenu* fileMenu = new QMenu("File");

    QAction* openProjectAct_ = new QAction("Open Project", this);
    openProjectAct_->setShortcut(tr("Ctrl+O"));
    connect(openProjectAct_, SIGNAL(triggered()), this, SLOT(openProject()));
    fileMenu->addAction(openProjectAct_);

    QStringList recents = conf::UserProjects().projectPaths();
    if (recents.count() > 0) {
        QMenu* openRecentsMenu = new QMenu("Recent Projects");

        foreach(QString recent, recents) {
            if (recent != "") {
                QAction* act = new QAction(recent, this);
                connect(openProjectAct_, &QAction::triggered,
                        [ = ] (bool){openProject(recent);});
                openRecentsMenu->addAction(act);
            }
        }
        fileMenu->addMenu(openRecentsMenu);
    }

    QAction* importImagesAct_ = new QAction("Import Images", this);
    importImagesAct_->setShortcut(tr("Ctrl+I"));
    connect(importImagesAct_, SIGNAL(triggered()), this, SLOT(importImages()));
    fileMenu->addAction(importImagesAct_);

    QAction* exitAct_ = new QAction("Quit", this);
    exitAct_->setShortcut(tr("Ctrl+Q"));
    connect(exitAct_, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
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
    QProcess::startDetached(repo::PathRepo::applicationExecutable());
}

void MainWindow::openProject(const QString& projectPath) {
    QProcess::startDetached(repo::PathRepo::applicationExecutable() + " " + projectPath);
}

void MainWindow::newProject(const QString& projectPath) {
    quint32 choice = QMessageBox::question(NULL,
            "Confirm Create new Project?",
            "No configuration data found in:\n" + projectPath + "\n\nCreate new config files in this directory?",
            "Create", "Cancel", QString(), 0, 1);

    if (choice) qApp->closeAllWindows();

    QDir dir(projectPath);
    dir.mkdir("merge");
    dir.mkdir("images");
    dir.mkpath("merge/proc");
    dir.mkpath("merge/LOGS");
}

void MainWindow::importImages() {
    wizard::ImportImagesWizard* importWizard_ = new wizard::ImportImagesWizard(this);
    importWizard_->setAttribute(Qt::WA_DeleteOnClose);
    connect(importWizard_, &wizard::ImportImagesWizard::imagesImported,
            libraryWin_, &window::LibraryWindow::load);
    importWizard_->showNormal();
}

void MainWindow::loadProject(const QString& projectPath) {
    repo::ProjectRepo::Instance().setProjectPath(projectPath);

    if (!QFileInfo(projectPath + "/.2dx_project").isDir()) {

    }

    if (!conf::UserProjects().projectPaths().contains(projectPath)) {
        conf::UserProjects().addProjectPath(projectPath);
    }

}

void MainWindow::showPreferences() {
    if (!preferencesDialogInit_) {
        preferencesDialogInit_ = true;
        preferencesDialog_ = new dialog::PreferencesDialog(this);
    }
    preferencesDialog_->showNormal();
}

void MainWindow::showParameters() {
    if (!parametersDialogInit_) {
        parametersDialogInit_ = true;
        parametersDialog_ = new dialog::ParametersDialog(this);
    }
    parametersDialog_->showNormal();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    conf::UserPreferences().saveCurrentFontSettings();
    conf::UserPreferences().saveWindowPreferences(this);
    event->accept();
}

bool MainWindow::userReallyWantsToQuit() {
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

