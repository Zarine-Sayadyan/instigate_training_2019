
#
# Copyright © 2005-2010 Instigate CJSC, Armenia
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free
# Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#

# The name of the project
# 
project_name := "messenger"

# The version of the project
#
project_version := 1.0.0

# The absolute path to the directory where the current project is located 
#
project_root := $(shell pwd)

# Install path prefix
#
prefix := $(HOME)

# The projects should be listed here
#
# Example:
# projects := src/project1 src/project2
#
projects :=  \
	src/client_tcp \
	src/client_udp\
	src/ipc\
	src/server_tcp\
	src/server_udp\
	src/threads\
	src/threads_test\
	src/command\
	src/command_test\
	src/messenger_server\
	src/messenger\

# Prerequisite tools
preconditions := gcc doxygen ar ln pkg-config lcov

# Prerequisite libraries
library_preconditions := \

# Tests which are run after each modification. 
#
continuous_tests := \

# Includes the tests to check the basic principles of the
# application.  Should be called after each modification to
# check the regression of application.
#
regression_tests := 

# Tests set which are run after working day
#
nightly_tests := 

# Tests set which are run after working week
#
weekly_tests := 

test_type := continuous_tests

# List of the projects to collect coverage data
#
coverage_projects := $(projects)

# Defined the path where the package will be installed
#
install_path := $(prefix)/$(project_name)/$(project_version)

# Directories which should be installed/packaged in release mode
#
export opt_package := mkf ReleaseNotes.pdf

# Directories which should be installed/packaged in debug mode
export dbg_package := $(opt_package)

# Run time search path, used by patchELF tool while installing the project.
export RPATHS :=

# The path to the mkf should be assigned to this variable
#
mkf_path := $(project_root)/mkf

include $(mkf_path)/main.mk
include $(mkf_path)/doc.mk

# Dependencies between projects
#
src/client_tcp: src/ipc
src/client_udp: src/ipc
src/server_tcp: src/ipc src/threads
src/server_udp: src/ipc src/threads
src/command_test: src/command
src/messenger: src/threads src/ipc src/command
src/messenger_server: src/threads src/ipc src/command
src/threads_test: src/threads
