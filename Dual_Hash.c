#include<stdlib.h>
#include <stdio.h>
#include <string.h>
struct hash {
    struct hashnode *ptr;
};

struct hashnode {
    int val,r;
    char s[15],c[10];
    struct hashnode *next;
};

struct hash *create_hash(int size)
{
    struct hash *htable;
    int i;
    htable = (struct hash *) malloc(sizeof(struct hash) * size);
    for (i = 0; i < size; i++)
        htable[i].ptr = NULL;
    return htable;
};

struct hashnode *create_hashnode(int val,int r,char *s,char *c)
{
    struct hashnode *tmp;
    tmp = (struct hashnode *) malloc(sizeof(struct hashnode));
    tmp->r=r;
    strcpy(tmp->s,s);
    strcpy(tmp->c,c);
    tmp->next = NULL;
    tmp->val = val;
    return tmp;
};

void insert_value(struct hash **htable,struct hash **htable2, int val,int r, int hsize,char *s,char *c)
{
    int slot,slot2=0,i;
    struct hash *htptr = (*htable);
    struct hash *htptr2 = (*htable2);
    struct hashnode *tmp,*temp;
    for(i=0;i<strlen(s);i++){
        slot2+=s[i];
    }
    slot2=slot2%100;
    slot = val;
    if (htptr[slot].ptr == NULL) {
        tmp = create_hashnode(val,r,s,c);
        htptr[slot].ptr = tmp;
    }
    else {
        tmp = create_hashnode(val,r,s,c);
        tmp->next = htptr[slot].ptr;
        htptr[slot].ptr = tmp;
    }
    if (htptr2[slot2].ptr==NULL){
        temp=create_hashnode(val,r,s,c);
        htptr2[slot2].ptr=temp;
    }else{
        temp=create_hashnode(val,r,s,c);
        temp->next=htptr2[slot2].ptr;
        htptr2[slot2].ptr=temp;
    }
}


void print_hashtable(struct hash **htable, int size)
{
    int i;
    struct hashnode *tmp;
    struct hash *htmp = (*htable);
    printf("\nRank\tName\tRating\tCountry");
    for (i = 0; i < size; i++) {
        tmp = htmp[i].ptr;
        while (tmp != NULL) {
            printf("\n%d\t%s\t%d\t%s ", tmp->val,tmp->s,tmp->r,tmp->c);
            tmp = tmp->next;
        }
    }
}

void seach_hashtable(struct hash **htable, int val, int size)
{
    int slot, found = 0;
    slot = val;
    struct hashnode *tmp;
    tmp = (*htable)[slot].ptr;
    while (tmp != NULL) {
        if (tmp->val == val) {
            found = 1;
            printf("\nRank\tName\tRating\tCountry");
            printf("\n%d\t%s\t%d\t%s", tmp->val,tmp->s,tmp->r,tmp->c);
            break;
        }
        tmp = tmp->next;
    }if (found==0){printf("\nnot found...");}
}

void search_hashtable(struct hash **htable, char *s, int size)
{
    int i,slot=0;
    for (i=0;i<strlen(s);i++){
        slot+=s[i];
    }
    slot=slot%100;
    struct hashnode *tmp;
    tmp = (*htable)[slot].ptr;
    if (tmp==NULL){
        printf("\nnot found....");
    }else{
        while (tmp != NULL) {
            if (strcmp(tmp->s,s)==0) {
                printf("\nRank\tName\tRating\tCountry");
                printf("\n%d\t%s\t%d\t%s ", tmp->val,tmp->s,tmp->r,tmp->c);
                break;
            }
            tmp = tmp->next;
        }
    }
}


int main()
{
    struct hash *hashtable1,*hashtable2;
    int hashtable1size=100;
    hashtable1 = create_hash(hashtable1size);
    hashtable2 = create_hash(hashtable1size);
    int key, val, r;
    char s[15],c[10];
    FILE *fp;
    fp=fopen("cricket.txt","r");
    fseek(fp,0,SEEK_SET);
    while(!feof(fp)){
        fscanf(fp,"%d %s %d %s\n",&val,s,&r,c);
        insert_value(&hashtable1,&hashtable2, val, r, hashtable1size,s,c);
    }
    fclose(fp);
    while(1) {
        printf("\n 1. Print Table");
        printf("\n 2. Search by Rank");
        printf("\n 3. Search by Name");
        printf("\n 4. Exit");
        printf("\n Enter any option :");
        scanf("%d", &key);
        switch (key) {

            case 1:
                print_hashtable(&hashtable1, hashtable1size);
                break;
            case 2:
                printf("\n Enter rank : ");
                scanf("%d", &val);
                seach_hashtable(&hashtable1, val, hashtable1size);
                break;
            case 3:
                printf("\n Enter name : ");
                scanf("%s", s);
                search_hashtable(&hashtable2, s, hashtable1size);
                break;
            case 4:
                exit(0);
                break;
            default:
                printf("\nwrong option...");
                break;
        }
    }
    return 0;
}

