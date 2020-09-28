
#include "model.hxx"
#include <cstdlib>

Model::Model(Geometry const& geometry)
        : geometry_(geometry)
        , player_(geometry)
        , pturret_ { 20 }
        , turret_level { 5 }
        , wave_ { 1 }
        , level_ { 1 }
        , game_over {false}
        , new_level {true}
        , time  {ge211::time::Timer::future(ge211::time::Duration(geometry_.level_screen_length))}
{
    enemies_ = new_wave(1);
}
//returns top left position of player
ge211::Position Model::player() {
    return player_.top_left();
}
//returns vector of enemies
std::vector<Enemy> Model::enemies() {
    const std::vector<Enemy> baddies = enemies_;
    return baddies;
}
//returns vector of bullets
std::vector<Bullet*> Model::bullets() {
    const std::vector<Bullet*> bullets = bullets_;
    return bullets;
}
//returns level number
int Model::level() {
    return level_;
}
int Model::wave() {
    return wave_;
}

std::vector<Enemy> Model::new_wave(int level_num = -1) {

    //level_num defaults to -1 if not specified
    if (level_num == -1)
    {
        level_num = level_;
    }
    std::vector<Enemy> wave;
    int x_offset = geometry_.enemy_spacing.width + geometry_.enemy_dims().width;
    int y_offset = geometry_.enemy_spacing.height + geometry_.enemy_dims().height;
    for (int i = 0; i < geometry_.enemy_rows; i++){
        for (int j = 0; j < geometry_.enemy_cols; j++) {
            int type = 1;
            int velocity = geometry_.grunt_move_speed_;
            if (level_num >= turret_level && rand() % 100 < pturret_) {
                type = 2;
                velocity = 0;
            }
            Enemy enemy = {{geometry_.side_margin + (j * x_offset), geometry_.top_margin + (i * y_offset)},
                           {geometry_.enemy_dims().width, geometry_.enemy_dims().height},
                           velocity,
                           type};
            wave.push_back(enemy);
        }
    }
    return wave;
}

void Model::move_player(int x, int y) {
    if (x - player_.width()/2 > 0 && x + player_.width()/2 < geometry_.scene_dims.width) {
        player_.player_to_x(x - player_.width()/2);
    }
    if (y - player_.height()/2 > geometry_.scene_dims.height/2 && y + player_.height()/2 < geometry_.scene_dims.height) {
        player_.player_to_y(y - player_.height()/2);
    }


}

// creates a bullet and adds it to the bullets_ array, with varying behavior depending on
// the Ship's type:
/*
 * 0: slow straight up from the ship, enemy_ = false
 * 1: slow straight down from the ship, enemy_ = true
 * 2: fast in the direction of the player ship's center from the ship, enemy_ = true
 */
//(int radius, ge211::Position center, int speed, ge211::Dimensions direction, bool enemy = true)
void Model::fire_bullet(Ship& ship) {
    Bullet* result;
    if (ship.type() == 0) {
        auto* bullet = new Bullet(geometry_.bullet_radius
                , ship.top_left().right_by(ship.width()/2)
                , geometry_.slow_bullet_speed
                , {0, -1}
                , false);
        result = bullet;
        //printf("firing player bullet centered at: %i, %i\n", bullet->top_left().x, bullet->top_left().y);
    } else if (ship.type() == 1) {
        auto* bullet = new Bullet(geometry_.bullet_radius
                ,ship.top_left().right_by(ship.width()/2).down_by(ship.height())
                , geometry_.slow_bullet_speed
                , {0, 1}
                , true);
        result = bullet;
    }
    else if (ship.type() == 2) {
        int x_player_dist = player_.top_left().right_by(player_.width()/2).x - ship.top_left().right_by(ship.width()/2).x;
        int y_player_dist = player_.top_left().down_by(player_.height()/2).y - ship.top_left().down_by(ship.height()).y;
        auto* bullet = new Bullet(geometry_.bullet_radius
                ,ship.top_left().right_by(ship.width()/2).down_by(ship.height())
                , geometry_.fast_bullet_speed
                , {x_player_dist, y_player_dist}
                , true);
        result = bullet;
    } else {
        result = new Bullet(0, {0,0}, 0, {1,1});
    }

    bullets_.push_back(result);
    //printf("added bullet");
    /*
    for (Bullet* bullet : bullets_) {
        printf("at %i, %i\n", bullet->center().x, bullet->center().y);
    }
     */


}

int Model::divide_and_round_up(int numerator, int denominator) {
    return numerator / denominator
           + (((numerator < 0) ^ (denominator > 0)) && (numerator%denominator));
}

bool Model::hits_player(Bullet& bullet) {
    bool sides = player_.top_left().x + player_.width() < bullet.center().x-bullet.radius()
            || bullet.center().x+bullet.radius() < player_.top_left().x;
    bool top_bot = player_.top_left().y + player_.height() < bullet.center().y-bullet.radius()
            || bullet.center().y+bullet.radius() < player_.top_left().y;
    return (!sides && !top_bot);
}




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
void Model::update() {
    if (!game_over) {
        if (time.elapsed_time().milliseconds() >= 0) {
            new_level = false;
            //Move enemy ships and possibly fire, depending on the result of rand()
            for (Enemy &enemy : enemies_) {
                if (enemy.type() == 1) {

                    Enemy temp = enemy.next();
                    // this re-create can't cause problems even though the next()
                    // func can switch the velocity, because the only way that
                    // would happen is if the original position of the ship was
                    // outside the bounds of the window
                    if (temp.hits_side(geometry_)) {
                        enemy.flip_direction();
                        temp = enemy.next();
                    }
                    if (rand() % 1000 < geometry_.grunt_percent_fire_chance) {
                        fire_bullet(enemy);
                    }
                    //printf("moving %i\n", new_vel);
                    enemy = temp;
                } else if (enemy.type() == 2) {
                    if (rand() % 100 < geometry_.turret_percent_fire_chance) {
                        fire_bullet(enemy);
                    }
                }
            }

            // move bullets and check for collisions
            // if any bullets are off screen, mark them dead and remove them from the vector
            for (Bullet *&bullet : bullets_) {
                if (bullet->on_screen(geometry_)) {
                    bullet = bullet->next();
                    if (!bullet->enemy()) {
                        //printf("%i, %i\n", bullet->velocity().width, bullet->velocity().height);

                        bool dead = bullet->destroy_enemies(enemies_);
                        if (dead) {
                            bullet->kill_bullet();
                            /*
                            std::swap(bullets_.back(), bullet);
                            printf("Deleting bullet enemy", bullets_.size());
                            delete bullets_.back();
                            bullets_.pop_back();
                             */
                        }
                    } else if (hits_player(*bullet)) {
                        bullet->kill_bullet();
                        /*
                         std::swap(bullets_.back(), bullet);
                         printf("Deleting bullet player", bullets_.size());
                         delete bullets_.back();
                         bullets_.pop_back();
                          */
                        player_.remove_life();
                        if (player_.lives() <= 0) {
                            game_over = true;
                            break;
                        }
                    }
                } else {
                    bullet->kill_bullet();
                    /*
                    std::swap(bullets_.back(), bullet);
                    printf("Deleting bullet off-screen size: %lu || ", bullets_.size());
                    delete bullets_.back();
                    bullets_.pop_back();
                     */
                    //printf("size: %lu\n", bullets_.size());

                }

            }

            for (int i = 0; i < bullets_.size();) {
                if (!bullets_[i]->live()) {
                    std::swap(bullets_.back(), bullets_[i]);
                    //printf("Deleting bullet\n", bullets_.size());
                    delete bullets_.back();
                    bullets_.pop_back();
                } else {
                    i++;
                }
            }

//  if enemies_ is empty, increase wave_
//  if wave_ is now > divide_and_round_up(level, 2), reset wave_ to 1 and increment level_
//  if 5, refill enemies with new_wave(level_)

            if (enemies_.empty()) {
                wave_++;
                if (wave_ > divide_and_round_up(level_, 2)) {
                    wave_ = 1;
                    level_++;
                    new_level = true;

                    for (Bullet *&bullet : bullets_) {
                        delete bullet;
                    }
                    bullets_.clear();
                    time = ge211::time::Timer::future(ge211::time::Duration(geometry_.level_screen_length));
                }
                enemies_ = new_wave(level_);
            }


        }
    }
}



