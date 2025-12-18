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
    void search_Costumer(int id){
        if(isExists(id))
            cout<<"Costumer with ID: "<<id<<" is found"<<nl;
        else 
            cout<<"Costumer with ID: "<<id<<" isn't found"<<nl;
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
//-----------------------------------------------------------------------------------------------------------------

// Product catalog and sorting BST - Youssef and Farha---------------------------------------------------------------
class productNode{
public:
    int productID;
    string name;
    string category;
    double price;
    int stock;
    productNode * left;
    productNode * right;
    productNode* priceLeft;
    productNode* priceRight;
    productNode(int id, string n, string c, double p , int s){
        productID = id;
        name = n;
        category = c;
        price = p;
        stock = s;
        left = right = NULL;
        priceLeft=NULL;
        priceRight=NULL;
    }
};
class productCatalog{
public:
    productNode* root;
    productNode* rootPrice;
    productCatalog(){
        root = NULL;
        rootPrice=NULL;
    }
    productNode* addID(productNode* r,productNode* newnode){
        if(r == NULL){
            return newnode;
        }
        if(newnode->productID < r->productID){
            r->left = addID(r->left, newnode);
        }
        if(newnode->productID > r->productID){
            r->right = addID(r->right, newnode);
        }
        return r;
    }
    

    productNode* addPrice(productNode* root, productNode* newnode){
        if(!root) return newnode;
        if(newnode->price< root->price)
            root->priceLeft=addPrice(root->priceLeft,newnode);
        else 
            root->priceRight=addPrice(root->priceRight,newnode);
        return root;
        }
    
    
    void insertProduct(int id, string n, string c, double p, int s){
        productNode* newnode=new productNode(id,n,c,p,s);
        root=addID(root,newnode);
        rootPrice=addPrice(rootPrice,newnode);
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
            cout<<"Product not found "<<nl;
        }
        else{cout << "Product with ID: " << result->productID << " is found" <<nl;}
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


    void sortBy_ID(productNode* root){
        if(!root) return;
        sortBy_ID(root->left);
        cout<<"Product Name: "<<root->name<<nl<<"ID: "<<root->productID<<nl<<"Price: "<<root->price<<" L.E"<<nl;
        sortBy_ID(root->right);
    }

    void sortBy_price(productNode* root){
        if(!root) return;
        sortBy_price(root->priceLeft);
        cout<<"Product Name: "<<root->name<<nl<<"ID: "<<root->productID<<nl<<"Price: "<<root->price<<" L.E"<<nl;
        sortBy_price(root->priceRight);
    }
};
//---------------------------------------------------------------------------------------------------------------------------


int main()
{
    FIO
     productCatalog catalog;
    catalog.insertProduct(101,"Laptop","Electronics",30000,10);
    catalog.insertProduct(55,"Mouse","Accessories",250,100);
    catalog.insertProduct(200,"Phone","Electronics",15000,25);
    catalog.insertProduct(80,"Keyboard","Accessories",500,60);

    catalog.searchProduct(55);

    cout << "\t Products by ID"<<nl;
    catalog.sortBy_ID(catalog.root);

    cout << "\tProducts by Price"<<nl;
    catalog.sortBy_price(catalog.rootPrice);
    return 0;
}