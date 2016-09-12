#include <cmath>
#include <iostream>
#include "Meteoro.h"
using namespace std;

#define LARGURA  600
#define ALTURA   600

#define PI 3.14159265

double rotationX = 0.0;
double rotationY = 0.0;

double zTranslation = 20.0f;
double rotationShip = 0.0f;

bool floating = true;
bool goingRight = false;
bool goingLeft = false;
Meteoro *m = new Meteoro;

void Anima(int value)  /* Usada quando se usar glutTimerFunc() */
{
	if(zTranslation > -10.0f){
		zTranslation --;
	}
	else
		zTranslation = 20.0f;

	if(floating){
		rotationShip = rotationShip + 0.5;
		if(rotationShip > 8)
			floating = false;
	}
	else{
		rotationShip = rotationShip - 0.5;
		if(rotationShip < -8)
			floating = true;
	}

	if(rotationShip < 30 && goingRight)
		rotationShip++;

	if(rotationShip > 30){
		goingRight = false;
	}
	if(rotationShip > -30 && goingLeft)
		rotationShip--;

	if(rotationShip < -30){
		goingLeft = false;
	}
	glutPostRedisplay();
	glutTimerFunc(100,Anima,1);
}


//Ocorre a incremetação das variáveis de rotação.
void Movimento(unsigned char key, int x, int y)
{
    switch (key) {
		case 'W':
		case 'w':
			rotationY+= 1.0f;
			break;

		case 'A':
		case 'a':
			goingLeft = true;
			rotationX+= 1.0f;
			break;

		case 'D':
		case 'd':
			goingRight = true;
			rotationX-= 1.0f;
			break;

		case 'S':
		case 's':
			rotationY-= 1.0f;
			break;

    }

    /* Necessário chamar toda vez que se faz uma alteração ou evento na janela
     * Indica a funcao glutMainLoop a chamar glutDisplayFunc com as alterações */
    glutPostRedisplay();
}

void ParametrosIluminacao()
{
	/* Parâmetros para a Luz GL_LIGHT0 sendo uma fonte de Luz Pontual */
	GLfloat luzAmbiente[4]={1.0, 1.0, 1.0, 1.0};
	GLfloat luzDifusa[4]={1.0, 1.0, 1.0, 1.0};
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};
	GLfloat posicaoLuz[4]={1.0, 1.0, 1.0, 1.0};

	/* Define os parâmetros da luz de número 0 (Luz Pontual) */
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	/* Ativa o uso de uma fonte de luz ambiente */
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	/* Características do material */
	GLfloat ka[4]={0.3, 0.2, 0.1, 1.0};		/* Reflete porcentagens da cor ambiente */
	GLfloat kd[4]={0.1, 0.2, 0.2, 1.0};		/* Reflete porcentagens da cor difusa */
	GLfloat ks[4]={1.0, 1.0, 1.0, 1.0};		/* Reflete porcentagens da cor especular */
	GLfloat shininess = 60.0;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ka);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, kd);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ks); /* Refletância do material */
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);   /* Concentração do brilho */
}

void criaNave(void){
// Criando a nave...
	glPushMatrix();
	    glLoadIdentity();
		glTranslatef(0.0, 0.0, -10.0);
		glRotatef(10, 1.0, 0.0, 0.0);
		glRotatef(180, 0.0, 1.0, 0.0);
		glRotatef(rotationShip, 0.0, 0.0, 1.0);

		glPushMatrix();
			glTranslatef(1.8, 0.0, -1.0);
			glutSolidCylinder(0.8, 1.8, 20, 20);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-1.8, 0.0, -1.0);
			glutSolidCylinder(0.8, 1.8, 20, 20);
		glPopMatrix();

		glColor3f(0.4, 0.8, 0.3);

		glPushMatrix();
			glTranslatef(0.0, 0.0, 4.0);
			glutSolidTorus(0.3, 1.8, 20, 20);
		glPopMatrix();

		glColor3f(0.4, 0.3, 0.8);

		glutSolidCone(1.0, 8.0, 20, 20);
	glPopMatrix();
// Nave criada.
}

void Desenha(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    /* Especifica uma Câmera com:
     * olho = (0, 0, 30)
     * olhar = (0, 0, 0)
     * up = (0, 1, 0) */
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 2.0,		/* eye */
    		  0.0, 0.0, 0.0,		/* look */
    		  0.0, 1.0, 0.0);		/* up */

    /* Rotaciona os objetos para visualizar a 3 dimensão */
	glRotatef(rotationY, 1.0, 0.0, 0.0); /* Rotaciona em torno do X */
	glRotatef(rotationX, 0.0, 1.0, 0.0); /* Rotaciona em torno de Y */
    ParametrosIluminacao();
//	Desenha_Origem();
//	Desenha_Eixos_Coordenados();
	glColor3f(0.8, 0.4, 0.3);


// Cubo para testes de camera... Só exemplo;
//	glPushMatrix();
//		glTranslatef(5.0f,5.0f,-zTranslation);
//		glutSolidCube(2);
//	glPopMatrix();
	for(int i = 0; i < 50; i++)
		m[i].drawCube();
	criaNave();
	/* Executa os comandos OpenGL */
	glFlush();
}





/* Inicializa parâmetros de rendering */
void Inicializa (void)
{
	/* Especifica uma projeção Ortogonal */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-10, 10, -10, 10, -50 ,50);
	gluPerspective(120.0f, 1, 1, 1000.0f);

	/* Indica qual o botao que acionará o menu */
	glutAttachMenu(GLUT_RIGHT_BUTTON);
    /*************** Parâmetros de Iluminação ***************/
	/* Habilita o uso de iluminação */
	glEnable(GL_LIGHTING);
	/* Habilita a luz de número 0 */
	glEnable(GL_LIGHT0);
	/* Habilita o depth-buffering para remoção de faces escondidas */
	glEnable(GL_DEPTH_TEST);

	/* Modelos de Iluminação Defaut */
	glShadeModel(GL_SMOOTH); 		/* Gouraud */
}

/* Programa Principal */
int main(int argc, char **argv)
{	
	for(int i = 0; i < 50; i++){
		cout  << "x : "<< m[i].getX()<< " Y: " << m[i].getY() << " Z: " << m[i].getZ() << endl;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize (LARGURA, ALTURA);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Projecoes e Camera - Primitivas 3D");
	glutDisplayFunc(Desenha);
	glutKeyboardFunc(Movimento);
	glutTimerFunc(100, Anima, 1);
	Inicializa();
	glutMainLoop();
}




