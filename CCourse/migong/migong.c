#include <stdio.h>
 
int main() {
    FILE *file; // 定义文件指针变量
    char buffer[1024]; // 存放每次读取到的字符串
    
    file = fopen("migong.in", "r"); // 打开要读取的文件（"filename"为文件名）
    
    if (file == NULL) {
        printf("无法打开文件\n");
        return -1;
    }
    
    while (!feof(file)) {
        fgets(buffer, sizeof(buffer), file); // 从文件中读取一行并保存在buffer中
        
        // 对读取到的内容进行处理或输出
        printf("%s", buffer);
    }
    
    fclose(file); // 关闭文件
    
    return 0;
}