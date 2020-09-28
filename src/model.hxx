#pragma once


#include <vector>
#include <ge211.hxx>
#include "geometry.hxx"
#include "ship.hxx"
#include "bullet.hxx"


struct Model {


    /// Member Variables
    Geometry const geometry_;
    std::vector<Enemy> enemies_;
    std::vector<Bullet*> bullets_;
    Player player_;
    int turret_level;
    //percent chance of spawning a turret after lvl turret_level
    double pturret_;

    //current level and wave number
    int level_;
    int wave_;

    //true when the player's lives == 0
    bool game_over;

    ge211::time::Timer time;

public:
    /// Constructor
    // Constructs a model from its geometry.
    explicit Model(Geometry const& geometry = Geometry());


    bool new_level;

    /// Member Functions
    //returns position of player
    ge211::Position player();
    //returns vector of enemies
    std::vector<Enemy> enemies();
    //returns vector of bullets
    std::vector<Bullet *> bullets();
    //returns level number
    int level();



    /*
     * Updates the game state for one frame. This entails:
     * 1. move all enemy ships. if moving an enemy ship would cause it
     *      to hit a side, then reflect the velocity horizontally
     * 2. move all bullets and check for collisions using Bullet::destroy_ship(std::vector<Ship>& ships)
     * 3. If any bullets move off screen, mark them dead
     * 4. remove all dead bullets from bullets_
     * 5. if enemies_ is empty, increase wave_
     * 6. if wave_ is now > divide_and_round_up(level, 2), reset wave_ to 1 and increment level_
     * 7. if 5, refill enemies with new_wave(level_)
     */
    void update();

    //moves the player ship to x and y
    void move_player(int x, int y);

    // fires and returns a bullet, with varying behavior depending on
    // the Ship's type:
    /*
     * 0: slow straight up from the ship, enemy_ = false
     * 1: slow straight down from the ship, enemy_ = true
     * 2: fast in the direction of the player ship's center from the ship, enemy_ = true
     */
    void fire_bullet(Ship& ship);



    //divides a/b, and rounds up the answer.
    static int divide_and_round_up(int numerator, int denominator);

    // generates a wave of enemies. If level_num >=5,
    // includes turrets. otherwise, the returned vector
    // should only include Grunts
    std::vector<Enemy> new_wave(int level_num);


    bool hits_player(Bullet &bullet);

    int wave();
};

