#include "dashboard.h"

#include <QApplication>
#include <QJsonDocument>

using namespace std;

int main(int argc, char *argv[])
{/*
    //QByteArray data="{\"session_key\":9472,\"meeting_key\":1229,\"broadcast_name\":\"L HAMILTON\",\"country_code\":\"GBR\",\"first_name\":\"Lewis\",\"full_name\":\"Lewis HAMILTON\",\"headshot_url\":\"https://media.formula1.com/d_driver_fallback_image.png/content/dam/fom-website/drivers/L/LEWHAM01_Lewis_Hamilton/lewham01.png.transform/1col/image.png\",\"last_name\":\"Hamilton\",\"driver_number\":44,\"team_colour\":\"27f4d2\",\"team_name\":\"Mercedes\",\"name_acronym\":\"HAM\"},{\"session_key\":9472,\"meeting_key\":1229,\"broadcast_name\":\"G RUSSELL\",\"country_code\":\"GBR\",\"first_name\":\"George\",\"full_name\":\"George RUSSELL\",\"headshot_url\":\"https://media.formula1.com/d_driver_fallback_image.png/content/dam/fom-website/drivers/G/GEORUS01_George_Russell/georus01.png.transform/1col/image.png\",\"last_name\":\"Russell\",\"driver_number\":63,\"team_colour\":\"27f4d2\",\"team_name\":\"Mercedes\",\"name_acronym\":\"RUS\"}";
    QByteArray data = "{\"session_key\":9472,\"meeting_key\":1229,\"broadcast_name\":\"L HAMILTON\",\"country_code\":\"GBR\",\"first_name\":\"Lewis\",\"full_name\":\"Lewis HAMILTON\",\"headshot_url\":\"https://media.formula1.com/d_driver_fallback_image.png/content/dam/fom-website/drivers/L/LEWHAM01_Lewis_Hamilton/lewham01.png.transform/1col/image.png\",\"last_name\":\"Hamilton\",\"driver_number\":44,\"team_colour\":\"27f4d2\",\"team_name\":\"Mercedes\",\"name_acronym\":\"HAM\"}";
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    qDebug() << obj.value("session_key").toInt();

    return 0;*/
    QApplication m_appA(argc, argv);
    Dashboard m_wndDash;
    m_wndDash.show();
    return m_appA.exec();
}
