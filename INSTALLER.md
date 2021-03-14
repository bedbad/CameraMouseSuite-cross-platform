# Steps for creating an installable package with a binary

### Step 1

After installing InstallShield create a new project

### Step 2

Select Basic MSI from the menu and add a project name and check the last box to create projects in subfolders.

### Step 3

A general info page will appear.

### Step 4

Select File and Folders and rename the company/product name and drag the binary under the product name section. In the example, company name is HW, product name is HW too. After adding files a dialogue box will appear for a feature name. Add a feature name.

### Step 5

Then go for the Shortcut section and create a shortcut. Shortcut should be an exe. Here we find the HW.exe file in the wizard after clicking Desktop and add it.

### Step 6

Set Icon to the Shortcut by clicking on it a control box will appear on right. Set an icon to the icon section.

## Step 7

Now press build. After build, clicking Run should install the app to the machine.

### Step 8 (for setup exe)

Press release wizard to generate setup.exe. The setup file will be in <INSTALL_SHIELD_PROJECT_PATH>/<YOUR_PROJECT>/<Product Configuration>/<Release>/<DiskImages>/<DISK>.


# removing terminal from popping up after installed application is run

Application may pop up a terminal when it is clicked and run. So I used a technique following this old [question and answer](https://stackoverflow.com/questions/2139637/hide-console-of-windows-application) on stackoverflow where the the entry point of the program is changed to `mainCRTStartup` for **windows subsystem**. So I have put a `#pragma` directive in `main.cpp`.
```
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
```
For further reading on the matter one can follow [this discussion](https://stackoverflow.com/questions/22934206/what-is-the-difference-between-main-and-maincrtstartup) on stackoverflow.

