#include <2D/global/global.h>
#include <2D/gui_tags/form/input_simple/input_simple.h>
#include <2D/gui_tags/display/div/div.h>
#include <2D/gui_tags/form/form_tags_container/form_tags_container.h>
#include <2D/gui_tags/display/display_tags_container/display_tags_container.h>
#include <2D/gui_tags/display/img/img.h>
#include <2D/gui_tags/display/button/button.h>



int main(void)
{
    DisplayTagsContainer disp;
    FormTagsContainer form;

    TextDisplayTag* loginLabel = new TextDisplayTag(0, 100, 1, "assets/fonts/Roboto-Bold.ttf", "Login");
    loginLabel->set_color(glm::vec3(1, 1, 1));
    loginLabel->change_font_size(24);
    int test = loginLabel->get_wrapper_text_size("Login").x;
    loginLabel->set_x_pos((root_window->get_window_width() - test) / 2);
    DivDisplayTag* div = new DivDisplayTag(0, 120, 1, 60, 50);
    div->set_background_color(glm::vec4(0, 1, 1, 1));



    disp.add_tag(div);
    disp.add_tag(loginLabel);
   // form.add_tag(loginInput);

    root_window->set_display_tags_container(disp);
    root_window->set_form_tags_container(form);


    root_window->render();
    return 0;
}





