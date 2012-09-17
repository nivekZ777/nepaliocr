======================================================================= 
=
    APPLICATION: Headliner_ver_1.03 Project Overview
======================================================================= 
=

AppWizard has created the Headliner_ver_1.03 Application. This file contains a summary of 
what we have done in each of the files that makes up our Headliner_ver_1.03 application.

Headliner_ver_1.03.vcproj
This is the main project file for VC++ projects generated using an Application Wizard. 
It contains information about the version of Visual C++ that generated the file, and 
information about the platforms, configurations, and project features selected with the 
Application Wizard.

Form1.cpp
This is the main application source file. It contains the code to display the form.

Form1.h
It contains the implementation of the form class and InitializeComponent() function.
It contains the header files. They are ThresholedValue.h, rgbConvert.h and Separate.h. 
The work done here is firstly to open an existing image file which is done by 
OpenImage(void) method. After the image is opened, then that image is binarized which 
is done by DoBinary() method. To do this first the threshold value of that image is
calculated. After that the text of that image is separated. It is done by DoSeparate() 
method. Here, if ImageLoaded and BinaryDone both are true then it calls separate() method. 
This method separates each character from the word. After that the final image (which 
is binarized and separated) is saved which is done by saveImageFile() method.

ThresholedValue.h
It contains the declaration of ThresholdedValue class. It contains the variables and 
methods (GetThresholed(), calculateValue(), ImHist()) useful for the calculation of 
the threshold value. 

ThresholdedValue.cpp 
It contains the code to calculate the threshold value and returns the threshold value. 

rgbConvert.h
It contains the declaration of the rgbConvert class. Here the image variables are
defined such as rgbImage, bainaryImage. The rgb (red, green and blue) color image 
is converted to binary (black and white) image. getGrayImage() method takes the rgb 
color image and convert it into binary image which is done by GetBinaryImage(). And 
returns the binary image. 

Separate.h
It contains the declaration of the separate class. The constructor is defined here
named as Separate() which contains three parameters. It contains all the necessary 
methods (LineSeparate(), WordSeparate(), CheckMattra() and many more) which help to
separate the particular text from the image. Here the variables such as xSize and ySize 
are declared. It includes the header file Line.h.

Separate.cpp
It contains the code to separate the text from the input image. The variables xSize 
and ySize are defined to get the width and height of the image. Separation of words from 
the image takes many steps to be completed. First, it calls the method LineSeparate() 
which helps to extract the word present in that line. Then, WordSeparate() method is 
called which contains the code to separate each word from the line. After word separation
is done, next step is to separate the characters from the word. Directly separating the
characters from the word is not possible because of the presence of the Mattra. So at first
we have to remove the Mattra from the word. This is done by CheckMattra() method. The 
image obtained after the removal of the Mattra is saved by Save() method. CharSeparate() 
method helps to separate the character from the word after the mattra has been removed.

Line.h
It contains the declaration of the line class. It includes the header file Word.h. It 
contains the variables and methods. It returns the total word from the line.

Word.h
It contains the declaration of the word class. It includes the header file Unit.h. It 
contains the variables and methods. It identifies the number of word in the line and returns
the starting and ending column number of line.And also returns the total unit.

Unit.h
It contains the declaration of the unit class. It contains the variables and methods. It 
separates the characters from the word and returns the starting and ending column number 
of Unit.

AssemblyInfo.cpp
It contains custom attributes for modifying assembly metadata.




/////////////////////////////////////////////////////////////////////// 
//////
Other standard files:

StdAfx.h, StdAfx.cpp
These files are used to build a precompiled header (PCH) file named Win32.pch and 
a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////// 
//////
