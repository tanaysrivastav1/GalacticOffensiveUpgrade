//do some shit

#include "ui.hxx"
#include <string>

///
/// VIEW CONSTANTS
///

ge211::Color const enemy_bullet_c   {170, 35,  35 };
ge211::Color const grunt_c {204, 157, 122};
ge211::Color const turret_c     {30,  210, 60 };
ge211::Color const player_c  {30,  60,  210};
ge211::Color const player_bullet_c    {210, 45,  156};


Ui::Ui(Model& model)
       : model_ (model)
       , frames_ {0}
       , size { model_.geometry_.scene_dims.height/25}

{ }

ge211::Dimensions Ui::initial_window_dimensions() const
{
    return model_.geometry_.scene_dims;
}

void Ui::draw(ge211::Sprite_set& sprites)
{

    if (model_.new_level) {
        level_text =
                ge211::Text_sprite::Builder(arcade)
                        .message("Level " + std::to_string(model_.level()))
                        .color(ge211::Color::medium_yellow())
                        .build();

        sprites.add_sprite(level_text,  {model_.geometry_.scene_dims.width/2 - level_text.dimensions().width/2, model_.geometry_.scene_dims.height/2 - level_text.dimensions().height/2}, 5);

    } else if (!model_.game_over) {
        sprites.add_sprite(player_sprite_, model_.player_.top_left(), 1);
        for (Bullet* bullet : model_.bullets_)
            sprites.add_sprite(bullet->enemy() ? enemy_bullet_sprite_ : player_bullet_sprite_, bullet->top_left(), 1);
        for (Enemy &enemy : model_.enemies_) {
            if (enemy.type() == 1)
                sprites.add_sprite(grunt_sprite_, enemy.top_left(), 2);
            else if (enemy.type() == 2)
                sprites.add_sprite(turret_sprite_, enemy.top_left(), 2);
        }

        level_text =
                ge211::Text_sprite::Builder(sans)
                        .message("Level: " + std::to_string(model_.level()))
                        .color(ge211::Color::medium_yellow())
                        .build();
        sprites.add_sprite(level_text,  {model_.geometry_.scene_dims.width/75, model_.geometry_.scene_dims.height/75}, 0);

        wave_text =
                ge211::Text_sprite::Builder(sans)
                        .message("Wave: " + std::to_string(model_.wave()))
                        .color(ge211::Color::medium_yellow())
                        .build();
        sprites.add_sprite(wave_text,  {model_.geometry_.scene_dims.width/75, model_.geometry_.scene_dims.height/75 + size + 3 }, 0);

        lives_text =
                ge211::Text_sprite::Builder(sans)
                        .message("Lives: " + std::to_string(model_.player_.lives()))
                        .color(ge211::Color::medium_yellow())
                        .build();
        sprites.add_sprite(lives_text,  {model_.geometry_.scene_dims.width/75, model_.geometry_.scene_dims.height * 74 /75 - size - 3}, 0);


    } else {
        game_over_text =
                ge211::Text_sprite::Builder(arcade)
                        .message("Game Over!")
                        .color(ge211::Color::white())
                        .build();
        sprites.add_sprite(game_over_text,  {model_.geometry_.scene_dims.width/2 - game_over_text.dimensions().width/2, model_.geometry_.scene_dims.height/2 - game_over_text.dimensions().height}, 5);
        level_text =
                ge211::Text_sprite::Builder(end_level_text)
                        .message("Level " + std::to_string(model_.level()) + " reached")
                        .color(ge211::Color::white())
                        .build();
        sprites.add_sprite(level_text,  {model_.geometry_.scene_dims.width/2 - level_text.dimensions().width/2, model_.geometry_.scene_dims.height/2 - level_text.dimensions().height/2}, 0);
    }

}

void Ui::on_key_down(ge211::Key key)
{

}

void Ui::on_key_up(ge211::Key key)
{

}

void Ui::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q'))
        quit();
    else if (key == ge211::Key::code(' '))
        model_.fire_bullet(model_.player_);
}

void Ui::on_mouse_move(ge211::Position position)
{
    model_.move_player(position.x, position.y);
}

void Ui::on_mouse_down(ge211::Mouse_button, ge211::Position)
{
    model_.fire_bullet(model_.player_);
}

void Ui::on_frame(double dr)
{
    model_.update();

}

ge211::Text_sprite Ui::get_wave_sprite(int wave) {
    wave_text =
            ge211::Text_sprite::Builder(sans)
                    .message("Wave: " + std::to_string(wave))
                    .color(ge211::Color::medium_yellow())
                    .build();
    return wave_text;
}

ge211::Text_sprite Ui::get_level_sprite(int level) {
    level_text =
            ge211::Text_sprite::Builder(sans)
                    .message("Level: " + std::to_string(level))
                    .color(ge211::Color::medium_yellow())
                    .build();
    return level_text;

}

