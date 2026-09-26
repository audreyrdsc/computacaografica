#include "personagem.h"
#include <GL/glut.h>

namespace {

// Guarda o ângulo do golpe e da caminhada, definidos externamente pelo main.cpp
float anguloGolpeAtual = 0.0f;
float anguloCaminhadaAtual = 0.0f;

// Função auxiliar usada apenas neste arquivo.
// O bloco é criado em torno de seu centro (x, y, z).
void desenharBloco(float x, float y, float z,
                   float largura, float altura, float profundidade,
                   float vermelho, float verde, float azul) {
    glPushMatrix();
        glTranslatef(x, y, z);
        glScalef(largura, altura, profundidade);

        glColor3f(vermelho, verde, azul);
        glutSolidCube(1.0);
    glPopMatrix();
}

// Desenha a picareta, relativa ao pivô do ombro (já transladado por fora).
void desenharPicareta(void) {
    glPushMatrix();
        // Relativo ao ombro: desce até a altura da mão, um pouco à frente
        glTranslatef(0.0f, -1.25f, 0.30f);
        glRotatef(60.0f, 1.0f, 0.0f, 0.0f);

        // Cabo (madeira)
        glPushMatrix();
            glTranslatef(0.0f, 0.75f, 0.0f);
            glScalef(0.10f, 1.50f, 0.10f);
            glColor3f(0.45f, 0.28f, 0.12f);
            glutSolidCube(1.0);
        glPopMatrix();

        // Cabeça da picareta (metal)
        glPushMatrix();
            glTranslatef(0.0f, 1.50f, 0.0f);
            glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            glScalef(0.9f, 0.14f, 0.14f);
            glColor3f(0.35f, 0.35f, 0.38f);
            glutSolidCube(1.0);
        glPopMatrix();

    glPopMatrix();
}

} // namespace

void definirAnguloGolpe(float angulo) {
    anguloGolpeAtual = angulo;
}

void definirAnguloCaminhada(float angulo) {
    anguloCaminhadaAtual = angulo;
}

void desenharPersonagem(void) {
    // Perna esquerda (pivô no quadril em Y = 1.30f)
    glPushMatrix();
        glTranslatef(-0.30f, 1.30f, 0.0f);
        glRotatef(anguloCaminhadaAtual, 1.0f, 0.0f, 0.0f);
        desenharBloco(0.0f, -0.65f, 0.0f,
                      0.45f, 1.30f, 0.50f,
                      0.85f, 0.05f, 0.05f);
    glPopMatrix();

    // Perna direita (pivô no quadril em Y = 1.30f, rotação oposta)
    glPushMatrix();
        glTranslatef(0.30f, 1.30f, 0.0f);
        glRotatef(-anguloCaminhadaAtual, 1.0f, 0.0f, 0.0f);
        desenharBloco(0.0f, -0.65f, 0.0f,
                      0.45f, 1.30f, 0.50f,
                      0.85f, 0.05f, 0.05f);
    glPopMatrix();

    // Tronco
    desenharBloco(0.0f, 2.00f, 0.0f,
                  1.20f, 1.40f, 0.55f,
                  0.10f, 0.70f, 0.75f);

    // Braço esquerdo (balança oposto à perna esquerda)
    glPushMatrix();
        glTranslatef(-0.85f, 2.70f, 0.0f); // pivô ombro esquerdo
        glRotatef(-anguloCaminhadaAtual * 0.7f, 1.0f, 0.0f, 0.0f);
        desenharBloco(0.0f, -0.65f, 0.0f,
                      0.45f, 1.30f, 0.50f,
                      0.80f, 0.60f, 0.42f);
    glPopMatrix();

    // Braço direito + picareta (balança na caminhada e executa o golpe)
    float rotacaoBracoDireito = -anguloGolpeAtual + (anguloGolpeAtual > 0.0f ? 0.0f : anguloCaminhadaAtual * 0.7f);

    glPushMatrix();
        glTranslatef(0.85f, 2.70f, 0.0f); // pivô = ombro direito
        glRotatef(rotacaoBracoDireito, 1.0f, 0.0f, 0.0f);

        desenharBloco(0.0f, -0.65f, 0.0f,
                      0.45f, 1.30f, 0.50f,
                      0.80f, 0.60f, 0.42f);

        desenharPicareta();
    glPopMatrix();

    // Cabeça
    desenharBloco(0.0f, 3.20f, 0.0f,
                  1.00f, 1.00f, 1.00f,
                  0.85f, 0.65f, 0.45f);

    // Cabelo
    desenharBloco(0.0f, 3.66f, 0.0f,
                  1.02f, 0.12f, 1.02f,
                  0.12f, 0.08f, 0.05f);

    // Olhos na face voltada para Z positivo
    desenharBloco(-0.20f, 3.30f, 0.505f,
                  0.12f, 0.12f, 0.03f,
                  0.05f, 0.05f, 0.05f);

    desenharBloco( 0.20f, 3.30f, 0.505f,
                  0.12f, 0.12f, 0.03f,
                  0.05f, 0.05f, 0.05f);
}