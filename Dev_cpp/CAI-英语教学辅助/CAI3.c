// ======================================== 总设计流程 ========================================
//~头文件 + 宏定义
//~数据结构体定义
//~全局变量声明
//~辅助函数（trim, strcmpi, check）
//~initVocab()			- 初始化90条词汇
//~showMenu()			- 主菜单
//~showLevelMenu()		- 难度选择菜单
//~getLevelName()		- 等级名称
//~getRandomQuestion()	- 随机抽题
//~checkPromotion()		- 晋级检查
//~checkDemotion()		- 降级检查
//~showStats()			- 显示统计
//~runQuiz()				- 单题答题循环
//practiceMode()		- 练习模式主函数
//main()				- 主函数


// ======================================== 头文件声明 ========================================
#define _CRT_SECURE_NO_WARNINGS
//解决一些函数的报错警告(scanf等)
#include <stdio.h>				 //标准输入输出
#include <stdlib.h>              // 标准库（malloc, rand, srand等）
#include <string.h>              // 字符串处理
#include <ctype.h>               // 字符判断（tolower等）
#include <time.h>                // 时间（time, srand）
#include <windows.h>			 //	windows API(system等)
/* <ctype.h>
比较 "Apple" 和 "apple" 被视为相同
tolower('A') == tolower('a')  // true
*/

/* <time.h>
srand(time(NULL));  // 用当前时间作为随机起点
rand();             // 之后调用 rand() 生成随机数
*/

/* <windows.h>
system("chcp 65001 > nul");  // 将控制台设为UTF-8编码，隐藏输出
*/


// ======================================== 宏定义声明 ========================================
#define MAX_VOCAB 500				// 词库最大容量
#define MAX_ENGLISH 100				// 英文最大长度
#define MAX_CHINESE 100				// 中文最大长度
#define UPGRADE_RATE 90				// 晋级正确率（%）
#define DOWNGRADE_RATE 60			// 降级正确率（%）
#define MIN_QUESTIONS 10			// 晋级/降级最少答题数
#define MAX_ROUND 10				// 每次练习题数


// ======================================== 结构体定义 ========================================
typedef struct {
    char english[MAX_ENGLISH];		//英文内容
    char chinese[MAX_CHINESE];		//中文内容
    int level;						//难度等级
    int correct;					//正确次数
    int wrong;						//错误次数
}Vocabulary;						//词汇信息

typedef struct {
    int CurrentLevel;				//当前等级
    int TotalScore;					//总得分
    int LevelScore;					//本级总得分
    int LevelTotal;					//本题答题总数
} UserProgress;						//用户进度


// ======================================== 全局变量 ========================================
Vocabulary vocab[MAX_VOCAB];		//词库数组
int count = 0;						//实际词汇数量
UserProgress user = { 1, 0, 0, 0 };	//用户进度

// trim 去除字符串首尾空格
void trim(char* str) {
    char* start = str;										//start指向字符串第一个字符
    char* end = str + strlen(str) - 1;						//end指向字符串最后一个字符
    while (*start == ' ') { start++; }						//排除字符串前的空格
    while ((*end > *start) && (*end == ' ')) { end--; }		//排除字符串后的空格
    int len = end - start + 1;								//重新计算字符串的长度
    memmove(str, start, len);								//移动并截断字符串
    str[len] = '\0';										//添加字符串结束符
}

// strcm 忽略大小写的字符串比较
int strcm(const char* s1, const char* s2) {
    while (*s1 || *s2) {
        unsigned char c1 = (unsigned char)*s1;
        unsigned char c2 = (unsigned char)*s2;
        if (c1 >= 'A' && c1 <= 'Z') c1 += 32;  // 转小写 (ASCII)
        if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
        if (c1 != c2) { return 0; }
        s1++;
        s2++;
    }
    return 1;
}

//检查答案
int CheckAnswer(const char* answer, const char* correct) {
    char a[MAX_CHINESE], c[MAX_CHINESE];					//两个字符数组
    strcpy(a, answer);
    strcpy(c, correct);
    trim(a);
    trim(c);
    return strcm(a, c);
}


// ======================================== 词库初始 ========================================
void InitVocab() {
    count = 0;

    // ---- level 1: 常用单词 ----
   
    strcpy(vocab[count].english, "apple");
    strcpy(vocab[count].chinese, "苹果");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "banana");
    strcpy(vocab[count].chinese, "香蕉");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "cat");
    strcpy(vocab[count].chinese, "猫");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "dog");
    strcpy(vocab[count].chinese, "狗");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "egg");
    strcpy(vocab[count].chinese, "鸡蛋");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "fish");
    strcpy(vocab[count].chinese, "鱼");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "grape");
    strcpy(vocab[count].chinese, "葡萄");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "house");
    strcpy(vocab[count].chinese, "房子");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "ice");
    strcpy(vocab[count].chinese, "冰");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "juice");
    strcpy(vocab[count].chinese, "果汁");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "kite");
    strcpy(vocab[count].chinese, "风筝");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "lamp");
    strcpy(vocab[count].chinese, "灯");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "moon");
    strcpy(vocab[count].chinese, "月亮");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "nest");
    strcpy(vocab[count].chinese, "鸟巢");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "orange");
    strcpy(vocab[count].chinese, "橙子");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "pen");
    strcpy(vocab[count].chinese, "钢笔");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "queen");
    strcpy(vocab[count].chinese, "女王");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "rain");
    strcpy(vocab[count].chinese, "雨");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "sun");
    strcpy(vocab[count].chinese, "太阳");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "tree");
    strcpy(vocab[count].chinese, "树");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "umbrella");
    strcpy(vocab[count].chinese, "雨伞");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "violin");
    strcpy(vocab[count].chinese, "小提琴");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "water");
    strcpy(vocab[count].chinese, "水");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "xylophone");
    strcpy(vocab[count].chinese, "木琴");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "yacht");
    strcpy(vocab[count].chinese, "游艇");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "zebra");
    strcpy(vocab[count].chinese, "斑马");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "book");
    strcpy(vocab[count].chinese, "书");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "chair");
    strcpy(vocab[count].chinese, "椅子");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "desk");
    strcpy(vocab[count].chinese, "桌子");
    vocab[count].level = 1;
    count++;

    strcpy(vocab[count].english, "eye");
    strcpy(vocab[count].chinese, "眼睛");
    vocab[count].level = 1;
    count++;

    // ---- Level 2: 常用词组 ----
    strcpy(vocab[count].english, "good morning");
    strcpy(vocab[count].chinese, "早上好");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "good night");
    strcpy(vocab[count].chinese, "晚安");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "thank you");
    strcpy(vocab[count].chinese, "谢谢你");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "you're welcome");
    strcpy(vocab[count].chinese, "不客气");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "how are you");
    strcpy(vocab[count].chinese, "你好吗");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "nice to meet you");
    strcpy(vocab[count].chinese, "很高兴认识你");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "see you later");
    strcpy(vocab[count].chinese, "回头见");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "goodbye");
    strcpy(vocab[count].chinese, "再见");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "my name is");
    strcpy(vocab[count].chinese, "我的名字是");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "what's your name");
    strcpy(vocab[count].chinese, "你叫什么名字");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "happy birthday");
    strcpy(vocab[count].chinese, "生日快乐");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "merry christmas");
    strcpy(vocab[count].chinese, "圣诞节快乐");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "new year");
    strcpy(vocab[count].chinese, "新年快乐");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "good luck");
    strcpy(vocab[count].chinese, "祝你好运");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "come on");
    strcpy(vocab[count].chinese, "加油");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "well done");
    strcpy(vocab[count].chinese, "做得好");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "keep going");
    strcpy(vocab[count].chinese, "继续加油");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "sit down please");
    strcpy(vocab[count].chinese, "请坐下");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "open your book");
    strcpy(vocab[count].chinese, "打开你的书");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "close the door");
    strcpy(vocab[count].chinese, "关门");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "look at the blackboard");
    strcpy(vocab[count].chinese, "看黑板");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "listen to me");
    strcpy(vocab[count].chinese, "听我说");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "read after me");
    strcpy(vocab[count].chinese, "跟我读");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "very good");
    strcpy(vocab[count].chinese, "非常好");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "i am a student");
    strcpy(vocab[count].chinese, "我是一名学生");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "this is my friend");
    strcpy(vocab[count].chinese, "这是我的朋友");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "what time is it");
    strcpy(vocab[count].chinese, "现在几点钟");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "it is a sunny day");
    strcpy(vocab[count].chinese, "今天阳光明媚");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "i like to play football");
    strcpy(vocab[count].chinese, "我喜欢踢足球");
    vocab[count].level = 2;
    count++;

    strcpy(vocab[count].english, "what is your hobby");
    strcpy(vocab[count].chinese, "你的爱好是什么");
    vocab[count].level = 2;
    count++;

    // ----- Level 3: 日常短句 -----
    strcpy(vocab[count].english, "i am ten years old");
    strcpy(vocab[count].chinese, "我今年十岁");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "where do you live");
    strcpy(vocab[count].chinese, "你住在哪里");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "my favourite colour is blue");
    strcpy(vocab[count].chinese, "我最喜欢的颜色是蓝色");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "i have a big family");
    strcpy(vocab[count].chinese, "我有一个大家庭");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "what is your phone number");
    strcpy(vocab[count].chinese, "你的电话号码是多少");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "nice to see you again");
    strcpy(vocab[count].chinese, "很高兴再次见到你");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "i am from china");
    strcpy(vocab[count].chinese, "我来自中国");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "what is the weather like today");
    strcpy(vocab[count].chinese, "今天天气怎么样");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "the sky is blue today");
    strcpy(vocab[count].chinese, "今天天空是蓝色的");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "i go to school by bus");
    strcpy(vocab[count].chinese, "我乘公共汽车去学校");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "my teacher is very kind");
    strcpy(vocab[count].chinese, "我的老师很和蔼");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "i can speak a little english");
    strcpy(vocab[count].chinese, "我会说一点英语");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "what did you do yesterday");
    strcpy(vocab[count].chinese, "你昨天做了什么");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "i played games with my friends");
    strcpy(vocab[count].chinese, "我和朋友玩游戏了");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "there are many books on the desk");
    strcpy(vocab[count].chinese, "桌上有许多书");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "my mother cooks delicious food");
    strcpy(vocab[count].chinese, "我妈妈做美味的食物");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "the cat is sleeping now");
    strcpy(vocab[count].chinese, "猫正在睡觉");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "i will go to the park tomorrow");
    strcpy(vocab[count].chinese, "我明天将去公园");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "what is your favourite food");
    strcpy(vocab[count].chinese, "你最喜欢的食物是什么");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "i love my family very much");
    strcpy(vocab[count].chinese, "我非常爱我的家人");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "the sun rises in the east");
    strcpy(vocab[count].chinese, "太阳从东方升起");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "can you help me please");
    strcpy(vocab[count].chinese, "请问你能帮我吗");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "i am doing my homework now");
    strcpy(vocab[count].chinese, "我正在做家庭作业");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "what do you want to be when you grow up");
    strcpy(vocab[count].chinese, "你长大后想做什么");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "i want to be a doctor");
    strcpy(vocab[count].chinese, "我想成为一名医生");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "the book is on the table");
    strcpy(vocab[count].chinese, "书在桌子上");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "how many people are there in your family");
    strcpy(vocab[count].chinese, "你家有几口人");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "i study english every day");
    strcpy(vocab[count].chinese, "我每天学习英语");
    vocab[count].level = 3;
    count++;

    strcpy(vocab[count].english, "the weather is very nice today");
    strcpy(vocab[count].chinese, "今天天气很好");
    vocab[count].level = 3;
    count++;
}


// ======================================== 主页菜单 ========================================
void showMenu() {
    printf("=================================\n");
    printf("   CAI 小学生英语学习软件\n");
    printf("=================================\n");
    printf("1. 开始练习\n");
    printf("2. 查看统计\n");
    printf("3. 退出程序\n");
    printf("=================================\n");
    printf("请选择: ");
}


// ======================================== 难度选择 ========================================
void showLevelMenu() {
    printf("\n\n\n=================================\n");
    printf("   选择难度等级\n");
    printf("=================================\n");
    printf("1. level 1 - 单词\n");
    printf("2. level 2 - 词组\n");
    printf("3. level 3 - 短句\n");
    printf("=================================\n");
    printf("请选择 :");
}

const char* getLevelName(int level) {
    switch (level) {
    case 1: return "单词";
    case 2: return "词组";
    case 3: return "短句";
    default: return "未知";
    }
}


// ======================================== 随机抽题 ========================================
int getRandomQuestion(int level) {
    int pool[MAX_VOCAB];                        //临时数组
    int c = 0;
	int i;                                  //计数
    for (i = 0; i < count; i++) {
        if (vocab[i].level == level) {
            pool[c++] = i;                      //将索引存入pool
        }
    }
    if (c == 0) { return -1; }                  //没有符合等级的词汇
    return pool[rand() % c];                    //返回索引
}


// ======================================== 晋级检查 ========================================
int checkPromotion() {
    if (user.LevelTotal < MIN_QUESTIONS) {              //最小答题数规定
        return 0;
    }
    if (user.LevelTotal == 0) { return 0; }
    int rate = user.LevelScore * 100 / user.LevelTotal; //百分比计算
    return rate >= UPGRADE_RATE;                        //是否晋级
}


// ======================================== 降级检查 ========================================
int checkDemotion() {
    if (user.LevelTotal < MIN_QUESTIONS) {              //最小答题数规定
        return 0;
    }
    int rate = user.LevelScore * 100 / user.LevelTotal; //百分比计算
    return rate >= DOWNGRADE_RATE;                      //是否降级
}


// ======================================== 显示统计 ========================================
void showStats() {
    printf("\n=================================\n");
    printf("   学习统计");
    printf("\n=================================\n");

    printf("当前等级: Level %d (%s)\n", user.CurrentLevel, getLevelName(user.CurrentLevel));
    printf("总得分: %d\n", user.TotalScore);                        //总得分
    printf("本级正确: %d/%d\n", user.LevelScore, user.LevelTotal);  //本级正确
    if (user.LevelTotal > 0) {
        int rate = user.LevelScore * 100 / user.LevelTotal;
        printf("正确率: %d%%\n", rate);      //正确率
    }

    if (user.LevelScore <= 5) {
		printf("**** 需要加油，继续努力！****\n\n\n");
	}
	else if (6 < user.LevelScore && user.LevelScore <= 9) {
		printf("**** 继续努力，离晋级不远了！****\n\n\n");
	}
    else {
        printf("**** 表现优秀，继续保持！****\n\n\n");
    }
}


// ======================================== 单题循环 ========================================
void runQuiz(int vocabIndex) {
    int success = 0;
    int show = rand() % 2;
    char input[MAX_CHINESE];

    printf("\n==================================\n");

    if (show) {
        printf("请翻译为中文: %s\n", vocab[vocabIndex].english);
        printf("你的答案:");
    }
    else {
        printf("请翻译为英文: %s\n", vocab[vocabIndex].chinese);
        printf("你的答案:");
    }

    while (!success) {
        fgets(input, MAX_CHINESE, stdin);
        input[strcspn(input, "\n")] = '\0';

        const char* correct = show
            ? vocab[vocabIndex].chinese
            : vocab[vocabIndex].english;

        if (CheckAnswer(input, correct)) {
            printf("回答正确!\n");
            success = 1;
            vocab[vocabIndex].correct++;

            user.LevelScore++;
            user.TotalScore++;
        }
        else {
            printf("回答错误，请重新输入: ");
			vocab[vocabIndex].wrong++;
			printf("你还剩%d次机会", 3 - vocab[vocabIndex].wrong);
            if (vocab[vocabIndex].wrong >= 3) {
                printf("机会用完，正确答案是: %s\n\n", correct);
                success = 1;
            }
        }
    }
    user.LevelTotal++;
}


// ======================================== 练习模式 ========================================
/*
1. 循环出题
2. 检查晋级/降级
3. 答题后显示统计
*/
void practiceMode(int level) {                  //接收练习等级
    printf("\n\n\n开始 level %d (%s) 练习\n", level, getLevelName(level));
    printf("按 ctrl + c 退出练习模式\n\n\n");

    int round = 0;
    while (round < MAX_ROUND) {                 //循环练习题目
        int index = getRandomQuestion(level);
        runQuiz(index);
        round++;
        if (checkPromotion() && level < 3) {
            printf("\n**** 恭喜晋级! 当前等级: Level %d ****\n", level + 1);
            user.CurrentLevel++;
            user.LevelScore = 0;
            user.LevelTotal = 0;
        }
        else if (checkDemotion() && level > 1) {
            printf("\n**** 需要加油! 降级到 Level %d ****\n", level - 1);
            user.CurrentLevel--;
            user.LevelScore = 0;
            user.LevelTotal = 0;
        }
    }
    showStats();
}
/*
practiceMode(int level)	            接收选择的等级（1/2/3）
MAX_ROUND	                        每次练习的题数（10）
while (round < MAX_ROUND)	        循环10次
getRandomQuestion(level)	        从指定等级随机抽题
runQuiz(index)	                    答题，直到答对
checkPromotion()	                检查是否晋级
checkDemotion()	                    检查是否降级
user.currentLevel++	                等级+1
user.LevelScore = 0	                重置本级得分
user.LevelTotal = 0	                重置本级答题数
showStats()	                        练习结束后显示统计
*/


// ======================================== main函数 ========================================
/*
1. 初始化（编码设置、随机种子、词库）
2. 显示主菜单循环
3. 处理用户选择
*/
int main() {
    srand(time(NULL));            // 初始化随机种子
    InitVocab();                  // 加载词库

    while (1) {
        showMenu();
        int choice;
        scanf("%d", &choice);
        while (getchar() != '\n');  // 清空缓冲区

        switch (choice) {
        case 1:
            showLevelMenu();
            int levelChoice = 0;
            scanf("%d", &levelChoice);
            while (getchar() != '\n');
            if (levelChoice >= 1 && levelChoice <= 3) {
                practiceMode(levelChoice);
            }
            break;

        case 2:
            showStats();
            break;

        case 3:
            printf("感谢使用，再见!\n");
            return 0;

        default:
            printf("无效选择，请重新选择!\n\n\n");
        }
    }
}
