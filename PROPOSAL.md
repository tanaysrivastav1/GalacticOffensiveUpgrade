#Proposal: Galactic Offensive

——Synopsis——
The player controls a spaceship and must destroy enemy ships by shooting them with the ship's cannon.

Elements:
    - A (variable) number of Enemy ships
    - The player's ship, controlled by the mouse
    - The bullets shot by both the player and the enemies

Goal:
The game isn't truly beatable, as the levels will continue to semi-randomly generate according to the level number. Therefore, the goal of the game is for the player to progress as far as possible before losing all their lives.

Gameplay:
The player's ship starts at the bottom of the screen, and the enemy waves come from the top of the screen and shoot at the player. The player ship is moved by the mouse, and the player can fire bullets by left-clicking. If a ship is hit by a bullet, it loses a life. If a ship runs out of lives, it is destroyed. When the player loses a life, they respawn in the original place and are given a short period of invulnerability. Each level consists of a number of "waves" of enemies equal to the level number divided by 2 and rounded up, so level 1 has one wave, level 4 has 2 waves, and level 11 has 6 waves. The waves increase in difficulty as the player progresses.

——Functional Requirements——
1.  Bullets have collision detection with ships. 
2.  The player's ship follows  the mouse, but cannot move above the bottom half of the screen.
3.  The player's ship begins with a set number of lives (probably 3)
4.  The player can shoot by pressing the spacebar.
5.  There are two types of enemy ship:
    a. Grunts, which move back and forth horizontally and fire slow bullets straight down
    b. Turrets, which do not move but fire fast bullets in the direction of the player and have 2 lives
6.  Turrets begin appearing at level 5
7.  Once the player destroys all the enemies in a given level, the playing field is reset to a new level
8.  Each level contains level_num/2 rounded up waves of enemies
9.  If a ship is hit by an enemy bullet, it loses a life (no friendly fire). 
10. If a ship runs out of lives, it is destroyed.
11. There is an indicator somewhere on the screen of the current level and wave progress, as well as the player's remaining lives
12. If the player loses all lives, the screen is replaced with a Game Over Screen that displays the score(level) the player reached.



