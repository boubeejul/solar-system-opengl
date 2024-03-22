#include <GL/glut.h>
#include <cmath>
#include <stdlib.h>

float tMercurio, tVenus, tTerra, tMarte, tJupiter, tSaturno, tUrano, tNetuno, xSunIn, ySunIn, posNaveX, posNaveY, escalaNave;
int posX[50];
int posY[50];
bool aumenta, volta;

void init()
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   gluOrtho2D(0.0, 800.0, 0.0, 600.0);
}

void movPlanetas(int movimento)
{
   switch (movimento)
   {
   case -1:
      tMercurio += 12.0;
      tVenus += 10.0;
      tTerra += 8.0;
      tMarte += 6.0;
      tJupiter += 4.0;
      tSaturno += 2.0;
      tUrano += 1.0;
      tNetuno += 0.5;
      break;
   case 1:
      tMercurio -= 12.0;
      tVenus -= 10.0;
      tTerra -= 8.0;
      tMarte -= 6.0;
      tJupiter -= 4.0;
      tSaturno -= 2.0;
      tUrano -= 1.0;
      tNetuno -= 0.5;
      break;
   }

   if (ySunIn >= 1.15)
   {
      aumenta = false;
   }

   if (aumenta)
   {
      xSunIn += 0.005;
      ySunIn += 0.005;
   }

   if (!aumenta)
   {
      xSunIn -= 0.005;
      ySunIn -= 0.005;
   }

   if (ySunIn <= 1.0)
   {
      aumenta = true;
   }
}

void eventoTeclado(unsigned char tecla, int x, int y)
{
   switch (tecla)
   {
   case '+':
      movPlanetas(-1);
      if (posNaveX <= 0)
         volta = true;

      if (posNaveX >= 680)
         volta = false;

      if (volta)
         posNaveX += 10.0;
      else
         posNaveX -= 10.0;
      break;
   case '-':
      movPlanetas(1);
      if (posNaveX <= 0)
         volta = false;

      if (posNaveX >= 680)
         volta = true;

      if (volta)
         posNaveX -= 10.0;
      else
         posNaveX += 10.0;
      break;
   case 122:
      if (escalaNave <= 2)
         escalaNave += 0.3;
      break;
   case 120:
      if (escalaNave > 1)
         escalaNave -= 0.3;
      break;
   case 27:
      exit(0);
      break;
   }

   glutPostRedisplay();
}

void setasTeclado(int key, int x, int y)
{
   switch (key)
   {
   case GLUT_KEY_UP:
      if (posNaveY < 500)
         posNaveY += 10.0;
      break;
   case GLUT_KEY_DOWN:
      if (posNaveY > 0)
         posNaveY -= 10.0;
      break;
   case GLUT_KEY_LEFT:
      if (posNaveX > 0)
         posNaveX -= 10.0;
      break;
   case GLUT_KEY_RIGHT:
      if (posNaveX < 680)
         posNaveX += 10.0;
      break;
   }

   glutPostRedisplay();
}

void eventoMouse(int botao, int estado, int x, int y)
{
   if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
   {
      y = glutGet(GLUT_WINDOW_HEIGHT) - y;
      posNaveX = x - 50;
      posNaveY = y - 50;
   }
   glutPostRedisplay();
}

void circulo(int vertices, int x, int y, int r, char tipo)
{
   float t = 0;

   switch (tipo)
   {
   case 'f':
      glBegin(GL_POLYGON);
      break;
   case 'l':
      glBegin(GL_LINE_LOOP);
      break;
   }

   for (int i = 0; i < vertices; ++i)
   {
      glVertex3f(x + r * cos(t), y + r * sin(t), 0.0);
      t += 2 * M_PI / vertices;
   }
   glEnd();
}

void background()
{
   // fundo azul
   glBegin(GL_POLYGON);
   glColor3f(0.0039, 0, 0.1647);
   glVertex3f(0.0, 600.0, 0.0);
   glVertex3f(800.0, 600.0, 0.0);
   glVertex3f(800.0, 0.0, 0.0);
   glVertex3f(0.0, 0.0, 0.0);
   glEnd();

   // estrelas
   glColor3f(0.9176, 0.9176, 0.9176);
   for (int i = 0; i < 50; i++)
   {
      circulo(100, posX[i], posY[i], 1, 'f');
   }
}

void sol()
{
   glPushMatrix();
   glTranslatef(400, 300, 0);
   glScalef(xSunIn, ySunIn, 0.0);
   glColor3f(1.0, 0.7255, 0.2353);
   circulo(500, 0, 0, 40, 'f');
   glPopMatrix();

   glColor3f(1.0, 0.8353, 0.2275);
   circulo(500, 400, 300, 30, 'f');
}

void orbitas()
{
   glLineWidth(1);
   glColor3f(0.2667, 0.2667, 0.3765);
   int r = 60;

   for (int i = 0; i < 8; i++)
   {
      circulo(500, 400, 300, r, 'l');
      r += 33;
   }
}

void mercurio()
{
   glPushMatrix();
   glTranslatef(400, 300, 0);
   glRotatef(tMercurio, 0.0, 0.0, 1.0);
   glColor3f(0.6863, 0.5529, 0.4588);
   circulo(500, 50, 30, 8, 'f');
   glPopMatrix();
}

void venus()
{
   glPushMatrix();
   glTranslatef(400, 300, 0);
   glRotatef(tVenus, 0.0, 0.0, 1.0);
   glColor3f(0.9098, 0.7373, 0.7255);
   circulo(500, 50, 75, 14, 'f');
   glPopMatrix();
}

void terra()
{
   glPushMatrix();
   glTranslatef(400, 300, 0);
   glRotatef(tTerra, 0.0, 0.0, 1.0);
   glColor3f(0.5686, 0.7922, 0.9059);
   circulo(500, 50, 115, 14, 'f');
   glPopMatrix();
}

void marte()
{
   glPushMatrix();
   glTranslatef(400, 300, 0);
   glRotatef(tMarte, 0.0, 0.0, 1.0);
   glColor3f(0.7608, 0.2784, 0.2078);
   circulo(500, 50, 150, 11, 'f');
   glPopMatrix();
}

void jupiter()
{
   glPushMatrix();
   glTranslatef(400, 300, 0);
   glRotatef(tJupiter, 0.0, 0.0, 1.0);
   glColor3f(0.7647, 0.5647, 0.4431);
   circulo(500, 50, 190, 18, 'f');
   glPopMatrix();
}

void saturno()
{
   float t = 0;

   glPushMatrix();
   glTranslatef(400, 300, 0);
   glRotatef(tSaturno, 0.0, 0.0, 1.0);

   // aneis
   glColor3f(0.6745, 0.6745, 0.6745);
   glLineWidth(2);
   glBegin(GL_LINE_LOOP);
   for (int i = 0; i < 100; ++i)
   {
      glVertex3f(50 + 22 * cos(t), 227 + 22 * sin(t), 0.0);
      t += 2 * M_PI / 100;
   }
   glEnd();

   // planeta
   glColor3f(0.9725, 0.8980, 0.4941);
   circulo(500, 50, 227, 16, 'f');

   glPopMatrix();
}

void urano()
{
   float t = 0;

   glPushMatrix();
   glTranslatef(400, 300, 0);
   glRotatef(tUrano, 0.0, 0.0, 1.0);

   // aneis
   glColor3f(1.0, 1.0, 1.0);
   glLineWidth(1);
   glBegin(GL_LINE_LOOP);
   for (int i = 0; i < 100; ++i)
   {
      glVertex3f(50 + 20 * cos(t), 257 + 20 * sin(t), 0.0);
      t += 2 * M_PI / 100;
   }
   glEnd();

   // planeta
   glColor3f(0.5176, 0.6431, 0.8353);
   circulo(500, 50, 257, 14, 'f');

   glPopMatrix();
}

void netuno()
{
   float t = 0;

   glPushMatrix();
   glTranslatef(400, 300, 0);
   glRotatef(tNetuno, 0.0, 0.0, 1.0);

   glColor3f(0.3137, 0.3608, 0.6501);
   circulo(500, 50, 287, 14, 'f');

   glPopMatrix();
}

void planetas()
{
   mercurio();
   venus();
   terra();
   marte();
   jupiter();
   saturno();
   urano();
   netuno();
}

void nave()
{
   float t = 0;
   int x = 0;

   glPushMatrix();
   glTranslatef(posNaveX, posNaveY, 0);
   glScalef(escalaNave, escalaNave, 0.0);
   // vidro da nave
   glColor3f(0.6549, 0.8235, 0.8588);
   glBegin(GL_POLYGON);
   for (int i = 0; i < 300; ++i)
   {
      glVertex3f(65 + 20 * cos(t), 55 + 20 * sin(t), 0.0);
      t += 2 * M_PI / 300;
   }
   glEnd();

   // corpo do alien
   glColor3f(0.4078, 0.7412, 0.2667);
   glBegin(GL_POLYGON);
   for (int i = 0; i < 300; ++i)
   {
      glVertex3f(65 + 10 * cos(t), 50 + 15 * sin(t), 0.0);
      t += 2 * M_PI / 300;
   }
   glEnd();

   // olhos do alien
   glColor3f(0, 0, 0);
   x = 60;
   for (int i = 0; i < 2; i++)
   {
      glBegin(GL_POLYGON);
      for (int i = 0; i < 300; ++i)
      {
         glVertex3f(x + 2 * cos(t), 55 + 3 * sin(t), 0.0);
         t += 2 * M_PI / 300;
      }
      glEnd();
      x += 10;
   }

   // pes da nave
   glColor3f(0.4235, 0.4235, 0.4235);
   x = 55;
   for (int i = 0; i < 2; i++)
   {
      glBegin(GL_POLYGON);
      for (int i = 0; i < 300; ++i)
      {
         glVertex3f(x + 5 * cos(t), 27 + 5 * sin(t), 0.0);
         t += 2 * M_PI / 300;
      }
      glEnd();
      x += 20;
   }

   // estrutura cinza
   glColor3f(0.6863, 0.6863, 0.6863);
   glBegin(GL_POLYGON);
   for (int i = 0; i < 300; ++i)
   {
      glVertex3f(65 + 30 * cos(t), 35 + 7 * sin(t), 0.0);
      t += 2 * M_PI / 300;
   }
   glEnd();

   // borda branca
   glBegin(GL_POLYGON);
   glColor3f(0.7647, 0.1647, 0.1765);
   glVertex3f(45.0, 50.0, 0.0);
   glVertex3f(85.0, 50.0, 0.0);
   glVertex3f(100.0, 35.0, 0.0);
   glVertex3f(30.0, 35.0, 0.0);
   glEnd();

   // bolinhas brancas
   glColor3f(1.0, 1.0, 1.0);
   x = 50;
   for (int i = 0; i < 3; i++)
   {
      circulo(100, x, 43, 3, 'f');
      x += 14;
   }

   // estrutura vermelha
   glBegin(GL_POLYGON);
   glVertex3f(30.0, 35.0, 0.0);
   glVertex3f(100.0, 35.0, 0.0);
   glVertex3f(105.0, 33.0, 0.0);
   glVertex3f(25.0, 33.0, 0.0);
   glEnd();

   glPopMatrix();
}

void desenha()
{
   glClear(GL_COLOR_BUFFER_BIT);
   background();
   sol();
   orbitas();
   planetas();
   nave();

   glutSwapBuffers();
}

void gerarPosicoesEstrelas()
{
   for (int i = 0; i < 50; i++)
   {
      posX[i] = rand() % (780 - 20 + 1) + 20;
      posY[i] = rand() % (580 - 20 + 1) + 20;
   }
}

int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitWindowSize(800, 600);
   glutInitWindowPosition(100, 100);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
   glutCreateWindow("Trabalho 2");
   srand(12);
   gerarPosicoesEstrelas();
   ySunIn = 1;
   xSunIn = 1;
   posNaveX = 0;
   posNaveY = 0;
   escalaNave = 1;

   init();

   glutDisplayFunc(desenha);           // chama a funcao com os desenhos
   glutKeyboardFunc(eventoTeclado); // funcao com os eventos das teclas
   glutMouseFunc(eventoMouse);      // funcao com os eventos do mouse
   glutSpecialFunc(setasTeclado);   // funcao com os eventos das setas do teclado

   glutMainLoop();

   return EXIT_SUCCESS;
}
