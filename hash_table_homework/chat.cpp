#include "chat.h"
#include "iostream"
#include <string>

Chat::Chat() {
    data_count = 0;
}
void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    // Ваш код
    uint * digest = sha1(_pass, pass_length);
    data[data_count] = AuthData(_login, digest);
    //delete [] digest;
    data_count++;
}
bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    // Ваш код
    // Нужно вернуть true в случае успешного логина
    uint * hash_password = sha1(_pass, pass_length);
    for (int i = 0; i < data_count; i++){
      std::cout << data[i].login << " " << "name" << std::endl;
      int temp = 0;
      for (int j = 0; j < strlen(data[i].login); j++){
        if(data[i].login[j] == _login[j]){
          temp++;
        }
      }

      if (((*hash_password) == (*data[i].pass_sha1_hash)) && (temp == strlen(data[i].login))){
        return true;
      }

    }
    return false;
}
