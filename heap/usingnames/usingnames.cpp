// Test with:
// CXX=clang++
// $CXX --std=c++17 -o usingnames usingnames.cpp && ./usingnames

#include <iostream>

class A
{
public: //< necessary if exporting Info
  struct Info
  {
    int a{};
    int b{};
    int id{};
    Info() :id{nextId(true)} { std::cout << "Constructing Info " << id << '\n'; }
    ~Info() { std::cout << "Destructing Info " << id << '\n'; }
    // Rule of 5 requires following
    Info(const Info& r) : a(r.a), b(r.b), id(r.id+10) {}
    Info(Info&&) = default;
    Info& operator=(const Info& rhs) = default;
    Info& operator=(Info&&) = default;
    void show() const { std::cout << "{ id:" << id << ", a:" << a << ", b:" << b << "}\n"; }
    static int nextId(bool update=false) { static int id{0}; if(update) ++id; return id; }
  };
};

class B
{
public: //< necessary if exporting Myinfo and f
  using Myinfo = A::Info;
  void f(const Myinfo &info);
private:
  int used{0};
};

void B::f(const Myinfo &info) {
    std::cout << "Executing " << __func__ << '\n';
    Myinfo temp = info; //< Copy construction
    temp.a = 2;
    temp.show();
    ++used;
}

int main()
{
  using Myinfo = B::Myinfo;
  B b;
  Myinfo info;
  info.show();
  b.f(info);
  return 0;
}
