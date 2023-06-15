#include "camera.h"
#include <QNetworkAccessManager>

Camera::Camera(QMainWindow *_mainWindow)
    : mainWindow(_mainWindow)
{
    //Association du widget à l'objet caméra + chargement de la page web de la caméra
    view = mainWindow->findChild<QWebEngineView*>("Camera");
    view->load(QUrl("http://192.168.1.106:8080/?action=stream"));
    view->setZoomFactor(2);
    view->show();
}

void Camera::move(Direction direction, bool slow){
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    //Déplacement de la caméra à l'aide de rêquete envoyé
    switch(direction){
    case Direction::FORWARD: //haut
        if (!slow)
            manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-200")));
        else
            manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-20")));
        break;

    case Direction::LEFT: //gauche
        if (!slow)
            manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=200")));
        else
            manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=20")));
        break;

    case Direction::RIGHT: //droite
        if(!slow)
            manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-200")));
        else
            manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-20")));
        break;

    case Direction::BACKWARD: //bas
        if (!slow)
            manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=200")));
        else
            manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=20")));
        break;

    default:
        break;
    }

}
