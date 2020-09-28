#include "model.hxx"
#include <catch.hxx>
/*
 * NOT DONE YET
 */


TEST_CASE("initial level player position");
{
    Model m;

    CHECK (m.player_.top_left == m.geometry_.player_top_left0());

    //Not sure how exactly we want the waves to be initially structured,
    // but once we figure that out it would go here
    std::vector<Enemy>& expected;
    CHECK( m.enemies() == expected);

    m.update();

    //again, not sure what the default velocities and various things
    // will be, but this would contain those.
    std::vector<Enemy>& updated;
    CHECK( m.enemies() == updated);
}

TEST_CASE("bullet hit ship");
{
    Geometry geo;
    Bullet bullet({10, 100}, geo, {1,0} false, 0);
    Enemy bad_guy(ge211::geometry::Position(0, 0), <#initializer#>, 0,
                  {10 + geo.bullet_radius + 1, 100 - geo.enemy_dims().height / 2}, geo, 2, 0);

    std::vector<Enemy>& enemies = {bad_guy};
    CHECK (!bullet.destroy_ship(enemies));
    bullet = bullet.next();
    //minus one life
    CHECK (bullet.destroy_ship(enemies));
    //minus second life
    CHECK (bullet.destroy_ship(enemies));
    CHECK (enemies.empty());

}

TEST_CASE("Ship movement");
{
    Geometry geo;
    //Grunts move default 5 pixels per update
    Enemy bad_guy(ge211::geometry::Position(0, 0), <#initializer#>, 0, {20, 100}, geo, 1, 0);
    bad_guy = bad_guy.next();
    CHECK (bad_guy.top_left() == {25, 100});

    //turrets don't move
    Enemy turret(ge211::geometry::Position(0, 0), <#initializer#>, 0, {20, 100}, geo, 2, 0);
    turret = turret.next();
    CHECK (turret.top_left() == {20, 100});

    //player can be moved anywhere
    Player guy(geo);
    guy.player_to(5, 5);
    CHECK( guy.top_left() == {5, 5});
}

TEST_CASE("TURRETS AT, and not before LEVEL 5");
{
    Model m;

    for (int i = 1; i < 5; i++) {
        std::vector<Enemy> new_wave = m.new_wave(i);
        for (Enemy ship(ge211::geometry::Position(0, 0), <#initializer#>, 0, ge211::geometry::Position(0, 0),
                        ge211::geometry::Dimensions(), 0, 0)
: new_wave) {
            CHECK (ship.type() == 1);
        }
    }
    bool has_turret= false;
    bool has_grunt = false;
    std::vector<Enemy> new_wave = m.new_wave(5);
    for (Enemy ship(ge211::geometry::Position(0, 0), <#initializer#>, 0, ge211::geometry::Position(0, 0),
                    ge211::geometry::Dimensions(), 0, 0)
: new_wave) {
        if (ship.type() == 1) has_grunt = true;
        else if (ship.type() == 2) has_turret = true;
    }
    CHECK (has_grunt);
    CHECK (has_turret);
}

TEST_CASE("WAVE SPAWNING");
{
    Model m;
    //Not sure how exactly we want the waves to be initially structured,
    // but once we figure that out it would go here
    std::vector<Enemy> expected_lvl2;
    CHECK (m.new_wave(2) == expected_lvl2)
}