#include <bits/stdc++.h>
#define FIO ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define nl '\n'
using namespace std;

class node_queue
{
public:
    node_queue *next;
    int order_num;
};
class Delivery_Queue
{
public:
    node_queue *front;
    node_queue *rear;
    Delivery_Queue()
    {
        front = rear = NULL;
    }
    bool isempty()
    {
        if (front == NULL && rear == NULL)
        {
            return true;
        }
        return false;
    }
    void deliveryenqueue(int id)
    {
        node_queue *newnode = new node_queue();
        newnode->order_num = id;
        newnode->next = NULL;
        if (isempty())
        {
            rear = front = newnode;
        }

        else
        {
            rear->next = newnode;
            rear = newnode;
        }
    }
    void deliverydequeue()
    {
        if (isempty())
        {
            cout << "No orders to process. " << nl;
        }
        else
        {
            node_queue *del = front;
            front = front->next;
            cout << "Done with order number: " << del->order_num << nl;
            if (front == NULL)
            {
                rear = NULL;
            }
            delete del;
        }
    }
};
int main()
{
    FIO
    Delivery_Queue q;
    q.deliveryenqueue(1233);
    q.deliveryenqueue(234);
    q.deliverydequeue();
    return 0;
}