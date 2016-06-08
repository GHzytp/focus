/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parameter.hpp
 * Author: biyanin
 *
 * Created on May 25, 2016, 4:55 PM
 */

#ifndef PARAMETER_HPP
#define PARAMETER_HPP

#include <QString>
#include <QStringList>
#include <QVariant>
#include <QHash>
#include <QSharedPointer>

#include "conf/parameters_configuration.hpp"

namespace tdx {

    namespace app {

        namespace data {

            class Parameter {
            public:

                enum class ConfigLevel {
                    GLOBAL = -1,
                    PROJECT = 0,
                    GROUP = 1,
                    IMAGE = 2
                };

                enum class Type {
                    NONE,
                    TEXT_EDIT,
                    DIRECTORY,
                    FILE,
                    DROP_DOWN,
                    FLOAT,
                    BOOL,
                    INT
                };

                class TypeInfo {
                public:

                    Type type;
                    int count;
                    QStringList properties;

                    TypeInfo() {
                    };

                    TypeInfo(QString typeStr) {
                        type = getType(typeStr);
                        count = getCount(typeStr);
                        properties = getProperties(typeStr);
                    }

                    static Parameter::Type getType(const QString& typeStr) {
                        QString typeStr_ = typeStr.trimmed().toLower();
                        if (typeStr_ == "") return Type::NONE;
                        else if (typeStr_.startsWith("dir")) return Type::DIRECTORY;
                        else if (typeStr_.startsWith("fil")) return Type::FILE;
                        else if (typeStr_.startsWith("dro")) return Type::DROP_DOWN;
                        else if (typeStr_.startsWith("flo")) return Type::FLOAT;
                        else if (typeStr_.startsWith("two")) return Type::FLOAT;
                        else if (typeStr_.startsWith("thr")) return Type::FLOAT;
                        else if (typeStr_.startsWith("fou")) return Type::FLOAT;
                        else if (typeStr_.startsWith("boo")) return Type::BOOL;
                        else if (typeStr_.startsWith("int")) return Type::INT;
                        else if (typeStr_.startsWith("tex")) return Type::TEXT_EDIT;
                        else {
                            std::cerr << "CRITICAL: Parameter type not understood: \n" << typeStr.toStdString() << "\n";
                            return Type::NONE;
                        }
                    }

                    static int getCount(const QString& typeStr) {
                        QString typeStr_ = typeStr.trimmed().toLower();
                        if (typeStr_.startsWith("two")) return 2;
                        else if (typeStr_.startsWith("thr")) return 3;
                        else if (typeStr_.startsWith("fou")) return 4;
                        else return 1;
                    }

                    static QStringList getProperties(const QString& typeStr) {
                        QStringList options = typeStr.trimmed().split('"');
                        if (options.count() < 2) return QStringList();
                        else {
                            return options[1].split(';');
                        }
                    }

                };

                class ConfigContext {
                public:
                    ConfigContext(QStringList levels = QStringList()) 
                    : levels_(levels) {}
                    
                    QStringList levels() {
                        return levels_;
                    }
                    
                    QString levelAt(int i) {
                        if(i < levels_.size()) return levels_[i];
                        else return QString();
                    }

                    void levelUp(const QString& level) {
                        levels_.append(level);
                    }

                    void levelDown() {
                        levels_.removeLast();
                    }

                    void resetLevels() {
                        levels_.clear();
                    }
                private:
                    QStringList levels_;
                };

                Parameter(QString name, ConfigContext context = ConfigContext())
                : name_(name), context_(context) {
                }

                QString name() const {
                    return name_;
                }

                ConfigContext context() {
                    return context_;
                }

                void setContext(ConfigContext context) {
                    context_ = context;
                }

                TypeInfo typeInfo() {
                    return TypeInfo(property("type"));
                }

                QString property(const QString& prop) {
                    //Check for the changable properties
                    //if not return global otherwise return at correct config location
                    if (prop == "iswrong" || prop == "locked") {
                        ConfigLevel configFileLevel_ = resetConfigFileLevel();
                        if (configFileLevel_ == ConfigLevel::GLOBAL) {
                            return globalProperty(prop);
                        } else {
                            conf::ProjectParameterConfiguration paramConfig;
                            paramConfig.setCurrentParameter(name_);
                            for (int i = 1; i <= static_cast<int> (configFileLevel_); ++i) { 
                                paramConfig.beginGroup(context_.levelAt(i--));
                            }
                            return paramConfig.currentParameterProperty(prop);
                        }
                    } else {
                        return globalProperty(prop);
                    }
                }

                void setProperty(const QString& prop, const QString& val) {
                    if (prop == "iswrong" || prop == "locked") {
                        if (property(prop).toLower() != val.toLower()) {
                            conf::ProjectParameterConfiguration paramConfig;
                            QString level;
                            foreach(level, context_.levels()) paramConfig.beginGroup(level);
                            paramConfig.setCurrentParameter(name_);
                            paramConfig.setCurrentParameterProperty(prop, val);
                        }
                    }
                }

                QVariant value() {
                    ConfigLevel configFileLevel_ = resetConfigFileLevel();

                    if (configFileLevel_ == ConfigLevel::GLOBAL) {
                        conf::GlobalParameterConfiguration globalConfig;
                        globalConfig.setCurrentParameter(name_);
                        return globalConfig.currentParameterValue();
                    } else {
                        conf::ProjectParameterConfiguration paramConfig;
                        paramConfig.setCurrentParameter(name_);
                        for (int i = 1; i <= static_cast<int> (configFileLevel_); ++i) {
                            paramConfig.beginGroup(context_.levelAt(i--));
                        }
                        return paramConfig.currentParameterValue();
                    }

                }

                void setValue(const QVariant& val) {
                    if (value() != val) {
                        conf::ProjectParameterConfiguration paramConfig;
                        QString level;
                        foreach(level, context_.levels()) paramConfig.beginGroup(level);
                        paramConfig.setCurrentParameter(name_);
                        paramConfig.setCurrentParameterValue(val);
                    }
                }

                bool isLocked() {
                    QString locked = property("locked");
                    if (locked.toLower() == "yes") return true;
                    else return false;
                };

                void setLock(bool lock) {
                    QString locked = "no";
                    if (lock) locked = "yes";
                    setProperty("locked", locked);
                };


            private:

                ConfigLevel resetConfigFileLevel() {
                    conf::ProjectParameterConfiguration paramConfig;
                    QString level;
                    foreach(level, context_.levels()) paramConfig.beginGroup(level);
                    paramConfig.setCurrentParameter(name_);
                    int configLevel = context_.levels().size();
                    while (configLevel >= 0 && !paramConfig.currentParameterExists()) {
                        if (configLevel != 0) paramConfig.endGroup();
                        configLevel--;
                    }
                    ConfigLevel configFileLevel_ = static_cast<ConfigLevel> (configLevel);
                    return configFileLevel_;
                }

                QString globalProperty(const QString& prop) {
                    conf::GlobalParameterConfiguration globalConfig;
                    globalConfig.setCurrentParameter(name_);
                    return globalConfig.currentParameterProperty(prop);
                }

                QString name_;
                ConfigContext context_;

            };



        }
    }
}

#endif /* PARAMETER_HPP */

