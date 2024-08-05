# Tutorial for CreateC

### This tutorial will help you use CreateC

To make a project build file.
1. Make a build.json in your project directory
2. Add a required 'project' entry. This will contain your project's name
3. Add a required 'sources' array entry. This will contain your source file paths.
4. Add a optional 'libraries' array entry. This will contain your library names. Go to the 'libraries' header to see how to link with gtk, gtkmm and qt5
5. Add a optional 'optlvl' entry. This will contain the optimisation level. Ranging from 1 (min) to 3 (max)
6. Add a optional 'cppstd' entry. This will contain the c++ standard you want to use. Valid vals are: 98, 11, 14, 17, 20, 23


# Libraries
### To add gtkmm, add 'gtkmm' in the libraries entry
### To add gtk3, add 'gtk3' in the libraries entry
### To add QtWidgets, QtCore, QtGui.  Add 'qt5widgets', 'qt5core' and 'qt5gui' in the libraries entry

## Here is a example json file
<pre>
{
    "project": "helloworld",
    "sources": [ 
        "main.cpp"
    ],
    "libraries": [
        "qt5widgets",
        "qt5core",
        "qt5gui",
        "gtkmm",
        "gtk3",
        "raylib",
        "SDL2",
        "SFML"
    ]
}
</pre>