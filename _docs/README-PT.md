# Stay Alive

[[🇺🇸 EN](https://github.com/gabe-frasz/stay-alive#stay-alive) | 🇧🇷 PT]

🏆 <mark>***Um dos jogos mais curtidos no Senac***</mark> 🏆

Este repositório contém o segundo projeto integrador do Senac e consiste em um jogo 2D educacional voltado ao ensino de disciplinas do ensino médio. O objetivo é transmitir conceitos científicos por meio do tema "forças da natureza", integrando-os à mecânica do jogo de forma interativa e contextualizada.

Os assuntos abordados incluem cadeia alimentar, destilação, reinos Fungi e Plantae, etnobotânica, atrito e combustão. O jogo adota um estilo de sobrevivência e é estruturado em fases, em que cada desafio está diretamente relacionado a um desses conteúdos.

A narrativa acompanha Linus, um estudante do ensino médio que, durante suas férias em um cruzeiro, acaba naufragando e ficando preso em uma ilha. Para sobreviver aos próximos cinco dias até o resgate, ele precisa aplicar seus conhecimentos de biologia e ciências naturais, enfrentando desafios baseados em situações reais.

[One sheet paper](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/one-sheet-paper.pdf) com os conceitos e as ideias principais por trás do jogo.

[Pôster](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/poster.pdf) para a apresentação final.

- [🖥️ Como rodar](#%EF%B8%8F-como-rodar)
  - [Fazer o build e rodar você mesmo](#fazer-o-build-e-rodar-você-mesmo)
- [🕹️ Como jogar](#%EF%B8%8F-como-jogar)
- [📹 Capturas do jogo](#-capturas-do-jogo)
  - [Menu e telas finais](#menu-e-telas-finais)
  - [Mapa](#mapa)
  - [Desafios](#desafios)
- [✨ Funcionalidades extra](#-funcionalidades-extra)
- [👥 Contribuidores](#-contribuidores)
- [🤝 Agradecimentos](#-agradecimentos)
- [📝 Licença](#-licença)

# 🖥️ Como rodar

**Windows:** Faça o download do instalador na [página do Senac BCC na itch.io](https://bccsenac.itch.io/stay-alive)

**Linux:** Faça o download do arquivo zip na [página Releases](https://github.com/gabe-frasz/stay-alive/releases)

## Fazer o build e rodar você mesmo

<details>
  <summary>Windows</summary>

  1. Abra o [Visual Studio](https://visualstudio.microsoft.com/)
  2. Clone o repositório
  3. Instale os pacotes [Allegro](https://www.nuget.org/packages/Allegro/) e [AllegroDeps](https://www.nuget.org/packages/AllegroDeps/)
  4. Execute
</details>

<details>
  <summary>Linux</summary>

  1. Faça o download da [biblioteca Allegro](https://liballeg.org/download.html)
  2. Clone o repositório
  3. Compile o código C
     - `gcc ./main.c -lm $(pkg-config allegro-5 allegro_font-5 allegro_primitives-5 allegro_image-5 allegro_audio-5 allegro_acodec-5 allegro_video-5 --libs --cflags)`
  5. Execute
</details>

# 🕹️ Como jogar

Siga as placas no mapa para saber qual desafio você deve ir. No começo de cada desafio, um rápido tutorial será disponibilizado.

- **`wasd` ou setas** -> movem o personagem pelo mapa e no terceiro desafio 
- **botão esquerdo do mouse** -> seleciona os items em alguns desafios
- **barra de espaço** -> é usada no último desafio

# 📹 Capturas do jogo

## Menu e telas finais

![menu](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/menu.png)
![tela do final bom](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/good-ending.png)
![tela do final ruim](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/bad-ending.png)
![resgate](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/rescue.png)

## Mapa

![mapa](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/map.gif)

## Desafios

![tutorial](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/tutorial.gif)
![desafio 1](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/challenge-1.png)
![desafio 2](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/challenge-2.png)
![desafio 2 sucesso](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/challenge-2-success.png)
![desafio 3](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/challenge-3.png)
![desafio 4](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/challenge-4.png)
![desafio 5](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/challenge-5.png)
![desafio 5 parte 2](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/challenge-5-pt-2.png)
![desafio 5 sucesso](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/challenge-5-success.png)

# ✨ Funcionalidades extra

**Algo na floresta parece estar te observando... Cuidado com seus passos**

<details>
  <summary>Spoiler</summary>

  ![cobra](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/snake.gif)
</details>

**Nem tudo que parece gostoso é seguro de comer... sua percepção pode enganar você**

<details>
  <summary>Spoiler</summary>

  ![alucinação](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/hallucination.gif)
</details>

**O oceano pode parecer uma rota de fuga, mas será que ele realmente quer te deixar ir?**

<details>
  <summary>Spoiler</summary>

  ![afogamento](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/drowning.gif)
</details>

# 👥 Contribuidores

<a href="https://github.com/manuezi"><img src="https://github.com/manuezi.png" width="70"/></a>
<a href="https://github.com/stefrny"><img src="https://github.com/stefrny.png" width="70"/></a>
<a href="https://github.com/gabe-frasz"><img src="https://github.com/gabe-frasz.png" width="70"/></a>

# 🤝 Agradecimentos

- [Beatriz Paiva](https://github.com/beeepaiva) pela colaboração significativa e ideias excelentes que enriqueceram o jogo.
- [Deepnight Games](https://deepnight.net/about/) pela ferramenta incrível utilizada para montar o mapa do jogo.
- [Comunidade Pixabay](https://pixabay.com/users/) pela biblioteca de áudios que forneceram os sons ambientes.
- [Senac BCC e Thiago Claro](https://bccsenac.itch.io/) por reconhecerem o esforço e colocarem o jogo em destaque.

# 📝 Licença

[MIT License](https://github.com/gabe-frasz/stay-alive/blob/main/LICENSE) &copy;
