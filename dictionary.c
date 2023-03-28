// Implements a dictionary's functionality
//#include
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1]; // LENGTHは最も単語数が多いときの文字数
    struct node *next;     //連結の次
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26; //ハッシュテーブルの大きさ
unsigned int count[6];
int aa = 0;
int bb = -1;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
//外部からファイルを読み取って一行ずつデータ構造に組み込む
bool check(const char *word) // checkしたい単語が読み込んだ辞書の中にあるかどうか
{
    // TODO
    //ハッシュ関数のどのインデックスにあるか
    //
    node *n = table[hash(word)];
    while (n != NULL)
    {
        if (strcasecmp(n->word, word) == 0)
        {
            return true;
        }
        n = n->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return (toupper(word[0]) - 'A' + toupper(word[0]) - 'A') % 26;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    char word[LENGTH + 1];
    //ファイルを読み取る、ファイルの行数分ハッシュテーブルに格納
    //開いたファイルを閉じる
    FILE *file;
    file = fopen(dictionary, "r");
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        strcpy(n->word, word);

        int index = hash(word);
        //ハッシュテーブルの頭に新たなノードを追加する。
        node *tmp = table[index];
        table[index] = n;
        n->next = tmp;

        count[aa]++;
    }
    aa++;
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // loadで数えていく
    for (int ac = 0; ac < 6; ac++)
    {
        //printf("%d\n", bb);
    }
    bb++;
    return count[bb];
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    //線形探索
    for (int i = 0; i < N; i++)
    {
        // node *n=table[i];
        while (table[i] != NULL)
        {
            node *tmp = table[i];
            table[i] = table[i]->next;
            free(tmp);
        }
    }
    return true;
}
