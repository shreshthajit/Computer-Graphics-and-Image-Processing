# Computer-Graphics-and-Image-Processing

## For Ubuntu users

## For Lab setup We can go throuh the following [Link](https://dev.to/dhar01/setting-up-codeblocks-with-freeglut-in-linux-9if?fbclid=IwAR0if8ZgpiLdzuAWPREZomoyCGL9sjG-KTr4bJRuUuRExx3Bc6wNrGKds2w)

## Still Stuck?
### Go through the document I have written below:
 
 
 
```
sudo apt install g++ freeglut3 freeglut3-dev

sudo apt install libxmu-dev libxi-dev

```
Open Codeblocks, go to settings > Global Variables.

type freeglut, press ok and setup the rest like this:

![g1](https://user-images.githubusercontent.com/43321488/212568061-299e611a-ac50-4590-acb4-d5210e9da817.png)

Go to /usr/share/codeblocks/templates, create a file by following command:
```
nano freeglut.cbp

```
the file freeglut.cbp and put the following code there:

```
<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<CodeBlocks_project_file>
    <FileVersion major="1" minor="4" />
    <Project>
        <Option title="freeglut" />
        <Option pch_mode="0" />
        <Option compiler="gcc" />
        <Build>
            <Target title="default">
                <Option output="freeglut.exe" />
                <Option type="0" />
                <Option compiler="gcc" />
                <Option includeInTargetAll="1" />
            </Target>
        </Build>
        <Compiler>
            <Add directory="$(#freeglut.include)" />
        </Compiler>
        <Linker>
            <Add library="freeglut" />
            <Add library="glu32" />
            <Add library="opengl32" />
            <Add library="winmm" />
            <Add library="gdi32" />
            <Add library="user32" />
            <Add library="kernel32" />
            <Add directory="$(#freeglut.lib)" />
        </Linker>
        <Unit filename="main.cpp">
            <Option compilerVar="CPP" />
            <Option target="default" />
        </Unit>
    </Project>
</CodeBlocks_project_file>
```
Now go to the following directory: /usr/share/codeblocks/templates/wizard/
```
sudo mkdir freeglut

sudo chmod 777 /usr/share/codeblocks/templates/wizard/freeglut
```

You will find another directory named glut in wizard. Copy all the contents and paste it on the newly created freeglut directory.

Now type the following command on terminal:
```
/usr/share/codeblocks/templates/wizard:   sudo  cp -r glut freeglut
/usr/share/codeblocks/templates/wizard/freeglut/glut: sudo cp -r files logo.png wizard.png wizard.script ../
/usr/share/codeblocks/templates/wizard/freeglut:  sudo rm -rf glut
/usr/share/codeblocks/templates/wizard/freeglut:  sudo rm wizard.script
/usr/share/codeblocks/templates/wizard/freeglut:  sudo nano wizard.script

```

Now in wizard.script file paste the following code:

```
////////////////////////////////////////////////////////////////////////////////
//
// FreeGLUT project wizard
//
////////////////////////////////////////////////////////////////////////////////

// globals
FreeGlutPathDefault    <- _T("$(#freeglut)");
FreeGlutPathDefaultInc <- _T("$(#freeglut.include)");
FreeGlutPathDefaultLib <- _T("$(#freeglut.lib)");
FreeGlutPath <- _T("");

function BeginWizard()
{
    local intro_msg = _T("Welcome to the new FreeGLUT project wizard!\n\n" +
                         "This wizard will guide you to create a new project\n" +
                         "using the FreeGLUT OpenGL extensions.\n\n" +
                         "When you 're ready to proceed, please click \"Next\"...");

    local glutpath_descr = _T("Please select the location of FreeGLUT on your computer.\n" +
                              "This is the top-level folder where FreeGLUT was installed (unpacked).\n" +
                              "To help you, this folder must contain the subfolders\n" +
                              "\"include\" and \"lib\".");

    Wizard.AddInfoPage(_T("GlutIntro"), intro_msg);
    Wizard.AddProjectPathPage();
    if (PLATFORM == PLATFORM_MAC)
    {
        FreeGlutPathDefault="/System/Library/Frameworks/FreeGLUT.framework";
    }
    else
        Wizard.AddGenericSelectPathPage(_T("FreeGlutPath"), glutpath_descr, _T("Please select FreeGLUT's location:"), FreeGlutPathDefault);
    Wizard.AddCompilerPage(_T(""), _T("*"), true, true);
}

////////////////////////////////////////////////////////////////////////////////
// GLUT's path page
////////////////////////////////////////////////////////////////////////////////

function OnLeave_GlutPath(fwd)
{
    if (fwd)
    {
        local dir         = Wizard.GetTextControlValue(_T("txtFolder")); // txtFolder is the text control in GenericSelectPathPage
        local dir_nomacro = VerifyDirectory(dir);

        if (dir_nomacro.IsEmpty())
            return false;

        // verify include dependencies
        local dir_nomacro_inc = GetCompilerIncludeDir(dir, FreeGlutPathDefault, FreeGlutPathDefaultInc);
        if (dir_nomacro_inc.IsEmpty())
            return false;
        if (!VerifyFile(dir_nomacro_inc + wxFILE_SEP_PATH + _T("GL"), _T("freeglut.h"), _T("FreeGLUT's include"))) return false;

        // verify library dependencies
        local dir_nomacro_lib = GetCompilerLibDir(dir, FreeGlutPathDefault, FreeGlutPathDefaultLib);
        if (dir_nomacro_lib.IsEmpty())
            return false;

        if (PLATFORM == PLATFORM_MSW)
        {
            if (!VerifyLibFile(dir_nomacro_lib, _T("freeglut"), _T("FreeGLUT's"))) return false;
        }
        else
        {
            if (!VerifyLibFile(dir_nomacro_lib, _T("freeglut"), _T("FreeGLUT's"))) return false;
        }


        FreeGlutPath = dir; // Remember the original selection.

        local is_macro = _T("");

        // try to resolve the include directory as macro
        is_macro = GetCompilerIncludeMacro(dir, FreeGlutPathDefault, FreeGlutPathDefaultInc);
        if (is_macro.IsEmpty())
        {
            // not possible -> use the real inc path we had computed instead
            FreeGlutPathDefaultInc = dir_nomacro_inc;
        }

        // try to resolve the library directory as macro
        is_macro = GetCompilerLibMacro(dir, FreeGlutPathDefault, FreeGlutPathDefaultLib);
        if (is_macro.IsEmpty())
        {
            // not possible -> use the real lib path we had computed instead
            FreeGlutPathDefaultLib = dir_nomacro_lib;
        }
    }
    return true;
}

// return the files this project contains
function GetFilesDir()
{
    return _T("glut/files");
}

// setup the already created project
function SetupProject(project)
{
    // set project options
    if (PLATFORM != PLATFORM_MAC)
    {
        project.AddIncludeDir(FreeGlutPathDefaultInc);
        project.AddLibDir(FreeGlutPathDefaultLib);
    }

    // add link libraries
    if (PLATFORM == PLATFORM_MSW)
    {
        project.AddLinkLib(_T("freeglut"));
        project.AddLinkLib(_T("opengl32"));
        project.AddLinkLib(_T("glu32"));
        project.AddLinkLib(_T("winmm"));
        project.AddLinkLib(_T("gdi32"));
    }
    else if (PLATFORM == PLATFORM_MAC)
    {
        project.AddLinkerOption(_T("-framework GLUT"));
        project.AddLinkerOption(_T("-framework OpenGL"));

        project.AddLinkerOption(_T("-framework Cocoa")); // GLUT dependency
    }
    else
    {
        project.AddLinkLib(_T("glut"));
        project.AddLinkLib(_T("GL"));
        project.AddLinkLib(_T("GLU"));
        project.AddLinkLib(_T("Xxf86vm"));
    }

    // enable compiler warnings (project-wide)
    WarningsOn(project, Wizard.GetCompilerID());

    // Debug
    local target = project.GetBuildTarget(Wizard.GetDebugName());
    if (!IsNull(target))
    {
        target.SetTargetType(ttConsoleOnly); // ttConsoleOnly: console for debugging
        target.SetOutputFilename(Wizard.GetDebugOutputDir() + Wizard.GetProjectName() + DOT_EXT_EXECUTABLE);
        target.SetWorkingDir(FreeGlutPath + _T("/bin"));
        // enable generation of debugging symbols for target
        DebugSymbolsOn(target, Wizard.GetCompilerID());
    }

    // Release
    target = project.GetBuildTarget(Wizard.GetReleaseName());
    if (!IsNull(target))
    {
        target.SetTargetType(ttExecutable); // ttExecutable: no console
        target.SetOutputFilename(Wizard.GetReleaseOutputDir() + Wizard.GetProjectName() + DOT_EXT_EXECUTABLE);
        target.SetWorkingDir(FreeGlutPath + _T("/bin"));
        // enable optimizations for target
        OptimizationsOn(target, Wizard.GetCompilerID());
    }

    return true;
}

```
After pasting all the codes type cntrl+s and cntrl+x

Now on /usr/share/codeblocks/templates/wizard directory, there is a script named config.script
and add the following line at the end of the file:
```
RegisterWizard(wizProject,     _T("freeglut"),     _T("FreeGLUT project"),      _T("2D/3D Graphics"));

```
## Now go to following [Link](https://freeglut.sourceforge.net/index.php#download)

## Download this: freeglut 3.4.0 (sourceforge mirror)

* Copy the contents of the extracted folder and paste it on the /usr/share/codeblocks/templates/wizard/freeglut directory

* Open Codeblocks. Go to File > New > Projects and this dialog should be showing with Freeglut Project:

* Give a name of the project as you see fit.

* Then, specify the location where the Freeglut is: /usr/share/codeblocks/templates/wizard/freeglut

* Go to sources, there should be a main.cpp file for test running

* Build and Run!

## We must edit the main file everytime we need to run a new code:

Type the following command for an error:
```
sudo apt-get install libgl1-mesa-dev xorg-dev
```
Check weather you can see this pic after running main.cpp file:

![finalpic](https://user-images.githubusercontent.com/43321488/212569214-12fc52a4-277f-4e91-a136-4e3f306a4ade.png)







