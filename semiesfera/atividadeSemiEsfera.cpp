#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>

// Controle da rotação contínua da cena
static float anguloCena = 0.0f;
static int tempoAnterior = 0;
static float anguloTriangulo = 0.0f;

// Função para desenhar o chão da cena
void desenharChao(void) {
    glColor3f(0.2f, 0.2f, 0.65f);
    glBegin(GL_QUADS);
        glVertex3f(-15.0f, 0.0f, -15.0f);
        glVertex3f(-15.0f, 0.0f,  15.0f);
        glVertex3f( 15.0f, 0.0f,  15.0f);
        glVertex3f( 15.0f, 0.0f, -15.0f);
    glEnd();
}

// Função para desenhar o pilar com base em Y = 0 e altura de 4.0
void desenharPilar(void) {
    glColor3f(0.7f, 0.65f, 0.5f);
    glBegin(GL_QUADS);
        // Frente (Z = +0.5)
        glVertex3f( 0.5f, 0.0f,  0.5f);
        glVertex3f(1.5f, 0.0f,  0.5f);
        glVertex3f(1.5f, 4.0f,  0.5f);
        glVertex3f( 0.5f, 4.0f,  0.5f);

        // Trás (Z = -0.5)
        glVertex3f( 0.5f, 0.0f, -0.5f);
        glVertex3f( 0.5f, 4.0f, -0.5f);
        glVertex3f(1.5f, 4.0f, -0.5f);
        glVertex3f(1.5f, 0.0f, -0.5f);

        // Cima (Y = 4)
        glVertex3f( 0.5f, 4.0f, -0.5f);
        glVertex3f( 0.5f, 4.0f,  0.5f);
        glVertex3f(1.5f, 4.0f,  0.5f);
        glVertex3f(1.5f, 4.0f, -0.5f);

        // Baixo (Y = 0)
        glVertex3f( 0.5f, 0.0f, -0.5f);
        glVertex3f(1.5f, 0.0f, -0.5f);
        glVertex3f(1.5f, 0.0f,  0.5f);
        glVertex3f( 0.5f, 0.0f,  0.5f);

        // Esquerda (X = 0.5)
        glVertex3f(0.5f, 0.0f, -0.5f);
        glVertex3f(0.5f, 0.0f,  0.5f);
        glVertex3f(0.5f, 4.0f,  0.5f);
        glVertex3f(0.5f, 4.0f, -0.5f);

        // Direita (X = 1.5)
        glVertex3f(1.5f, 0.0f, -0.5f);
        glVertex3f(1.5f, 4.0f, -0.5f);
        glVertex3f(1.5f, 4.0f,  0.5f);
        glVertex3f(1.5f, 0.0f,  0.5f);
    glEnd();
}

// Função para desenhar o triângulo com base em Y = 4.5 e altura de 1.0
void desenharTriangulo(void) {
    glColor3f(1.0f, 0.5f, 0.0f); // Laranja
    glBegin(GL_TRIANGLES);
        // Frente
        glVertex3f(0.5f, 4.5f,  0.5f);
        glVertex3f(1.5f, 4.5f,  0.5f);
        glVertex3f(1.0f, 5.5f,  0.0f);

        // Trás
        glVertex3f(1.5f, 4.5f, -0.5f);
        glVertex3f(0.5f, 4.5f, -0.5f);
        glVertex3f(1.0f, 5.5f,  0.0f);

        // Esquerda
        glVertex3f(0.5f, 4.5f, -0.5f);
        glVertex3f(0.5f, 4.5f,  0.5f);
        glVertex3f(1.0f, 5.5f,  0.0f);

        // Direita
        glVertex3f(1.5f, 4.5f,  0.5f);
        glVertex3f(1.5f, 4.5f, -0.5f);
        glVertex3f(1.0f, 5.5f,  0.0f);
    glEnd();

    // Base em Y = 4.5, voltada para baixo
    glBegin(GL_QUADS);
        glVertex3f(0.5f, 4.5f, -0.5f);
        glVertex3f(1.5f, 4.5f, -0.5f);
        glVertex3f(1.5f, 4.5f,  0.5f);
        glVertex3f(0.5f, 4.5f,  0.5f);
    glEnd();
}

// Função para desenhar a pirâmide com base quadrada
void desenharPiramide(void) {
    glBegin(GL_QUADS);
        // Cima (Y = 1.0)
        glVertex3f(-5.0f, 1.0f, -5.0f);
        glVertex3f(-5.0f, 1.0f,  5.0f);
        glVertex3f( 5.0f, 1.0f,  5.0f);
        glVertex3f( 5.0f, 1.0f, -5.0f);

        // Baixo (Y = 0)
        glVertex3f(-5.0f, 0.0f, -5.0f);
        glVertex3f( 5.0f, 0.0f, -5.0f);
        glVertex3f( 5.0f, 0.0f,  5.0f);
        glVertex3f(-5.0f, 0.0f,  5.0f);

        // Frente (Z = 5)
        glVertex3f(-5.0f, 0.0f, 5.0f);
        glVertex3f( 5.0f, 0.0f, 5.0f);
        glVertex3f( 5.0f, 1.0f, 5.0f);
        glVertex3f(-5.0f, 1.0f, 5.0f);

        // Trás (Z = -5)
        glVertex3f(-5.0f, 0.0f, -5.0f);
        glVertex3f(-5.0f, 1.0f, -5.0f);
        glVertex3f( 5.0f, 1.0f, -5.0f);
        glVertex3f( 5.0f, 0.0f, -5.0f);

        // Esquerda (X = -5)
        glVertex3f(-5.0f, 0.0f, -5.0f);
        glVertex3f(-5.0f, 0.0f,  5.0f);
        glVertex3f(-5.0f, 1.0f,  5.0f);
        glVertex3f(-5.0f, 1.0f, -5.0f);

        // Direita (X = 5)
        glVertex3f(5.0f, 0.0f, -5.0f);
        glVertex3f(5.0f, 1.0f, -5.0f);
        glVertex3f(5.0f, 1.0f,  5.0f);
        glVertex3f(5.0f, 0.0f,  5.0f);
    glEnd();
}

// Função para calcular as coordenadas de um vértice na superfície de uma esfera
void verticeEsfera(float raio, float anguloVertical, float anguloHorizontal) {
    glVertex3f(
        raio * sinf(anguloVertical) * cosf(anguloHorizontal),
        raio * cosf(anguloVertical),
        raio * sinf(anguloVertical) * sinf(anguloHorizontal)
    );
}

// Função para desenhar uma semiesfera oca com borda superior
void desenharSemiesferaOca(void) {
    const float raioExterno = 2.5f;
    const float raioInterno = 2.3f;
    const int fatias = 32;
    const int faixas = 16;
    const float pi = 3.14159265f;

    // Superfície externa: da borda (Y = 0) até o fundo
    glColor3f(1.0f, 0.5f, 0.0f); // Laranja

    for (int faixa = 0; faixa < faixas; faixa++) {
        float a1 = pi / 2.0f + faixa * (pi / 2.0f) / faixas;
        float a2 = pi / 2.0f + (faixa + 1) * (pi / 2.0f) / faixas;

        glBegin(GL_QUADS);
            for (int fatia = 0; fatia < fatias; fatia++) {
                float b1 = fatia * 2.0f * pi / fatias;
                float b2 = (fatia + 1) * 2.0f * pi / fatias;

                verticeEsfera(raioExterno, a1, b1);
                verticeEsfera(raioExterno, a1, b2);
                verticeEsfera(raioExterno, a2, b2);
                verticeEsfera(raioExterno, a2, b1);
            }
        glEnd();
    }

    // Superfície interna: ordem inversa para ficar visível por dentro
    glColor3f(0.1f, 0.4f, 0.9f); // Azul

    for (int faixa = 0; faixa < faixas; faixa++) {
        float a1 = pi / 2.0f + faixa * (pi / 2.0f) / faixas;
        float a2 = pi / 2.0f + (faixa + 1) * (pi / 2.0f) / faixas;

        glBegin(GL_QUADS);
            for (int fatia = 0; fatia < fatias; fatia++) {
                float b1 = fatia * 2.0f * pi / fatias;
                float b2 = (fatia + 1) * 2.0f * pi / fatias;

                verticeEsfera(raioInterno, a1, b1);
                verticeEsfera(raioInterno, a2, b1);
                verticeEsfera(raioInterno, a2, b2);
                verticeEsfera(raioInterno, a1, b2);
            }
        glEnd();
    }

    // Borda superior: fecha a espessura entre os dois raios
    glColor3f(0.8f, 0.3f, 0.0f); // Laranja mais escuro

    glBegin(GL_QUADS);
        for (int fatia = 0; fatia < fatias; fatia++) {
            float b1 = fatia * 2.0f * pi / fatias;
            float b2 = (fatia + 1) * 2.0f * pi / fatias;

            verticeEsfera(raioExterno, pi / 2.0f, b1);
            verticeEsfera(raioInterno, pi / 2.0f, b1);
            verticeEsfera(raioInterno, pi / 2.0f, b2);
            verticeEsfera(raioExterno, pi / 2.0f, b2);
        }
    glEnd();
}


// Função principal de desenho da cena
void desenharCena(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Afasta e inclina a visualização da cena
    glTranslatef(0.0f, -1.8f, -30.0f);
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);

    // Gira o chão e o prisma juntos
    glRotatef(anguloCena, 0.0f, 1.0f, 0.0f);

    // 1. Desenhar chão
    desenharChao();

    // 2. Desenhar Pilares
    glPushMatrix(); // Pilar 1
        glTranslatef(-10.0f, 0.0f, 10.0f);
        //glRotatef(25.0f, 0.0f, 1.0f, 0.0f);
        glScalef(1.0f, 1.0f, 1.0f);
        desenharPilar();
    glPopMatrix();

    glPushMatrix(); // Pilar 2
        glTranslatef(-10.0f, 0.0f, -10.0f);
        glScalef(1.0f, 1.0f, 1.0f);
        desenharPilar();
    glPopMatrix();

    glPushMatrix(); // Pilar 3
        glTranslatef(10.0f, 0.0f, 10.0f);
        glScalef(1.0f, 1.0f, 1.0f);
        desenharPilar();
    glPopMatrix();

    glPushMatrix(); // Pilar 4
        glTranslatef(10.0f, 0.0f, -10.0f);
        glScalef(1.0f, 1.0f, 1.0f);
        desenharPilar();
    glPopMatrix();

    // 3. Desenhar Triângulo
    glPushMatrix();     // Desenhar Triângulo 1 sobre a base do pilar 1
        glTranslatef(10.0f, 0.0f, -10.0f);              // Posiciona o conjunto na cena
        glTranslatef(1.0f, 0.0f, 0.0f);                 // Vai até o eixo da pirâmide
        glRotatef(anguloTriangulo, 0.0f, 1.0f, 0.0f);   // Gira em torno de Y
        glTranslatef(-1.0f, 0.0f, 0.0f);                // Compensa o deslocamento do eixo
        desenharTriangulo();
    glPopMatrix();

    glPushMatrix();     // Desenhar Triângulo 2 sobre a base do pilar 2
        glTranslatef(-10.0f, 0.0f, -10.0f);
        glTranslatef(1.0f, 0.0f, 0.0f);
        glRotatef(anguloTriangulo, 0.0f, 1.0f, 0.0f);
        glTranslatef(-1.0f, 0.0f, 0.0f);
        desenharTriangulo();    
    glPopMatrix();

    glPushMatrix();     // Desenhar Triângulo 3 sobre a base do pilar 3
        glTranslatef(10.0f, 0.0f, 10.0f);
        glTranslatef(1.0f, 0.0f, 0.0f);
        glRotatef(anguloTriangulo, 0.0f, 1.0f, 0.0f);
        glTranslatef(-1.0f, 0.0f, 0.0f);
        desenharTriangulo();
    glPopMatrix();

    glPushMatrix();     // Desenhar Triângulo 4 sobre a base do pilar 4
        glTranslatef(-10.0f, 0.0f, 10.0f);
        glTranslatef(1.0f, 0.0f, 0.0f);
        glRotatef(anguloTriangulo, 0.0f, 1.0f, 0.0f);
        glTranslatef(-1.0f, 0.0f, 0.0f);
        desenharTriangulo();
    glPopMatrix();

    // 4. Desenhar Pirâmide com 5 camadas
    for (int i = 0; i < 5; i++) {
        float escala = 1.0f - i * 0.18f; // Escalas: 1.00, 0.82, 0.64, 0.46, 0.28

        glPushMatrix();
            glTranslatef(0.0f, i * 1.0f, 0.0f);
            glScalef(escala, 1.0f, escala);
            glColor3f(0.05f + i * 0.12f, 0.35f + i * 0.12f, 0.05f + i * 0.12f);
            desenharPiramide();
        glPopMatrix();
    }

    // 5. Desenhar Esfera 
    glPushMatrix();
        glTranslatef(0.0f, 8.0f, 0.0f);
        desenharSemiesferaOca();
    glPopMatrix();

    glutSwapBuffers();
}

void atualizar(void) {
    int tempoAtual = glutGet(GLUT_ELAPSED_TIME);

    if (tempoAnterior == 0) {
        tempoAnterior = tempoAtual;
    }

    float dt = (tempoAtual - tempoAnterior) / 1000.0f;
    tempoAnterior = tempoAtual;

    anguloCena += 20.0f * dt;

    if (anguloCena >= 360.0f) {
        anguloCena -= 360.0f;
    }

    // Giro dos triângulos em torno do eixo Y, com velocidade de 60 graus por segundo
    anguloTriangulo += 60.0f * dt; // 60 graus por segundo

    if (anguloTriangulo >= 360.0f) {
        anguloTriangulo -= 360.0f;
    }

    glutPostRedisplay();
}

void redimensionar(int largura, int altura) {
    if (altura == 0) {
        altura = 1;
    }

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
    glutCreateWindow("Cenario 3D - Semi Esfera Oca com Borda Superior");

    inicializar();

    glutDisplayFunc(desenharCena);
    glutReshapeFunc(redimensionar);
    glutIdleFunc(atualizar);

    glutMainLoop();
    return 0;
}