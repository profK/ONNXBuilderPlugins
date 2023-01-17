# ONNXPlugins - Work in Progress
A set of UE5 pluins for creating and using ONNX models in memory from blueprints.  Currently only supports Multilayer Perceptrons

NOTE: This plugin contains library files from the ONNXBuilder github project.  To change these libs you want to doawnload the ONNXBuilder repo, buid it, and then copy them over the ones here.  To create lib files that link properly with UE5 you MUST rebuild ONNXBuilder for Release/x64 with MSVC tools 142.  (Not 141, not 143. ONLY 142 will link properly.)

If you get such a load failure, open your entire project in your IDE and attempt to build it.  This will generate a  lot more
error detail.

## To Use
1. Clone or copy this repo into your <your project>/Plugins directory.  You may have to create this directory yourself if
these are your first plugins.
2. Load the project in UE5
3. See the WIKI for blueprint information
