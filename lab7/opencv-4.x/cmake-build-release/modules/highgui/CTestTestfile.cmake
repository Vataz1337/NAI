# CMake generated Testfile for 
# Source directory: C:/Users/patry/OneDrive/Pulpit/Studia/Semestr5/NAI/lab7/opencv-4.x/modules/highgui
# Build directory: C:/Users/patry/OneDrive/Pulpit/Studia/Semestr5/NAI/lab7/opencv-4.x/cmake-build-release/modules/highgui
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_highgui "C:/Users/patry/OneDrive/Pulpit/Studia/Semestr5/NAI/lab7/opencv-4.x/cmake-build-release/bin/opencv_test_highgui.exe" "--gtest_output=xml:opencv_test_highgui.xml")
set_tests_properties(opencv_test_highgui PROPERTIES  LABELS "Main;opencv_highgui;Accuracy" WORKING_DIRECTORY "C:/Users/patry/OneDrive/Pulpit/Studia/Semestr5/NAI/lab7/opencv-4.x/cmake-build-release/test-reports/accuracy" _BACKTRACE_TRIPLES "C:/Users/patry/OneDrive/Pulpit/Studia/Semestr5/NAI/lab7/opencv-4.x/cmake/OpenCVUtils.cmake;1752;add_test;C:/Users/patry/OneDrive/Pulpit/Studia/Semestr5/NAI/lab7/opencv-4.x/cmake/OpenCVModule.cmake;1352;ocv_add_test_from_target;C:/Users/patry/OneDrive/Pulpit/Studia/Semestr5/NAI/lab7/opencv-4.x/modules/highgui/CMakeLists.txt;318;ocv_add_accuracy_tests;C:/Users/patry/OneDrive/Pulpit/Studia/Semestr5/NAI/lab7/opencv-4.x/modules/highgui/CMakeLists.txt;0;")
