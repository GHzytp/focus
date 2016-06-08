/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   project_manager.hpp
 * Author: biyanin
 *
 * Created on June 1, 2016, 3:22 PM
 */

#ifndef PROJECT_MANAGER_HPP
#define PROJECT_MANAGER_HPP

#include <QString>
#include <QMultiHash>

namespace tdx {
    
    namespace app {
        
        namespace data {
            
            class Project {
                
            public:
                Project();
                
            private:
                
                //Properties
                QString name_;
                QString path_;
                
                QMultiHash<QString, Image>* parameters_;
                
                
            };
        }
    }
}


#endif /* PROJECT_MANAGER_HPP */

