## COP290 Task2: Maze Game
This is the readme for COP290(Design Practices) Task2: Maze Game.<br>
Contributed by: Arushi Goyal(2020CS50418) and Supreeti Kumari(2020CS10396)<br>

## IITD Maze Treasure Hunt

### Instructions:
- This is a 2-player game with the objective to find treasures using the hints provided. These treasures will earn you points. 
- The player also needs to refrain from entering restricted areas which are indicated through warnings during the course of the game. You receive some penalty upon stumbling over these areas.
- Treasures can also be looked for inside certain buildings.

### Game Controls:
- Use arrow keys to navigate inside the campus.
- Use number keys(1 to 8) to display and hide hints(Press ‘1’ to display first hint and press it again to hide the hint).
- Press ‘E’ to enter a building and press it again to  exit. You can also use the exit button on the building maps to go back to the main map.
- Use letter keys(‘a’ to ‘c’) to display warnings(Press ‘a’ to display first warning and press it again to hide the warning).
- Use the quit button on the main map to quit the game.

### Treasures:
- Ruby worth 150 points
- Sapphire worth 200 points
- Pearl worth 25 points
- Silver worth 75 points
- Gold worth 175 points
- Emerald worth 100 points
- Coins worth 50 points
- Diamond

**General Note**: Each player has 3 lives. You lose one life and earn some penalty upon stumbling over some restricted area. Also, this is a timed game; you have ``` 5 minutes ``` to play this game.<br>

### Winning criteria:

- The player who finds the diamond first wins the game.
- In case no player is able to find the diamond within the designated time, the one with the maximum score at the end of the timer, wins.
- In case a player exhausts all his lives, the other player automatically wins the game. 

---

## How to run the game:

1. Navigate to the location on your system where you want to clone the repository.
2. Clone our git repo using the command: ``` git clone ```  https://github.com/SupreetiKumari/COP290-MazeGame
3. Enter username and PAT as the password.
4. Run ``` cd COP290_MazeGame ```.
5. Depending upon whether you are the server or the client, navigate to the respective folder using ``` cd client/server ```.
6. Run ``` make ```.
7. The game window is visible.

---
Our folder COP290-MazeGame consists of the following contents:

- client folder
- server folder
- IITD Maze Treasure Hunt.pdf: Slides explaining the crux of our game
- Readme.md

A brief description of the files contained within client/server folders:

- hints folder: Consists of 30 hints to the locations where treasures are hidden. 
- warning folder: Consists of 9 warnings about restricted areas.
- treasure: Consists of 8 treasures. These pop-up when you successfully find the hidden treasure using the hints provided. They add to your score depending upon the treasure you found.
- penalty: Consists of 9 penalties which pop-up when you enter restricted areas. They decrease your score depending upon the area you stumbled upon.
- 












Files description-

1. LTexture.cpp- This file contains the class-LTexture and its constructor, deconstructor and functions.
2. Dot.cpp- This file contains the class-Dot ( this the class for the player ) and its constructor, deconstructor and functions.
3. helper.cpp- This contains the helper functions that we have used in our main program for example setwalls etc.
4. sdl_helper.cpp- This contains some other helper functions which mainly uses SDL.

