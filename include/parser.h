/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** ast
*/

#ifndef PARSER_H
    #define PARSER_H

    #include <stdbool.h>
    #include "../src/lexer/lexer.h"

typedef enum node_type_e {
    NODE_COMMAND,
    NODE_PIPE,
    NODE_REDIRECT,
    NODE_SEQUENCE,
    NODE_AND,
    NODE_OR,
    NODE_BACKGROUND,
    NODE_GROUP,
    NODE_CONDITION,
    NODE_IF,
    NODE_THEN,
    NODE_ELIF,
    NODE_ELSE,
    NODE_WHILE,
    NODE_UNKNOWN
} node_type_t;

/*
* Parameters used by each node type:
*
* NODE_COMMAND:
*   - args: command arguments
*   - arg_count: number of arguments
*   - quoted_args: array of bools indicating if each arg is quoted
*   - backticked_args: array of bools indicating if each arg is backticked
*
* NODE_PIPE:
*   - left: left command/expression
*   - right: right command/expression
*
* NODE_REDIRECT:
*   - left: command to redirect
*   - redirect_type: type of redirection
*   - redirect_path: path to redirect to/from
*
* NODE_SEQUENCE:
*   - left: first command
*   - right: next command
*
* NODE_AND:
*   - left: first command
*   - right: command to run if left succeeds
*
* NODE_OR:
*   - left: first command
*   - right: command to run if left fails
*
* NODE_BACKGROUND:
*   - left: command to run in background
*
* NODE_GROUP:
*   - left: command sequence in parentheses
*
* NODE_CONDITION:
*   - left: expression to evaluate
*
* NODE_IF:
*   - left: condition node
*   - right: then node
*
* NODE_THEN:
*   - left: commands for true condition
*   - right: elif or else node (if present)
*
* NODE_ELIF:
*   - left: condition to evaluate
*   - right: commands to execute if condition is true
*
* NODE_ELSE:
*   - left: commands for false condition
*
* NODE_WHILE:
*   - left: condition node
*   - right: commands to execute in the loop body
*
* NODE_UNKNOWN: used for any parsing error
*/

typedef struct node_s {
    node_type_t type;
    char **args;
    bool *quoted_args;
    bool *backticked_args;
    int arg_count;
    struct node_s *left;
    struct node_s *right;
    token_type_t redirect_type;
    char *redirect_path;
} node_t;

typedef struct parser_s {
    lexer_t *lexer;
    node_t *root;
    bool syntax_error;
} parser_t;


parser_t *create_parser(char *content);
void destroy_parser(parser_t *parser);

node_t *parse(parser_t *parser);

node_t *create_empty_node(void);
void destroy_node(node_t *node);

node_t *parse_command(parser_t *parser);

node_t *create_pipe_node(node_t *left, node_t *right);
node_t *parse_pipe(parser_t *parser);

node_t *create_redirect_node(node_t *left, node_t *right, token_type_t type,
    char *path);
node_t *parse_redirect(parser_t *parser, node_t *left);

node_t *create_sequence_node(node_t *left, node_t *right);
node_t *parse_sequence(parser_t *parser);

node_t *create_and_node(node_t *left, node_t *right);
node_t *create_or_node(node_t *left, node_t *right);
node_t *parse_logical(parser_t *parser);

node_t *create_background_node(node_t *left);
node_t *parse_background(parser_t *parser);

node_t *create_group_node(node_t *left);
node_t *parse_group(parser_t *parser);

node_t *create_condition_node(node_t *left);
node_t *parse_condition(parser_t *parser);

node_t *create_if_node(node_t *condition, node_t *then_branch);
node_t *create_then_node(node_t *left);
node_t *create_elif_node(node_t *condition, node_t *then_branch);
node_t *create_else_node(node_t *left);
node_t *parse_if(parser_t *parser);
node_t *handle_after_then(parser_t *parser, node_t *then_branch);

node_t *create_while_node(node_t *condition, node_t *do_branch);
node_t *parse_while(parser_t *parser);

void print_ast(parser_t *parser);
void print_node(node_t *node);


#endif /* PARSER_H */
