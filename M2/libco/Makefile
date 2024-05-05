# 库名称变量
NAME := libco

# 生成的目标共享库文件
all: $(NAME)-64.so $(NAME)-32.so

# 通用编译标志
CFLAGS += -U_FORTIFY_SOURCE -fPIC

# 64位共享库目标
$(NAME)-64.so: co-64.o
	gcc -shared -m64 -o $@ $^ $(LDFLAGS)

# 32位共享库目标
$(NAME)-32.so: co-32.o
	gcc -shared -m32 -o $@ $^ $(LDFLAGS)

# 编译 64 位对象文件
co-64.o: co.c co.h
	gcc -m64 -c co.c -o $@ $(CFLAGS)

# 编译 32 位对象文件
co-32.o: co.c co.h
	gcc -m32 -c co.c -o $@ $(CFLAGS)

# 清理规则
clean:
	rm -f $(NAME)-64.so $(NAME)-32.so co-64.o co-32.o

# 包含子目录的 Makefile
.PHONY: tests
tests:
	$(MAKE) -C tests
