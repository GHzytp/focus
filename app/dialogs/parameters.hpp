
#ifndef PARAMETERS_DIALOG_HPP
#define PARAMETERS_DIALOG_HPP

#include <QDialog>
#include <QGridLayout>

#include "widgets/parameters_widget.hpp"

namespace tdx {

    namespace app {

        namespace dialog {

            class ParametersDialog : public QDialog {

                Q_OBJECT

            public:

                ParametersDialog() {
                    setWindowTitle(tr("Project Parameters"));
                    
                    widget::ParametersWidget* wid = new widget::ParametersWidget(0);
                                     
                    QGridLayout* layout = new QGridLayout(this);
                    layout->addWidget(wid);
                    setLayout(layout);
                }

            };
        }
    }
}

#endif 
