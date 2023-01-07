#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"
#include "debugmalloc.h"

//This function scans the morse_alpha.txt to return it as a dynamic array

/*

char* scanning_alpha(){
    int lines_allocated = 128;
    int max_line_len = 100;

    // Allocate lines of text
    char **words = (char **)malloc(sizeof(char*)*lines_allocated);
    if (words==NULL)
        {
        fprintf(stderr,"Out of memory (1).\n");
        exit(1);
        }

    FILE *fp = fopen("morse_alpha.txt", "r");
    if (fp == NULL)
        {
        fprintf(stderr,"Error opening file.\n");
        exit(2);
        }

    int i;
    for (i=0;1;i++)
        {
        int j;

        // Have we gone over our line allocation?
        if (i >= lines_allocated)
            {
            int new_size;

            // Double our allocation and re-allocate
            new_size = lines_allocated*2;
            words = (char **)realloc(words,sizeof(char*)*new_size);
            if (words==NULL)
                {
                fprintf(stderr,"Out of memory.\n");
                exit(3);
                }
            lines_allocated = new_size;
            }
        //Allocate space for the next line
        words[i] = malloc(max_line_len);
        if (words[i]==NULL)
            {
            fprintf(stderr,"Out of memory (3).\n");
            exit(4);
            }
        if (fgets(words[i],max_line_len-1,fp)==NULL)
            break;

        // Get rid of CR or LF at end of line
        for (j=strlen(words[i])-1;j>=0 && (words[i][j]=='\n' || words[i][j]=='\r');j--)
            ;
        words[i][j+1]='\0';
        }
        return words;
    // Close file
    fclose(fp);

    //free memory
    for (;i>=0;i--)
        free(words[i]);
    free(words);

}

//This function scans the morse_num.txt to return it as a dynamic array

char* scanning_num(){
    int lines_allocated = 128;
    int max_line_len = 100;

    // Allocate lines of text
    char **words = (char **)malloc(sizeof(char*)*lines_allocated);
    if (words==NULL)
        {
        fprintf(stderr,"Out of memory (1).\n");
        exit(1);
        }

    FILE *fp = fopen("morse_num.txt", "r");
    if (fp == NULL)
        {
        fprintf(stderr,"Error opening file.\n");
        exit(2);
        }

    int i;
    for (i=0;1;i++)
        {
        int j;

        // Have we gone over our line allocation?
        if (i >= lines_allocated)
            {
            int new_size;

            // Double our allocation and re-allocate
            new_size = lines_allocated*2;
            words = (char **)realloc(words,sizeof(char*)*new_size);
            if (words==NULL)
                {
                fprintf(stderr,"Out of memory.\n");
                exit(3);
                }
            lines_allocated = new_size;
            }
        // Allocate space for the next line
        words[i] = malloc(max_line_len);
        if (words[i]==NULL)
            {
            fprintf(stderr,"Out of memory (3).\n");
            exit(4);
            }
        if (fgets(words[i],max_line_len-1,fp)==NULL)
            break;

        // Get rid of CR or LF at end of line
        for (j=strlen(words[i])-1;j>=0 && (words[i][j]=='\n' || words[i][j]=='\r');j--)
            ;
        words[i][j+1]='\0';
        }
        return words;
    // Close file
    fclose(fp);

    //Free memory
    for (;i>=0;i--)
        free(words[i]);
    free(words);

}

*/

//This function scans a line of string from the user
//until enter is pressed

char* scan(char *string)
{
    int c;
    string = malloc(sizeof(char));                                  //allocating memory

    string[0]='\0';

    for(int i=0; i<100 && (c=getchar())!='\n' && c != EOF ; i++)
    {
        string = realloc(string, (i+2)*sizeof(char));               //reallocating memory
        string[i] = (char) c;                                       //type casting `int` to `char`
        string[i+1] = '\0';                                         //inserting null character at the end
    }

    return string;
}

//It's like decoding but now encoding without secondary functions

void encode_out(const char *s){
    for(;;++s){
        char ch = *s;
        if(ch == '\0')
            break;
        if(isalpha(ch)){
            ch = toupper(ch);
            fputs(table[ALPHA][ch - 'A'], stdout);
        } else if(isdigit(ch))
            fputs(table[NUM][ch - '0'], stdout);
        else if(ch == ' ')
            fputc('/', stdout);                              //this inspects if we need to skip the next spaces
        else
            ;                                                //this ignores the invalid characters
        fputc(' ', stdout);
    }
    fputc('\n', stdout);
}

//This function goes through the morse binary tree,
//depending on the value goes towards the right direction

static void decode_out_aux(MTree *tree, const char *s){
    if(tree == NULL) return;
    if(*s == '\0')
        fputc(tree->value, stdout);                         //when it reaches the end
    else if(*s == '/')
        fputc(' ', stdout);
    else if(*s == '.')
        decode_out_aux(tree->dot, ++s);
    else if(*s == '-')
        decode_out_aux(tree->bar, ++s);
}

//This function decodes a morse code using it's side function
//called decode_out_aux to do that

void decode_out(const char *s){
    char *p;
    while(*s){
        p = strchr(s, ' ');
        if(p){
            if(p-s != 0){
                char code[p-s+1];
                memcpy(code, s, p-s);
                code[p-s]='\0';
                decode_out_aux(root, code);
            }
            s = p + 1;
        } else {
            decode_out_aux(root, s);
            break;
        }
    }
    fputc('\n', stdout);
}

static void insert_aux(MTree **tree, char ch, const char *s){
    if(*tree == NULL)
        *tree = calloc(1, sizeof(**tree));
    if(*s == '\0')
        (*tree)->value = ch;
    else if(*s == '.')
        insert_aux(&(*tree)->dot, ch, ++s);
    else if(*s == '-')
        insert_aux(&(*tree)->bar, ch, ++s);
}

static inline void insert(char ch, const char *s){
    if(*s == '.')
        insert_aux(&root->dot, ch, ++s);
    else if(*s == '-')
        insert_aux(&root->bar, ch, ++s);
}

//This function creates the binary tree using the ALPHA
//and the NUM tables

void make_tree(void){
    root = calloc(1, sizeof(*root));                 //Allocating memory
    int i;
    for(i = 0; i < 26; ++i)
        insert('A'+i, table[ALPHA][i]);
    for(i = 0; i < 10; ++i)
        insert('0'+i, table[NUM][i]);
}

//This function drops the tree auxs

static void drop_tree_aux(MTree *root){
    if(root){
        drop_tree_aux(root->dot);
        drop_tree_aux(root->bar);
        free(root);
    }
}

//This function drops the whole tree

void drop_tree(void){
    drop_tree_aux(root);
}
