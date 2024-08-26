###############################################################################
# shared library file compile makefile 文件模板
# 此makefile文件模板用于将一个工程编译成Linux下的共享库文件
###############################################################################

###############################################################################
# Section 1. 工程配置段
###############################################################################

#===============================================================================
# PRG_NAME : 程序名称，此处的程序名称是工程编译完成后的可执行的名称的名字
#===============================================================================
PRG_NAME     := $(PRJ_NAME)

INCLUDE_DIR   := .
OUT_DIR       := .

# 定义用于可移植的文件操作命令串，无须修改
PARSER  := RimiParser -f
MAKE    := make
RM      := rm -f
MKDIR   := mkdir -p
LN      := ln -s -f
CP      := cp -f
ECHO    := echo

ITF_SRCS := $(shell find $(INCLUDE_DIR) -name "*.idl")
###############################################################################
# Section 2. 编译
###############################################################################
$(OUT_DIR)/%Servant.inl:$(INCLUDE_DIR)/%Itf.idl Makefile
	@$(ECHO) 'Building file    : $<'
	@$(ECHO) $(PARSER) $< -s $@
	@$(PARSER) $< -s $@ -p aa
	@$(ECHO) 'Finished building: $<'
	@$(RM) aa
	@$(ECHO) ' '

$(OUT_DIR)/%Proxier.inl: $(INCLUDE_DIR)/%Itf.idl Makefile
	@$(ECHO) 'Building file    : $<'
	@$(ECHO) $(PARSER) $< -p $@
	@$(PARSER) $< -s aa -p $@
	@$(ECHO) 'Finished building: $<'
	@$(RM) aa
	@$(ECHO) ' '

# 定义模块编译时的目标文件列表
SERVER_OBJS := $(ITF_SRCS:$(INCLUDE_DIR)/%Itf.idl=$(OUT_DIR)/%Servant.inl)
CLIENT_OBJS := $(ITF_SRCS:$(INCLUDE_DIR)/%Itf.idl=$(OUT_DIR)/%Proxier.inl)
OBJS := $(ITF_SRCS:$(INCLUDE_DIR)/%Itf.idl=%Itf)

# 定义编译tagert
all: $(SERVER_OBJS) $(CLIENT_OBJS)

%Itf : $(OUT_DIR)/%Servant.inl $(OUT_DIR)/%Proxier.inl
	
clean:
	@$(RM) $(SERVER_OBJS) $(CLIENT_OBJS)
	@$(ECHO) 'Clean Target     : $(SERVER_OBJS) $(CLIENT_OBJS)'

.PHONY: all clean
