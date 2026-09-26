#ifndef PERSONAGEM_H
#define PERSONAGEM_H

// Desenha o personagem com os pés em Y = 0.
// Sua posição na cena é definida pelo programa principal.
void desenharPersonagem(void);

// Define o ângulo atual do golpe da picareta (0 = parado, controlado pelo main.cpp).
void definirAnguloGolpe(float angulo);

// Define o ângulo de rotação das pernas durante a caminhada.
void definirAnguloCaminhada(float angulo);

#endif