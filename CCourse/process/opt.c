#include <stdio.h>
#include <unistd.h>

// #include <unistd.h>
// extern char *optarg;
// extern int optind, opterr, optopt;
// #include <getopt.h>
// int getopt(int argc, char * const argv[],const char *optstring);
// int getopt_long(int argc, char * const argv[], const char *optstring, const
// struct option *longopts, int *longindex); int getopt_long_only(int argc, char
// * const argv[], const char *optstring, const struct option *longopts, int
// *longindex);
//
// 参数说明
// argc和argv和main函数的两个参数一致。
// optstring: 表示短选项字符串。
// longopts：表示长选项结构体。结构如下：
// struct option {
//   const char *name;  name:表示选项的名称,比如daemon,dir,out等。
//   int has_arg; has_arg:表示选项后面是否携带参数。三个值，
//                no_argument(或者是0)后面不跟参数值 
//                required_argument(或者是1)参数输入格式为：--参数 值 或者 --参数=值
//                optional_argument(或者是2)参数输入格式只能为：--参数=值
//   int *flag; flag:这个参数有两个意思，空或者非空。
//              如果参数为空NULL，那么当选中某个长选项的时候，getopt_long将返回val值。eg，可执行程序 --help，getopt_long的返回值为h
//              如果参数不为空，那么当选中某个长选项的时候，getopt_long将返回0，并且将flag指针参数指向val值。
//              	eg: 可执行程序 --http-proxy=127.0.0.1:80 那么getopt_long返回值为0，并且lopt值为1。
//   int val; val：表示指定函数找到该选项时的返回值，或者当flag非空时指定flag指向的数据的值val
// };
// eg : static struct option longOpts[] = {
//          {"daemon", no_argument, NULL, 'D'},
//          {"dir", required_argument, NULL, 'd'},
//          {"out", required_argument, NULL, 'o'},
//          {"log", required_argument, NULL, 'l'},
//          {"split", required_argument, NULL, 's'},
//          {"http-proxy", required_argument, &lopt, 1},
//          {"http-user", required_argument, &lopt, 2},
//          {"http-passwd", required_argument, &lopt, 3},
//          {"http-proxy-user", required_argument, &lopt, 4},
//          {"http-proxy-passwd", required_argument, &lopt, 5},
//          {"http-auth-scheme", required_argument, &lopt, 6},
//          {"version", no_argument, NULL, 'v'},
//          {"help", no_argument, NULL, 'h'},
//          {0, 0, 0, 0}};
// longindex：longindex非空，它指向的变量将记录当前找到参数符合longopts里的第几个元素的描述，即是longopts的下标值
// 全局变量
// （1）optarg：表示当前选项对应的参数值。
// （2）optind：表示的是下一个将被处理到的参数在argv中的下标值。
// （3）opterr：如果opterr = 0，在getopt、getopt_long、getopt_long_only遇到错误将不会输出错误信息到标准输出流。opterr在非0时，向屏幕输出错误。
// （4）optopt：表示没有被未标识的选项
//返回值
// （1）如果短选项找到，那么将返回短选项对应的字符。
// （2）如果长选项找到，如果flag为NULL，返回val。如果flag不为空，返回0
// （3）如果遇到一个选项没有在短字符、长字符里面。或者在长字符里面存在二义性的，返回？
// （4）如果解析完所有字符没有找到（一般是输入命令参数格式错误，eg： 连斜杠都没有加的选项），返回-1
// （5）如果选项需要参数，忘了添加参数。返回值取决于optstring，如果其第一个字符是：，则返回：，否则返回？。

int main(int argc, char **argv) {
  int opt;
  // opterr = 0; //(1)
  while ((opt = getopt(argc, argv, "abcd:e::-")) != -1) {
    printf("current char: (opt)%c-(optopt)%c, optind: %d\n", opt, optopt,
           optind);
    switch (opt) {
    case 'a':
      break;
    case 'b':
      break;
    case 'c':
      break;
    case 'd':
      printf("arguments: %s\n", optarg);
      break;
    case 'e':
      printf("arguments: %s\n", optarg ? optarg : "none");
      break;
    case ':':
    case '?':
    default:
      printf("invalid parameter\n");
      break;
    }
  }
  printf("===extra arguments===\n");
  while (optind < argc) {
    printf("%s\n", argv[optind++]);
  }
  printf("=====================\n");
  return 0;
}