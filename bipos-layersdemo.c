/*
	
	Layers Demo for BipOS custom firmware
	
	by Enrico Rovere - https://github.com/enricorov/bipos-layersdemo
	
*/

#define CENTER_WINDOW 0
#define UP_WINDOW 1
#define DOWN_WINDOW 2
#define LEFT_WINDOW 3
#define RIGHT_WINDOW 4

#include "bipos-layersdemo.h"

#ifdef __SIMULATION__
#include <stdio.h>
#include <string.h>
#endif
//	screen menu structure - each screen has its own
struct regmenu_ screen_data = {
	55,					//	curr_screen - main screen number, value 0-255, for custom windows it is better to take from 50 and above
	1,					//	swipe_scr - auxiliary screen number (usually 1)
	0,					//	overlay - 0
	interactionHandler, //          - pointer to the handler of interaction (touch, swipe, long press)
	key_press_screen,	//	        - handler of short button press
	refreshScreen,		//	        - timer callback function and..
	0,					//	            ..the variable passed to it
	show_screen,		//	        - function writing to video buffer and..
	0,					//              ..the variable passed to it
	0					//	        - handler of long button press
};

#ifdef __SIMULATION__
int main_app(int param0)
{
#else
int main(int param0, char **argv)
{													//	here the variable argv is not defined
#endif
	show_screen((void *)param0);
}

// CALLBACK FUNCTIONS - functions associated to objects i.e. buttons or layers

void goToSettingsCallbackFunction(Layer_ *layer, short button_id)
{
}

void goToHelpCallbackFunction(Layer_ *layer, short button_id)
{
}

void startGameCallbackFunction(Layer_ *layer, short button_id)
{
}
// CONSTRUCTORS - Defining elements, put the messy intializations here

void layerOverlayConstructor(Layer_ *layerOverlay)
{

	setLayerBackground(layerOverlay, COLOR_SH_AQUA);

	/* 	TextBox_ tempText = DEFAULT_TEXTBOX;

	tempText.topLeft = (Point_ ) {4, 70};
	tempText.bottomRight = (Point_) {172, 150};
	_strcpy(tempText.body, "This is an overlay");
	tempText.colour = COLOR_SH_WHITE;
	tempText.background = COLOR_SH_BLACK; */

	//setLayerTextBox(layerOverlay, tempText);

	Button_ *placeholderButton = addButtonToLayer(layerOverlay);

	*placeholderButton = DEFAULT_BUTTON_INSTANCE;
	placeholderButton->topLeft = (Point_){4, 25};
	placeholderButton->bottomRight = (Point_){172, 50};
	placeholderButton->filling = COLOR_SH_BLACK;
	placeholderButton->border = COLOR_SH_RED;
	placeholderButton->params.style = BUTTON_STYLE_DEFAULT_SQUARED;
	_strcpy(placeholderButton->label, "OVERLAY");
}

void layerBlankConstructor(Layer_ *layerSettings)
{

	setLayerBackground(layerSettings, COLOR_SH_AQUA);

	/* 	TextBox_ tempText;

	tempText.topLeft = BIPUI_TOP_LEFT_POINT;
	tempText.bottomRight = BIPUI_BOTTOM_RIGHT_POINT;
	_strcpy(tempText.body, "Options");
	tempText.colour = COLOR_SH_WHITE;
	tempText.background = COLOR_SH_BLACK; */

	//setLayerTextBox(layerSettings, tempText);
}

void layerHelpConstructor(Layer_ *layerHelp)
{

	setLayerBackground(layerHelp, COLOR_SH_PURPLE);

	/* 	TextBox_ tempText;

	tempText.topLeft = BIPUI_TOP_LEFT_POINT;
	tempText.bottomRight = BIPUI_BOTTOM_RIGHT_POINT;
	_strcpy(tempText.body, "Help");
	tempText.colour = COLOR_SH_WHITE;
	tempText.background = COLOR_SH_BLACK; */

	//setLayerTextBox(layerHelp, tempText);
}

void layerCenterConstructor(Layer_ *layerMain)
{

	TextBox_ *temp = createTextbox(); // allocating textbox

	temp->topLeft = BIPUI_TOP_LEFT_POINT; // setting parameters
	temp->bottomRight = BIPUI_BOTTOM_RIGHT_POINT;
	temp->background = COLOR_SH_WHITE;
	temp->colour = COLOR_SH_BLACK;
	_strcpy(temp->body, "Swipe in any direction.");
	temp->visible = 1; // do not forget to set visibility

	layerMain->textBox = temp; // assigning pointer to layer

	movePoint(&temp->topLeft, DOWN, DEFAULT_TEXT_HEIGHT);

	/* 	short width = 81; // handy parameters for easier button creation
	short horizontalSeparation = 6;
	short verticalSeparation = 6;
	short height = 30;

	Point_ tempPointOne = BIPUI_BOTTOM_LEFT_POINT;
	Point_ tempPointTwo = BIPUI_BOTTOM_LEFT_POINT;

	tempPointOne.y -= height;
	tempPointTwo.x += width;

	layerMain->backgroundColour = COLOR_SH_BLACK;

 	Button_ *placeholderButton;

	placeholderButton = addButtonToLayer(layerMain);

	setButton(placeholderButton,
			   tempPointOne,
			   tempPointTwo,
			   "OPTIONS",
			   COLOR_SH_WHITE,
			   COLOR_SH_RED,
			   COLOR_SH_BLACK,
			   goToSettingsCallbackFunction,
			   BUTTON_STYLE_ROUNDED_NOBORDER);

	
	placeholderButton = addButtonToLayer(layerMain);

	movePoint(&tempPointOne, RIGHT, horizontalSeparation + width);
	movePoint(&tempPointTwo, RIGHT, horizontalSeparation + width);

	setButton(placeholderButton,
			   tempPointOne,
			   tempPointTwo,
			   "HELP",
			   COLOR_SH_WHITE,
			   COLOR_SH_YELLOW,
			   COLOR_SH_BLACK,
			   goToHelpCallbackFunction,
			   BUTTON_STYLE_ROUNDED_NOBORDER);

	placeholderButton = addButtonToLayer(layerMain);

	tempPointOne.x = 44;
	tempPointOne.y = 44;

	tempPointTwo.x = 132;
	tempPointTwo.y = 132;

	setButton(placeholderButton, // initial button on the bottom left
			   tempPointOne,
			   tempPointTwo,
			   "START GAME",
			   COLOR_SH_WHITE,
			   COLOR_SH_GREEN,
			   COLOR_SH_WHITE,
			   startGameCallbackFunction,
			   BUTTON_STYLE_ROUNDED_NOBORDER); */
}

void begin(app_data_t *app_data)
{

	// creating windows here, adding them to the viewport allocates them and increments the index

	Viewport_ *vp = &app_data->vp;

	Window_ *centerWindow = addWindowToViewport(vp); // index 0
	setWindowName("Center", centerWindow);

	Window_ *leftWindow = addWindowToViewport(vp); // index 1
	setWindowName("Left", leftWindow);

	Window_ *rightWindow = addWindowToViewport(vp); // index 2
	setWindowName("Right", rightWindow);

	Window_ *upWindow = addWindowToViewport(vp); // index 3
	setWindowName("Up", upWindow);

	Window_ *downWindow = addWindowToViewport(vp); // index 4
	setWindowName("Down", downWindow);

	linkWindows(centerWindow, LEFT, leftWindow);
	linkWindows(centerWindow, RIGHT, rightWindow);
	linkWindows(centerWindow, UP, upWindow);
	linkWindows(centerWindow, DOWN, downWindow);

	// Creating (i.e. allocating) layers and using constructors to define their elements

	Layer_ *layerTemp = addLayerToWindow(centerWindow);
	layerTemp->backgroundColour = COLOR_SH_PURPLE;
	layerCenterConstructor(layerTemp);

	layerTemp = addLayerToWindow(leftWindow);
	layerTemp->backgroundColour = COLOR_SH_RED;

	layerTemp = addLayerToWindow(rightWindow);
	layerTemp->backgroundColour = COLOR_SH_AQUA;

	layerTemp = addLayerToWindow(upWindow);
	layerTemp->backgroundColour = COLOR_SH_BLUE;

	layerTemp = addLayerToWindow(downWindow);
	layerTemp->backgroundColour = COLOR_SH_YELLOW;

	vp->active = centerWindow;
}

void end(app_data_t *app_data)
{

	destroyViewport(&app_data->vp);
}

// Utility functions

void show_screen(void *param0)
{
#ifdef __SIMULATION__
	app_data_t *app_data = get_app_data_ptr();
	app_data_t **app_data_p = &app_data;
#else
	app_data_t **app_data_p = get_ptr_temp_buf_2(); //	pointer to a pointer to screen data
	app_data_t *app_data;							//	pointer to screen data
#endif

	Elf_proc_ *proc;

	// check the source at the procedure launch
	if ((param0 == *app_data_p) && get_var_menu_overlay())
	{ // return from the overlay screen (incoming call, notification, alarm, target, etc.)

		app_data = *app_data_p; //	the data pointer must be saved for the deletion
								//	release memory function reg_menu
		*app_data_p = NULL;		//	reset the pointer to pass it to the function reg_menu

		// 	create a new screen when the pointer temp_buf_2 is equal to 0 and the memory is not released
		reg_menu(&screen_data, 0); // 	menu_overlay=0

		*app_data_p = app_data;
	}
	else
	{ // if the function is started for the first time i.e. from the menu

		// create a screen (register in the system)
		reg_menu(&screen_data, 0);

		// allocate the necessary memory and place the data in it (the memory by the pointer stored at temp_buf_2 is released automatically by the function reg_menu of another screen)
		*app_data_p = (app_data_t *)pvPortMalloc(sizeof(app_data_t));
		app_data = *app_data_p; //	data pointer

		// clear the memory for data
		_memclr(app_data, sizeof(app_data_t));

		//	param0 value contains a pointer to the data of the running process structure Elf_proc_
		proc = param0;

		// remember the address of the pointer to the function you need to return to after finishing this screen
		if (param0 && proc->ret_f) //	if the return pointer is passed, then return to it
			app_data->ret_f = proc->elf_finish;
		else //	if not, to the watchface
			app_data->ret_f = show_watchface;

#ifdef __SIMULATION__
		set_app_data_ptr(app_data);
#endif

		begin(app_data);
	}
	caffeine(WEAK);

	refreshWindow(app_data->vp.active, 0);
}

void key_press_screen()
{
#ifdef __SIMULATION__
	app_data_t *app_data = get_app_data_ptr();
	app_data_t **app_data_p = &app_data;
#else
	app_data_t **app_data_p = get_ptr_temp_buf_2(); //	pointer to a pointer to screen data
	app_data_t *app_data = *app_data_p;				//	pointer to screen data
#endif

	// destroy all elements, memory leaks are bad
	destroyViewport(&app_data->vp);

	// call the return function (usually this is the start menu), specify the address of the function of our application as a parameter
	show_menu_animate(app_data->ret_f, (unsigned int)show_screen, ANIMATE_RIGHT);
};

void refreshScreen()
{ // triggered by set_update_period

#ifdef __SIMULATION__
	app_data_t *app_data = get_app_data_ptr();
	app_data_t **app_data_p = &app_data;
#else
	app_data_t **app_data_p = get_ptr_temp_buf_2(); //	pointer to a pointer to screen data
	app_data_t *app_data = *app_data_p;				//	pointer to screen data
#endif
	refreshWindow(app_data->vp.active, 1);
	vibrate(2, 50, 150);
}

int interactionHandler(void *param)
{
#ifdef __SIMULATION__
	app_data_t *app_data = get_app_data_ptr();
	app_data_t **app_data_p = &app_data;
#else
	app_data_t **app_data_p = get_ptr_temp_buf_2(); //	pointer to a pointer to screen data
	app_data_t *app_data = *app_data_p;				//	pointer to screen data
#endif

	struct gesture_ *gest = param;
	int result = 0;

	Window_ *activeWindow = app_data->vp.active;
	Layer_ *activeLayer = activeWindow->layerArray[0]; // for now, interaction can be had with the first layer

	switch (gest->gesture)
	{
	case GESTURE_CLICK:
	{
		processTap(activeLayer, gest->touch_pos_x, gest->touch_pos_y);
		break;
	};
	case GESTURE_SWIPE_RIGHT:
	{ //	swipe to the right
		processSwipe(activeWindow, gest->gesture);
		refreshWindow(app_data->vp.active, 1);
		// show_menu_animate(show_menu, (unsigned int) refreshWindow(app_data->vp.active, 0), gest->gesture%4);
		break;
	};
	case GESTURE_SWIPE_LEFT:
	{ // swipe to the left
		processSwipe(activeWindow, gest->gesture);
		refreshWindow(app_data->vp.active, 1);
		// show_menu_animate(show_menu, (unsigned int) refreshWindow(app_data->vp.active, 0), gest->gesture%4);
		break;
	};
	case GESTURE_SWIPE_UP:
	{ // swipe up
		processSwipe(activeWindow, gest->gesture);
		refreshWindow(app_data->vp.active, 1);
		// show_menu_animate(show_menu, (unsigned int) refreshWindow(app_data->vp.active, 0), gest->gesture%4);
		break;
	};
	case GESTURE_SWIPE_DOWN:
	{ // swipe down

		processSwipe(activeWindow, gest->gesture);
		refreshWindow(app_data->vp.active, 1);
		// show_menu_animate(show_menu, (unsigned int) refreshWindow(app_data->vp.active, 0), gest->gesture%4);
		break;
	};
	default:
	{ // something went wrong ...

		break;
	};
	}
	//	}

	return result;
};