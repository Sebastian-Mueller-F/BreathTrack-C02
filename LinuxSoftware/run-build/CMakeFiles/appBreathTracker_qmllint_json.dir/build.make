# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ccs/01_Repos/BreathTrack-C02/BreathTracker

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ccs/01_Repos/BreathTrack-C02/build-BreathTracker-Desktop_Qt_6_4_1-Release

# Utility rule file for appBreathTracker_qmllint_json.

# Include any custom commands dependencies for this target.
include CMakeFiles/appBreathTracker_qmllint_json.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/appBreathTracker_qmllint_json.dir/progress.make

CMakeFiles/appBreathTracker_qmllint_json: /opt/VM/Qt-6.4.1/bin/qmllint
CMakeFiles/appBreathTracker_qmllint_json: /home/ccs/01_Repos/BreathTrack-C02/BreathTracker/qml/main.qml
CMakeFiles/appBreathTracker_qmllint_json: /home/ccs/01_Repos/BreathTrack-C02/BreathTracker/qml/DataTrends.qml
CMakeFiles/appBreathTracker_qmllint_json: /home/ccs/01_Repos/BreathTrack-C02/BreathTracker/qml/LiveData.qml
CMakeFiles/appBreathTracker_qmllint_json: /home/ccs/01_Repos/BreathTrack-C02/BreathTracker/qml/LiveDataBackground.qml
CMakeFiles/appBreathTracker_qmllint_json: /home/ccs/01_Repos/BreathTrack-C02/BreathTracker/qml/SettingsDrawer.qml
CMakeFiles/appBreathTracker_qmllint_json: /home/ccs/01_Repos/BreathTrack-C02/BreathTracker/qml/SettingsSection.qml
CMakeFiles/appBreathTracker_qmllint_json: /home/ccs/01_Repos/BreathTrack-C02/BreathTracker/qml/ArcRight.qml
CMakeFiles/appBreathTracker_qmllint_json: /home/ccs/01_Repos/BreathTrack-C02/BreathTracker/qml/ArcLeft.qml
CMakeFiles/appBreathTracker_qmllint_json: /home/ccs/01_Repos/BreathTrack-C02/BreathTracker/qml/ArcItem.qml
CMakeFiles/appBreathTracker_qmllint_json: /home/ccs/01_Repos/BreathTrack-C02/BreathTracker/qml/CircleIndicator.qml
CMakeFiles/appBreathTracker_qmllint_json: /home/ccs/01_Repos/BreathTrack-C02/BreathTracker/qml/CustomLabel.qml
	cd /home/ccs/01_Repos/BreathTrack-C02/BreathTracker && /opt/VM/Qt-6.4.1/bin/qmllint --bare -I /home/ccs/01_Repos/BreathTrack-C02/build-BreathTracker-Desktop_Qt_6_4_1-Release -I /opt/VM/Qt-6.4.1/./qml --resource /home/ccs/01_Repos/BreathTrack-C02/build-BreathTracker-Desktop_Qt_6_4_1-Release/.rcc/qmake_BreathTracker.qrc --resource /home/ccs/01_Repos/BreathTrack-C02/build-BreathTracker-Desktop_Qt_6_4_1-Release/.rcc/appBreathTracker_raw_qml_0.qrc /home/ccs/01_Repos/BreathTrack-C02/BreathTracker/qml/main.qml /home/ccs/01_Repos/BreathTrack-C02/BreathTracker/qml/DataTrends.qml /home/ccs/01_Repos/BreathTrack-C02/BreathTracker/qml/LiveData.qml /home/ccs/01_Repos/BreathTrack-C02/BreathTracker/qml/LiveDataBackground.qml /home/ccs/01_Repos/BreathTrack-C02/BreathTracker/qml/SettingsDrawer.qml /home/ccs/01_Repos/BreathTrack-C02/BreathTracker/qml/SettingsSection.qml /home/ccs/01_Repos/BreathTrack-C02/BreathTracker/qml/ArcRight.qml /home/ccs/01_Repos/BreathTrack-C02/BreathTracker/qml/ArcLeft.qml /home/ccs/01_Repos/BreathTrack-C02/BreathTracker/qml/ArcItem.qml /home/ccs/01_Repos/BreathTrack-C02/BreathTracker/qml/CircleIndicator.qml /home/ccs/01_Repos/BreathTrack-C02/BreathTracker/qml/CustomLabel.qml --json /home/ccs/01_Repos/BreathTrack-C02/build-BreathTracker-Desktop_Qt_6_4_1-Release/appBreathTracker_qmllint.json

appBreathTracker_qmllint_json: CMakeFiles/appBreathTracker_qmllint_json
appBreathTracker_qmllint_json: CMakeFiles/appBreathTracker_qmllint_json.dir/build.make
.PHONY : appBreathTracker_qmllint_json

# Rule to build all files generated by this target.
CMakeFiles/appBreathTracker_qmllint_json.dir/build: appBreathTracker_qmllint_json
.PHONY : CMakeFiles/appBreathTracker_qmllint_json.dir/build

CMakeFiles/appBreathTracker_qmllint_json.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/appBreathTracker_qmllint_json.dir/cmake_clean.cmake
.PHONY : CMakeFiles/appBreathTracker_qmllint_json.dir/clean

CMakeFiles/appBreathTracker_qmllint_json.dir/depend:
	cd /home/ccs/01_Repos/BreathTrack-C02/build-BreathTracker-Desktop_Qt_6_4_1-Release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ccs/01_Repos/BreathTrack-C02/BreathTracker /home/ccs/01_Repos/BreathTrack-C02/BreathTracker /home/ccs/01_Repos/BreathTrack-C02/build-BreathTracker-Desktop_Qt_6_4_1-Release /home/ccs/01_Repos/BreathTrack-C02/build-BreathTracker-Desktop_Qt_6_4_1-Release /home/ccs/01_Repos/BreathTrack-C02/build-BreathTracker-Desktop_Qt_6_4_1-Release/CMakeFiles/appBreathTracker_qmllint_json.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/appBreathTracker_qmllint_json.dir/depend

