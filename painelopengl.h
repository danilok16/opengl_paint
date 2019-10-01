#ifndef PAINELOPENGL_H
#define PAINELOPENGL_H

#include <QGLWidget>
#include <QtOpenGL>

class PainelOpenGl : public QGLWidget
{
Q_OBJECT
public:
    //PainelOpenGl();
    explicit PainelOpenGl(QWidget *parent = 0);
    void drawMesh();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

public slots:
    void alterarLados(int l);
    void alterarRaio(double r);

private:
    int lados;
    double raio;
    double menorX, maiorX, menorY, maiorY;
};

#endif // PAINELOPENGL_H
