#include <2D/global/global.h>
#include <2D/gui_tags/form/input_simple/input_simple.h>
#include <2D/gui_tags/form/form_tags_container/form_tags_container.h>
#include <2D/gui_tags/display/display_tags_container/display_tags_container.h>
#include <2D/gui_tags/display/button/button.h>

int main(void)
{
    DisplayTagsContainer dspl;
    FormTagsContainer cnt;
    InputSimpleFormTag* inpt = new InputSimpleFormTag(50, 50, 1, 100, 40);
    cnt.add_tag(inpt);
    ButtonDisplayTag* btn = new ButtonDisplayTag(180, 180, 2, "clickme");
    dspl.add_tag(btn);
    root_window->set_display_tags_container(dspl);
    root_window->set_form_tags_container(cnt);
    root_window->render();
    return 0;
}

