/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "old_config_porter.hpp"
#include "parameters_configuration.hpp"

using namespace tdx::app::conf;

void OldConfigPorter::portConfigFile(QString sourceOldConfigFile, QString destinationIniConfigFile, QStringList levels) {

    ParametersConfiguration newConfig(destinationIniConfigFile);
    QString level;
    foreach(level, levels) newConfig.beginGroup(level);

    QFile data(sourceOldConfigFile);
    QHash<QString, QString> props;

    QStringList valueSearch;
    valueSearch << "LABEL" << "LEGEND" << "EXAMPLE" << "HELP" << "TYPE"
            << "RELATION" << "LOCKED" << "USERLEVEL"
            << "INHERITABLE_UPON_INIT" << "SYNC_WITH_UPPER_LEVEL"
            << "ISWRONG";

    if (!data.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "The old config file could not be located. Tried in:\n\t" << data.fileName().toStdString() << "\n";
        return;
    }

    newConfig.clear();

    QString lineData;
    QString currSection = "";
    qint64 pos = -1;
    while (!data.atEnd() && pos != data.pos()) {
        pos = data.pos();
        lineData = data.readLine().trimmed();
        lineData.remove('#');
        lineData = lineData.trimmed();

        if (lineData.toLower().startsWith("section:")) {
            lineData.remove(0, 8);
            QString section = lineData.simplified();
            currSection = section;
        }

        for (int i = 0; i < valueSearch.size(); i++) {
            if (lineData.startsWith(valueSearch[i] + ':')) {
                lineData.remove(0, valueSearch[i].size() + 1);
                props.insert(valueSearch[i].simplified().toLower(), lineData.simplified());
            }
        }

        if (lineData.toLower().startsWith("set ")) {
            int k = lineData.indexOf('=');
            if (k > 0) {
                QStringList val = lineData.split('=');

                val[0].remove(0, 4);
                val[1].remove('"');

                val[0] = val[0].simplified();
                val[1] = val[1].simplified();

                newConfig.setCurrentParameter(val[0]);
                newConfig.setCurrentParameterValue(val[1]);
                newConfig.setCurrentParameterProperty("section", currSection);
                QString prop;

                foreach(prop, props.keys()) {
                    newConfig.setCurrentParameterProperty(prop, props[prop]);
                }

                props.clear();
            }
        }
    }
    data.close();
    for (int i = 0; i < levels.size(); ++i) newConfig.endGroup();
}
