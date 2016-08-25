//Header Files
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//Structure of each Node
struct node
{
    int data;
    struct node * next;
};

typedef struct node* Node;
//Function Definition
Node push( Node,int);       //To add node at the starting of the list
void insert(Node,int);      //To insert node after a given node
void display(Node);         //To display content of the list
int countNode(Node);        //Number of nodes in the list
Node deleteNode(Node,int);      //To delete a node from list
Node deleteDup(Node);           //To remove duplicate elements from list
int skipList(Node);             //To implement a skip list and seatch an element in the list
void middle(Node head);        //The node present in the center of the list

Node push(Node head,int data)
{
    Node newNode = malloc(sizeof(struct node));         //Dynamically declaring memory for a node
    newNode->next = head;
    newNode->data = data;
    
    return newNode;
}

void insert(Node cur,int data)
{
    Node newNode = malloc(sizeof(struct node));
    newNode -> data = data;
    newNode -> next = cur->next;
    cur -> next = newNode;

}

int countNode(Node head)
{
    int cnt = 0;
    while(head != NULL)
    {
        cnt ++;
        head = head -> next;
    }
    return cnt;
}

void display(Node head)
{
    
    if(head == NULL)        //List empty
    {
        printf("Empty\n");
        return;
    }

    int cnt = countNode(head);
    printf("Number of nodes are : %d\n",cnt);
    while(head != NULL)
    {
        printf("%d\t",head -> data);
        head = head -> next;
    }
}

Node deleteNode(Node head,int data)
{
    Node prev;
    Node cur;
    prev = cur = head;

    //If the data to be deleted is the first node
  if(data == cur-> data && cur != NULL)
    {   
        prev = head -> next;
        free(cur);
        printf("Data Deleted\n");
        return prev;
    }
    while(cur != NULL)
    {
        if(data < cur -> data)      //If data is less than cur -> data,no match possible as the list is in sorted order
            {
                printf("Data not found\n");
                return head;
            }
        else if(data == cur -> data)
        {
            prev -> next = cur -> next;
            free(cur);
             printf("Data Deleted\n");
            return head;
        }
        prev = cur;
        head = cur -> next;
    }
    printf("Data not found\n");
    return head;
}

Node deleteDup(Node head)
{
    Node cur,trav;
    cur = head;
    while(cur != NULL)          //Till all the nodes are checked
    {
        trav = cur -> next;
        while(trav != NULL)         //To compare 'cur' with all the nodes in the list
        {
            if(cur -> data == trav -> data)
            {

                cur ->next = trav -> next;   //Address of node after the duplicate node must be stored in previous node
                free(trav);
            }
            else
                trav = trav -> next;

            if(trav -> data > cur -> data)      //List is in sorted order.If 'cur' should be less than 'trav',
                trav = NULL; 
        }
        cur = cur -> next;
    }
    return head;

}

void middle(Node head)
{
    int cnt = countNode(head);
    if(cnt % 2 == 0)            //if number of elements are even,then there is not single middle element
    {
        printf("No middle node(Even number of nodes present in the list)\n");
        return;
    }
    int c = 0;

    while(c < cnt/2 && head != NULL)
    {
        c ++;
        head = head -> next;
    }
    printf("Middle Node is %d\n",head -> data);
}

int skipList(Node head)
{
    int n = sqrt(countNode(head));          //Determines number of nodes in express way
    printf("%d\n",n);
    Node layerTwo[10],startRange,endRange,cur;      //layerTwo is the layer of abstraction used to traverse the linked list
    int pos = 1,cntr = 0 , count = 1,num,c = 0;
    cur = head;
    
    while(cntr < n)         //Number of enodes in express way is 'n'
    {
        layerTwo[cntr++] = cur ;    //Store nodes in express way
        while((pos + n + 1) != count && cur != NULL)        //In the linked list,the difference between two express way nodes is 'n' list elements
        {
            cur = cur -> next;
            count ++;
        }
        pos = count;        
    }
    printf("\nExpress Way : \n");
    for(int i = 0;i < n;i ++)       //Display express way nodes
        printf("%d\t",layerTwo[i] -> data);
    
    printf("\nEnter the number to be searched in Skip List : ");
    scanf("%d",&num);
    startRange = endRange = NULL;       // {5,15,20,25,35,40,45,50,55,65,70}, where 15 and 55 are express nodes,and we are looking for '35'.Then startRange = 15 and endRange = 55
    for(int i = 0;i < n;i ++)
    {
        if(layerTwo[i] -> data == num)          //If startRange contains the element we are searching
            return 1;
        else if(layerTwo[i] -> data < num && layerTwo[i] -> next != NULL && i == n - 1)      /*If number of elements in a list is not a perfect square,then num maybe present beyond 
                                                                                              the last express way node.If num is equal to '65'' or '70' from the above example */    
           {
                startRange = layerTwo[i] -> next;
                c = 1;
                break;
           }
        else if(layerTwo[i] -> data > num && i != 0)        /*If the express way node 'data' is greater than 'num','num' is now present between the previous express way node and current
                                                         express way node. Except when 1st express way node 'data' is greater than 'num' shows it is not present in the list(List is in sorted order) */   
        {
            startRange = layerTwo[i - 1];
            endRange = layerTwo[i];
            break;
        }
        else            //Not preset
            return 0;
    }

    if(startRange == NULL)      //When 'num' is not found in list
        return 0;
    else
    {
        if(c)               //Checking if 'num' is present after the last express way node in the link list
        {
            while(startRange != NULL)       //startRange = NULL indicates 'num' is not present in the list
            {
                if(startRange -> data == num)       //'num' found in the list
                    return 1;
                startRange = startRange -> next;        //traverse  the list
            }
            return 0;           //When startRange equals NULL
        }
        else                //When we have both startRange and endRange
        {
            cur = startRange;
            while(cur -> data <= endRange->data)        //traverse the list from startRange till endRange
            {
                if(cur -> data == num)
                    return 1;
                cur = cur -> next;
            }
        }
        return 0;
    }
}

//Main Method
int main()
{
    // struct Node *first = malloc(sizeof(struct Node));
    int num,res;
    // printf("Enter the data for 1st element : ");
    // scanf("%d",&num);
    // first -> data = num;        //Accept the 1st node
    // first -> data = first -> next = NULL;
    Node head = NULL;
    int ch = 0;
    while(1)
    {
        printf("\n1.Insert\t2.Display\t3.Delete\t4.Delete Duplicate\t5.Middle\t6.Skip List\tAny Other Input To Exit\nEnter Choice : ");
        scanf("%d",&ch);
        switch(ch)
        {
          case 1:  printf("Enter the data for next element : ");
                    scanf("%d",&num);
                    if(head == NULL) 
                        head = push(head,num);
                    else
                        {
                            Node prev = NULL;
                            Node cur;
                            cur=  head;
                    // Finding the position for the new node
                            while(cur != NULL && num > cur -> data)
                            {
                                if(num <  cur -> data)
                                {
                                    break;
                                }   
                                else
                                {
                                    prev = cur;
                                    cur = cur -> next;
                                }
                            }

                        if(prev == NULL)        //To be inserted in the front of the list
                            head = push(cur,num);
                        
                        else                    //To be inserted in after 'prev'
                            insert(prev,num);
                        }
                        break;

            case 2 :  display(head);
                      break;

            case 3 :  printf("Enter the data to be deleted : ");
                      scanf("%d",&num);
                      head = deleteNode(head,num);
                      break;
            
            case 4 : head = deleteDup(head);
                     break;

            case 5 : middle(head);
                     break;

            case 6 : res = skipList(head);
                     if(res)
                        printf("\nElement Found\n");
                     else   
                        printf("\nElement not found!\n");
                     break;
            default : exit(0);
        }
    }
    return 0;
}