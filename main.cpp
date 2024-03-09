#include "dashboard.h"

#include <QApplication>
#include <QJsonDocument>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication m_appA(argc, argv);            // Creates an instance of QApplication
    Dashboard m_wndDash;                        // Creates an instance of Dashboard
    m_wndDash.show();                           // Shows dashboard
    return m_appA.exec();                       // Starts and returns main event loop
}
