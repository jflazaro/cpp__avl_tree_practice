Template for developing c++ projects 

The file structure was designed with CMake in mind.<br />
Assign an executable name in the CMakeLists.txt by editing this line:<br />
  set(MY_PROJECT_NAME "template_project") <-- Replace 'template_project' with your desired executable name.<br />

Usage (MacOS/Linux):<br />
cd build/<br />
cmake ..<br />
make<br />
(Find binary file within this same directory.)<br />

Usage (Windows):<br />
cd build/<br />
cmake ..<br />
cmake --build .<br />
(Find exe under build/Debug/)<br />