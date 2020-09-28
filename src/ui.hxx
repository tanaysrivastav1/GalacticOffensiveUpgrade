//
// Defines the structure of the user interface
//

#pragma once

#include "model.hxx"
#include <ge211.hxx>

///
/// VIEW CONSTANTS
///
// These constants are defined in 'ui.cpp' but declared here for use in the
// sprite declaration
extern ge211::Color const enemy_bullet_c, player_bullet_c, player_c, grunt_c, turret_c;



// this struct inherits from abstract game to take advantage of the
// built in game functionality in ge211
struct Ui : ge211::Abstract_game
{
    ///
    /// CONSTRUCTOR
    ///

    // Constructs the ui given a reference to the model. AKA the damn
    // thing is controled by a separate structure.
    explicit Ui(Model&);

    ///
    /// MEMBER FUNCTIONS FOR THE VIEW
    ///

    // returns the window dimensions based on the geometry
    ge211::Dimensions initial_window_dimensions() const override;

    // renders all the sprites to the screen so they are viewable
    // in the initial positions defined by the geometry and then
    // by the new postions defined by the model
    void draw(ge211::Sprite_set&) override;

    ///
    /// MEMBER FUNCTIONS
    ///

    // Defines how the game responds to key down input. Game is controlled
    // completely by key input.
    // recognized  key strokes:
    //
    // 'w', 's', Key::up(), Key::down()
    void on_key_down(ge211::Key) override;

    // negates any key stroke made by onn_key_down
    void on_key_up(ge211::Key) override;

    // on_key is used for the space bar to fire and for q to quit
    void on_key(ge211::Key) override;

    //mouse moved is for moving the player
    void on_mouse_move(ge211::Position position) override;

    //fires a bullet whenever the player clicks
    void on_mouse_down(ge211::Mouse_button, ge211::Position) override;

    // Updates the model by calling Model::update()
    //
    // picks a random double between 0 and 2pi as the angle of initial
    // or random bounce. Also picks a random boost to add to the magnitude
    // of the velocity which will be then broken into it's components.
    void  on_frame(double dr) override;

    ///
    /// MEMBER VARIABLES
    ///

    // this is a reference to the model that is first created in the client
    // function and passed to the ui constructor
    Model& model_;


    // this is the number of frames since the start of the game
    int frames_ = 0;

    int const size;



    ///
    /// SPRITE VARIABLES
    ///

    // These are the objects that are controlled by the model and will
    // be displayed to the screen. Each are defined by the geometry unless
    // they are modified by a powerup. That will be done in the model.

    ge211::Circle_sprite    const
            enemy_bullet_sprite_        {model_.geometry_.bullet_radius,  enemy_bullet_c};

    ge211::Circle_sprite    const
            player_bullet_sprite_        {model_.geometry_.bullet_radius,  player_bullet_c};

    ge211::Rectangle_sprite const
            player_sprite_      {model_.geometry_.player_dims_, player_c};

    ge211::Rectangle_sprite const
            grunt_sprite_            {model_.geometry_.enemy_dims(), grunt_c};

    ge211::Rectangle_sprite const
            turret_sprite_         {model_.geometry_.enemy_dims(), turret_c};



    //  these lines create sprites text for player
    ge211::Font sans = ge211::Font("sans.ttf", size);
    ge211::Font arcade = ge211::Font("ARCADECLASSIC.ttf", size * 5);
    ge211::Font end_level_text = ge211::Font("ARCADECLASSIC.ttf", size * 4);

    // creates and returns a text sprite for the current level.
    ge211::Text_sprite get_level_sprite(int level);
    ge211::Text_sprite get_wave_sprite(int wave);


    ge211::Text_sprite      level_text = ge211::Text_sprite::Builder(sans)
            .message("Wave: 1")
            .color(ge211::Color::medium_yellow())
            .build();
    ge211::Text_sprite      wave_text = ge211::Text_sprite::Builder(sans)
            .message("Level: 1")
            .color(ge211::Color::medium_yellow())
            .build();
    ge211::Text_sprite       lives_text = ge211::Text_sprite::Builder(sans)
            .message("Lives: _")
            .color(ge211::Color::medium_yellow())
            .build();

    ge211::Text_sprite       game_over_text = ge211::Text_sprite::Builder(arcade)
            .message("Game Over!")
            .color(ge211::Color::white())
            .build();


};