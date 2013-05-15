#include "tilemap.h"

/* Keep track of pressed mouse button. */
int mouse;


int main(void) {


    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *queue;
    bool redraw = true;
 
    srand(time(NULL));
 
    /* Init Allegro 5 + addons. */
    al_init();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_install_mouse();
    al_install_keyboard();
 
	//test NEW
 
    /* The example will work without those, but there will be no
     * FPS display and no icon.
     */
    /* Create our window. */
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    display = al_create_display(640, 480);
    al_set_window_title(display, "Allegro 5 Tilemap Example");
  
    icon = al_load_bitmap("icon.tga");
    if (icon)
        al_set_display_icon(display, icon);
 
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
 
    tile_map_create();
 
    timer = al_create_timer(1.0 / 60);
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
 
    while (1) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
 
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                break;
        }
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            mouse = event.mouse.button;
        }
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            mouse = 0;
        }
        if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            /* Left button scrolls. */
            if (mouse == 1) {
                float x = event.mouse.dx / zoom;
                float y = event.mouse.dy / zoom;
                scroll_x -= x * cos(rotate) + y * sin(rotate);
                scroll_y -= y * cos(rotate) - x * sin(rotate);
            }
            /* Right button zooms/rotates. */
            if (mouse == 2) {
                rotate += event.mouse.dx * 0.01;
                zoom += event.mouse.dy * 0.01 * zoom;
            }
            zoom += event.mouse.dz * 0.1 * zoom;
            if (zoom < 0.1) zoom = 0.1;
            if (zoom > 10) zoom = 10;
        }
        if (event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;
        if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
            al_acknowledge_resize(display);
            redraw = true;
        }
 
        if (redraw && al_is_event_queue_empty(queue)) {
            double t = al_get_time();
            tile_map_draw();
            al_flip_display();

        }
    }
    return 0;
}