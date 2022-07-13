#pragma bank 255

#include <gbdk/platform.h>

#include "musicmanager.h"
#include "joy.h"
#include "screen.h"
#include "states.h"
#include "bankdata.h"
#include "state_camera.h"

// audio assets
#include "sound_ok.h" 
#include "sound_error.h"

// menus
#include "menus.h"
#include "menu_codes.h"
#include "menu_main.h"
#include "menu_popup_camera.h"

BANKREF(state_camera)

camera_mode_e camera_mode = camera_mode_manual;
trigger_mode_e trigger_mode = trigger_mode_abutton;
after_action_e after_action = after_action_save;

const uint8_t * const camera_modes[] = {" Manual", " Assist", " Auto", " Iterate"};
const uint8_t * const trigger_modes[] = {" Btn: [A]", " Timer", " Interval"};
const uint8_t * const after_actions[] = {" Save", " Print", " S & P"};

static void refresh_screen() {
    screen_clear_rect(DEVICE_SCREEN_X_OFFSET, DEVICE_SCREEN_Y_OFFSET, DEVICE_SCREEN_WIDTH, DEVICE_SCREEN_HEIGHT, SOLID_BLACK);
    menu_text_out( 0, 0, 5, SOLID_WHITE, camera_modes[camera_mode]);
    menu_text_out( 5, 0, 5, SOLID_WHITE, trigger_modes[trigger_mode]);
    menu_text_out(10, 0, 5, SOLID_WHITE, after_actions[after_action]);
}

uint8_t ENTER_state_camera() BANKED {
    refresh_screen();
    return 0;     
}

uint8_t UPDATE_state_camera() BANKED {
    static uint8_t menu_result;
    PROCESS_INPUT();
    if (KEY_PRESSED(J_START)) {
        // run Main Menu
        if (!MainMenuDispatch(menu_execute(&MainMenu, NULL))) refresh_screen();
    } else if (KEY_PRESSED(J_SELECT)) {
        switch (menu_result = menu_popup_camera_execute()) {
            case ACTION_MODE_MANUAL:
                camera_mode = camera_mode_manual;
                break;            
            case ACTION_MODE_ASSISTED:
                camera_mode = camera_mode_assisted;
                break;            
            case ACTION_MODE_AUTO:
                camera_mode = camera_mode_auto;
                break;            
            case ACTION_MODE_ITERATE:
                camera_mode = camera_mode_iterate;
                break;            
            case ACTION_TRIGGER_ABUTTON:
                trigger_mode = trigger_mode_abutton;
                break;
            case ACTION_TRIGGER_TIMER:
                trigger_mode = trigger_mode_timer;
                break;
            case ACTION_TRIGGER_INTERVAL:
                trigger_mode = trigger_mode_interval;
                break;
            case ACTION_ACTION_SAVE:
                after_action = after_action_save;
                break;
            case ACTION_ACTION_PRINT:
                after_action = after_action_print;
                break;
            case ACTION_ACTION_SAVEPRINT:
                after_action = after_action_printsave;
                break;
            default:
                // error, must not get here
                music_play_sfx(BANK(sound_error), sound_error, SFX_MUTE_MASK(sound_error));
                break;
        }
        refresh_screen();
    }
    return 0;
}

uint8_t LEAVE_state_camera() BANKED {
    return 0;     
}
