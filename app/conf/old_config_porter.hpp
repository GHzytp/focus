/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   old_config_porter.hpp
 * Author: biyanin
 *
 * Created on June 7, 2016, 11:38 AM
 */

#ifndef OLD_CONFIG_PORTER_HPP
#define OLD_CONFIG_PORTER_HPP

#include <QObject>
#include <QString>
#include <QStringList>
#include <QFile>


namespace tdx {
    
    namespace app {
        
        namespace conf {
            
            class OldConfigPorter {
               
            public:
                static void portConfigFile(QString sourceOldConfigFile, 
                                      QString destinationIniConfigFile,
                                      QStringList levels = QStringList());
                
            };
        }
    }
}

#endif /* OLD_CONFIG_PORTER_HPP */

