#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QtOpenGL>
#include "windows.h"
#include "GL/glu.h"
#include <QVector2D>
#include <QOpenGLWidget>
#include <QObject>

class GLWidget : public QOpenGLWidget
{

      Q_OBJECT


public:

    explicit GLWidget(QWidget *parent =0);

/*public slots:
    void       SetWRotation(float new_w);                      //Update the angle w
    void       SetXRotation(float new_x);            // Update the rotation around X
    void       SetYRotation(float new_y);            // Update the rotation around Y
    void       SetZRotation(float new_z);            // Update the rotaiton around Z
*/
public:
    void initializeGL() ;
    void paintGL();
    void resizeGL(int wi, int h);
    float w,x,y,z;
    QQuaternion quaternion;

/*signals:
    void       wRotationChanged(float new_w);
    void       xRotationChanged(float new_x);        // Signals for new orientations
    void       yRotationChanged(float new_y);
    void       zRotationChanged(float new_z);
*/
private:


   QTimer timer;
   QMatrix4x4 projection;



};


#endif // GLWIDGET_H
