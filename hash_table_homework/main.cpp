#include <iostream>
#include <cstring>
#include "chat.h"
#include "sha1.h"

int main(){
  Chat chat;
  char * name[LOGINLENGTH] = {"name"};
  char * password[] = {"pip"};
  int size_str = sizeof(* password);

  chat.reg( * name, * password, size_str);
  std::cout << "Is our login-password ok? " << chat.login(* name, * password, size_str) << std::endl;
  //std::cout << true << std::endl;
  return 0;
}
