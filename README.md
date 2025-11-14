# Tvmaze
api for Tvmaze.com tv shows and serials information site
# main
```cpp
#include "Tvmaze.h"
#include <iostream>

int main() {
   Tvmaze api;

    auto photos = api.get_people_list().then([](json::value result) {
        std::cout << "Search results: " << result.serialize() << std::endl;
    });
    photos.wait();
    
    return 0;
}
```

# Launch (your script)
```
g++ -std=c++11 -o main main.cpp -lcpprest -lssl -lcrypto -lpthread -lboost_system -lboost_chrono -lboost_thread
./main
```
