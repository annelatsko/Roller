#include <pebble.h>

#define NUM_DICE_DEFAULT 1
#define NUM_INDEX_DEFAULT -1  
  
static Window *dwindow;
static TextLayer *dice_layer, *header_layer;
static BitmapLayer *dimage_layer;
static GBitmap *dimage_bitmap, *s_icon_plus, *s_icon_minus, *s_icon_select;
static ActionBarLayer *daction_bar;

static uint32_t IMAGE_RESOURCES[] = {
  RESOURCE_ID_IMAGE_RBG_IDENTIFIER,
  RESOURCE_ID_IMAGE_D6_IDENTIFIER,
  RESOURCE_ID_IMAGE_RBG_IDENTIFIER,
  RESOURCE_ID_IMAGE_RBG_IDENTIFIER,
  RESOURCE_ID_IMAGE_D20_IDENTIFIER,
};

//the dice options available in the order that corresponds to their menuindex
static uint32_t DICE_RESOURCES[] = {4, 6, 8, 10, 20};

int dice = NUM_DICE_DEFAULT;
MenuIndex *dice_index;

static void update_text(){
  static char dice_text[10];
  snprintf(dice_text, sizeof(dice_text), "%u", dice);
  text_layer_set_text(dice_layer, dice_text);
}


static void increment_click_handler(ClickRecognizerRef recognizer, void *context) {
  if(dice == 10){
    return;
  }
  else{
    dice++;
    update_text();
  }
}

static void decrement_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (dice == 1) {
    // Keep the counter at onee
    return;
  }
  else{
    dice--;
    update_text();
  }
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context){
  
}

void click_config_provider(void *context){
  window_single_click_subscribe(BUTTON_ID_DOWN, (ClickHandler) decrement_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, (ClickHandler) increment_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, (ClickHandler) select_click_handler);
}

void detailLoad(){
  
}

void detailUnload(Window *win){
  //will show up in the log
  APP_LOG(APP_LOG_LEVEL_INFO, "Destroying Detail Window.");
  
  text_layer_destroy(dice_layer);
  text_layer_destroy(header_layer);
  
  gbitmap_destroy(s_icon_plus);
  gbitmap_destroy(s_icon_minus);
  gbitmap_destroy(s_icon_select);
	gbitmap_destroy(dimage_bitmap);
  
  bitmap_layer_destroy(dimage_layer);
  
  action_bar_layer_destroy(daction_bar);
  window_destroy(dwindow);
}


void showDetail(MenuIndex* index){
  
  dwindow = window_create();
  window_set_window_handlers(dwindow, (WindowHandlers) {
    .load = detailLoad,
    .unload = detailUnload,
  });
  
  dice_index = index;
  
  Layer *window_layer = window_get_root_layer(dwindow);
  s_icon_plus = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_ICON_PLUS);
  s_icon_minus = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_ICON_MINUS);
  s_icon_select = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ACTION_ICON_SELECT);
  
  //creates the action bar layer (the thing on the side)
  daction_bar = action_bar_layer_create();
  action_bar_layer_add_to_window(daction_bar, dwindow);
  action_bar_layer_set_click_config_provider(daction_bar, click_config_provider);

  //creates the plus and minus icons and adds them to the actionbarlayer
  action_bar_layer_set_icon(daction_bar, BUTTON_ID_UP, s_icon_plus);
  action_bar_layer_set_icon(daction_bar, BUTTON_ID_DOWN, s_icon_minus);
  action_bar_layer_set_icon(daction_bar, BUTTON_ID_SELECT, s_icon_select);
  
  //creates the appropriate image depending on what was clicked
  dimage_bitmap = gbitmap_create_with_resource(IMAGE_RESOURCES[index->row]);
  dimage_layer = bitmap_layer_create(GRect(0, 0, 70, 70)); //puts it in the top left corner
  bitmap_layer_set_bitmap(dimage_layer, dimage_bitmap);
  layer_add_child(window_get_root_layer(dwindow), bitmap_layer_get_layer(dimage_layer));
  
  //sets the text dice_header
  header_layer = text_layer_create(GRect(40, 70, 55, 55));
  text_layer_set_font(header_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD));
  text_layer_set_background_color(header_layer, GColorClear);
  text_layer_set_text(header_layer, "Number of Dice");
  layer_add_child(window_layer, text_layer_get_layer(header_layer));
  
  //sets the text dice_text
  dice_layer = text_layer_create(GRect(100, 60, 150, 150));
  text_layer_set_font(dice_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_background_color(dice_layer, GColorClear);
  layer_add_child(window_layer, text_layer_get_layer(dice_layer));
  
  update_text();
  window_stack_push(dwindow, true);

  // The back button will dismiss the current window, not close the app.  So just press back to go back to the master view.
}




