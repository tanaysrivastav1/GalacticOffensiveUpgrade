#pragma once

#include <ge211.hxx>

//adapting the geometry struct from Brick_out
struct Geometry
{
    // Constructs an instance with the default parameters.
    Geometry() noexcept;

    // The dimensions of the whole window:
    ge211::Dimensions scene_dims;


    // The dimensions of the player's ship:
    ge211::Dimensions player_dims_;

    // Number of columns of enemies per wave:
    int enemy_cols;

    // Number of rows of enemies per wave:
    int enemy_rows;

    // The number of pixels of space between each column and row of
    // enemy ships:
    ge211::Dimensions enemy_spacing;

    // The radius of bullets:
    int bullet_radius;

    // speed of fast bullets, exact velocities are handled in ball constructor:
    int fast_bullet_speed;

    // slow bullet speed, exact velocities are handled in ball constructor:
    int slow_bullet_speed;

    // Number of pixels from top of screen to top of enemy formation:
    int top_margin;

    // Number of pixels from sides of screen to sides of enemy formation:
    int side_margin;

    // Number of pixels from *top* of screen to *bottom* of enemy formation.
    int enemy_depth;

    // Number of pixels from bottom of screen to bottom of player.
    int bottom_margin;

    //maximum velocity of an enemy ship
    int max_ship_velocity;

    int grunt_percent_fire_chance;
    int turret_percent_fire_chance;
    int grunt_move_speed_;

    int level_screen_length;



    // The initial position of the player. This is a member function because
    // it's computed from the other properties.
    ge211::Position player_top_left0() const noexcept;

    // The dimensions of the enemy ships. Also computed from the other properties.
    //
    // PRECONDITIONS (asserted):
    //  - enemy_cols > 0
    //  - enemy_rows > 0
    ge211::Dimensions enemy_dims() const noexcept;
};
