/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   new_project.hpp
 * Author: biyanin
 *
 * Created on June 13, 2016, 12:46 PM
 */

#ifndef NEW_PROJECT_DIALOG_HPP
#define NEW_PROJECT_DIALOG_HPP

#include <QInputDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QDir>
#include <QListWidget>
#include <QGridLayout>
#include <QMessageBox>

#include <widgets/browser_widget.hpp>
#include <widgets/edit_set_widget.hpp>

#include <conf/user_projects.hpp>
#include <conf/project_preferences.hpp>

#include <repositories/project_repo.hpp>

namespace tdx {

    namespace app {

        namespace dialog {

            class NewProjectDialog : public QInputDialog {

                Q_OBJECT

            public:

                NewProjectDialog(QWidget* parent = 0)
                : QInputDialog(parent) {
                    setWindowTitle("Setup new 2DX project");
                    setModal(true);

                    projectPathBrowser = new widget::BrowserWidget(widget::BrowserWidget::BrowseType::DIRECTORY);
                    projectNameEdit = new QLineEdit();
                    projectNameEdit->setFrame(false);

                    QFormLayout* layout = new QFormLayout;
                    layout->setRowWrapPolicy(QFormLayout::WrapAllRows);
                    layout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
                    layout->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
                    layout->setLabelAlignment(Qt::AlignRight);
                    layout->addRow("Project Name", projectNameEdit);
                    layout->addRow("Project Directory", projectPathBrowser);

                    setLayout(layout);
                }

                void accept() override {
                    if (QDir(projectPathBrowser->path() + "/.2dx_project").exists()) {
                        QMessageBox::warning(this, "Project Exists!", "This folder already has 2DX configuration files");
                    } else {
                        repo::ProjectRepo::Instance().setProjectPath(projectPathBrowser->path());
                        conf::ProjectPreferences().setProjectName(projectNameEdit->text());
                        QDir dir(projectPathBrowser->path());
                        dir.mkdir("merge");
                        dir.mkdir("images");
                        dir.mkpath("merge/proc");
                        dir.mkpath("merge/LOGS");
                    }
                    conf::UserProjects().addProjectPath(projectPathBrowser->path());
                    QDialog::accept();
                }

            private:
                widget::BrowserWidget* projectPathBrowser;
                QLineEdit* projectNameEdit;
            };
        }
    }
}

#endif /* NEW_PROJECT_HPP */

