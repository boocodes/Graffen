#include <2D/global/global.h>
#include <2D/gui_tags/display/div/div.h>
#include <2D/gui_tags/display/display_tags_container/display_tags_container.h>
#include <2D/gui_tags/display/img/img.h>
#include <2D/gui_tags/display/text/text.h>
#include <2D/gui_tags/display/button/button.h>

int main(void)
{
    DisplayTagsContainer display_container;
    /*TextDisplayTag* text = new TextDisplayTag(10, 10, 1, "assets/fonts/Roboto-Bold.ttf", "Hello, world!");
    display_container.add_tag(text);*/

    ButtonDisplayTag* btn = new ButtonDisplayTag(30, 30, 1, "Hello");
    display_container.add_tag(btn);
    btn->resize(100,100);
    btn->set_border_radius(glm::vec4(10, 10, 10, 10));
    root_window->set_display_tags_container(display_container);
    root_window->render();
    return 0;
}

