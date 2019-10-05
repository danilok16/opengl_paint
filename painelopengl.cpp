#include "painelopengl.h"
#include <cmath>


PainelOpenGl::PainelOpenGl(QWidget *parent):
    QGLWidget(parent)
{
    setFormat(QGL::DoubleBuffer | QGL::DepthBuffer);
    lados = 3;
    raio = 1.0;
    this->zoom = 1;
    this->shapeFocus = 0;
}

double PainelOpenGl::getZoom() const
{
    return zoom;
}

void PainelOpenGl::setZoom(double value)
{
    zoom = value;
}

int PainelOpenGl::getShapeFocus() const
{
    return shapeFocus;
}

void PainelOpenGl::setShapeFocus(int value)
{
    shapeFocus = value;
}

// Não utilizar updateOpenGL nesse metodo
void PainelOpenGl::initializeGL(){
    glShadeModel(GL_SMOOTH);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

// Não utilizar updateOpenGL nesse metodo
void PainelOpenGl::resizeGL(int width, int height){
    this->menorX = 0, this->maiorX = 10, this->menorY = 0, this->maiorY = 10;
    glViewport( 0, 0, (GLint)width, (GLint)height );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluOrtho2D(-1,1,-1,1);
    glOrtho(-1,1,-1,1,180,-180);
    if (width > height)
    {
        height = height?height:1;
        double novaLargura = (maiorX - menorX) * width / height;
        double difLargura = novaLargura - (maiorX - menorX);
        menorX = 0.0 - difLargura / 2.0;
        maiorX = 10 + difLargura / 2.0;

    }
    else
    {
        width = width?width:1;
        double novaAltura = (maiorY - menorY) * height / width;
        double difAltura = novaAltura - (maiorY - menorY);
        menorY = 0.0 - difAltura / 2.0;
        maiorY = 10 + difAltura / 2.0;
    }
    //gluOrtho2D(menorX, maiorX, menorY, maiorY);
    glOrtho(menorX, maiorX, menorY, maiorY,100,-100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


}

double PainelOpenGl::mouseCoordinate(int width, int height, double mouseX, double mouseY){
    /*this->menorX = 0, this->maiorX = 10, this->menorY = 0, this->maiorY = 10;

    width =89;
    mouseX = 143;
    height = 25;

    // glViewport( 0, 0, (GLint)width, (GLint)height );

   // glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //gluOrtho2D(-1,1,-1,1);
    //glOrtho(-1,1,-1,1,180,-180);
    if (width > height)
    {
        height = height?height:1;
        double novaLargura = (maiorX - menorX) * width / height;
        double difLargura = novaLargura - (maiorX - menorX);
        menorX = mouseX - difLargura / 2.0;
        //qDebug()<<menorX;
        maiorX = mouseX + difLargura / 2.0;
        //qDebug()<<maiorX;
    }
    else
    {
        width = width?width:1;
        double novaAltura = (maiorY - menorY) * height / width;
        double difAltura = novaAltura - (maiorY - menorY);
        menorY = 0.0 - difAltura / 2.0;
        maiorY = 10 + difAltura / 2.0;
    }
    //gluOrtho2D(menorX, maiorX, menorY, maiorY);
   // glOrtho(menorX, maiorX, menorY, maiorY,100,-100);
    //glMatrixMode(GL_MODELVIEW);
    //LoadIdentity();

    double teste;
    teste = (mouseX / (89/ 2.0)) -1;
    qDebug()<<teste;
*/

}
// Não utilizar updateOpenGL nesse metodo
void PainelOpenGl::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    this->drawMesh();
    this->drawShape();
    //shape.draw();
  /*  // Limpa a janela de visualiza��o com a cor branca
    // e Limpa o buffer de teste de profundidade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); // limpa todas as transforma��es
    this->drawMesh();
    glTranslated(5.0, 5.0, 0.0);

    // Desenha um pol�gono com N lados informado pelo usu�rio
    glLineWidth(1);
    glColor3f(0,0.7f,0.7f); // Define a cor de desenho: vermelho
    glBegin(GL_POLYGON);
        for (int i = 0; i < lados; ++i)
            glVertex2f(raio*cos(i*2*3.14159265/lados),
                       raio*sin(i*2*3.14159265/lados));
    glEnd();

    // Desenha as areastas de pol�gono com N lados informado pelo usu�rio
    glLineWidth(2);
    glColor3f(0,1,0);   // Define a cor de desenho: verde
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i < lados; ++i)
            glVertex2f(raio*cos(i*2*3.14159265/lados),
                       raio*sin(i*2*3.14159265/lados));
    glEnd();*/
}
void PainelOpenGl::alterarLados(int l){
    if(lados!=l && l>=3 && l<=60){
        this->shapesList.at(this->shapeFocus).setSide(l);
        //lados =l;
        updateGL();
    }
}
void PainelOpenGl::alterarRaio(double r){
    if(raio!= r && r>=1.0 && r<=5.0){
        this->shapesList.at(this->shapeFocus).setRadius(r);
       // raio=r;
        updateGL();
    }
}



// Não utilizar updateOpenGL nesse metodo
void PainelOpenGl::drawMesh(){
    glLineWidth(10);
    glColor3f(0,0,0);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    for(int i = this->menorX; i<= this->maiorX; i++){
        for(int j = this->menorY; j<= this->maiorY; j++){
            glVertex2f(i,j);
        }
    }
    glEnd();

}

void PainelOpenGl::drawShape()
{
/*glLoadIdentity();
    glLineWidth(10);
    glColor3f(1,0,0);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
        glVertex2f(5,1);
    glEnd();

glLoadIdentity();

mouseCoordinate(0,0,0,0);*/

    if(this->shapesList.size() > 0){
        for(int i = 0; i <= shapesList.size()-1; i++){
             glTranslated(this->shapesList.at(i).getXTranslated(), this->shapesList.at(i).getYTranslated(), 0.0);
             glScalef(this->shapesList.at(i).getXScale(),this->shapesList.at(i).getYScale(),0);
             glRotatef(this->shapesList.at(i).getAngle(),0,0,1);
             this->shapesList.at(i).draw();
        }
        //glLoadIdentity();
    }
}

void PainelOpenGl::scale(double x, double y)
{
   this->shapesList.at(this->shapeFocus).setXScale(x);
   this->shapesList.at(this->shapeFocus).setYScale(y);
}

void PainelOpenGl::rotate(double angle)
{
    this->shapesList.at(this->shapeFocus).setAngle(angle);
}


void PainelOpenGl::translated(int direction)
{

    switch (direction) {
    case UP: this->shapesList.at(this->shapeFocus).setYTranslated(this->shapesList.at(this->shapeFocus).getYTranslated()+0.5);
        break;
    case LEFT:this->shapesList.at(this->shapeFocus).setXTranslated(this->shapesList.at(this->shapeFocus).getXTranslated()-0.5);
        break;
    case RIGHT:this->shapesList.at(this->shapeFocus).setXTranslated(this->shapesList.at(this->shapeFocus).getXTranslated()+0.5);
        break;
    case DOWN: this->shapesList.at(this->shapeFocus).setYTranslated(this->shapesList.at(this->shapeFocus).getYTranslated()-0.5);
        break;
    }
}

void PainelOpenGl::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"X: "<<event->x();
    qDebug()<<"Y: "<<event->y();
}


void PainelOpenGl::keyPressEvent(QKeyEvent *event)
{
}

