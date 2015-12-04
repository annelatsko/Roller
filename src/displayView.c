#include <pebble.h>
#include <stdlib.h>
#include <time.h>
  
  
Window *result_window;
TextLayer *total_layer;
TextLayer *d1, *d2, *d3, *d4, *d5, *d6, *d7, *d8, *d9, *d10, *d11, *d12; //these layers will show the individual dice

static BitmapLayer *reroll_layer, *arrow_layer;
static GBitmap *reroll_bitmap, *arrow_bitmap;

static int DICE_RESOURCES[] = {4, 6, 8, 10, 12, 20};
static int total = 0;

MenuIndex *this_index;
static int this_dice;

//LITERALLY BOP, THERE MUST BE A BETTER WAY TO DO THIS
static char d1_text[30];
static char d2_text[30];
static char d3_text[30];
static char d4_text[30];
static char d5_text[30];
static char d6_text[30];
static char d7_text[30];
static char d8_text[30];
static char d9_text[30];
static char d10_text[30];
static char d11_text[30];
static char d12_text[30];

//gets rid of everything
void resultUnload(Window *win){
  //will show up in the log
  APP_LOG(APP_LOG_LEVEL_INFO, "Destroying Result Window.");
  text_layer_destroy(total_layer);
  text_layer_destroy(d1);
  text_layer_destroy(d2);
  text_layer_destroy(d3);
  text_layer_destroy(d4);
  text_layer_destroy(d5);
  text_layer_destroy(d6);
  text_layer_destroy(d7);
  text_layer_destroy(d8);
  text_layer_destroy(d9);
  text_layer_destroy(d10);
  text_layer_destroy(d11);
  text_layer_destroy(d12); 
  
  gbitmap_destroy(reroll_bitmap);
  bitmap_layer_destroy(reroll_layer);
  
  gbitmap_destroy(arrow_bitmap);
  bitmap_layer_destroy(arrow_layer);
  
  window_destroy(result_window);
}

static void resultLoad(){
  //Pbltm tick_time;
  //get_time(&tick_time);
  //unsigned int unix_time;
  //unix_time = ((0-TIME_ZONE_OFFSET)*3600) + /* time zone offset */ 
  //            + current_time->tm_sec /* start with seconds */
  //            + current_time->tm_min*60 /* add minutes */
  //            + current_time->tm_hour*3600 /* add hours */
  //            + current_time->tm_yday*86400 /* add days */
  //            + (current_time->tm_year-70)*31536000
  //srand(); //seeds the srand() function with the current time to generate a new set of numbers
}

//this select click handler is the function that deals with what happens when the select button is hit on the results display screen
//it basically just rerolls the particular type of dice and the number of dice that was specified on the last screen 

static void select_click_handler(ClickRecognizerRef recognizer, void *context){
  //resets the total back to zero
  total = 0;
  
  //takes the parameters sent to the showResult() function
  int dice = this_dice;
  MenuIndex *index = this_index;
  
  //initializes a new dice_array
  int dice_array [dice]; 
  
  for (int x = 0; x < dice; x++){   
      int ran_num = rand();
      ran_num = ran_num % DICE_RESOURCES[index->row] + 1;
      dice_array[x] = ran_num;
    }
  
  //literally me just populating the textlayers
  int y = 1; //this is a counter to show where i am in the array  
  //D1
  snprintf(d1_text, sizeof(d1_text), "%d", dice_array[y-1]);
  text_layer_set_text(d1, d1_text);
  y++;
  
  //D2
  if(y > dice){
    text_layer_set_text(d2, " ");
  }
  else{
    snprintf(d2_text, sizeof(d2_text), "%d", dice_array[y-1]);
    text_layer_set_text(d2, d2_text);
  }
  y++;
  
  //D3
  if(y > dice){
    text_layer_set_text(d3, " ");
  }
  else{
    snprintf(d3_text, sizeof(d3_text), "%d", dice_array[y-1]);
    text_layer_set_text(d3, d3_text);
  }
  y++;
  
  //D4
  if(y > dice){
    text_layer_set_text(d4, " ");
  }
  else{
    snprintf(d4_text, sizeof(d4_text), "%d", dice_array[y-1]);
    text_layer_set_text(d4, d4_text);
  }
  y++;
  
  //D5
  if(y > dice){
    text_layer_set_text(d5, " ");
  }
  else{
    snprintf(d5_text, sizeof(d5_text), "%d", dice_array[y-1]);
    text_layer_set_text(d5, d5_text);
  }
  y++;
  
  //D6
  if(y > dice){
    text_layer_set_text(d6, " ");
  }
  else{
    snprintf(d6_text, sizeof(d6_text), "%d", dice_array[y-1]);
    text_layer_set_text(d6, d6_text);
  }
  y++;

  //D7
  if(y > dice){
    text_layer_set_text(d7, " ");
  }
  else{
    snprintf(d7_text, sizeof(d7_text), "%d", dice_array[y-1]);
    text_layer_set_text(d7, d7_text);
  }
  y++;
  
  //D8
  if(y > dice){
    text_layer_set_text(d8, " ");
  }
  else{
    snprintf(d8_text, sizeof(d8_text), "%d", dice_array[y-1]);
    text_layer_set_text(d8, d8_text);
  }
  y++;
  
  //D9
  if(y > dice){
    text_layer_set_text(d9, " ");
  }
  else{
    snprintf(d9_text, sizeof(d9_text), "%d", dice_array[y-1]);
    text_layer_set_text(d9, d9_text);
  }
  y++;
  
  //D10
  if(y > dice){
    text_layer_set_text(d10, " ");
  }
  else{
    snprintf(d10_text, sizeof(d10_text), "%d", dice_array[y-1]);
    text_layer_set_text(d10, d10_text);
  }
  y++;
  
  //D11
  if(y > dice){
    text_layer_set_text(d11, " ");
  }
  else{
    snprintf(d11_text, sizeof(d11_text), "%d", dice_array[y-1]);
    text_layer_set_text(d11, d11_text);
  }
  y++;
  
  //D12
  if(y > dice){
    text_layer_set_text(d12, " ");
  }
  else{
    snprintf(d12_text, sizeof(d12_text), "%d", dice_array[y-1]);
    text_layer_set_text(d12, d12_text);
  }
  y++;
  
  //calculates the big total number
  for(int q = 0; q < dice; q++){
     total += dice_array[q];
   }

  text_layer_set_font(total_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_LIGHT));
  
  //gets the int into a string that the text_layer can actually handle (for total_layer)
  static char total_text[5];
  snprintf(total_text, sizeof(total_text), "%u", total);
  total = 0;
  text_layer_set_text(total_layer, total_text);
}

void click_conf_provider(void *context){
  window_single_click_subscribe(BUTTON_ID_SELECT, (ClickHandler) select_click_handler);
}

//this is the funciton that is called in detailView.c when anyone hits the select button
void showResult(MenuIndex *index, int dice){
  ///////////////////////////////CREATE THE WINDOW AND ALL THE SHIT ON IT//////////////////////////////////////////////////////
  this_index = index;
  this_dice = dice;
  
  //creates all of the other layers, starting from underneath "total_layer" and continuing down three, then moving over
  //30 pixels and going down another three (total layer created at the bottom)
    
  //COLUMN ONE
  d1 = text_layer_create(GRect(5, 65, 30, 30));
  text_layer_set_font(d1, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_background_color(d1, GColorClear);
  d2 = text_layer_create(GRect(5, 95, 30, 30));
  text_layer_set_font(d2, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_background_color(d2, GColorClear);
  d3 = text_layer_create(GRect(5, 125, 30, 30));
  text_layer_set_font(d3, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_background_color(d3, GColorClear);
  //COLUMN TWO
  d4 = text_layer_create(GRect(35, 65, 30, 30));
  text_layer_set_font(d4, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_background_color(d4, GColorClear);
  d5 = text_layer_create(GRect(35, 95, 30, 30));
  text_layer_set_font(d5, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_background_color(d5, GColorClear);
  d6 = text_layer_create(GRect(35, 125, 30, 30));
  text_layer_set_font(d6, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_background_color(d5, GColorClear);
  //COLUMN THREE
  d7 = text_layer_create(GRect(65, 65, 30, 30));
  text_layer_set_font(d7, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_background_color(d7, GColorClear);
  d8 = text_layer_create(GRect(65, 95, 30, 30));
  text_layer_set_font(d8, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_background_color(d8, GColorClear);
  d9 = text_layer_create(GRect(65, 125, 30, 30));
  text_layer_set_font(d9, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_background_color(d9, GColorClear);
  //COLUMN FOUR
  d10 = text_layer_create(GRect(95, 65, 30, 30));
  text_layer_set_font(d10, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_background_color(d10, GColorClear);
  d11 = text_layer_create(GRect(95, 95, 30, 30));
  text_layer_set_font(d11, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_background_color(d11, GColorClear);
  d12 = text_layer_create(GRect(95, 125, 30, 30));
  text_layer_set_font(d12, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_background_color(d12, GColorClear);
  
  result_window = window_create();
  window_set_window_handlers(result_window, (WindowHandlers) {
    .load = resultLoad,
    .unload = resultUnload,
  });
  window_set_click_config_provider(result_window, click_conf_provider);

  
  Layer *window_layer = window_get_root_layer(result_window);
  /////////////////////////////END WINDOW CREATION/////////////////////////////////////////////////////////////////////
  
  int dice_array [dice]; 
  
  for (int x = 0; x < dice; x++){   
      int ran_num = rand();
      ran_num = ran_num % DICE_RESOURCES[index->row] + 1;
      dice_array[x] = ran_num;
    }
  
  //literally me just populating the textlayers
  int y = 1; //this is a counter to show where i am in the array  
  //D1
  snprintf(d1_text, sizeof(d1_text), "%d", dice_array[y-1]);
  text_layer_set_text(d1, d1_text);
  y++;
  
  //D2
  if(y > dice){
    text_layer_set_text(d2, " ");
  }
  else{
    snprintf(d2_text, sizeof(d2_text), "%d", dice_array[y-1]);
    text_layer_set_text(d2, d2_text);
  }
  y++;
  
  //D3
  if(y > dice){
    text_layer_set_text(d3, " ");
  }
  else{
    snprintf(d3_text, sizeof(d3_text), "%d", dice_array[y-1]);
    text_layer_set_text(d3, d3_text);
  }
  y++;
  
  //D4
  if(y > dice){
    text_layer_set_text(d4, " ");
  }
  else{
    snprintf(d4_text, sizeof(d4_text), "%d", dice_array[y-1]);
    text_layer_set_text(d4, d4_text);
  }
  y++;
  
  //D5
  if(y > dice){
    text_layer_set_text(d5, " ");
  }
  else{
    snprintf(d5_text, sizeof(d5_text), "%d", dice_array[y-1]);
    text_layer_set_text(d5, d5_text);
  }
  y++;
  
  //D6
  if(y > dice){
    text_layer_set_text(d6, " ");
  }
  else{
    snprintf(d6_text, sizeof(d6_text), "%d", dice_array[y-1]);
    text_layer_set_text(d6, d6_text);
  }
  y++;

  //D7
  if(y > dice){
    text_layer_set_text(d7, " ");
  }
  else{
    snprintf(d7_text, sizeof(d7_text), "%d", dice_array[y-1]);
    text_layer_set_text(d7, d7_text);
  }
  y++;
  
  //D8
  if(y > dice){
    text_layer_set_text(d8, " ");
  }
  else{
    snprintf(d8_text, sizeof(d8_text), "%d", dice_array[y-1]);
    text_layer_set_text(d8, d8_text);
  }
  y++;
  
  //D9
  if(y > dice){
    text_layer_set_text(d9, " ");
  }
  else{
    snprintf(d9_text, sizeof(d9_text), "%d", dice_array[y-1]);
    text_layer_set_text(d9, d9_text);
  }
  y++;
  
  //D10
  if(y > dice){
    text_layer_set_text(d10, " ");
  }
  else{
    snprintf(d10_text, sizeof(d10_text), "%d", dice_array[y-1]);
    text_layer_set_text(d10, d10_text);
  }
  y++;
  
  //D11
  if(y > dice){
    text_layer_set_text(d11, " ");
  }
  else{
    snprintf(d11_text, sizeof(d11_text), "%d", dice_array[y-1]);
    text_layer_set_text(d11, d11_text);
  }
  y++;
  
  //D12
  if(y > dice){
    text_layer_set_text(d12, " ");
  }
  else{
    snprintf(d12_text, sizeof(d12_text), "%d", dice_array[y-1]);
    text_layer_set_text(d12, d12_text);
  }
  y++;
  
  //calculates the big total number
  for(int q = 0; q < dice; q++){
     total += dice_array[q];
   }
  
  
  //creates the layer displaying the total (at the top of the screen)
  total_layer = text_layer_create(GRect(5, 5, 70, 50));
  text_layer_set_font(total_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_LIGHT));
  text_layer_set_background_color(total_layer, GColorClear); 
  
  //gets the int into a string that the text_layer can actually handle (for total_layer)
  static char total_text[5];
  snprintf(total_text, sizeof(total_text), "%u", total);
  total = 0;
  text_layer_set_text(total_layer, total_text);
  
  //creates the reroll symbol
  reroll_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_REROLL_IDENTIFIER);
  reroll_layer = bitmap_layer_create(GRect(70, 0, 85, 55)); //puts it in the top right corner
  bitmap_layer_set_bitmap(reroll_layer, reroll_bitmap);
  layer_add_child(window_layer, bitmap_layer_get_layer(reroll_layer));
  
  //creates the arrow pointing to the select button
  arrow_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ARROW_IDENTIFIER);
  arrow_layer = bitmap_layer_create(GRect(120, 45, 20, 45)); //sticks it beneath the reroll image
  bitmap_layer_set_bitmap(arrow_layer, arrow_bitmap);
  layer_add_child(window_layer, bitmap_layer_get_layer(arrow_layer));
  
  //adds all the text layers to the window
  layer_add_child(window_layer, text_layer_get_layer(total_layer));
  layer_add_child(window_layer, text_layer_get_layer(d1));
  layer_add_child(window_layer, text_layer_get_layer(d2));
  layer_add_child(window_layer, text_layer_get_layer(d3));
  layer_add_child(window_layer, text_layer_get_layer(d4));
  layer_add_child(window_layer, text_layer_get_layer(d5));
  layer_add_child(window_layer, text_layer_get_layer(d6));
  layer_add_child(window_layer, text_layer_get_layer(d7));
  layer_add_child(window_layer, text_layer_get_layer(d8));
  layer_add_child(window_layer, text_layer_get_layer(d9));
  layer_add_child(window_layer, text_layer_get_layer(d10));
  layer_add_child(window_layer, text_layer_get_layer(d11));
  layer_add_child(window_layer, text_layer_get_layer(d12));
   
  window_stack_push(result_window, true); 
}