#include <2D/global/global.h>
#include <2D/gui_tags/form/input_simple/input_simple.h>
#include <2D/gui_tags/display/div/div.h>
#include <2D/gui_tags/form/form_tags_container/form_tags_container.h>
#include <2D/gui_tags/display/display_tags_container/display_tags_container.h>
#include <2D/gui_tags/display/img/img.h>
#include <2D/gui_tags/display/button/button.h>



void enable_settings_page();
void enable_game_prepares_page();
void enable_game();

int main(void)
{
    DisplayTagsContainer disp;
    FormTagsContainer form;

   
    ImgDisplayTag* userProfile = new ImgDisplayTag(154, 31, 1, "assets/userProfile.png");
    
    DivDisplayTag* workArea = new DivDisplayTag(0, 125, 1, 609, 436);
    workArea->set_background_color(glm::vec4(UtilModule::hex_to_vec3("#200B40"), 1.0f));
    workArea->set_border_radius(glm::vec4(15, 15, 15, 15));
    int id = workArea->get_self_id();
    ButtonDisplayTag* startGameButton = new ButtonDisplayTag(25, 125, 2, "Start game");
    startGameButton->set_font_size(22);
    startGameButton->set_font_color(UtilModule::hex_to_vec3("#FFFFFF"));
    startGameButton->set_background_color(glm::vec4(0, 0, 0, 0));
    startGameButton->set_border_color(glm::vec4(0, 0, 0, 0));

    ButtonDisplayTag* settingGameButton = new ButtonDisplayTag(25, 183, 2, "Settings");
    settingGameButton->set_font_size(22);
    settingGameButton->set_font_color(UtilModule::hex_to_vec3("#FFFFFF"));
    settingGameButton->set_background_color(glm::vec4(0, 0, 0, 0));
    settingGameButton->set_border_color(glm::vec4(0, 0, 0, 0));
    std::cout << "old size - " << disp.get_tags().size() << std::endl;
   
    ButtonDisplayTag* exitGameButton = new ButtonDisplayTag(25, 241, 2, "Exit");
    exitGameButton->set_font_size(22);
    exitGameButton->set_font_color(UtilModule::hex_to_vec3("#FFFFFF"));
    exitGameButton->set_background_color(glm::vec4(0, 0, 0, 0));
    exitGameButton->set_border_color(glm::vec4(0, 0, 0, 0));
    exitGameButton->on_click = []() {
        exit(0);
        };

    InputSimpleFormTag* userNameField = new InputSimpleFormTag(225, 48, 1, 120, 20);
    userNameField->set_background_color(glm::vec4(0, 0, 0, 0));
    userNameField->set_font_color(glm::vec3(1, 1, 1));
    userNameField->set_max_input_size(15);
    userNameField->set_text_align("left");

    disp.add_tag(exitGameButton);
    disp.add_tag(settingGameButton);
    disp.add_tag(startGameButton);
    disp.add_tag(userProfile);
    disp.add_tag(workArea);
    root_window->set_display_tags_container(disp);
    form.add_tag(userNameField);
    root_window->set_form_tags_container(form);


    root_window->render();
    return 0;
}





void enable_settings_page()
{

};
void enable_game_prepares_page()
{

};
void enable_game()
{

};
