# Libtimer

Libtimer is a C++ lirary that implements a simple timer.

This library uses threads and mutex.

## Timer Methods

### constructor()
Creates the timer

Params:
- running: if the timer starts running immediately
- time: time in seconds for timeout
- timer_callback: the fuction that runs when the timer reaches timeout

### stop()
Stops the timer is timer is running

### start()
Starts the timer if timer is stopped

## Setup
```bash
cd your-third-party-folder
git clone https://github.com/LynTheDev/libtimer
```
Now in your CMakeLists.txt
```cmake
add_subdirectory(your-third-party-folder/libtimer)

...

target_link_libraries(${PROJECT_NAME} PRIVATE
    // Your other libraries
    libtimer
)
```

## Example

```cpp
#include <iostream>
#include <timer.hpp>

void t_time_out()
{
    std::cout << "Timed out!" << std::endl;
}

int main()
{
    // Create a timer that runs t_time_out every 5 seconds.
    Timer t = Timer(true, 5, t_time_out);
}
```

## License
MIT