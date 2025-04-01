/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** Key handler definitions
*/

#ifndef KEY_HANDLER_H_
    #define KEY_HANDLER_H_

    #include "minishell2.h"

    #define KEY_ESC 27
    #define KEY_NEWLINE '\n'
    #define KEY_BACKSPACE 127
    #define KEY_CLEAR 12
    #define KEY_UP 'A'
    #define KEY_DOWN 'B'
    #define KEY_RIGHT 'C'
    #define KEY_LEFT 'D'
    #define KEY_HOME 'H'
    #define KEY_END 'F'
    #define KEY_DELETE '3'
    #define KEY_CTRL_T 20
    #define KEY_CTRL_I 9
    #define KEY_CTRL_D 4

typedef void (*key_handler_t)(input_state_t *state);
typedef bool (*escape_handler_t)(input_state_t *state);

typedef struct key_func_s {
    char key;
    key_handler_t handler;
} key_func_t;

typedef struct esc_func_s {
    char key;
    key_handler_t handler;
} esc_func_t;

// Function declarations
void handle_left_key(input_state_t *state);
void handle_right_key(input_state_t *state);
void handle_up_key(input_state_t *state);
void handle_down_key(input_state_t *state);
void handle_home_key(input_state_t *state);
void handle_end_key(input_state_t *state);
void handle_delete_key(input_state_t *state);
void handle_backspace(input_state_t *state);
void handle_clear_screen(input_state_t *state);
void handle_toggle_history(input_state_t *state);
void handle_chatgpt(input_state_t *state);
void handle_printable_char(input_state_t *state, char c);
void process_input_char(input_state_t *state, char c);
void handle_newline(input_state_t *state);
void handle_escape_sequence(input_state_t *state);
void handle_ctrl_d(input_state_t *state);

#endif /* !KEY_HANDLER_H_ */
