#include <2D/global/global.h>
#include <2D/gui_tags/display/div/div.h>
#include <2D/gui_tags/display/display_tags_container/display_tags_container.h>


int main(void)
{
    init_shaders();
    std::cout << div_display_tag_shader.get_ID() << std::endl;
    root_window->render();   
    return 0;
}

