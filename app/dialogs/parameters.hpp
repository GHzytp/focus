
#ifndef PARAMETERS_DIALOG_HPP
#define PARAMETERS_DIALOG_HPP

#include <QDialog>
#include <QScrollArea>
#include <QGridLayout>

#include "widgets/parameters_widget.hpp"

namespace tdx {

    namespace app {

        namespace dialog {

            class ParametersDialog : public QDialog {

                Q_OBJECT

            public:

                ParametersDialog() {
                    QScrollArea *window = new QScrollArea(this);
                    window->setWidgetResizable(true);
                    window->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
                    
                    widget::ParametersWidget* wid = new widget::ParametersWidget(0);
                    window->setWidget(wid);
                    
                    setWindowTitle(tr("Project Parameters"));
                    
                    QGridLayout* layout = new QGridLayout(this);
                    setLayout(layout);
                    
                    layout->addWidget(window);
                }

            };
        }
    }
}

#endif 
