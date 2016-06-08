
#ifndef PARAMETER_VALIDATOR_HPP
#define PARAMETER_VALIDATOR_HPP

#include <QString>
#include <QStringList>
#include <QDir>
#include <QFileInfo>
#include <QVariant>

namespace tdx {
    
    namespace app {
        
        namespace validator {
            
            class ParameterValidator {
            
            public:
                static QStringList valueErrors(data::Parameter::TypeInfo info, const QString& value) {
                    QStringList errorMsg_;
                    if(info.type == data::Parameter::Type::DIRECTORY && !QDir(value).exists()) {
                        errorMsg_ << QString("The directory used does not exit: ") + value + QString("\n");
                    }
                    else if(info.type == data::Parameter::Type::FILE && !QFileInfo(value).exists()) {
                        errorMsg_ << QString("The file used does not exit: ") + value + QString("\n");;
                    }
                    else if(info.type == data::Parameter::Type::DROP_DOWN) {
                        if(!(QVariant(value).canConvert<int>())) {
                            errorMsg_ << QString("The drop down index can't be converted to int\n"); 
                        }
                        else if(value.toInt() >= info.properties.size()) {
                            errorMsg_ << QString("The drop down index exceeds it's size \n");
                        }
                    }
                    else if(info.type == data::Parameter::Type::FLOAT && !(QVariant(value).canConvert<float>())) {
                            errorMsg_ << QString("The provided value cannot be converted to float: ") + value + QString("\n");
                    }
                    else if(info.type == data::Parameter::Type::INT && !(QVariant(value).canConvert<int>())) {  
                            errorMsg_ << QString("The provided value cannot be converted to int: ") + value + QString("\n");
                    }
                    else if(info.type == data::Parameter::Type::BOOL) {
                        if(value != "y" || value != "n" || value != "yes" || value != "no" || value != "0" || value != "1" ) {
                            errorMsg_ << QString("The provided value cannot be converted to bool: ") + value + QString("\n");
                        }
                    }
                    
                    return errorMsg_;
                }

                
            };
        }
    }
}

#endif /* PARAMETER_VALIDATOR_HPP */

