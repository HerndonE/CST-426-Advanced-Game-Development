/*
  Simplified MVC Example
  CST 426 Advanced Game Design Lab 00 MVC
  Original :Krzysztof Pietroszek
  Updated 29-July-2020 Clinkenbeard
*/

#include <iostream>
#include <list>
using namespace std;

class Controller;
class View;
class TextView;
class Model;

/*
    View is a generic abstract class that does not know anything about the model.

    Sometimes view is combined with input reading, so we read it here
*/

class View {
    string dataToDisplay;
    Controller* controller;
public:
    // we will implement Update function in subclasses (late binding)
    virtual void Update(string dataToDisplay) = 0;
    //Late binding function
    virtual void Reverse(string datatToDisplay) = 0;
    virtual void attachController(Controller* c){
        controller = c;
    }
    // we could override the input function in concrete views below, but it is implemented in this class (below)
    virtual void acceptInput();
};

/*
    This is a concrete implementation of a View: text View. It will display data as text, but it is still a view so it inherits from the View class
*/
class TextView : public View{
public:
    /*
    Update is a pure virtual function defined in 'View' written above.
    We implement it here.
    */
    virtual void Update(string dataToDisplay){
        // notice that TextView does not store any data, only displays it

        cout << "New data arrived! Displaying it: " << endl << dataToDisplay[0] << endl;
    }

    void Reverse(string dataToDisplay){
      //Reverse the string that was inputted by user
      cout << "Reversing String " << dataToDisplay << endl;
      for(int i = dataToDisplay.size()-1; i>=0; i--)
        cout << dataToDisplay.at(i);
      cout << endl;
    }
};

/*
    Models only knows about data and which views should be informed.
    A model does not know anything about the controller of the data, or who (which controller) modified the data that is stored in the model
*/

class Model {
    /*
        here is a list of all the views. Notice that we have list of type View. We will be adding an object of type TextView. What is the tenant of object oriented programming that makes this possible?
    */
    list<View*> views;
    string modelData;

public:
    // we can attach many views to Model
    void attachView (View* v){
        // add/register a new view (not of class View, but of a subclass of class view)
        views.push_front(v);
    }

    void detachView (View* v) {
        // remove/deregister a view
        views.remove(v);
    }

    void notifyViews() {
        /*
            notify all views that there is a new data to be displayed
            Note: I'm using the "old" iterator to iterate through list of views, but you could also use C++ 11 lamda notation, if you wish
        */
        for (list<View*>::iterator it = views.begin(); it != views.end(); it++)
        {
            /*
             We are using late-binding here so the Update function of subclass of View will be called
            */
            (*it)->Update(modelData);
            (*it)->Reverse(modelData);
        }
    }

    void setState(string updatedData){
        modelData = updatedData;
        notifyViews();
    }
};

class Controller {
    Model* model;
public:
    void setModel(Model* m){
        model = m;
    }
    void processInput(string input);
};

void Controller::processInput(string input) {
    // do something to input, e.g. distribute it to various models
    // in this case, we simply take the first letter
    string data = input;
    model->setState(data);
};

void View::acceptInput() {
        // notice that view only accepts input,
        // (sometimes) validates it
        // but immediately sends it to the controller and NEVER updated the model
        string input;
        getline(cin, input);
        controller->processInput(input);
};


int main(int argc, const char * argv[]) {

    // initialize objects and link them, as required
    Model*      m = new Model();
    TextView*   v = new TextView();
    Controller* c = new Controller();

    c->setModel(m);
    m->attachView(v);//notice that we are passing TextView* to View* (polymorphism again)
    v->attachController(c);

    // main (game) loop. Just read input forever,
    cout << "Welcome to the SimplifiedMVC! Write something and I will pass it to controller\n, who will process it (taking just the first letter) and update the model\n, which will then notify all registered views to show it. \nIn result of this complex information flow you will be able to see the first letter of what you wrote!" << endl;
    while(true){
        v->acceptInput();
    }
}
