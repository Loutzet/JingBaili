#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

int classify_files(const char *directory);
int main() {
    const char *directory = "./"; // 指定要分类的目录
    if (classify_files(directory) == 0) {
        printf("文件分类完成。\n");
    } else {
        printf("文件分类过程中发生错误。\n");
    }
    return 0;
}
int classify_files(const char *directory) {
    DIR *dir;
    struct dirent *ent;
    char source_path[1024];
    char dest_path[1024];
    char *file_extension;
    // 打开目录
    dir = opendir(directory);
    if (dir == NULL) {
        perror("无法打开目录");
        return 1;
    }
    // 读取目录中的每个条目
    while ((ent = readdir(dir)) != NULL) {
        // 跳过目录自身和父目录的引用
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
            continue;
        }
        // 构建完整的源文件路径
        snprintf(source_path, sizeof(source_path), "%s%s", directory, ent->d_name);
        // 获取文件扩展名
        file_extension = strrchr(ent->d_name, '.');
        if (file_extension != NULL) {
            // 构建目标目录路径
            snprintf(dest_path, sizeof(dest_path), "%s%s/", directory, file_extension + 1);
            // 创建目标目录（如果它不存在）
            mkdir(dest_path, 0755);
            // 添加文件名到目标路径
            strcat(dest_path, ent->d_name);
            // 移动文件
            if (rename(source_path, dest_path) != 0) {
                perror("无法移动文件");
                closedir(dir);
                return 1;
            }
        }
    }

    // 关闭目录
    closedir(dir);
    return 0;
}
