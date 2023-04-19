#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Trie{
    int flag;
    struct Trie* letters[26];
} Trie;

void insert(struct Trie **ppTrie, char *word){
    if(*ppTrie == NULL) return;
    Trie* temp = *ppTrie;
    int length = strlen(word);

    for(int i = 0; i < length; i++){
        if(temp->letters[word[i] - 'a'] == NULL){
            temp->letters[word[i] - 'a'] = (Trie*)calloc(1, sizeof(Trie));
        }
        temp = temp->letters[word[i] - 'a']; 
    }
    temp->flag++;
}

int numberOfOccurances(struct Trie *pTrie, char *word){
    if(pTrie == NULL) return 0;
    Trie* temp = pTrie;

    for(int i = 0; i < strlen(word); i++){
        temp = temp->letters[word[i] - 'a']; 
    }
    return temp->flag;
}

struct Trie *deallocateTree(struct Trie *pTrie){
    if(pTrie == NULL) return NULL;
    
    for(int i = 0; i < 26; i++){
        if(pTrie->letters[i] != NULL){
            pTrie->letters[i] = deallocateTree(pTrie->letters[i]);
        }
    }
    free(pTrie);
    return NULL;
}

int main(void)
{
      //read the number of the words in the dictionary
      // parse line  by line, and insert each word to the trie data structure
      Trie *trie = (Trie*)calloc(1, sizeof(Trie));
      char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
      for (int i=0;i<5;i++)
        insert(&trie, pWords[i]);

      for (int i=0;i<5;i++)
          printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
    trie = deallocateTree(trie);
    if (trie != NULL)
       printf("There is an error in this program\n");
    return 0;
}
