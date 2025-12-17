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
//----------------------------------------------------------------- Order History- yousef tarek
class OrderNode{
    public:
    int orderID;
    int customerID;
    string product_name;
    int price;
    OrderNode* Next;
    OrderNode* Prev;
    OrderNode(int or_id, int cs_id, string name, int money){
        orderID = or_id;
        customerID = cs_id;
        product_name = name;
        price = money;
        Next = Prev = NULL;
    }
};
class OrderHistory{
public:
    OrderNode* head;
    OrderNode* tail;
    OrderHistory(){
        head = tail = NULL;
    }
    void addOrder(int or_id, int cs_id, string name, int money){
        OrderNode * newNode = new OrderNode(or_id, cs_id, name, money);
        if (head== NULL){
            head = tail = newNode;
        }
        else{
            tail->Next = newNode;
            newNode->Prev = tail;
            tail = newNode;
        }
    }
    void viewOrders(int cs_id){
        OrderNode * temp = head;
        bool found = false;
        while(temp!= NULL){
            if(temp->customerID == cs_id){
                cout << "Order ID: " << temp->orderID << endl;
                cout << "Product: " << temp->product_name << endl;
                cout << "Price: " <<temp->price<<" $"<< endl;
                cout << "------------------------\n";
                found = true;
            }
            temp= temp->Next;
            }
            if(!found){
                cout<<" customer has not placed any orders"<<endl;
        }
    }
};
//----------------------------------------------------------------------------------------Product Catalog- yousef tarek
class productNode{
public:
    int productID;
    string name;
    string category;
    int price;
    int stock;
    productNode * left;
    productNode * right;
    productNode(int id, string n, string c, int p , int s){
        productID = id;
        name = n;
        category = c;
        price = p;
        stock = s;
        left = right = NULL;
    }
};
class productCatalog{
public:
    productNode* root;
    productCatalog(){
        root = NULL;
    }
    productNode* addProduct(productNode* r, int id, string n, string c, int p, int s){
        if(r == NULL){
            return new productNode(id,n,c,p,s);
        }
        if(id< r->productID){
            r->left = addProduct(r->left, id, n, c, p, s);
        }
        if(id> r->productID){
            r->right = addProduct(r->right, id, n, c, p, s);
        }
        return r;
    }
    void addProduct(int id, string n, string c, int p, int s){
        root = addProduct(root,id ,n ,c , p, s);
    }
    productNode* searchProduct(productNode* r, int id){
        if(r == NULL || id==r->productID){
            return r;
        }
        if(id < r->productID ){
            return searchProduct(r->left,id);
        }
        if(id > r->productID){
            return searchProduct(r->right,id);
        }
    }
    void searchProduct(int id){
        productNode* result = searchProduct(root, id);
        if(result == NULL){
            cout<<"product not found "<<endl;
        }
        else{cout << "Product ID: " << result->productID << endl;
        cout << "Name: " << result->name << endl;
        cout << "Category: " << result->category << endl;
        cout << "Price: " << result->price << " $" << endl;
        cout << "Stock: " << result->stock << endl;}
    }
    productNode* findMin(productNode* r){
        while(r->left != NULL){
            r = r->left;
        }
        return r;
    }
    productNode* removeProduct(productNode* r, int id){
        if(r== NULL){
            return NULL;
        }
        if(id< r->productID){
            r->left = removeProduct(r->left,id);
        }
        else if(id> r->productID){
            r->right = removeProduct(r->right,id);
        }
        else{
            if(r->left == NULL && r->right == NULL){
                delete r;
                return NULL;
            }
            else if(r->left == NULL){
                productNode* temp = r->right;
                delete r;
                return temp;
            }
            else if(r->right == NULL){
                productNode* temp = r->left;
                delete r;
                return temp;
            }
            else{
                productNode* temp = findMin(r->right);
                r->productID = temp->productID;
                r->name = temp->name;
                r->category = temp->category;
                r->price = temp->price;
                r->stock = temp->stock;
                r->right = removeProduct(r->right, temp->productID);
            }
        }
        return r;
    }
    void removeProduct(int id){
        root = removeProduct(root,id);
    }

};

//-----------------------------------------------------------------------------------------------------------------
int main()
{
    FIO
    return 0;
}
