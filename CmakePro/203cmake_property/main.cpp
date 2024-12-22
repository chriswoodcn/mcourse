#include <iostream>
using namespace std;
int main() {
  cout << "Test cmake property" << endl;
#ifdef PARA1
  cout << "PARA1 = " << PARA1 << endl;
#endif
#ifdef PARA2
 cout << "PARA2 = " << PARA2 << endl;
#endif
  return 0;
}