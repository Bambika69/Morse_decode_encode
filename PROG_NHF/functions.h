#ifndef SCAN_FN_H_INCLUDED
#define SCAN_FN_H_INCLUDED

static const char *alpha[] = {

    ".-",   //A
    "-...", //B
    "-.-.", //C
    "-..",  //D
    ".",    //E
    "..-.", //F
    "--.",  //G
    "....", //H
    "..",   //I
    ".---", //J
    "-.-",  //K
    ".-..", //L
    "--",   //M
    "-.",   //N
    "---",  //O
    ".--.", //P
    "--.-", //Q
    ".-.",  //R
    "...",  //S
    "-",    //T
    "..-",  //U
    "...-", //V
    ".--",  //W
    "-..-", //X
    "-.--", //Y
    "--..", //Z

};

static const char *num[] = {

    "-----", //0
    ".----", //1
    "..---", //2
    "...--", //3
    "....-", //4
    ".....", //5
    "-....", //6
    "--...", //7
    "---..", //8
    "----.", //9

};

static const char **table[] = { alpha, num };

typedef enum Kind {
    ALPHA, NUM
} Kind;

typedef struct MTree {                                              //binary structure
    char value;
    struct mtree *dot;
    struct mtree *bar;
} MTree;

MTree *root;

char* scan(char *string);
void encode_out(const char *s);
void decode_out(const char *s);
void make_tree(void);
void drop_tree(void);

#endif // SCAN_FN_H_INCLUDED
