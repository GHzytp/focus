/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   open_project_wizard.hpp
 * Author: biyanin
 *
 * Created on June 13, 2016, 12:05 PM
 */

#ifndef OPEN_PROJECT_WIZARD_HPP
#define OPEN_PROJECT_WIZARD_HPP

#include <QWizard>
#include <QWizardPage>
#include <QLineEdit>
#include <QFormLayout>
#include <QDir>
#include <QListWidget>
#include <QGridLayout>
#include <QAbstractItemView>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>

#include <widgets/browser_widget.hpp>
#include <widgets/edit_set_widget.hpp>

#include <conf/user_projects.hpp>
#include <conf/project_preferences.hpp>

#include <repositories/project_repo.hpp>

namespace tdx {

    namespace app {

        namespace wizard {

            class OpenProjectWizard : public QWizard {

                Q_OBJECT

            public:

                OpenProjectWizard(QWidget* parent = 0)
                : QWizard(parent) {

                    optionsPage_ = new OptionsPage(this);
                    addPage(optionsPage_);
                    setWindowTitle(tr("Open Project"));
                    setModal(true);
                }

                void accept() override {
                    emit projectSelected(optionsPage_->projectPath());
                    QDialog::accept();
                }

                void reject() override {
                    qApp->closeAllWindows();
                }


            signals:

                void projectSelected(const QString& projectPath);

            private:

                class OptionsPage : public QWizardPage {
                public:

                    OptionsPage(QWidget* parent)
                    : QWizardPage(parent) {

                        setTitle("Open project");
                        setSubTitle("Select the project from list or create new project");

                        QLabel* label = new QLabel("Available Projects");
                        QPushButton* createProject = new QPushButton("New Project");
                        connect(createProject, &QPushButton::clicked,
                                [ = ](){
                            createNewProject();
                        });

                        listWidget_ = new QListWidget(this);
                        listWidget_->setSelectionMode(QAbstractItemView::SingleSelection);

                        QGridLayout* layout = new QGridLayout;
                        layout->addWidget(label, 0, 0, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
                        layout->addWidget(createProject, 0, 1, 1, 1, Qt::AlignRight | Qt::AlignVCenter);
                        layout->addWidget(listWidget_, 1, 0, 1, 2);

                        updateListWiget();

                        setLayout(layout);

                    }

                    QString projectPath() {
                        if (listWidget_->selectedItems().isEmpty()) return QString();
                        else return listWidget_->selectedItems()[0]->data(Qt::DisplayRole).toString();
                    }

                    bool validatePage() override {
                        if (listWidget_->selectedItems().isEmpty()) {
                            QMessageBox::information(this, "Project not selected.", "The project is not selected, please select one from the list");
                            return false;
                        } else {
                            return true;
                        }
                    }

                private:
                    QListWidget* listWidget_;

                    void updateListWiget() {
                        listWidget_->clear();
                        listWidget_->insertItems(0, conf::UserProjects().projectPaths());
                    }

                    void createNewProject() {
                        QString projectDir = QFileDialog::getExistingDirectory(this, "Select a Project Directory");
                        if (projectDir.isEmpty() || !QDir(projectDir).exists()) return;

                        conf::UserProjects().addProjectPath(projectDir);
                        
                        if (QDir(projectDir + "/.2dx_project").exists()) {
                            QMessageBox::warning(this, "Project Exists!", "This folder already has 2DX configuration files");
                            return;
                        }
                        
                        QDir dir(projectDir);
                        dir.mkdir(".2dx_project");
                        dir.mkdir("merge");
                        dir.mkdir("images");
                        dir.mkpath("merge/proc");
                        dir.mkpath("merge/LOGS");
                        
                        bool ok;
                        QString projectName = QInputDialog::getText(this, "Project Name", "Enter a name for the project", QLineEdit::Normal,
                                                "image_folder", &ok);

                        if (ok && !projectName.isEmpty()) {
                            repo::ProjectRepo::Instance().setProjectPath(projectDir);
                            conf::ProjectPreferences().setProjectName(projectName);
                        }

                        updateListWiget();
                        
                    }

                };

                OptionsPage* optionsPage_;

            };
        }
    }
}

#endif /* OPEN_PROJECT_WIZARD_HPP */

