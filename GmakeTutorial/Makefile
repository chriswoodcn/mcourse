.DEFAULT_GOAL = main

# test_@ $@表示目标名称
test_@: 
	@echo $@ 

# test_function_dir dir方法 expect：src/ ./
test_function_dir__f1 = src/hello.cpp main.cpp
test_function_dir__f2 = $(dir $(test_function_dir__f1))
test_function_dir:
	@echo $(test_function_dir__f2)

# test_function_join join方法 expect：hello.cpp main.hpp test
test_function_join__f1 = hello main test
test_function_join__f2 = .cpp .hpp
test_function_join__f3 = $(join $(test_function_join__f1),$(test_function_join__f2))
test_function_join:
	@echo $(test_function_join__f3)  
# hello.cpp main.hpp test

# test_function_realpath realpath方法 abspath方法
test_function_realpath__f1 = $(wildcard *.md)
test_function_realpath__f2 = $(wildcard *.h)
test_function_realpath:
	@echo realpath test_function_realpath__f1 = $(realpath $(test_function_realpath__f1))
	@echo realpath test_function_realpath__f2 = $(realpath $(test_function_realpath__f2))
	@echo abspath test_function_realpath__f1 = $(abspath $(test_function_realpath__f1))
	@echo abspath test_function_realpath__f2 = $(abspath $(test_function_realpath__f2))

# test_function_or or方法
test_function_or__f1 =
test_function_or__f2 = 
test_function_or__f3 = hello.cpp
test_function_or__f4 = $(or $(test_function_or__f1)\
,$(test_function_or__f2)\
,$(test_function_or__f3))
test_function_or:
	@echo $(test_function_or__f4)

# test_function_foreach foreach方法
test_function_foreach__list = 1 2 3 4 5
test_function_foreach__result = $(foreach item,$(test_function_foreach__list),$(addprefix cpp,$(addsuffix .cpp,$(item))))
test_function_foreach:
	@echo $(test_function_foreach__result)


# test_function_eval
define test_function_eval__target =
test_function_eval:
    @echo Target Eval Test
endef
aaa = aaa
define test_function_eval__target2 =
aaa += bbb
endef
$(eval $(test_function_eval__target2))
test_function_eval__p1 = $(shell echo This is from shell function)
test_function_eval:
	@echo $(test_function_eval__p1)
	@echo $(aaa)


# 官网示例
# PROGRAMS    = server client
# server_OBJS = server.o server_priv.o server_access.o
# server_LIBS = priv protocol
# client_OBJS = client.o client_api.o client_mem.o
# client_LIBS = protocol
# # Everything after this is generic
# .PHONY: all
# all: $(PROGRAMS)
# define PROGRAM_template =
#  $(1): $$($(1)_OBJS) $$($(1)_LIBS:%=-l%)
#  ALL_OBJS   += $$($(1)_OBJS)
# endef
# $(foreach prog,$(PROGRAMS),$(eval $(call PROGRAM_template,$(prog))))
# $(PROGRAMS):
# 	$(LINK.o) $^ $(LDLIBS) -o $@
# clean:
# 	rm -f $(ALL_OBJS) $(PROGRAMS)

reverse = $(let first rest,$(1),$(if $(rest),$(call reverse,$(rest)) )$(first))
test_function_let:
	@echo $(call reverse,d c b a)