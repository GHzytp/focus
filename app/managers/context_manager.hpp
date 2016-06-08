
#ifndef CONTEXT_MANAGER_HPP
#define CONTEXT_MANAGER_HPP

#include <QString>

#include "conf/parameters_configuration.hpp"
#include "repositories/path_repo.hpp"

namespace tdx {
    
    namespace app {
        
        namespace manager {
            
            class ProjectManager {
                
            public:
                ProjectManager() {}
                
                void setGroup(const QString& groupUid) {
                    
                }
                
                void setImage(const QString& Image) {
                    
                }
                
            private:
                QString currentGroup_;
                QString currentImage_;
                QString currentParameter_;
                        
            };
        }
    }
}

#endif 

