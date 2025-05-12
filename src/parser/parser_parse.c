/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** parser_parse
*/

#include "parser.h"

/*
* Hierarchy for nodes:
* 1. Sequence      (';')       - lowest precedence
* 2. Background    ('&')
* 3. Logical       ('&&', '||')
* 4. Pipe          ('|')
* 5. Redirect      ('>', '>>', '<', '<<')
* 6. Group         ('(', ')')
* 7. Command                   - highest precedence
*
* The order of precedence is the inverse of parsing order.
* We parse with a recursive descent parser, starting from the lowest
* precedence operators (sequence) and recursively parsing higher precedence
* operators. This means parse_sequence() calls parse_background(), which calls
* parse_logical(), and so on down to parse_command().
*/
node_t *parse(parser_t *parser)
{
    node_t *node = parse_sequence(parser);

    if (!node)
        return NULL;
    if (peek_token(parser->lexer).type != END) {
        destroy_node(node);
        return NULL;
    }
    return node;
}
