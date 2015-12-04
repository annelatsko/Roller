#include <pebble.h>
 
Window* window;
MenuLayer *mainMenu;
void showDetail(MenuIndex* index); //see detailView.c

//draws the menu itself
void draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
     
       
 switch(cell_index->row){
   case 0:
     menu_cell_basic_draw(ctx, cell_layer, "1. d4", "Four Sided Dice", NULL);
     break;
   case 1:
     menu_cell_basic_draw(ctx, cell_layer, "2. d6", "Six Sided Dice", NULL);
     break;
   case 2:
     menu_cell_basic_draw(ctx, cell_layer, "3. d8", "Eight Sided Dice", NULL);
     break;
   case 3:
     menu_cell_basic_draw(ctx, cell_layer, "4. d10", "Ten Sided Dice", NULL);
     break;
   case 4:
     menu_cell_basic_draw(ctx, cell_layer, "5. d12", "Twelve Sided Dice", NULL);
     break;
   case 5:
     menu_cell_basic_draw(ctx, cell_layer, "6. d20", "Twenty Sided Dice", NULL);
     break;
 } 
}
uint16_t num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *callback_context)
{
  //basically useless  
  return 6;
}
 

void select_click_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context){
  showDetail(cell_index);
}

void window_load(Window *window)
{
   mainMenu = menu_layer_create(GRect(0, 0, 144, 168 - 16));
   menu_layer_set_click_config_onto_window(mainMenu, window);
   MenuLayerCallbacks callbacks = {
        .draw_row = (MenuLayerDrawRowCallback) draw_row_callback,
        .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback) num_rows_callback,
        .select_click = (MenuLayerSelectCallback) select_click_callback
    };
    menu_layer_set_callbacks(mainMenu, NULL, callbacks);
 
    //Add to Window
    layer_add_child(window_get_root_layer(window), menu_layer_get_layer(mainMenu));
}
 
void window_unload(Window *window)
{
 menu_layer_destroy(mainMenu);
}
 
static void init(void)
{
    window = window_create();
    WindowHandlers handlers = {
        .load = window_load,
        .unload = window_unload
    };
    window_set_window_handlers(window, (WindowHandlers) handlers);
    window_stack_push(window, true);
}
 
static void deinit()
{
    window_destroy(window);
}
 
int main(void)
{
    init();
    srand(time(NULL));
    app_event_loop();
    deinit();
}