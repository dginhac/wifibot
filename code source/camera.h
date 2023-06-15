#ifndef CAMERA_H
#define CAMERA_H

#include <QWebEngineView>
#include <QMainWindow>

#include "direction.h".h"

class Camera
{
private:
    QWebEngineView *view;
    QMainWindow *mainWindow;

public:
    Camera(QMainWindow *_mainWindow);
    void move(Direction direction, bool slow = false);
};

#endif // CAMERA_H
