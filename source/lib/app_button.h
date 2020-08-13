/*******************************************************************************
 * LICENSE : Apache 2.0
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/11/27 10:35          V1.0             build this file
 *
 *******************************************************************************/
#ifndef APP_BUTTON_H
#define APP_BUTTON_H

#include "app_config.h"

#include "hal_gpio.h"

/*! @defgroup app_button
* @ingroup lib
* @brief    This module is used for keyboard scanning and provides callback.Support long-press detection.
*           The module will scan(Polling) gpio pin in timer interrupt.
*
*   example for linear keyboard:
*       #include "app_button.h"
*       #define UI_BUTTON_LIST	{		\
*           {PIN_BUTTON_1,	HAL_GPIO_NOPULL, APP_BUTTON_ACTIVE_LOW, ui_button_handler},\
*           {PIN_BUTTON_2,	HAL_GPIO_NOPULL, APP_BUTTON_ACTIVE_LOW, ui_button_handler},\
*           {PIN_BUTTON_3,	HAL_GPIO_NOPULL, APP_BUTTON_ACTIVE_LOW, ui_button_handler},\
*           {PIN_BUTTON_4,	HAL_GPIO_NOPULL, APP_BUTTON_ACTIVE_LOW, my_button_handler},\
*           {PIN_BUTTON_5,	HAL_GPIO_NOPULL, APP_BUTTON_ACTIVE_LOW, your_button_handler},\
*       }//The button list is an array of app_button_cfg_t
*
*       APP_BUTTON_LIST_DEF(m_button_list, UI_BUTTON_LIST);
*
*       void ui_button_init(void)
*       {
*           app_button_init(&m_button_list);
*
*       }
*
*		void ui_button_handler(uint8_t button_pin, app_button_action_t action)
*		{
*			switch (action)
*			{
*			case APP_BUTTON_RELEASE:
*				break;
*			case APP_BUTTON_PRESS:
*               if (button_pin == PIN_BUTTON_2)
*                   do_something();
*				break;
*			case APP_BUTTON_LONG_PRESS:
*				break;
*			default:
*				break;
*			}
*		}
*
*	example for matrix keyboard:
*       #define UI_BUTTON_MATRIX {	\
*		    .input_pins      = { PIN_BUTTON_I_0, PIN_BUTTON_I_1, PIN_BUTTON_I_2, PIN_BUTTON_I_3, PIN_BUTTON_I_4 },\
*		    .output_pins     = { PIN_BUTTON_O_0, PIN_BUTTON_O_1, PIN_BUTTON_O_2, PIN_BUTTON_O_3, PIN_BUTTON_O_4 },\
*		    .input_pin_pull  = HAL_GPIO_PULLUP,\
*		    .active_level    = APP_BUTTON_ACTIVE_LOW,\
*		    .matrix_callback = ui_button_matrix_handler\
*       }
*
*	    APP_BUTTON_MATRIX_DEF(m_matrix, UI_BUTTON_MATRIX);
*
*	    void ui_button_init(void)
*	    {
*		    app_button_matrix_init(&m_matrix);
*
*	    }
*
* @{ */

//********************************* Module Config *******************************/

/*! button scan interval , in ms */
#define APP_BUTTON_SCAN_INTERVAL              CFG_BUTTON_SCAN_INTERVAL         

//be used for Elimination Buffeting,but currently not implemented
#define APP_BUTTON_DETECTION_DELAY            CFG_BUTTON_DETECTION_DELAY  

/*! long-press interval */
#define APP_BUTTON_LONG_PRESS_DETECT_DELAY    CFG_BUTTON_LONG_PRESS_DETECT_DELAY    

/*! if true, the callback function of active button will be called in interrupt
     else,    will be called in main loop*/
#define APP_BUTTON_REALTIME_MODE              CFG_BUTTON_REALTIME_MODE     


/*! Enable matrix keyboard */
#define APP_BUTTON_MATRIX_ENABLE     CFG_BUTTON_MATRIX_ENABLE  

#if APP_BUTTON_MATRIX_ENABLE
/*
I[x]: Input line
O[y]: Output line
#: key id

    O[0] O[1] O[2] O[3] O[4]
I[0]  0    1    2    3    4
I[1]  5    6    7    8    9
I[2]  10   11   12   13   14
I[3]  15   16   17   18   19
I[4]  20   21   22   23   24

* The above table is a matrix composed of input and output lines of matrix keyboard. 
    Each input line is a group of keys. 
    The key id(#) is calculated by the index of input line(x) and output line(y),
    key_id = x * Output_line_bandwide + y;
e.g:  11   = 2 *   5   +   1;
*/

#define APP_BUTTON_MATRIX_OUTPUT_BANDWIDE   CFG_BUTTON_MATRIX_OUTPUT_BANDWIDE   /*!< Number of output lines */
#define APP_BUTTON_MATRIX_INPUT_BANDWIDE    CFG_BUTTON_MATRIX_INPUT_BANDWIDE   /*!< Number of input lines */

#define APP_BUTTON_MATRIX_LINE_CLEAN_MASK   ((1 << APP_BUTTON_MATRIX_OUTPUT_BANDWIDE) - 1)

/*! If enable this, you are allowed to connect an output line to GND.
    It can extend the matrix keyboard to use more keys (additional output line).
    ATTENTION: When a key on GND line is pressed, other keys on the same input line can not be scanned. */
#define APP_BUTTON_MATRIX_ALLOW_GND_AS_OUTPUT_LINE CFG_BUTTON_MATRIX_ALLOW_GND_AS_OUTPUT_LINE

#if APP_BUTTON_MATRIX_ALLOW_GND_AS_OUTPUT_LINE
#define APP_BUTTON_MATRIX_GND_LINE (-1)     /*!< Use this flag to mark which output line was connected to GND  */
#endif //APP_BUTTON_MATRIX_ALLOW_GND_AS_OUTPUT_LINE

/*! Get key_id by Input_line_index and Output_line_index */
#define APP_BUTTON_MATRIX_KEY_ID(_I_x, _O_y) ((_I_x) * APP_BUTTON_MATRIX_OUTPUT_BANDWIDE + (_O_y))

#define APP_BUTTON_MATRIX_COMBINATION_SUPPORT   CFG_BUTTON_MATRIX_COMBINATION_SUPPORT

/*! Get keys combination bit-mask. Tips: get key id by APP_BUTTON_MATRIX_KEY_ID()*/
#define APP_BUTTON_MATRIX_KEY_COMBINATION_2(_key1_id, _key2_id)\
    ((1UL << (_key1_id)) | (1UL << (_key2_id)))

#define APP_BUTTON_MATRIX_KEY_COMBINATION_3(_key1_id, _key2_id, _key3_id)\
    ((1UL << (_key1_id)) | (1UL << (_key2_id)) | (1UL << (_key3_id)))

#endif //APP_BUTTON_MATRIX_ENABLE


//********************************* Data Type ***********************************/

typedef enum
{
    APP_BUTTON_RELEASE,
    APP_BUTTON_PRESS,
    APP_BUTTON_LONG_PRESS,
} app_button_action_t;

/*! The button action callback function typedef 
@param button : the pin number of the active button, or key id if use matrix keyboard
@param action : the action of the active button \ref app_button_action_t
*/
typedef void (*app_button_callback)(uint8_t button, app_button_action_t action);

typedef enum
{
    APP_BUTTON_ACTIVE_LOW,      /*!< low level active */
    APP_BUTTON_ACTIVE_HIGH      /*!< high level active */
} app_button_active_level_t;

#if APP_BUTTON_LINEAR_ENABLE
typedef const struct
{
    uint32_t button_pin:8;                     /*!< The pin of chip which connected to the button */
    hal_gpio_pull_t pin_pull:1;               /*!< The pin pull state */
    app_button_active_level_t active_level:1;
    app_button_callback callback;           /*!< will be call if button active */
} app_button_linear_cfg_t;

/*! button state */
typedef struct
{
    bool is_press;
    uint16_t long_press_cnt;
} app_button_linear_sta_t;

typedef const struct
{
    app_button_linear_cfg_t* button_list;
    app_button_linear_sta_t* button_sta;
    uint8_t button_cnt;
} app_button_linear_t;
#endif

#if APP_BUTTON_MATRIX_ENABLE
// typedef const struct
// {
//     uint32_t combination_list[];
//     uint16_t pressed_time_cnt;
//     void (*combination_callback)(uint32_t combination, app_button_action_t action);
// }app_button_matrix_combination_cfg_t;

typedef const struct
{
    uint8_t input_pins[APP_BUTTON_MATRIX_INPUT_BANDWIDE];    /*!< The pins of input lines */
    uint8_t output_pins[APP_BUTTON_MATRIX_OUTPUT_BANDWIDE];  /*!< The pins of output lines */
    hal_gpio_pull_t input_pin_pull;                           /*!< The input pins pull state */
    app_button_active_level_t active_level;                   /*!< Keys active level at input lines */

    /*! will be call if button action detected.
        key_id: see the key matrix table above and the macro APP_BUTTON_MATRIX_KEY_ID
        action: see app_button_action_t
        state:  bit mark of all keys state 
    */
    void (*matrix_callback)(uint8_t key_id, app_button_action_t action, uint32_t state); 
// #if APP_BUTTON_MATRIX_COMBINATION_SUPPORT
//     app_button_matrix_combination_cfg_t combination;
// #endif
} app_button_matrix_cfg_t;

typedef struct
{
	uint32_t keys_pressed_mark;  /*!< Bit mask table of the pressed keys */
	uint16_t long_press_cnt[APP_BUTTON_MATRIX_INPUT_BANDWIDE * APP_BUTTON_MATRIX_OUTPUT_BANDWIDE];    
} app_button_matrix_sta_t;

typedef const struct
{
    app_button_matrix_cfg_t* button_cfg;
    app_button_matrix_sta_t* button_sta;
} app_button_matrix_t;
#endif

//********************************* Public Interface ****************************/

#if APP_BUTTON_LINEAR_ENABLE
/*!*****************************************************************************
\brief  	Use this macro to define a button list for linear keyboard
\param[in]	_name   The name of the list
\param[in]	_list   An array of app_button_cfg_t
*******************************************************************************/
#define APP_BUTTON_LIST_DEF(_name, _list)    \
    static app_button_linear_cfg_t _name##_cfg[] = _list;     \
    static app_button_sta_t _name##_sta[ARRAY_SIZE(_name##_cfg)] = {0}; \
    static app_button_t _name = {_name##_cfg, _name##_sta, ARRAY_SIZE(_name##_cfg)};

/*!*****************************************************************************
* @brief      initialize linear keyboard
* @param[in]    app_button_t * linear   The button list to be initialized
* @return     void
******************************************************************************/
void app_button_linear_init(app_button_linear_t* linear);

/*!*****************************************************************************
* @brief      enable linear keyboard scan
* @param[in]    void
* @return     void
******************************************************************************/
void app_button_linear_enable(void);

/*!*****************************************************************************
* @brief      disable linear keyboard scan
* @param[in]    void
* @return     void
******************************************************************************/
void app_button_linear_disable(void);

/*!*****************************************************************************
\brief  	immediately check button state 
\param[in]	uint8_t button_pin
\return     bool
******************************************************************************/
bool app_button_linear_is_pressed(uint8_t button_pin);

#endif


#if APP_BUTTON_MATRIX_ENABLE
/*!*****************************************************************************
\brief  	Use this macro to define a matrix keyboard
\param[in]	_name   The name of the keyboard
\param[in]	_matrix_cfg   The initial value of app_button_matrix_cfg_t
*******************************************************************************/
#define APP_BUTTON_MATRIX_DEF(_name, _matrix_cfg)  \
    static app_button_matrix_cfg_t _name##_cfg = _matrix_cfg;\
    static app_button_matrix_sta_t _name##_sta = { 0 };\
    static app_button_matrix_t _name = { &_name##_cfg, &_name##_sta };


/*!*****************************************************************************
\brief  	initialize matrix keyboard
\param[in]	app_button_matrix_t * matrix : Keyboard configuration define by APP_BUTTON_MATRIX_DEF
\return     void
******************************************************************************/
void app_button_matrix_init(app_button_matrix_t* matrix);

/*!*****************************************************************************
\brief  	 enable matrix keyboard scan
\param[in]	void
\return     void
******************************************************************************/
void app_button_matrix_enable(void);

/*!*****************************************************************************
\brief  	 disable matrix keyboard scan
\param[in]	void
\return     void
******************************************************************************/
void app_button_matrix_disable(void);

#endif


/*! @}*/ //end of group app_button
#endif   // APP_BUTTON_H
