/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** terminal handling
*/

#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include "minishell2.h"

static struct termios original_termios;
static struct termios raw_termios;

void setup_terminal(void)
{
    tcgetattr(STDIN_FILENO, &original_termios);
    raw_termios = original_termios;
    raw_termios.c_lflag &= ~(ICANON | ECHO);
    raw_termios.c_cc[VMIN] = 1;
    raw_termios.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_termios);
}

void restore_terminal(void)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}
