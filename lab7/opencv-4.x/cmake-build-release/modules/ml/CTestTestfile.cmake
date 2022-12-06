# CMake generated Testfile for 
# Source directory: C:/Users/patry/OneDrive/Pulpit/Studia/Semestr5/NAI/lab7/opencv-4.x/modules/ml
# Build directory: C:/Users/patry/OneDrive/Pulpit/Studia/Semestr5/NAI/lab7/opencv-4.x/cmake-build-release/modules/ml
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_ml "C:/Users/patry/OneDrive/Pulpit/Studia/Semestr5/NAI/lab7/opencv-4.x/cmake-build-release/bin/opencv_test_ml.exe" "--gtest_output=xml:opencv_test_ml.xml")
set_tests_properties(opencv_test_ml PROPERTIES  LABELS "Main;opencv_ml;Accuracy" WORKING_DIRECTORY "C:/Users/patry/OneDrive/Pulpit/Studia/Semestr5/NAI/lab7/opencv-4.x/cmake-build-release/test-reports/accuracy" _BACKTRACE_TRIPLES "C:/Users/patry/OneDrive/Pulpit/Studia/Semestr5/NAI/lab7/opencv-4.x/cmake/OpenCVUtils.cmake;1752;add_test;C:/Users/patry/OneDrive/Pulpit/Studia/Semestr5/NAI/lab7/opencv-4.x/cmake/OpenCVModule.cmake;1352;ocv_add_test_from_target;C:/Users/patry/OneDrive/Pulpit/Studia/Semestr5/NAI/lab7/opencv-4.x/cmake/OpenCVModule.cmake;1110;ocv_add_accuracy_tests;C:/Users/patry/OneDrive/Pulpit/Studia/Semestr5/NAI/lab7/opencv-4.x/modules/ml/CMakeLists.txt;2;ocv_define_module;C:/Users/patry/OneDrive/Pulpit/Studia/Semestr5/NAI/lab7/opencv-4.x/modules/ml/CMakeLists.txt;0;")
