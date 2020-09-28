//
// Created by Luke Arnold on 3/7/20.
//

#include "geometry.hxx"
#include "ship.hxx"

// position, size, speed of bullets, plus some methods to deal with them
struct Bullet {


    //creates a bullet at center, if speed =0, velocity_=geometry_.slow_bullet_speed,
    // and if speed = 1, velocity_=geometry.fast_bullet_speed.
    // All other parameters should also be gotten from geometry.
    // Bullets start live, and default to the enemy team
    Bullet(int radius, ge211::Position center, int speed, ge211::Dimensions direction, bool enemy = true);
private:
    // The radius of the bullet.
    int radius_;

    // The velocity of the bullet in pixels per tick.
    ge211::Dimensions velocity_;

    // The position of the center of the bullet.
    ge211::Position center_;

    //if the bullet is live or not
    bool live_;

    //true if fired by an enemy, false if from player
    bool enemy_;

public:

    //getter funcs for all the private stuff
    int radius();
    ge211::Dimensions velocity();
    ge211::Position center();
    bool live();
    bool enemy();

    //returns the position of the top left corner of the ball
    ge211::Position top_left() const;

    //returns a new bullet whose position has been updated by adding velocity
    Bullet * next();

    //checks if the bullet's bounding box intersects with the given ship
    bool hits_enemy(Enemy & ship) const;

    void kill_bullet();

    // Collision detection between the bullet and the whole vector of ships. If
    // the ball is live and collides with some ship then that ship loses a life
    // and the bullet is made no longer live. If the ship is out of lives, it is
    // removed from the vector. Only registers collisions between bullets and
    // ships on different teams. I.E. if bullet.enemy == true, then it will not
    // destroy any enemy ships. Returns true if there is a collision, and false
    // otherwise
    bool destroy_enemies(std::vector<Enemy>& ships);

    //returns false if the bullet is completely off the screen, and true otherwise
    bool on_screen(Geometry const& geo);


};

bool operator==(Bullet &, Bullet &);