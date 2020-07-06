#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

struct entry {
  char name[32];
  char sex;
  int  age;
  struct entry *next;
};

struct entry *CreateEntry()
{
  struct entry *ep;

  ep = (struct entry *)malloc(sizeof(struct entry));
  ep->next = NULL;
  return ep;
}

struct entry *GenerateData(struct entry *Top, int num)
{
  struct entry *ep;
  char name[32];
  char sex;
  int age;
  int i;

  srandom(getpid());
  for (i = 0; i < num; i++) {
  
    /*
     * Node setup
     */
    if (Top == NULL) {
      Top = CreateEntry();
      ep = Top;
    } else {
      for (ep = Top; ep->next != NULL; ep = ep->next);
      ep->next = CreateEntry();
      ep = ep->next;
    }

    sprintf(ep->name, "%d", i);
    ep->sex = (random()%2)?'M':'F';

    ep->age = random()%100;
  }
  return (Top);
}

int main(int argc, char *argv[])
{
  struct entry *Top;
  struct entry *ep;
  int num;

  /*
   *
   */
  if (argc < 2) {
    fprintf(stderr, "Usage: %s number\n", argv[0]);
    exit(-1);
  }
  num = atoi(argv[1]);
  /*
   * generate initial data with num
   */
  Top = (struct entry *)NULL;
  Top = GenerateData(Top, num);

  /*
   * Print out Entry Data
   */
  printf("Name\tSex\tAge\n");
  for (ep = Top; ep != NULL; ep = ep->next) {
    printf("%s\t%c\t%d\n", ep->name, ep->sex, ep->age);
  }

  /* 
   * sorting by age
   *
  Top = sortlist(Top);
  */
  printf("Name\tSex\tAge\n");
  for (ep = Top; ep != NULL; ep = ep->next) {
    printf("%s\t%c\t%d\n", ep->name, ep->sex, ep->age);
  }


}
