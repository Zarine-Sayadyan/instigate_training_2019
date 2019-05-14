
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
$(call check_variable,bin_dir)
$(call check_variable,lib_dir)
$(call check_variable,lib32_dir)
$(call check_variable,lib64_dir)
$(call check_variable,obj_dir)
$(call check_variable,obj32_dir)
$(call check_variable,obj64_dir)
$(call check_variable,inc_dir)
$(call check_variable,doc_dir)
$(call check_variable,pkg_dir)
$(call check_variable,test_result)
$(call check_variable,test_result_dir)
$(call check_variable,coverage_result)
$(call check_variable,coverage_result_dir)


tmp_obj_dirs:=$(obj_dir) $(obj32_dir) $(obj64_dir)
tmp_lib_dirs:=$(lib_dir) $(lib32_dir) $(lib64_dir)
tmp_all_gcda:=$(foreach t,$(tmp_obj_dirs),$(wildcard $t/*.gcda))
tmp_all:=$(bin_dir) $(tmp_lib_dirs) $(tmp_obj_dirs) $(inc_dir)

.PHONY: clean
clean: clean_docs clean_test clean_conf clean_coverage
	@$(echo) -n "Cleaning up ... "
	@rm -rf $(tmp_all)
	@$(echo) "done"

.PHONY: clean_test
clean_test: clean_coverage
	@$(echo) -n "Cleaning up tests results ... "
	@rm -rf $(test_result) $(test_result_dir) 
	@$(echo) "done"

.PHONY: clean_coverage
clean_coverage:
	@$(echo) -n "Cleaning up tests coverage ... "
	@rm -rf $(coverage_result) $(coverage_result_dir) $(tmp_all_gcda)
	@$(echo) "done"

.PHONY: clean_docs
clean_docs:
	@$(echo) -n "Cleaning Doxygen generated files ... "
	@rm -rf $(doc_dir)
	@$(echo) "done"
	
.PHONY: clean_user_docs
clean_user_docs:
	@$(echo) -n "Cleaning user documents generated by Doxygen ... "
	@rm -rf $(usr_doc_dir)
	@$(echo) "done"

.PHONY: clean_developer_docs
clean_developer_docs:
	@$(echo) -n "Cleaning developer documents generated by Doxygen ... "
	@rm -rf $(dev_doc_dir)
	@$(echo) "done"

.PHONY: clean_conf
clean_conf:
	@$(echo) -n "Cleaning pkg configuration files ... "
	@rm -rf $(pkg_dir)
	@$(echo) "done"

