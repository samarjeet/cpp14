class X {
private:
  int m;

public:
  X(int i = 0) : m{i} {}
  int mf(int i) {
    int old = m;
    m = i;
    return old;
  }
};

X var{7};

int user(X var, X *ptr) {
  int x = var.mf(7);
  int y = ptr->mf(9);
  // int z = var.m;
}
