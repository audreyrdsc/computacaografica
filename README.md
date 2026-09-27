# 💻 Repositório de Projetos — Computação Gráfica

<p align="center">
  <b>Universidade Federal do Amapá — UNIFAP</b><br>
  <b>Bacharelado em Ciência da Computação</b><br>
  <b>Disciplina:</b> Computação Gráfica<br>
  <b>Docente:</b> Prof. Dr. Julio Furtado
</p>

<p align="center">
  <b>Discente:</b> Audrey Regison dos Santos Cardoso<br>
  <b>Matrícula:</b> 2024000888
</p>

---

## 📌 Sobre o Repositório

Este repositório reúne as atividades práticas, cenários 3D e aplicações interativas desenvolvidas durante as aulas da disciplina de **Computação Gráfica** no curso de Ciência da Computação da **UNIFAP**. 

Os projetos exploram conceitos fundamentais de síntese de imagens, transformações geométricas 3D (translação, rotação, escala), projeção perspectiva, animação articulada hierárquica, texturização 2D e manipulação interativa de câmeras virtuais utilizando a API gráfica **OpenGL**.

---

## 🛠️ Tecnologias, Requisitos e Bibliotecas

| Componente | Especificação / Descrição |
| :--- | :--- |
| **Linguagem Principal** | C++ (padrão C++11 ou superior) |
| **API Gráfica** | OpenGL (Pipeline de Função Fixa / Legacy OpenGL 1.x-2.x) |
| **Bibliotecas Gráficas** | `FreeGLUT` / `GLUT` (gerenciamento de janelas e eventos) e `GLU` (OpenGL Utility Library) |
| **Carregamento de Texturas** | `stb_image.h` (Biblioteca header-only por Sean Barrett) |
| **Compilador** | `g++.exe` (MinGW-w64 via MSYS64) |
| **Ambiente / IDE** | Visual Studio Code com extensão C/C++ |

---

## 📂 Estrutura de Diretórios e Armazenamento

```
projetos/
├── .vscode/
│   └── tasks.json              # Configuração de build do g++ no VS Code com flags de OpenGL/FreeGLUT
├── exemplos/                   # Exercícios e demonstrativos introdutórios
│   ├── triangulo.cpp          # Renderização 2D primitiva com gradiente de cor RGB por vértice
│   ├── cubo.cpp               # Cubo 3D vermelho animado com rotação contínua e temporizador (glutTimerFunc)
│   └── cenario.cpp            # Cenário 3D procedural (chão, montanhas, árvores, sol e cubo flutuante)
├── semiesfera/                 # Atividade de Modelagem Geométrica 3D
│   ├── atividadeSemiEsfera.cpp# Pirâmide em degraus, pilares com pirâmides flutuantes e semiesfera oca
│   └── atividadeSemiEsfera.exe# Executável compilado da semiesfera
├── MinecraftCameraMouse/       # Projeto Avançado Interativo (Estilo Minecraft)
│   ├── grama.jpg              # Textura em alta resolução para o terreno
│   ├── stb_image.h            # Header para decodificação de imagens (JPG/PNG)
│   ├── personagem.h           # Declaração do modelo e animações do personagem 3D (Steve)
│   ├── personagem.cpp         # Implementação hierárquica do personagem (cabeça, pernas, braços e picareta)
│   ├── main.cpp               # Loop principal, gerenciamento de câmeras, terreno e controles WASD/Mouse
│   └── main.exe               # Executável gerado do projeto Minecraft
├── .gitignore                  # Arquivos ignorados pelo Git (executáveis .exe, binários intermediários)
└── README.md                   # Documentação institucional do repositório
```

---

## 🎮 Projeto Destaque: Minecraft Camera & Mouse

Localizado na pasta `MinecraftCameraMouse/`, este projeto consiste em uma simulação 3D interativa inspirada no universo de **Minecraft**, incorporando movimentação de personagem, animação articulada e suporte a múltiplos modos de câmera.

### 🕹️ Funcionalidades e Animações
- **Personagem Articulado (Steve)**: Modela o personagem com cabeça, olhos, cabelo, tronco, pernas e braços acoplados a uma picareta 3D (cabo de madeira e lâmina metálica).
- **Animação de Caminhada**: Ciclo suave de oscilação das pernas e braços com desaceleração dinâmica ao parar.
- **Golpe de Picareta**: Animação de mineração ativada por comando com cálculo de arco de oscilação.
- **Texturização de Terreno**: Solo 3D texturizado com a imagem `grama.jpg` utilizando a biblioteca `stb_image.h` em modo repetição (`GL_REPEAT`).
- **Elementos do Cenário**: Pirâmide central em degraus, pilares de suporte, pirâmides flutuantes animadas e uma semiesfera oca no topo.

### 🎥 Modos de Câmera Suportados
O sistema oferece 4 visualizações dinâmicas trocadas em tempo real:

1. **Terceira Pessoa (`CAM_TERCEIRA_PESSOA`)**: Câmera orbital livre acoplada ao personagem.
2. **Primeira Pessoa (`CAM_PRIMEIRA_PESSOA`)**: Visão imersiva direto dos olhos do personagem.
3. **Sobre o Ombro (`CAM_SOBRE_OMBRO`)**: Visão de ação próxima ao ombro direito.
4. **Isométrica / Top-Down (`CAM_ISOMETRICA`)**: Visão estratégica superior inclinada.

### 🎮 Mapeamento de Controles

| Tecla / Evento | Ação no Jogo / Sistema |
| :--- | :--- |
| **W / S** ou **Seta Para Cima / Baixo** | Mover o personagem para frente / para trás |
| **A / D** ou **Seta Esquerda / Direita** | Rotacionar o personagem à esquerda / à direita |
| **Barra de Espaço** | Desferir golpe com a picareta |
| **Clique + Arrastar Mouse** | Orbitar/girar a câmera em volta do cenário |
| **Teclas 1, 2, 3, 4** | Alternar entre as câmeras (3ª Pessoa, 1ª Pessoa, Ombro, Isométrica) |

---

## ⚡ Como Compilar e Executar

### 1. Pré-requisitos de Compilação (Windows / MSYS64)
Certifique-se de que o **MinGW-w64** está instalado e adicionado ao `PATH` do sistema com suporte às bibliotecas **FreeGLUT**, **OpenGL** e **GLU**.

### 2. Compilação via Terminal (PowerShell / Command Prompt)

#### 🔸 Compilar o Projeto Minecraft (MinecraftCameraMouse):
```bash
cd MinecraftCameraMouse
g++ main.cpp personagem.cpp -o main.exe -lfreeglut -lopengl32 -lglu32
.\main.exe
```

#### 🔸 Compilar a Atividade da Semiesfera:
```bash
cd semiesfera
g++ atividadeSemiEsfera.cpp -o atividadeSemiEsfera.exe -lfreeglut -lopengl32 -lglu32
.\atividadeSemiEsfera.exe
```

#### 🔸 Compilar Exemplos (Ex: Cenário 3D):
```bash
cd exemplos
g++ cenario.cpp -o cenario.exe -lfreeglut -lopengl32 -lglu32
.\cenario.exe
```

### 3. Compilação via VS Code
Abra o arquivo `.cpp` desejado no VS Code e pressione `Ctrl + Shift + B` (ou acione `Run Build Task`). O arquivo `.vscode/tasks.json` executará o comando do `g++` automaticamente com todas as bibliotecas necessárias vinculadas.

---

<p align="center">
  <b>Universidade Federal do Amapá (UNIFAP) — 2024</b>
</p>
