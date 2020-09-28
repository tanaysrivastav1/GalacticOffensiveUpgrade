//
// Created by Luke Arnold on 3/8/20.
//

#include "ship.hxx"
#include <cstdlib>
#include <stdlib.h>

const int player_default_lives = 3;

//This shouldn't really be used
Ship::Ship(ge211::Position top_left, ge211::Dimensions init_vel, ge211::Dimensions size, int type)
        : num_lives_{ type == 0 ? player_default_lives : type }
        , type_     { type      }
        , top_left_ { top_left  }
        , velocity_ { init_vel  }
        , size_     { size      }

{ }

// getter functions for the member variables
int Ship::lives() {
    return num_lives_;
}
int Ship::width() {
    return size_.width;
}
int Ship::height() {
    return size_.height;
}
ge211::Position Ship::top_left() {
    return top_left_;
}
int Ship::type() {
    return type_;
}

//adds a life to the ship
void Ship::add_life() {
    num_lives_++;
}
//takes away a life from the ship
void Ship::remove_life() {
    num_lives_--;
}

bool Ship::hits_side(Geometry const &geo) {
    bool left = top_left_.x <= 0;
    bool right = top_left_.x + size_.width >= geo.scene_dims.width;
    return left || right;
}

Enemy::Enemy(ge211::Position top_left, ge211::Dimensions dims, int horiz_velocity, int type)
        : Ship(top_left, {horiz_velocity, 0}, dims, type)
        , top_left0_  { top_left }
        , move_threshold_ { 100 }
{}

// Returns the result of moving this enemy ship by its velocity.
// changes the ship's horizontal velocity to new_vel
// if the ship would move over a certain distance from its original position
// position, reverse its velocity
Enemy Enemy::next() {
    int new_x = top_left_.x + velocity_.width;
    int new_y = top_left_.y + velocity_.height;
    if (abs(new_x - top_left0_.x) > move_threshold_)
    {
        velocity_.width *= -1;
    }
    if (abs(new_y - top_left0_.y) > move_threshold_)
    {
        velocity_.height *= -1;
    }
    Enemy temp(*this);
    //printf("top left before: %i\n", temp.top_left_.x);
    temp.top_left_.x += velocity_.width;
    //printf("top left after: %i\n", temp.top_left_.x);
    temp.top_left_.y += velocity_.height;
    return temp;
}

void Enemy::flip_direction() {
    velocity_.width *= -1;
}

Player::Player(const Geometry &geo)
        : Ship(geo.player_top_left0(), {0, 0}, geo.player_dims_, 0)
{}

void Player::player_to_x(int x) {
    top_left_.x = x;
}
void Player::player_to_y(int y) {
    top_left_.y = y;
}