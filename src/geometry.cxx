//
// Created by Luke Arnold on 3/7/20.
//

#include "geometry.hxx"

Geometry::Geometry() noexcept
        : enemy_cols        {    5 }
        , enemy_rows        {    3 }
        , top_margin        {  100 }
        , side_margin       {  170 }
        , enemy_depth       {  300 }
        , bottom_margin     {   50 }
        , bullet_radius     {   10 }
        , fast_bullet_speed {    5 }
        , slow_bullet_speed {    3 }
        , enemy_spacing     {   50,  20 }
        , scene_dims        { 1024, 768 }
        , player_dims_      {   40,  40 }
        , max_ship_velocity {   5 }
        , grunt_percent_fire_chance  { 1 }
        , turret_percent_fire_chance { 1 }
        , grunt_move_speed_     { 5 }
        , level_screen_length   { 3 }


{ }

ge211::Position Geometry::player_top_left0() const noexcept
{
    return { scene_dims.width / 2,
             scene_dims.height - bottom_margin - player_dims_.height };
}


// Computes how large each brick can be (in a given dimension), given the
// total number of pixels available in that dimension, the number of bricks
// in that dimensions, and the number of space pixels to leave in between.
//
// PRECONDITION: divisor > 0
static int div_w_spacing(int total, int divisor, int space)
{
    if (divisor > 0)
        return (total - (divisor - 1) * space) / divisor;

    throw ge211::Client_logic_error("need at least 1 row & 1 column");
}

// Computes the dimensions of each brick from the other parameters.
ge211::Dimensions Geometry::enemy_dims() const noexcept
{
    ge211::Dimensions field{scene_dims.width - 2 * side_margin,
                            enemy_depth - top_margin};
    int width  = div_w_spacing(field.width, enemy_cols, enemy_spacing.width);
    int height = div_w_spacing(field.height, enemy_rows, enemy_spacing.height);
    return {width, height};
}
