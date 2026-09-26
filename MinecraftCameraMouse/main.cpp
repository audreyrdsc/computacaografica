#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>
#include "personagem.h"

// https://github.com/nothings/stb/blob/master/stb_image.h
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//Comando build e execução no terminal
//  g++ main.cpp personagem.cpp -o main.exe -lfreeglut -lopengl32 -lglu32  
//  .\main.exe

// Grama
static GLuint texturaGrama;

// Animação da cena
static float anguloCena = 0.0f;
static float anguloTriangulo = 0.0f;
static int tempoAnterior = 0;

// Câmera controlada pelo mouse
static float anguloHorizontal = 0.0f;
static float anguloVertical = 30.0f;
static float distanciaCamera = 30.0f;

static bool arrastandoMouse = false;
static int mouseXAnterior = 0;
static int mouseYAnterior = 0;

const float PI = 3.14159265f;

// ------------------------------------------------------------
// Chão
// ------------------------------------------------------------
void desenharChao(void) {
    glColor3f(1.0f, 1.0f, 1.0f); // Branco, para não tingir a textura

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaGrama);

    float repeticoes = 8.0f; // Quantas vezes a textura se repete pelo chão

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);              glVertex3f(-15.0f, 0.0f, -15.0f);
        glTexCoord2f(0.0f, repeticoes);        glVertex3f(-15.0f, 0.0f,  15.0f);
        glTexCoord2f(repeticoes, repeticoes);  glVertex3f( 15.0f, 0.0f,  15.0f);
        glTexCoord2f(repeticoes, 0.0f);        glVertex3f( 15.0f, 0.0f, -15.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

// ------------------------------------------------------------
// Grama
// ------------------------------------------------------------
GLuint carregarTextura(const char* caminho) {
    int largura, altura, canais;
    unsigned char* dados = stbi_load(caminho, &largura, &altura, &canais, 0);

    if (!dados) {
        printf("Erro ao carregar textura: %s\n", caminho);
        return 0;
    }

    GLenum formato = (canais == 4) ? GL_RGBA : GL_RGB;

    GLuint idTextura;
    glGenTextures(1, &idTextura);
    glBindTexture(GL_TEXTURE_2D, idTextura);

    // Parâmetros de filtragem e repetição
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    gluBuild2DMipmaps(GL_TEXTURE_2D, formato, largura, altura, formato, GL_UNSIGNED_BYTE, dados);

    stbi_image_free(dados);

    return idTextura;
}

// ------------------------------------------------------------
// Pilar: base em Y = 0; topo em Y = 4
// Centro local em X = 1, Z = 0
// ------------------------------------------------------------
void desenharPilar(void) {
    glColor3f(0.7f, 0.65f, 0.5f);

    glBegin(GL_QUADS);
        // Frente
        glVertex3f(0.5f, 0.0f,  0.5f);
        glVertex3f(1.5f, 0.0f,  0.5f);
        glVertex3f(1.5f, 4.0f,  0.5f);
        glVertex3f(0.5f, 4.0f,  0.5f);

        // Trás
        glVertex3f(0.5f, 0.0f, -0.5f);
        glVertex3f(0.5f, 4.0f, -0.5f);
        glVertex3f(1.5f, 4.0f, -0.5f);
        glVertex3f(1.5f, 0.0f, -0.5f);

        // Cima
        glVertex3f(0.5f, 4.0f, -0.5f);
        glVertex3f(0.5f, 4.0f,  0.5f);
        glVertex3f(1.5f, 4.0f,  0.5f);
        glVertex3f(1.5f, 4.0f, -0.5f);

        // Baixo
        glVertex3f(0.5f, 0.0f, -0.5f);
        glVertex3f(1.5f, 0.0f, -0.5f);
        glVertex3f(1.5f, 0.0f,  0.5f);
        glVertex3f(0.5f, 0.0f,  0.5f);

        // Esquerda
        glVertex3f(0.5f, 0.0f, -0.5f);
        glVertex3f(0.5f, 0.0f,  0.5f);
        glVertex3f(0.5f, 4.0f,  0.5f);
        glVertex3f(0.5f, 4.0f, -0.5f);

        // Direita
        glVertex3f(1.5f, 0.0f, -0.5f);
        glVertex3f(1.5f, 4.0f, -0.5f);
        glVertex3f(1.5f, 4.0f,  0.5f);
        glVertex3f(1.5f, 0.0f,  0.5f);
    glEnd();
}

// ------------------------------------------------------------
// Pequena pirâmide sobre um pilar
// Base em Y = 4; ápice em Y = 5.5
// ------------------------------------------------------------
void desenharTriangulo(void) {
    glColor3f(1.0f, 0.05f, 0.05f);

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

    glBegin(GL_QUADS);
        // Base voltada para baixo
        glVertex3f(0.5f, 4.5f, -0.5f);
        glVertex3f(1.5f, 4.5f, -0.5f);
        glVertex3f(1.5f, 4.5f,  0.5f);
        glVertex3f(0.5f, 4.5f,  0.5f);
    glEnd();
}

// Desenha um pilar e sua pirâmide giratória.
// Ambos usam o mesmo centro local: X = 1, Z = 0.
void desenharConjuntoPilar(float x, float z) {
    glPushMatrix();
        glTranslatef(x, 0.0f, z);

        desenharPilar();

        glPushMatrix();
            glTranslatef(1.0f, 0.0f, 0.0f);
            glRotatef(anguloTriangulo, 0.0f, 1.0f, 0.0f);
            glTranslatef(-1.0f, 0.0f, 0.0f);

            desenharTriangulo();
        glPopMatrix();
    glPopMatrix();
}

// ------------------------------------------------------------
// Bloco de uma camada da pirâmide em degraus
// Largura e profundidade locais: 10 unidades
// Altura local: 1 unidade
// ------------------------------------------------------------
void desenharCamadaPiramide(void) {
    glBegin(GL_QUADS);
        // Cima
        glVertex3f(-5.0f, 1.0f, -5.0f);
        glVertex3f(-5.0f, 1.0f,  5.0f);
        glVertex3f( 5.0f, 1.0f,  5.0f);
        glVertex3f( 5.0f, 1.0f, -5.0f);

        // Baixo
        glVertex3f(-5.0f, 0.0f, -5.0f);
        glVertex3f( 5.0f, 0.0f, -5.0f);
        glVertex3f( 5.0f, 0.0f,  5.0f);
        glVertex3f(-5.0f, 0.0f,  5.0f);

        // Frente
        glVertex3f(-5.0f, 0.0f, 5.0f);
        glVertex3f( 5.0f, 0.0f, 5.0f);
        glVertex3f( 5.0f, 1.0f, 5.0f);
        glVertex3f(-5.0f, 1.0f, 5.0f);

        // Trás
        glVertex3f(-5.0f, 0.0f, -5.0f);
        glVertex3f(-5.0f, 1.0f, -5.0f);
        glVertex3f( 5.0f, 1.0f, -5.0f);
        glVertex3f( 5.0f, 0.0f, -5.0f);

        // Esquerda
        glVertex3f(-5.0f, 0.0f, -5.0f);
        glVertex3f(-5.0f, 0.0f,  5.0f);
        glVertex3f(-5.0f, 1.0f,  5.0f);
        glVertex3f(-5.0f, 1.0f, -5.0f);

        // Direita
        glVertex3f(5.0f, 0.0f, -5.0f);
        glVertex3f(5.0f, 1.0f, -5.0f);
        glVertex3f(5.0f, 1.0f,  5.0f);
        glVertex3f(5.0f, 0.0f,  5.0f);
    glEnd();
}

void desenharPiramideEmDegraus(void) {
    for (int i = 0; i < 5; i++) {
        float escala = 1.0f - i * 0.18f;

        glPushMatrix();
            glTranslatef(0.0f, i * 1.0f, 0.0f);
            glScalef(escala, 1.0f, escala);

            // Roxo escuro na base, clareando até o topo
            glColor3f(
                0.25f + i * 0.12f,  // R
                0.05f + i * 0.10f,  // G (sempre baixo, é o que dá a "cara" de roxo)
                0.35f + i * 0.12f   // B
            );

            desenharCamadaPiramide();
        glPopMatrix();
    }
}

// ------------------------------------------------------------
// Semiesfera inferior oca
// ------------------------------------------------------------
void verticeEsfera(float raio,
                   float anguloVertical,
                   float anguloHorizontalEsfera) {
    glVertex3f(
        raio * sinf(anguloVertical) * cosf(anguloHorizontalEsfera),
        raio * cosf(anguloVertical),
        raio * sinf(anguloVertical) * sinf(anguloHorizontalEsfera)
    );
}

void desenharSemiesferaOca(void) {
    const float raioExterno = 2.5f;
    const float raioInterno = 2.3f;
    const int fatias = 32;
    const int faixas = 16;

    // Superfície externa: laranja
    glColor3f(1.0f, 0.5f, 0.0f);

    for (int faixa = 0; faixa < faixas; faixa++) {
        float a1 = PI / 2.0f + faixa * (PI / 2.0f) / faixas;
        float a2 = PI / 2.0f + (faixa + 1) * (PI / 2.0f) / faixas;

        glBegin(GL_QUADS);
            for (int fatia = 0; fatia < fatias; fatia++) {
                float b1 = fatia * 2.0f * PI / fatias;
                float b2 = (fatia + 1) * 2.0f * PI / fatias;

                verticeEsfera(raioExterno, a1, b1);
                verticeEsfera(raioExterno, a1, b2);
                verticeEsfera(raioExterno, a2, b2);
                verticeEsfera(raioExterno, a2, b1);
            }
        glEnd();
    }

    // Superfície interna: azul; ordem dos vértices invertida
    glColor3f(0.1f, 0.5f, 0.9f);

    for (int faixa = 0; faixa < faixas; faixa++) {
        float a1 = PI / 2.0f + faixa * (PI / 2.0f) / faixas;
        float a2 = PI / 2.0f + (faixa + 1) * (PI / 2.0f) / faixas;

        glBegin(GL_QUADS);
            for (int fatia = 0; fatia < fatias; fatia++) {
                float b1 = fatia * 2.0f * PI / fatias;
                float b2 = (fatia + 1) * 2.0f * PI / fatias;

                verticeEsfera(raioInterno, a1, b1);
                verticeEsfera(raioInterno, a2, b1);
                verticeEsfera(raioInterno, a2, b2);
                verticeEsfera(raioInterno, a1, b2);
            }
        glEnd();
    }

    // Borda superior que une as duas superfícies
    glColor3f(0.8f, 0.3f, 0.0f);

    glBegin(GL_QUADS);
        for (int fatia = 0; fatia < fatias; fatia++) {
            float b1 = fatia * 2.0f * PI / fatias;
            float b2 = (fatia + 1) * 2.0f * PI / fatias;

            verticeEsfera(raioExterno, PI / 2.0f, b1);
            verticeEsfera(raioInterno, PI / 2.0f, b1);
            verticeEsfera(raioInterno, PI / 2.0f, b2);
            verticeEsfera(raioExterno, PI / 2.0f, b2);
        }
    glEnd();
}

// ------------------------------------------------------------
// Controles do mouse
// ------------------------------------------------------------
void controlarMouse(int botao, int estado, int x, int y) {
    // Roda do mouse no FreeGLUT
    if (estado == GLUT_DOWN && botao == 3) {
        distanciaCamera -= 2.0f;
    } else if (estado == GLUT_DOWN && botao == 4) {
        distanciaCamera += 2.0f;
    }

    if (distanciaCamera < 8.0f) distanciaCamera = 8.0f;
    if (distanciaCamera > 80.0f) distanciaCamera = 80.0f;

    if (botao == GLUT_LEFT_BUTTON) {
        arrastandoMouse = (estado == GLUT_DOWN);
        mouseXAnterior = x;
        mouseYAnterior = y;
    }

    glutPostRedisplay();
}

void movimentarMouse(int x, int y) {
    if (!arrastandoMouse) return;

    anguloHorizontal += (x - mouseXAnterior) * 0.4f;
    anguloVertical   += (y - mouseYAnterior) * 0.4f;

    if (anguloVertical > 85.0f) anguloVertical = 85.0f;
    if (anguloVertical < -85.0f) anguloVertical = -85.0f;

    mouseXAnterior = x;
    mouseYAnterior = y;

    glutPostRedisplay();
}

// ------------------------------------------------------------
// Desenho e animação
// ------------------------------------------------------------
void desenharCena(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float horizontal = anguloHorizontal * PI / 180.0f;
    float vertical = anguloVertical * PI / 180.0f;

    // Centro da cena para o qual a câmera aponta
    const float alvoX = 0.0f;
    const float alvoY = 3.0f;
    const float alvoZ = 0.0f;

    float cameraX = alvoX
                  + distanciaCamera * cosf(vertical) * sinf(horizontal);

    float cameraY = alvoY
                  + distanciaCamera * sinf(vertical);

    float cameraZ = alvoZ
                  + distanciaCamera * cosf(vertical) * cosf(horizontal);

    gluLookAt(
        cameraX, cameraY, cameraZ,
        alvoX, alvoY, alvoZ,
        0.0f, 1.0f, 0.0f
    );

    // Mantém a rotação automática da cena.
    // Comente esta linha para girar apenas a câmera com o mouse.
    glRotatef(anguloCena, 0.0f, 1.0f, 0.0f);

    desenharChao();

    // Desenha o personagem no centro da cena, sobre a pirâmide em degraus.
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 9.0f);      // Posição do personagem
        glRotatef(180.0f, 0.0f, 1.0f, 0.0f); // Rosto voltado para o centro
        desenharPersonagem();
    glPopMatrix();

    desenharConjuntoPilar(-10.0f,  10.0f);
    desenharConjuntoPilar(-10.0f, -10.0f);
    desenharConjuntoPilar( 10.0f,  10.0f);
    desenharConjuntoPilar( 10.0f, -10.0f);

    desenharPiramideEmDegraus();

    glPushMatrix();
        // O fundo da semiesfera fica em Y = 5,
        // tocando o topo da pirâmide em degraus.
        glTranslatef(0.0f, 8.5f, 0.0f);
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
    if (anguloCena >= 360.0f) anguloCena -= 360.0f;

    anguloTriangulo += 60.0f * dt;
    if (anguloTriangulo >= 360.0f) anguloTriangulo -= 360.0f;

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

    // Grama
    glEnable(GL_TEXTURE_2D);
    texturaGrama = carregarTextura("grama.jpg");
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cenario 3D - Camera com mouse");

    inicializar();

    glutDisplayFunc(desenharCena);
    glutReshapeFunc(redimensionar);
    glutIdleFunc(atualizar);

    glutMouseFunc(controlarMouse);
    glutMotionFunc(movimentarMouse);

    glutMainLoop();
    return 0;
}