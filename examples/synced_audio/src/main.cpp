#include "bn_core.h"
#include "bn_music.h"
#include "bn_dmg_music.h"
#include "bn_synced_music.h"
#include "bn_keypad.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_text_generator.h"

#include "common_info.h"
#include "common_variable_8x16_sprite_font.h"

#include "bn_music_items.h"
#include "bn_dmg_music_items_galactic_quest_mus_theme_c.h"

int main()
{
    bn::core::init();

    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
    bn::bg_palettes::set_transparent_color(bn::color(16, 16, 16));

    static constexpr bn::string_view info_text_lines[] = {
        "A: pause/resume music",
        "B: stop music",
    };

    common::info info("Synced music", info_text_lines, text_generator);
    info.set_show_always(true);

    bn::dmg_music::set_master_volume(bn::dmg_music_master_volume::FULL);

    bn::synced_music::play(bn::music_items::galactic_quest_mus_theme_c, bn::dmg_music_items::galactic_quest_mus_theme_c);

    while(true)
    {
        if(bn::keypad::a_pressed())
        {
            if(! bn::synced_music::playing())
            {
                bn::synced_music::play(bn::music_items::galactic_quest_mus_theme_c, bn::dmg_music_items::galactic_quest_mus_theme_c);
            }
            else if(bn::synced_music::paused())
            {
                bn::synced_music::resume();
            }
            else
            {
                bn::synced_music::pause();
            }
        }

        if (bn::keypad::b_pressed())
        {
            if (bn::synced_music::playing())
            {
                bn::synced_music::stop();
            }
        }

        info.update();
        bn::core::update();
    }
}
