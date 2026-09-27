#include <GL/glut.h>
#include <math.h>

// Tempo de quadro e controle de rotação contínua da cena
static float anguloCena = 0.0f;
static int tempoAnterior = 0;


// 1. Plano de Base (Chão)
void desenharChao(void) {
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
        glVertex3f(-15.0f, 0.0f, -15.0f);
        glVertex3f(-15.0f, 0.0f,  15.0f);
        glVertex3f( 15.0f, 0.0f,  15.0f);
        glVertex3f( 15.0f, 0.0f, -15.0f);
    glEnd();
}

// 2. Montanha / Pirâmide
void desenharMontanha(void) {
    // Faces laterais (GL_TRIANGLE_FAN)
    glColor3f(0.65f, 0.4f, 0.25f); // Marrom
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 4.0f, 0.0f);  // Ápice
        glVertex3f(-2.5f, 0.0f,  2.5f);
        glVertex3f( 2.5f, 0.0f,  2.5f);
        glVertex3f( 2.5f, 0.0f, -2.5f);
        glVertex3f(-2.5f, 0.0f, -2.5f);
        glVertex3f(-2.5f, 0.0f,  2.5f);
    glEnd();

    // Base
    glBegin(GL_QUADS);
        glVertex3f(-2.5f, 0.0f, -2.5f);
        glVertex3f( 2.5f, 0.0f, -2.5f);
        glVertex3f( 2.5f, 0.0f,  2.5f);
        glVertex3f(-2.5f, 0.0f,  2.5f);
    glEnd();
}

// 3. Árvore / Coluna 3D (Tronco em Strip + Copa Piramidal)
void desenharArvoreColuna(void) {
    // Tronco (GL_QUAD_STRIP)
    glColor3f(0.4f, 0.25f, 0.1f);
    glBegin(GL_QUAD_STRIP);
        glVertex3f(-0.15f, 0.0f,  0.15f); glVertex3f(-0.15f, 0.8f,  0.15f);
        glVertex3f( 0.15f, 0.0f,  0.15f); glVertex3f( 0.15f, 0.8f,  0.15f);
        glVertex3f( 0.15f, 0.0f, -0.15f); glVertex3f( 0.15f, 0.8f, -0.15f);
        glVertex3f(-0.15f, 0.0f, -0.15f); glVertex3f(-0.15f, 0.8f, -0.15f);
        glVertex3f(-0.15f, 0.0f,  0.15f); glVertex3f(-0.15f, 0.8f,  0.15f);
    glEnd();

    // Copa em Camadas (Verde)
    glColor3f(0.1f, 0.7f, 0.3f);
    
    // Camada Inferior
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 2.0f, 0.0f);
        glVertex3f(-0.7f, 0.8f,  0.7f);
        glVertex3f( 0.7f, 0.8f,  0.7f);
        glVertex3f( 0.7f, 0.8f, -0.7f);
        glVertex3f(-0.7f, 0.8f, -0.7f);
        glVertex3f(-0.7f, 0.8f,  0.7f);
    glEnd();

    // Camada Superior
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 2.7f, 0.0f);
        glVertex3f(-0.5f, 1.6f,  0.5f);
        glVertex3f( 0.5f, 1.6f,  0.5f);
        glVertex3f( 0.5f, 1.6f, -0.5f);
        glVertex3f(-0.5f, 1.6f, -0.5f);
        glVertex3f(-0.5f, 1.6f,  0.5f);
    glEnd();
}

// 4. Cubo Flutuante
void desenharCuboFlutuante(void) {
    glColor3f(0.7f, 0.65f, 0.9f); // Lilás
    glBegin(GL_QUADS);
        // Frente
        glVertex3f(-0.7f, -0.5f,  0.7f);
        glVertex3f( 0.7f, -0.5f,  0.7f);
        glVertex3f( 0.7f,  0.5f,  0.7f);
        glVertex3f(-0.7f,  0.5f,  0.7f);
        // Trás
        glVertex3f(-0.7f, -0.5f, -0.7f);
        glVertex3f(-0.7f,  0.5f, -0.7f);
        glVertex3f( 0.7f,  0.5f, -0.7f);
        glVertex3f( 0.7f, -0.5f, -0.7f);
        // Cima
        glVertex3f(-0.7f,  0.5f, -0.7f);
        glVertex3f(-0.7f,  0.5f,  0.7f);
        glVertex3f( 0.7f,  0.5f,  0.7f);
        glVertex3f( 0.7f,  0.5f, -0.7f);
        // Baixo
        glVertex3f(-0.7f, -0.5f, -0.7f);
        glVertex3f( 0.7f, -0.5f, -0.7f);
        glVertex3f( 0.7f, -0.5f,  0.7f);
        glVertex3f(-0.7f, -0.5f,  0.7f);
        // Esquerda
        glVertex3f(-0.7f, -0.5f, -0.7f);
        glVertex3f(-0.7f, -0.5f,  0.7f);
        glVertex3f(-0.7f,  0.5f,  0.7f);
        glVertex3f(-0.7f,  0.5f, -0.7f);
        // Direita
        glVertex3f( 0.7f, -0.5f, -0.7f);
        glVertex3f( 0.7f,  0.5f, -0.7f);
        glVertex3f( 0.7f,  0.5f,  0.7f);
        glVertex3f( 0.7f, -0.5f,  0.7f);
    glEnd();
}

// 5. Sol 3D usando Leque de Triângulos (GL_TRIANGLE_FAN)
void desenharSol(void) {
    int numSegmentos = 20;
    float raio = 1.2f;
    float pi = 3.14159265f;

    glColor3f(1.0f, 0.9f, 0.0f); // Amarelo
    
    // Frente
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 0.0f, 0.1f);
        for (int i = 0; i <= numSegmentos; i++) {
            float angulo = i * 2.0f * pi / numSegmentos;
            glVertex3f(raio * cosf(angulo), raio * sinf(angulo), 0.0f);
        }
    glEnd();

    // Verso (Culling)
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 0.0f, -0.1f);
        for (int i = numSegmentos; i >= 0; i--) {
            float angulo = i * 2.0f * pi / numSegmentos;
            glVertex3f(raio * cosf(angulo), raio * sinf(angulo), 0.0f);
        }
    glEnd();
}


// MONTAGEM DO CENÁRIO COM INSTÂNCIAS

void desenharCena(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Afastamento da Câmera
    glTranslatef(0.0f, -1.8f, -18.0f);

    // Inclinação e rotação suave da cena
    glRotatef(18.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(anguloCena, 0.0f, 1.0f, 0.0f);

    // 1. Chão
    desenharChao();

    // 2. SOL 
    glPushMatrix();
        glTranslatef(6.0f, 6.0f, 6.0f);
        desenharSol();
    glPopMatrix();

    // 3. MONTANHAS 
    glPushMatrix();
        glTranslatef(-4.0f, 0.0f, -2.0f);
        glScalef(1.0f, 5.0f, 1.0f);
        desenharMontanha();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(3.5f, 0.0f, -3.0f);
        glScalef(2.1f, 1.9f, 2.1f);
        desenharMontanha();
    glPopMatrix();

    // 4. ÁRVORES 
    glPushMatrix();
        glTranslatef(-1.8f, 0.0f, 2.5f); // Árvore 1 (Esquerda)
        desenharArvoreColuna();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 2.5f);  // Árvore 2 (Centro)
        desenharArvoreColuna();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1.8f, 0.0f, 2.5f);  // Árvore 3 (Direita)
        desenharArvoreColuna();
    glPopMatrix();

    // 5. CUBO ROXO (Afastado para a esquerda e alto)
    glPushMatrix();
        glTranslatef(-4.5f, 4.0f, 0.0f);
        glRotatef(25.0f, 0.0f, 1.0f, 0.0f);
        desenharCuboFlutuante();
    glPopMatrix();

    glutSwapBuffers();
}

void atualizar(void) {
    int tempoAtual = glutGet(GLUT_ELAPSED_TIME);
    if (tempoAnterior == 0) tempoAnterior = tempoAtual;
    
    float dt = (tempoAtual - tempoAnterior) / 1000.0f;
    tempoAnterior = tempoAtual;

    anguloCena += 20.0f * dt; // Rotação de 20 graus por segundo
    if (anguloCena > 360.0f) anguloCena -= 360.0f;

    glutPostRedisplay();
}

void redimensionar(int largura, int altura) {
    if (altura == 0) altura = 1;
    float aspecto = (float)largura / (float)altura;

    glViewport(0, 0, largura, altura);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, aspecto, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

void inicializar(void) {
    glClearColor(0.12f, 0.12f, 0.15f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cenario 3d");

    inicializar();

    glutDisplayFunc(desenharCena);
    glutReshapeFunc(redimensionar);
    glutIdleFunc(atualizar);

    glutMainLoop();
    return 0;
}