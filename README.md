# Stay Alive

[🇺🇸 EN | [🇧🇷 PT](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/README-PT.md)]

This repo contains the Senac's second integrative project and consists of an educational 2D game aimed at teaching high school subjects. The goal is to convey scientific concepts through the theme "forces of nature", integrating them into the game mechanics in an interactive and contextualized way.

The subjects covered include food chain, distillation, Fungi and Plantae kingdoms, ethnobotany, friction and combustion. The game adopts a survival style and is structured in phases, in which each challenge is directly related to one of these contents.

The narrative follows Linus, a high school student who, during his vacation on a cruise, ends up shipwrecked and stranded on an island. To survive the next five days until rescue, he needs to apply his knowledge of biology and natural sciences, facing challenges based on real situations.

- [🖥️ How to run](#%EF%B8%8F-how-to-run)
  - [Build and run it yourself](#build-and-run-it-yourself)
- [🕹️ How to play](#%EF%B8%8F-how-to-play)
- [📹 In-game captures](#-in-game-captures)
  - [Menu and final screens](#menu-and-final-screens)
  - [Map](#map)
  - [Challenges](#challenges)
- [✨ Extra features](#-extra-features)
- [👥 Contributors](#-contributors)
- [🤝 Acknowledgements](#-acknowledgements)
- [📝 License](#-license)

# 🖥️ How to run

~~Download zip file from [Releases](https://github.com/gabe-frasz/stay-alive/releases) page or...~~ (soon)

## Build and run it yourself

<details>
  <summary>Windows</summary>

  1. Open [Visual Studio](https://visualstudio.microsoft.com/)
  2. Clone the repo
  3. Make sure to have [Allegro](https://www.nuget.org/packages/Allegro/) and [AllegroDeps](https://www.nuget.org/packages/AllegroDeps/) packages installed
  4. Run
</details>

<details>
  <summary>Linux</summary>

  1. Download [Allegro library](https://liballeg.org/download.html)
  2. Clone the repo
  3. Compile C code
     - `gcc ./main.c -lm $(pkg-config allegro-5 allegro_font-5 allegro_primitives-5 allegro_image-5 allegro_audio-5 allegro_acodec-5 allegro_video-5 --libs --cflags)`
  5. Run
</details>

# 🕹️ How to play

Follow the signs on the map to find out which challenge to take on. At the beginning of every challenge, a quick tutorial is diplayed.

- **`wasd` or arrow keys** -> moves the character on the map and in the third challenge 
- **left mouse button** -> selects items in some challenges
- **space bar** -> is used in the last challenge

# 📹 In-game captures

## Menu and final screens

![menu screen](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/menu.png)
![good ending screen](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/good-ending.png)
![bad ending screen](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/bad-ending.png)
![rescue](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/rescue.png)

## Map

![map](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/map.gif)

## Challenges

![tutorial](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/tutorial.gif)
![challenge 1](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/challenge-1.png)
![challenge 2](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/challenge-2.png)
![challenge 2 success](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/challenge-2-success.png)
![challenge 3](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/challenge-3.png)
![challenge 4](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/challenge-4.png)
![challenge 5](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/challenge-5.png)
![challenge 5 part 2](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/challenge-5-pt-2.png)
![challenge 5 success](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/challenge-5-success.png)

# ✨ Extra features

**Something in the woods seems to be watching you... watch your steps**

<details>
  <summary>Spoiler</summary>

  ![snake](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/snake.gif)
</details>

**Not everything that looks tasty is safe... your perception can deceive you**

<details>
  <summary>Spoiler</summary>

  ![hallucination](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/hallucination.gif)
</details>

**The ocean may seem like an escape route, but does it really want to let you go?**

<details>
  <summary>Spoiler</summary>

  ![drowning](https://github.com/gabe-frasz/stay-alive/blob/main/_docs/drowning.gif)
</details>

# 👥 Contributors

<a href="https://github.com/manuezi"><img src="https://github.com/manuezi.png" width="70"/></a>
<a href="https://github.com/stefrny"><img src="https://github.com/stefrny.png" width="70"/></a>
<a href="https://github.com/gabe-frasz"><img src="https://github.com/gabe-frasz.png" width="70"/></a>

# 🤝 Acknowledgements

- [Beatriz Paiva](https://github.com/beeepaiva) for the significant collaboration and excellent ideas that enriched the game.
- [Deepnight Games](https://deepnight.net/about/) for the incredible tool used to build the game map.
- [Pixabay community](https://pixabay.com/users/) for the audio library that provided sound ambiance, including ambient and animal sounds.

# 📝 License

[MIT License](https://github.com/gabe-frasz/stay-alive/blob/main/LICENSE) &copy;
