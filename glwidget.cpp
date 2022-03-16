#include "glwidget.h"
#include <windows.h>
#include "glwidget.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <QQuaternion>
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
#include <QMatrix4x4>
#include <QMatrix3x3>
#include <QTransform>

GLWidget::GLWidget(QWidget *parent):QOpenGLWidget(parent)

{



  quaternion =  QQuaternion( w, x, y, z); // construction of the quaternion
    quaternion.setScalar(w);
    quaternion.setX(x);
    quaternion.setY(y);
    quaternion.setZ(z);

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));

    timer.start(16);
}
//================================================================================================


void GLWidget::initializeGL()
{


    glClearColor(0.0f,0.0f,0.0f,1.0f); //background

}





void GLWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    glMatrixMode(GL_MODELVIEW); // Modelview matrix used to apply transformations on the object
    glLoadIdentity();

    // camera transformation
    gluLookAt(6.0, 6.0, 6.0, 3.0,3.5,0.0, 0.0,1.0,0.0);
    glTranslatef(1.1, 2.1, -3.1); // trnaslate the elements of the scene to the center
                                  // of the screen





     //Drawing the fixed_frame (world coordinate system)
        glLineWidth(5.0f);

        glBegin(GL_LINES);
         //X_axis
        glColor3f (1.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(4.0, 0.0, 0.0);
        // arrow
        glVertex3f(4.0, 0.0f, 0.0f);
        glVertex3f(3.75, 0.25f, 0.0f);

        glVertex3f(4.0, 0.0f, 0.0f);
        glVertex3f(3.75, -0.25f, 0.0f);
        //Y_axis
        glColor3f (0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 4.0, 0.0);
        // arrow
        glVertex3f(0.0, 4.0f, 0.0f);
        glVertex3f(0.25, 3.75f, 0.0f);

        glVertex3f(0.0, 4.0f, 0.0f);
        glVertex3f(-0.25, 3.75f, 0.0f);

        //Z_axis
        glColor3f (0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 4.0);
        // arrow


        glVertex3f(0.0, 0.0f ,4.0f );
        glVertex3f(0.0, 0.25f ,3.75f );

        glVertex3f(0.0, 0.0f ,4.0f );
        glVertex3f(0.0, -0.25f ,3.75f );
        glEnd();



        // Constructing my quaternion
          quaternion =  QQuaternion(w,x,y,z);
          qDebug()<<"quaternion before normalization"<<quaternion;

          quaternion.normalize(); // Normalizing my quaternion
          qDebug()<<"quaternion after normalization"<<quaternion;

          GLfloat m[16];

          glGetFloatv (GL_MODELVIEW_MATRIX, m); // retrieveing the values of the modelview
                                                // matrix so I can call in functions
          qDebug()<<"gl_modelview before rotation"<<m;

          QMatrix4x4 modelview(m); // putting these values in 4*4 matrix
          qDebug()<<"modelview before rotation"<<modelview;


          modelview.rotate(quaternion); // applying the rotation: rotate function calculates
                                        //the rotation matrix that corresponds to the quaternion
                                        // then multiplies it by the modelview matrix
          qDebug()<<"modelview after rotation"<<modelview;








//==================================================================================================
    //Draw the object I want to rotate


       glEnable(GL_DEPTH_TEST);
       glEnable(GL_CULL_FACE);


       glBegin(GL_QUADS);


       // Top (y=1.0)


       glColor4f(0.0f, 1.0f, 0.0f,0.5f);     // Green
       glVertex3f(2.0f, 1.0f, -1.0f);
       glVertex3f(-2.0f, 1.0f, -1.0f);
       glVertex3f(-2.0f, 1.0f, 1.0f);
       glVertex3f(2.0f, 1.0f, 1.0f);

      // Bottom face (y = -1.0f)

       glColor4f(1.0f, 0.5f, 0.0f,0.5f);     // Orange
       glVertex3f(2.0f, -1.0f, 1.0f);
       glVertex3f(-2.0f, -1.0f, 1.0f);
       glVertex3f(-2.0f, -1.0f, -1.0f);
       glVertex3f(2.0f, -1.0f, -1.0f);

       // Front face  (z = 1.0f)

       glColor4f(1.0f, 0.0f,0.0f,0.5f);     // Red
       glVertex3f(2.0f, 1.0f, 1.0f);
       glVertex3f(-2.0f, 1.0f, 1.0f);
       glVertex3f(-2.0f, -1.0f, 1.0f);
       glVertex3f(2.0f, -1.0f, 1.0f);

       // Back face (z = -1.0f)

       glColor4f(1.0f, 1.0f, 0.0f,0.5f);     // Yellow
       glVertex3f(2.0f, -1.0f, -1.0f);
       glVertex3f(-2.0f, -1.0f, -1.0f);
       glVertex3f(-2.0f, 1.0f, -1.0f);
       glVertex3f(2.0f, 1.0f, -1.0f);

       // Left face (x = -1.0f)

       glColor4f(0.0f, 0.0f, 1.0f,0.5f);     // Blue
       glVertex3f(-2.0f, 1.0f, 1.0f);
       glVertex3f(-2.0f, 1.0f, -1.0f);
       glVertex3f(-2.0f, -1.0f, -1.0f);
       glVertex3f(-2.0f, -1.0f, 1.0f);

       // Right face (x = 1.0f)

       glColor4f(1.0f, 0.0f, 1.0f,0.5f);     // Purple
       glVertex3f(2.0f, 1.0f, -1.0f);
       glVertex3f(2.0f, 1.0f, 1.0f);
       glVertex3f(2.0f, -1.0f, 1.0f);
       glVertex3f(2.0f, -1.0f, -1.0f);



       glEnd();
       glFlush();


//==================================================================================================
    // Object_frame (Local coordinate system)

     /* //glRotated(-90,0.0,1.0,0.0);
      glBegin(GL_LINES);
      glColor3f (1.0, 0.0, 0.0);
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(4.0, 0.0, 0.0);
      // arrow
      glVertex3f(4.0, 0.0f, 0.0f);
      glVertex3f(3.75, 0.25f, 0.0f);

      glVertex3f(4.0, 0.0f, 0.0f);
      glVertex3f(3.75, -0.25f, 0.0f);

      glColor3f (0.0, 1.0, 0.0);
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(0.0, 4.0, 0.0);
      // arrow
      glVertex3f(0.0, 4.0f, 0.0f);
      glVertex3f(0.25, 3.75f, 0.0f);

      glVertex3f(0.0, 4.0f, 0.0f);
      glVertex3f(-0.25, 3.75f, 0.0f);

      glColor3f (0.0, 0.0, 1.0);
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(0.0, 0.0, 4.0);

      // arrow
      glVertex3f(0.0, 0.0f ,4.0f );
      glVertex3f(0.0, 0.25f ,3.75f );

      glVertex3f(0.0, 0.0f ,4.0f );
      glVertex3f(0.0, -0.25f ,3.75f );
      glEnd();

      glColor3f(256,256,256);
      glPointSize(5);
      glBegin(GL_POINTS);
      glVertex3f(0,0,0);
      glEnd();*/
//=================================================================================================
    // draw the frame labels:
    QPainter p(this);
    p.setPen(Qt::red);
    p.setFont(QFont("Arial", 10));
    p.drawText(7, 50, "-----X_axis");
    QPainter p1(this);
    p1.setPen(Qt::green);
    p1.setFont(QFont("Arial", 10));
    p.drawText(7,100, "-----Y_axis");

    QPainter p2(this);
    p2.setPen(Qt::blue);
    p2.setFont(QFont("Arial", 10));
    p.drawText(7,150,"-----Z_axis");

    QPainter p3(this);
    p3.setPen(Qt::white);
    p3.setFont(QFont("Arial", 10));
    p3.drawText(7, 200, "-----Origin");
    p.end();
 }
//=================================================================================================
void GLWidget::resizeGL(int wi, int h)
{
     glViewport(0,0,wi,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 45.0, (float)wi/h, 0.01, 100.0);

    update();
}




















