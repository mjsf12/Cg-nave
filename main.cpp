#include <cmath>
#include <vector>
#include "Meteoro.h"

#define LARGURA  1280
#define ALTURA   720
#define qtdm 100
#define PI 3.14159265

double posX = 0.0;
double posY = 0.0;

bool nave = true;

double moveZ = -10.0f;

double zTranslation = 20.0f;
double rotationShip = 0.0f;

float raioColisao = 3.5;
int ponto = 0;
bool floating = true;
bool goingRight = false;
bool goingLeft = false;
std::vector<Meteoro> m;

void Anima(int value)  /* Usada quando se usar glutTimerFunc() */
{
	if(zTranslation > -10.0f){
		zTranslation --;
	}
	else
		zTranslation = 20.0f;

	if(floating){
		rotationShip = rotationShip + 1.5;
		if(rotationShip > 45)
			floating = false;
	}
	else{
		rotationShip = rotationShip - 1.5;
		if(rotationShip < -45)
			floating = true;
	}

	glutPostRedisplay();
	glutTimerFunc(100,Anima,1);
	if(nave)
		ponto+=1;
}


//Ocorre a incremetação das variáveis de rotação.
void Movimento(unsigned char key, int x, int y)
{
    switch (key) {
		case 'W':
		case 'w':
			if(posY < 17)
				posY+= 1.0f;
			break;

		case 'A':
		case 'a':
			goingLeft = true;
			if(posX > -17)
				posX-= 1.0f;
			break;

		case 'D':
		case 'd':
			goingRight = true;
			if(posX < 17)
				posX+= 1.0f;
			break;

		case 'S':
		case 's':
			if(posY > -17)
				posY-= 1.0f;
			break;
		case 'p':
		case 'P':
			moveZ-=3;
			break;

    }

    /* Necessário chamar toda vez que se faz uma alteração ou evento na janela
     * Indica a funcao glutMainLoop a chamar glutDisplayFunc com as alterações */
    glutPostRedisplay();
}

void ParametrosIluminacao(float c1, float c2, float c3, float c4)
{
	/* Parâmetros para a Luz GL_LIGHT0 sendo uma fonte de Luz Pontual */
	GLfloat luzAmbiente[4]={1.0, 1.0, 1.0, 1.0};
	GLfloat luzDifusa[4]={1.0, 1.0, 1.0, 1.0};
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};
	GLfloat posicaoLuz[4]={50.0, 50.0, 50.0, 1.0};

	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	/* Características do material */
	GLfloat ka[4]={c1/5 , c2/5 , c3/5, c4/5};		/* Reflete porcentagens da cor ambiente */
	GLfloat kd[4]={c1,c2, c3, c4};			/* Reflete porcentagens da cor difusa */
	GLfloat ks[4]={1.0, 1.0, 1.0, 1.0};		/* Reflete porcentagens da cor especular */
	GLfloat shininess = 100.0;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ka);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, kd);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ks); /* Refletância do material */
	glMaterialf(GL_FRONT, GL_SHININESS, shininess); /* Concentração do brilho */
}

void criaNave(void){
// Criando a nave...
	glPushMatrix();
	    glLoadIdentity();
		glTranslatef(posX,posY ,  0);
		ParametrosIluminacao(0.1, 0.9, 0.1, 1);
		glTranslatef(0.0, 0.0, -20);
		glRotatef(10, 1.0, 0.0, 0.0);
		glRotatef(180, 0.0, 1.0, 0.0);
		glRotatef(rotationShip, 0.0, 0.0, 1.0);

		ParametrosIluminacao(1, 0, 0.1, 1);
		glPushMatrix();
			glTranslatef(1.8, 0.0, -1.0);
			glutSolidCylinder(0.8, 1.8, 20, 20);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-1.8, 0.0, -1.0);
			glutSolidCylinder(0.8, 1.8, 20, 20);
		glPopMatrix();

		ParametrosIluminacao(0.4, 0.8, 0.3,1);

		glPushMatrix();
			glTranslatef(0.0, 0.0, 4.0);
			glutSolidTorus(0.3, 1.8, 20, 20);
		glPopMatrix();

		ParametrosIluminacao(0.4, 0.3, 0.8,1);

		glutSolidCone(1.0, 8.0, 20, 20);
	glPopMatrix();
// Nave criada.
}

void printtext(int x, int y, string String)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, LARGURA, 0, ALTURA, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPushAttrib(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
    glRasterPos2i(x,y);
    for (int i=0; i<String.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, String[i]);
    }
    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
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
	gluLookAt(0.0, 0.0, 2.0,		/* eye */
			  0.0, 0.0, 0.0,		/* look */
			  0.0, 1.0, 0.0);		/* up */
	/* Rotaciona os objetos para visualizar a 3 dimensão */
	//glRotatef(posY, 1.0, 0.0, 0.0); /* Rotaciona em torno do X */
	//glRotatef(posX, 0.0, 1.0, 0.0); /* Rotaciona em torno de Y */
	if(nave)
		criaNave();

	int	count = 0;
	ParametrosIluminacao(1, 0, 0, 1);
	for (auto &e: m){
		if(e.coletable){
			ParametrosIluminacao(0, 1, 0, 1);
		}
		if((e.getX() > posX - raioColisao && e.getX() < posX + raioColisao)
		&& (e.getY() > posY - raioColisao && e.getY() < posY + raioColisao)
		&& (e.getZ() > -24 -raioColisao && e.getZ() < -24 + raioColisao)){
			if(e.coletable == false)
				nave = false;
			else if(nave){
				ParametrosIluminacao(0, 1, 0, 1);
				m.erase(m.begin() + count);
				count--;
				ponto+=100;
			}
		}
		e.drawCube(0);
		ParametrosIluminacao(1, 0, 0, 1);
		count++;
	}
	char string[64];
	ParametrosIluminacao(0, 0.5, 1, 1);
	sprintf(string, "Pontos: %i",ponto);
	printtext(10,10,string);
	/* Executa os comandos OpenGL */
	if(!nave){
	ParametrosIluminacao(0, 0.5, 1, 1);
	char string2[64];
	sprintf(string2, "Perdeu Click na tela para Jogar Novamente.");
	printtext(ALTURA/2,LARGURA/2,string2);
	}
	glFlush();

}

/* Inicializa parâmetros de rendering */
void Inicializa (void)
{
	/* Especifica uma projeção Ortogonal */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-10, 10, -10, 10, -50 ,50);
	gluPerspective(70.0f, 1, 1, 1000.0f);

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

void GerenciaMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON){
			posX = 0;
			posY = 0;
			nave = true;
			ponto = 0;
    }

    /* Necessário chamar toda vez que se faz uma alteração ou evento na janela
     * Indica a funcao glutMainLoop a chamar glutDisplayFunc com as alterações */
    glutPostRedisplay();
}


/* Programa Principal */
int main(int argc, char **argv)
{
	for (size_t i = 0; i < qtdm; i++){
		Meteoro* aux = new Meteoro ();
		m.push_back(*aux);
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize (LARGURA, ALTURA);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Projecoes e Camera - Primitivas 3D");
	glutDisplayFunc(Desenha);
	glutKeyboardFunc(Movimento);
	glutMouseFunc(GerenciaMouse);
	glutTimerFunc(100, Anima, 1);
	Inicializa();
	glutMainLoop();
}
