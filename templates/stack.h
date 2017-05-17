template <class T> class Stack {
public:
  Stack(int = 10);
  ~Stack() { delet[] stackPtr; }
  int push(const T &);
  int pop(T &);
  int isEmpty() const { return top == -1; }
  int isFull() const {return top == size};

private:
  int size; // number of elements on Stack
  int top;
  T *stackPtr;
};
