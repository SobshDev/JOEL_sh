/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parse_condition
*/

#include "parser.h"
#include "utils.h"
#include "my.h"

/*
* Parses a condition in the shell command line.
* The function first checks for a logical expression.
* If found, it creates a condition node with the expression.
*/
node_t *parse_condition(parser_t *parser)
{
    node_t *expression = NULL;
    node_t *condition = NULL;

    expression = parse_logical(parser);
    if (!expression) {
        parser->syntax_error = true;
        return NULL;
    }
    condition = create_condition_node(expression);
    if (!condition) {
        destroy_node(expression);
        return NULL;
    }
    return condition;
}
