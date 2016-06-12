/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   project_repo.hpp
 * Author: biyanin
 *
 * Created on June 7, 2016, 1:16 PM
 */

#ifndef PROJECT_REPO_HPP
#define PROJECT_REPO_HPP

#include <iostream>
#include <QString>

namespace tdx {

    namespace app {

        namespace repo {

            class ProjectRepo {
            public:

                static ProjectRepo& Instance() {
                    static ProjectRepo instance_;
                    return instance_;
                }

                QString projectPath() const {
                    if(projectPath_ == "") {
                        std::cerr << "CRITICAL: The project path is still not set!!\n";
                    }
                    return projectPath_;
                }

                void setProjectPath(const QString& path) {
                    projectPath_ = path;
                }
                
                QString imagesDir() {
                    return projectPath()+"/images/";
                }
                
                QString parameterConfFilePath() {
                    return projectPath()+"/.2dx_project/project.parameters.conf";
                }
                
                QString preferencesConfFilePath() {
                    return projectPath()+"/.2dx_project/project.preferences.conf";
                }
                
                QString imagesConfFilePath() {
                    return projectPath()+"/.2dx_project/project.images.conf";
                }
                    

            private:

                ProjectRepo() {}

                QString projectPath_;

            };
        }
    }
}

#endif 
