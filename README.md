# ONNXPlugins - Work in Progress
A set of UE5 pluins for creating and using ONNX models in memory from blueprints.  Currently only supports Multilayer Perceptrons

NOTE: This plugin contains a project that builds an external library in a sub-project that the UE5 build then uses.  All necessary
libraries should be in this repo BUT if you want to change or rebuild the external library you must *manually* rebuild
it by loading <your project>\Plugins\ONNXBuilderPlugin\Source\ThirdParty\ONNXBuilderLibraryLibrary\ExampleLibrary.sln in your 
favorite IDE (I use Rider) and build the solution for Win64/release.  Failure to do so will keep the project from building which
will manifest as a failed load in the UE5 editor.

If you get such a load failure, open your entire project in your IDE and attempt to build it.  This will generate a  lot more
error detail.

## To Use
1. Clone or copy this repo into your <your project>/Plugins directory.  You may have to create this directory yourself if
these are your first plugins.
2. Load the project in UE5
3. See the WIKI for blueprint information
