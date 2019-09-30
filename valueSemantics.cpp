/*
 * Trying to work through Sean Parent's talk on 
 * Value semantics and concept based polymorphism
 */

#include<iostream>
#include<memory>
#include<string>
#include<vector>

using namespace std;

// Library

//using object_t = int;

class object_t {
public:
    virtual ~object_t() {}
    virtual void draw(ostream&, size_t) const = 0;
};


class my_class_t : public object_t {
public:
    void draw(ostream& out, size_t position) const {
        out << string(position, ' ') << "my_class_t" << endl;
    }
};
/*
 void draw(const object_t& x, ostream& out, size_t position){
    out << string(position, ' ') << x << endl;
}
*/


//using document_t = vector<object_t>;
using document_t = vector<shared_ptr<object_t>>;

void draw(const document_t& x, ostream& out, size_t position){
    out << string(position, ' ') << "<document>" << endl;
    for (auto& e : x) e->draw(out, position + 2);
    out << string(position, ' ') << "</document>" << endl;
}




// Client

int main() {
    document_t document;
/*
    document.emplace_back(0);
    document.emplace_back(1);
    document.emplace_back(2);
    document.emplace_back(3);
    document.emplace_back(4);
*/

    document.emplace_back(new my_class_t());
    draw(document, cout, 0);
    return 0;
}
