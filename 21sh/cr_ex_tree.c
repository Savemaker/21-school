#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
// /* 
// 1 pipe
// 2 command
// 3 suffix
// 4 word
// */

typedef struct eval{
    int args;
    char **argv;
    int cur;
}ev;

typedef struct tree{
    struct tree *left;
    struct tree *right;
    int type;
    char *buf;
}tree;

tree *create_suf()
{
    tree *suf;

    suf = (tree *)malloc(sizeof(tree));
    suf->buf = strdup("-l");
    suf->type = 4;
    suf->left = NULL;
    suf->right = NULL;
    return (suf);
}

tree *create_cmd_name()
{
    tree *name;

    name = (tree *)malloc(sizeof(tree));
    name->buf = strdup("ls");
    name->type = 4;
    name->left=NULL;
    name->right=NULL;
    return (name);
}

tree *create_command()
{
    tree *cmd;

    cmd = (tree *)malloc(sizeof(tree));
    cmd->buf = strdup("ls -l");
    cmd->type = 2;
    cmd->left = create_cmd_name();
    cmd->right =create_suf();
    return (cmd);
}

void    check_tree(tree *pipe, ev *eval)
{
    if (pipe == NULL)
        return ;
    if (pipe->type == 4)
        eval->args += 1;
    check_tree(pipe->left, eval);
    check_tree(pipe->right, eval);
}

void     create_argv(tree *tree, ev *eval)
{
    if (tree == NULL)
        return;
    if (tree->type == 4)
    {
        eval->argv[eval->cur] = strdup(tree->buf);
        eval->cur += 1;
    }
    create_argv(tree->left, eval);
    create_argv(tree->right, eval);
}

void     execute_tree(tree *tr, ev *eval)
{
    if (tr == NULL)
        return ;
    if (tr->type == 2)
    {
        check_tree(tr, eval);
        eval->argv = (char **)malloc(sizeof(char *) * (eval->args + 1));
        create_argv(tr, eval);
        eval->argv[eval->cur] = NULL;
        if (fork() == 0)
            execvp(eval->argv[0], eval->argv);
        eval->argv = NULL;
        eval->args = 0;
        eval->cur = 0;
        wait(NULL);
        
    }
    execute_tree(tr->left, eval);
    execute_tree(tr->right, eval);
}




int main()
{
    // my command is ls -l

    //1st node
    tree *pipe;

    pipe = (tree *)malloc(sizeof(tree));
    pipe->type = 1;
    pipe->buf = strdup("ls -l"); //we have no pipes so only one child to the left
    pipe->right = create_command();
    pipe->left = create_command();
    ev *eval;
    eval = (ev *)malloc(sizeof(ev) * 1);
    eval->args=0;
    eval->cur = 0;
    eval->argv =NULL;
    execute_tree(pipe, eval);
}