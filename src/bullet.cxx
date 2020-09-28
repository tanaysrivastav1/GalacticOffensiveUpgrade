

#include "bullet.hxx"
#include <cmath>

Bullet::Bullet(int radius, ge211::Position center, int speed, ge211::Dimensions direction, bool enemy )
        : radius_   { radius }
        , center_   { center }
        , live_     { true }
        , enemy_    { enemy }
        , velocity_ { 0,1 }
{
    double direction_length = sqrt(pow(direction.width, 2) + pow(direction.height, 2));
    velocity_.width = (int) (speed * direction.width/direction_length);
    velocity_.height = (int) (speed * direction.height/direction_length);
    //printf("New bullet with velocity: %i, %i at center: %i, %i\n", velocity_.width, velocity_.height, center_.x, center_.y);
}

ge211::Position Bullet::top_left() const {
    return center_.up_left_by({radius_, radius_});
}

//getter funcs for all the private stuff
int Bullet::radius() {
    return radius_;
}
ge211::Dimensions Bullet::velocity() {
    return velocity_;
}
ge211::Position Bullet::center() {
    return center_;
}
bool Bullet::live() {
    return live_;
}
bool Bullet::enemy() {
    return enemy_;
}

//returns a new bullet whose position has been updated by adding velocity
Bullet* Bullet::next() {
    auto* temp = new Bullet(*this);
    temp->center_.x += velocity_.width;
    temp->center_.y += velocity_.height;
    return temp;
}

//checks if the bullet's bounding box intersects with the given ship
bool Bullet::hits_enemy(Enemy & ship) const{
    int left_ball = center_.x-radius_;
    int right_ball = center_.x+radius_;
    int top_ball = center_.y-radius_;
    int bottom_ball = center_.y+radius_;
    bool sides = ship.top_left().x + ship.width() < left_ball || right_ball < ship.top_left().x;
    bool top_bot = ship.top_left().y + ship.height() < top_ball || bottom_ball < ship.top_left().y;
    return (!sides && !top_bot);
}

void Bullet::kill_bullet() {
    live_ = false;
}

// Collision detection between the bullet and the whole vector of ships. If
// the ball is live and collides with some ship then that ship loses a life
// and the bullet is made no longer live. If the ship is out of lives, it is
// removed from the vector. Only registers collisions between bullets and
// ships on different teams. I.E. if bullet.enemy == true, then it will not
// destroy any enemy ships. Returns true if there is a collision, and false
// otherwise
bool Bullet::destroy_enemies(std::vector<Enemy>& ships) {
    for (Enemy& ship : ships) {
        if (live_) {
            ///THIS IS SUS LOGIC VVV
            if ((!enemy_ && ship.type()) || (enemy_ && !ship.type())) {
            ///THIS IS SUS LOGIC ^^^
                if (hits_enemy(ship)) {
                    ship.remove_life();
                    if (ship.lives() <= 0) {
                        std::swap(ships.back(), ship);
                        ships.pop_back();
                    }
                    kill_bullet();
                    return true;
                }
            }
        }
    }
    return false;
}

//returns false if the bullet is completely off the screen, and true otherwise
bool Bullet::on_screen(Geometry const& geo) {
    bool off_top = 0 > (center_.y + radius_);
    bool off_side = 0 > (center_.x + radius_) || geo.scene_dims.width < (center_.x - radius_);
    bool off_bottom = geo.scene_dims.height < (center_.y - radius_);

    return !(off_top || off_side || off_bottom);
}

bool operator==(Bullet & b1, Bullet & b2)
{
    return (b1.radius()==b2.radius() && b1.center()==b2.center() && b1.velocity()==b2.velocity() && b1.live()==b2.live());
}

