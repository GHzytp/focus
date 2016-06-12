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

                    static QMap<int, QStringList> deduceMinMaxPairs(QStringList fields) {
                        QMap<int, QStringList> minMaxPairs;
                        bool minDefined = false;
                        bool maxDefined = false;
                        bool currentMaxDefined, currentMinDefined;
                        int k = 0;

                        foreach(QString field, fields) {
                            if (minDefined && field.contains("min", Qt::CaseInsensitive)) {
                                k++;
                                minDefined = false;
                                maxDefined = false;
                            }
                            if (maxDefined && field.contains("max", Qt::CaseInsensitive)) {
                                k++;
                                minDefined = false;
                                maxDefined = false;
                            }
                            currentMaxDefined = field.contains("max", Qt::CaseInsensitive);
                            currentMinDefined = field.contains("min", Qt::CaseInsensitive);

                            if (currentMinDefined) {
                                minMaxPairs[k].insert(0, field.section('=', -1, -1).trimmed());
                                minDefined = true;
                            }
                            if (currentMaxDefined) {
                                minMaxPairs[k].insert(1, field.section('=', -1, -1).trimmed());
                                maxDefined = true;
                            }
                        }

                        return minMaxPairs;
                    }

                };

                class ConfigContext {
                public:

                    ConfigContext(QStringList levels = QStringList())
                    : levels_(levels) {
                    }

                    QStringList levels() {
                        return levels_;
                    }

                    QString levelAt(int i) {
                        if (i < levels_.size()) return levels_[i];
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
                    if (prop == "value" || prop == "iswrong" || prop == "locked") {
                        conf::ProjectParameterConfiguration paramConfig_;
                        for (QString level : context_.levels()) paramConfig_.beginGroup(level);
                        paramConfig_.setCurrentParameter(name_);
                        int configLevel = context_.levels().size();
                        while (configLevel >= 0 && !paramConfig_.currentParameterPropertyExists(prop)) {
                            if (configLevel != 0) paramConfig_.endGroup();
                            configLevel--;
                        }
                        
                        if (configLevel < 0) return globalProperty(prop);
                        else return paramConfig_.currentParameterProperty(prop);
                    } else {
                        return globalProperty(prop);
                    }
                }

                void setProperty(const QString& prop, const QString& val) {
                    if (prop == "value" || prop == "iswrong" || prop == "locked") {
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
                    return QVariant(property("value"));
                }

                void setValue(const QVariant& val) {
                    setProperty("value", val.toString());
                }

                bool locked() {
                    bool yup = false;
                    if (property("locked").trimmed().toLower() == "yes") yup = true;
                    return yup;
                };

                void setLock(bool lock) {
                    if (lock) setProperty("locked", "yes");
                    else setProperty("locked", "no");
                };

                bool isWrong() {
                    bool yup = false;
                    if (property("iswrong").trimmed().toLower() == "yes") yup = true;
                    return yup;
                }

                void setIsWrong(bool iswrong) {
                    if (iswrong) setProperty("iswrong", "yes");
                    else setProperty("iswrong", "no");
                }


            private:

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

