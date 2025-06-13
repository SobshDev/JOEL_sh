/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** print_ast
*/
#include "parser.h"
#include "utils.h"
#include "my.h"

static void print_indent(int depth, bool *has_sibling)
{
    for (int i = 0; i < depth; i++) {
        if (i == depth - 1)
            my_printf("%s ", has_sibling[depth - 1] ? "├──" : "└──");
        else
            my_printf("%s ", has_sibling[i] ? "│  " : "   ");
    }
}

static void print_node_recursive(node_t *node, int depth, bool *has_sibling)
{
    if (!node)
        return;

    if (depth > 0)
        print_indent(depth, has_sibling);
    
    if (node->type == NODE_COMMAND) {
        my_printf("%sCOMMAND%s: ", BLUE, RESET BOLD);
        for (int i = 0; i < node->arg_count; i++)
            if (node->quoted_args && node->quoted_args[i])
                my_printf("'%s' ", node->args[i]);
            else if (node->backticked_args && node->backticked_args[i])
                my_printf("`%s` ", node->args[i]);
            else
                my_printf("%s ", node->args[i]);
        my_printf("%s\n", RESET);
    } else if (node->type == NODE_PIPE) {
        my_printf("%sPIPE%s\n", BLUE, RESET);
        has_sibling[depth] = node->right != NULL;
        print_node_recursive(node->left, depth + 1, has_sibling);
        has_sibling[depth] = false;
        if (node->right)
            print_node_recursive(node->right, depth + 1, has_sibling);
    } else if (node->type == NODE_REDIRECT) {
        const char *redirect_type_str = "";
        switch (node->redirect_type) {
            case REDIRECT_IN: redirect_type_str = "<"; break;
            case REDIRECT_OUT: redirect_type_str = ">"; break;
            case HEREDOC: redirect_type_str = "<<"; break;
            case REDIRECT_APPEND: redirect_type_str = ">>"; break;
            case REDIRECT_ERROR: redirect_type_str = "2>"; break;
            case REDIRECT_BOTH: redirect_type_str = "&>"; break;
            default: redirect_type_str = "UNKNOWN"; break;
        }
        my_printf("%sREDIRECT%s %s: %s%s%s\n", BLUE, RESET, redirect_type_str, BOLD, node->redirect_path, RESET);
        has_sibling[depth] = node->right != NULL;
        print_node_recursive(node->left, depth + 1, has_sibling);
        has_sibling[depth] = false;
        if (node->right)
            print_node_recursive(node->right, depth + 1, has_sibling);
    } else if (node->type == NODE_SEQUENCE) {
        my_printf("%sSEQUENCE%s\n", BLUE, RESET);
        has_sibling[depth] = node->right != NULL;
        print_node_recursive(node->left, depth + 1, has_sibling);
        has_sibling[depth] = false;
        if (node->right)
            print_node_recursive(node->right, depth + 1, has_sibling);
    } else if (node->type == NODE_AND) {
        my_printf("%sAND%s\n", BLUE, RESET);
        has_sibling[depth] = node->right != NULL;
        print_node_recursive(node->left, depth + 1, has_sibling);
        has_sibling[depth] = false;
        if (node->right)
            print_node_recursive(node->right, depth + 1, has_sibling);
    } else if (node->type == NODE_OR) {
        my_printf("%sOR%s\n", BLUE, RESET);
        has_sibling[depth] = node->right != NULL;
        print_node_recursive(node->left, depth + 1, has_sibling);
        has_sibling[depth] = false;
        if (node->right)
            print_node_recursive(node->right, depth + 1, has_sibling);
    } else if (node->type == NODE_BACKGROUND) {
        my_printf("%sBACKGROUND%s\n", BLUE, RESET);
        has_sibling[depth] = node->right != NULL;
        print_node_recursive(node->left, depth + 1, has_sibling);
        has_sibling[depth] = false;
        if (node->right)
            print_node_recursive(node->right, depth + 1, has_sibling);
    } else if (node->type == NODE_GROUP) {
        my_printf("%sGROUP%s\n", BLUE, RESET);
        has_sibling[depth] = node->right != NULL;
        print_node_recursive(node->left, depth + 1, has_sibling);
        has_sibling[depth] = false;
        if (node->right)
            print_node_recursive(node->right, depth + 1, has_sibling);
    } else if (node->type == NODE_CONDITION) {
        my_printf("%sCONDITION%s\n", BLUE, RESET);
        has_sibling[depth] = node->right != NULL;
        print_node_recursive(node->left, depth + 1, has_sibling);
        has_sibling[depth] = false;
        if (node->right)
            print_node_recursive(node->right, depth + 1, has_sibling);
    } else if (node->type == NODE_IF) {
        my_printf("%sIF%s\n", BLUE, RESET);
        has_sibling[depth] = node->right != NULL;
        print_node_recursive(node->left, depth + 1, has_sibling);
        has_sibling[depth] = false;
        if (node->right)
            print_node_recursive(node->right, depth + 1, has_sibling);
    } else if (node->type == NODE_THEN) {
        my_printf("%sTHEN%s\n", BLUE, RESET);
        has_sibling[depth] = node->right != NULL;
        print_node_recursive(node->left, depth + 1, has_sibling);
        has_sibling[depth] = false;
        if (node->right)
            print_node_recursive(node->right, depth + 1, has_sibling);
    } else if (node->type == NODE_ELIF) {
        my_printf("%sELIF%s\n", BLUE, RESET);
        has_sibling[depth] = node->right != NULL;
        print_node_recursive(node->left, depth + 1, has_sibling);
        has_sibling[depth] = false;
        if (node->right)
            print_node_recursive(node->right, depth + 1, has_sibling);
    } else if (node->type == NODE_ELSE) {
        my_printf("%sELSE%s\n", BLUE, RESET);
        has_sibling[depth] = node->right != NULL;
        print_node_recursive(node->left, depth + 1, has_sibling);
        has_sibling[depth] = false;
        if (node->right)
            print_node_recursive(node->right, depth + 1, has_sibling);
    } else if (node->type == NODE_WHILE) {
        my_printf("%sWHILE%s\n", BLUE, RESET);
        has_sibling[depth] = node->right != NULL;
        print_node_recursive(node->left, depth + 1, has_sibling);
        has_sibling[depth] = false;
        if (node->right)
            print_node_recursive(node->right, depth + 1, has_sibling);
    } else if (node->type == NODE_UNKNOWN) {
        my_printf("%sUNKNOWN%s\n", RED, RESET);
    } else {
        my_printf("%sUNKNOWN%s\n", RED, RESET);
    }
}

void print_node(node_t *node)
{
    bool has_sibling[128] = {false};

    print_node_recursive(node, 0, has_sibling);
}

void print_ast(parser_t *parser)
{
    if (!parser || !parser->root) {
        my_printf("AST is empty or parser is NULL\n");
        return;
    }
    my_printf("%s=== %sAbstract Syntax Tree%s ===%s\n",
        BOLD GREEN, UNDERLINE, RESET BOLD GREEN, RESET);
    print_node(parser->root);
}
