#include <bits/stdc++.h>
#define FIO ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define nl '\n'
using namespace std;
// Delivery Queue- Mohamed----------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------------------------------------

// Customer Accounts- SLL & file handeling- Farha-------------------------------------------------------------------------------
class node_Customer
{
private:
    int id;
    string name;
    string email;
    string phone;
    string address;

public:
    node_Customer *next;
    int getID() const{ return id; }
    string getName() const { return name; }
    string getEmail() const{ return email; }
    string getPhone() const{ return phone; }
    string getAddress() const{ return address; }
    node_Customer()
    {
        id = 0;
        name = email = phone = address = "";
        next = NULL;
    }
    node_Customer(int id, string name, string email, string phone, string address) : id(id), name(name), email(email), phone(phone), address(address), next(NULL) {}
    void display_Customer()
    {
        cout << "ID: " << id << nl << "Name: " << name << nl << "Phone: " << phone << nl << "Address: " << address << nl;
    }
};

class Customer
{
private:
    node_Customer *head;
    string filename = "customers.csv";

    bool isExists(int id) {
        node_Customer* temp = head;
        while(temp) {
            if(temp->getID() == id) return true;
            temp = temp->next;
        }
        return false;
    }

public:
    Customer()
    {
        head = NULL;
    }
    void addCustomer(int id, string name, string email, string phone, string address,bool autoSave=true)
    {
        if(isExists(id)){
            cout<<"Customer with ID "<<id<<" already exists!!"<<nl<<"-----------------------------"<<nl;
            return;
        }
        node_Customer *newcustomer = new node_Customer(id, name, email, phone, address);
        if (!head)
        {
            head = newcustomer;
        }
        else
        {
            node_Customer *temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newcustomer;
        }
        cout << "Customer with ID: " << newcustomer->getID() << " added successfully!" << nl << "--------------------------" << nl;
        if(autoSave) save_File();
    }
    void removeCustomer(int id)
    {
        if (!head)
        {
            cout << "Customer Accounts List is empty!!!!!" << nl << "-----------------------" << nl;
            return;
        }
        node_Customer *temp = head;
        if (head->getID() == id)
        {
            head = head->next;
            delete temp;
            cout << "Customer with ID: " << id << " removed successfully! " << nl << "-------------------------" << nl;
            save_File();
            return;
        }
        while (temp->next && temp->next->getID() != id)
            temp = temp->next;
        if (!temp->next)
        {
            cout << "Customer with ID: " << id << " is not found!!!!" << nl << "---------------------------------" << nl;
            return;
        }
        node_Customer *del = temp->next;
        temp->next = temp->next->next;
        delete del;
        cout << "Customer with ID: " << id << " removed successfully! " << nl << "----------------------------------" << nl;
        save_File();
    }
    void Show_Customers()
    {
        if (!head)
        {
            cout << "No customers to display!" << nl << "---------------------------" << nl;
            return;
        }
        node_Customer *temp = head;
        while (temp)
        {
            temp->display_Customer();
            cout << "------------------" << nl;
            temp = temp->next;
        }
    }
    void save_File(){
        ofstream file(filename);
        if(!file){
            cout<<"WARNING!!!!! Error opening the file!!!!!"<<"----------------------------------"<<nl;
            return;
        }
        file << "ID,Name,Email,Phone,Address" << nl;
        node_Customer* temp = head;
        while (temp) {
            file << temp->getID() << ","<< temp->getName() << ","<< temp->getEmail() << ","<< temp->getPhone() << ","<< temp->getAddress() << nl;
            temp = temp->next;
        }
        file.close();
        cout << "Customers data saved successfully!" << nl<<"-----------------------------"<<nl;
    }
    void load_Data(){
        ifstream file(filename);
        if (!file) {
            cout << "No data found." << nl<<"------------------------"<<nl;
            return;
        }
        string line;
        getline(file, line);
        while (getline(file, line)) {
            stringstream ss(line);
            string id, name, email, phone, address;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, email, ',');
            getline(ss, phone, ',');
            getline(ss, address, ',');
            if(!isExists(stoi(id))){
            addCustomer(stoi(id), name, email, phone, address, false); // false عشان ما يحفظش الملف تاني
        }   
        }

        file.close();
    }

    ~Customer()
    {
        while (head)
        {
            node_Customer *del = head;
            head = head->next;
            delete del;
        }
    }
};
//----------------------------------------------------------------- course enrollment- yousef tarek
class EnrollmentNode{
    public:
    int studentID;
    int courseID;
    EnrollmentNode* Next;
    EnrollmentNode* Prev;
    EnrollmentNode(int st_id, int cs_id){
        studentID = st_id;
        courseID = cs_id;
        Next = Prev = NULL;
    }
};
class EnrollmentHistory{
public:
    EnrollmentNode* head;
    EnrollmentNode* tail;
    EnrollmentHistory(){
        head = tail = NULL;
    }
    void add(int st_id, int course_id){
        EnrollmentNode * newNode = new EnrollmentNode(st_id,course_id);
        if (head== NULL){
            head = tail = newNode;
        }
        else{
            tail->Next = newNode;
            newNode->Prev = tail;
            tail = newNode;
        }
    }
    void view(int st_id){
        EnrollmentNode * temp = head;
        while(temp!= NULL){
            if(temp->studentID == st_id){
                cout<<"Course Id: "<<temp->courseID<<endl;

            }
            temp= temp->Next;
        }
    }
};
//-----------------------------------------------------------------------------------------------------------------
int main()
{
    FIO
    return 0;
}
