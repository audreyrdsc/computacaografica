#include "personagem.h"
#include <GL/glut.h>

namespace {

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

// Desenha a picareta, saindo da mão direita do personagem.
void desenharPicareta(void) {
    glPushMatrix();
        // Posição de partida: mão direita, um pouco à frente do corpo
        glTranslatef(0.85f, 1.45f, 0.30f);

        // Inclina o cabo para a FRENTE (rotação em torno de X, não Z)
        glRotatef(60.0f, 1.0f, 0.0f, 0.0f);

        // Cabo (madeira)
        glPushMatrix();
            glTranslatef(0.0f, 0.75f, 0.0f);
            glScalef(0.10f, 1.50f, 0.10f);
            glColor3f(0.45f, 0.28f, 0.12f);
            glutSolidCube(1.0);
        glPopMatrix();

        // Cabeça da picareta (metal) — perpendicular ao cabo, apontando para frente/trás
        glPushMatrix();
            glTranslatef(0.0f, 1.50f, 0.0f);
            glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // gira em torno do eixo do CABO (Y)
            glScalef(0.9f, 0.14f, 0.14f);
            glColor3f(0.35f, 0.35f, 0.38f);
            glutSolidCube(1.0);
        glPopMatrix();

    glPopMatrix();
}

} // namespace

void desenharPersonagem(void) {
    // Pernas vermelhas: a parte inferior fica em Y = 0
    desenharBloco(-0.30f, 0.65f, 0.0f,
                  0.45f, 1.30f, 0.50f,
                  0.85f, 0.05f, 0.05f);

    desenharBloco( 0.30f, 0.65f, 0.0f,
                  0.45f, 1.30f, 0.50f,
                  0.85f, 0.05f, 0.05f);

    // Tronco
    desenharBloco(0.0f, 2.00f, 0.0f,
                  1.20f, 1.40f, 0.55f,
                  0.10f, 0.70f, 0.75f);

    // Braços
    desenharBloco(-0.85f, 2.05f, 0.0f,
                  0.45f, 1.30f, 0.50f,
                  0.80f, 0.60f, 0.42f);

    desenharBloco( 0.85f, 2.05f, 0.0f,
                  0.45f, 1.30f, 0.50f,
                  0.80f, 0.60f, 0.42f);

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

    desenharPicareta();
}