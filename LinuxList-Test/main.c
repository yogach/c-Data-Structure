#include <stdio.h>
#include "LinuxList.h"

void List_demo_1()
{
    struct Node
    {
      struct list_head head;
      int value;
    };

    struct Node l = {0};
    struct list_head* list = (struct list_head*)&l;
    struct list_head* slider = NULL;

    INIT_LIST_HEAD(list);

    for(int i=0; i<5; i++)
    {
        struct Node* n = (struct Node*)malloc(sizeof(struct Node));

        n->value = i;

        list_add_tail((struct list_head*)n, list);
    }

    list_for_each(slider, list)
    {
        printf("%d\n", ((struct Node*)slider)->value);
    }

    printf("remove start..\n");

    list_for_each(slider, list)
    {
        if( ((struct Node*)slider)->value == 3 )
        {
            list_del(slider);
            free(slider);
            break;
        }
    }

    list_for_each(slider, list)
    {
        printf("%d\n", ((struct Node*)slider)->value);
    }

    printf("remove end..\n");

}


void List_demo_2()
{
    struct Node
    {
        int value;
        struct list_head head;
    };

    struct Node l = {0};
    struct list_head* list = &l.head;
    struct Node* slider = NULL;

    INIT_LIST_HEAD(list);

    for(int i=0; i<5; i++)
    {
        struct Node* n = (struct Node*)malloc(sizeof(struct Node));

        n->value = i;

        list_add(&n->head, list);
    }

    list_for_each_entry(slider, list, head)
    {
        printf("%d\n", slider->value);
    }

    printf("remove start..\n");

    //第一个参数存放每个链表节点 第二个参数为链表头，第三个参数是member在struct Node中的名字
    list_for_each_entry(slider, list, head)
    {
        if( slider->value == 3 )
        {
            list_del(&slider->head);
            free(slider);
            break;
        }
    }

    list_for_each_entry(slider, list, head)
    {
        printf("%d\n", slider->value);
    }

    printf("remove end..\n");

}

int main()
{
    //List_demo_1();
    List_demo_2();

    return 0;
}
