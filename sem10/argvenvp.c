asm (
	".text\n"
	".global _start\n"
	"_start:\n"
	"pop %eax\n" // argc
	"leal (%esp, %eax, 4), %ecx\n" // argv[argc]
	"add $4, %ecx\n" // argv[argc+1] = envp
	"mov %esp, %ebx\n" // argv

	"push %eax\n"
	"push %ecx\n" // envp
	"push %ebx\n" // argv
	"push %eax\n" // argc
	"call main\n" // return code;

	"push %eax\n"
	"call exit1\n"
);

void exit1(int code) {
	asm volatile (
		"mov $1, %%eax\n"
		"mov %0, %%ebx\n"
		"int $0x80\n"
		: : "g"(code) : "%eax", "%ebx"
	);
	//while(1);
}

int mystrlen(const char * const str) {
	const char * it = str;
	while(*it) it++;
	return it - str;
}

int write_str(const char * const str) {
	int len = mystrlen(str);
	int res;
	asm volatile (
		"mov $4, %%eax\n"
		"mov $1, %%ebx\n"
		"mov %1, %%ecx\n"
		"mov %2, %%edx\n"
		"int $0x80\n"
		"mov %%eax, %0"
		: "=g"(res) : "g"(str), "g"(len)
//		: "=a"(res) :"a"(4), "b"(1), "c"(str), "d"(len)
		: "%eax", "%ebx", "%ecx", "%edx", "memory"
	);
	return res;
}


int main(int argc, char *argv[]) {
	for (int i = 0; i < argc; i++) {
		write_str(argv[i]);
		write_str("\n");
	}
	int i = 0;
	while (envp[i]) {
		write_str(envp[i]);
		write_str("\n");
		i++;
	}
	return 2;
}
