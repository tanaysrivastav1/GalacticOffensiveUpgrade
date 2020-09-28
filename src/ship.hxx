//
// Created by Luke Arnold on 3/7/20.
//
#pragma once
#include "geometry.hxx"

// A general description of a ship
struct Ship
{
    Ship(ge211::Position top_left, ge211::Dimensions init_vel, ge211::Dimensions size, int type=1);
protected:
    //The number of lives, default 1
    int num_lives_;


    //0 = player, 1 = Grunt, 2 = Turret
    int type_;

    //the top left corner of the ship
    ge211::Position top_left_;



    ge211::Dimensions velocity_;

    ge211::Dimensions size_;


public:




    // getter functions for the member variables
    int lives();
    int width();
    int height();
    ge211::Position top_left();
    int type();

    //adds a life to the ship
    void add_life();
    //takes away a life from the ship
    void remove_life();

    //checks if the ship hits the side of the geometry
    bool hits_side(Geometry const &geo);




};

//contains specifics for enemy ships
struct Enemy : Ship {

    //Constructs a new enemy at top_left, defaulting to a Grunt enemy unless specified otherwise
    // type cannot be 0
    // if type=2, horiz_velocity should be ignored, and velocity_ set to {0,0}
    Enemy(ge211::Position top_left, ge211::Dimensions dims, int horiz_velocity, int type = 1);

    // original position of top_left;
    // used to move the ships
    ge211::Position top_left0_;

    int move_threshold_;


    // Returns the result of moving this enemy ship by its velocity.
    // if it moves over a certain distance from its original
    // position, reverse its velocity
    Enemy next();


    void flip_direction();
};

//contains specifics for player ship
struct Player : Ship {


    // creates a new player ship with num_lives lives
    explicit Player(const Geometry &geo);

    //moves the player ship's top left corner to the given x and y.
    void player_to_x(int x);
    void player_to_y(int y);
};
