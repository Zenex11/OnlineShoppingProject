#include<iostream>
using namespace std;
#include <string>;
class node{
    public:
    node* next;
    int  order_num;
};
class queue{
    public:
    node* front;
    node* rear;
    queue(){
        front=rear=NULL;
    }
    bool isempty(){
        if(front==NULL&&rear==NULL){
            return true;
        }
        return false;
    }
    void deliveryenqueue(int id){
        node* newnode=new node();
        newnode->order_num=id;
        newnode->next = NULL;
        if(isempty()){
            rear=front=newnode;
        }

        else{
            newnode->next=rear;
            rear=newnode;
        }

    }
    void deliverydequeue(){
        node* del=front;
        front=front->next;
        cout<<"done with order number: "<<del->order_num;
        delete del;
    }
};
int main(){
    queue q;
    q.deliveryenqueue(1233);
    q.deliveryenqueue(234);
    q.deliverydequeue();
    return 0;
}