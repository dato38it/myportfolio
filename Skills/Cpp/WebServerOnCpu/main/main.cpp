//№9
#undef   UNICODE
#define  WIN32_LEAN_AND_MEAN
#define  DEFAULT_PORT    "8080"  // Номер порта
#define  DEFAULT_BUFLEN   1024  // Размер буфера
#define  NMAX_SIZ_ZAP     1024  // Максиальный размер запроса
#define  NMAX_SIZ_OTV     1024  // Максиальный размер Ответа
#define  NMAX_SIZ_STR     1024  // Максиальный размер Ответа строки в паскалевском стиле
#define  SMAX_SIZ_ZAP    "1024" // Максиальный размер запроса
#define  SMAX_SIZ_OTV    "1024" // Максиальный размер Ответа
#define  SMAX_SIZ_STR    "1024" // Максиальный размер Строки в паскалевком стиле
#define  MAX_KOL_POT      16    // Максимальнео количество потоков
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#pragma comment (lib, "Ws2_32.lib")
//#pragma comment (lib, "Mswsock.lib")
#pragma comment(lib, "OpenCL.lib")
#include "CL\Cl.h"
struct TPot{
    bool   SVO; // Свободен ли поток
    SOCKET SOC; // сокет
};
char BZAP[NMAX_SIZ_ZAP*MAX_KOL_POT];// Буфер запросов
char BOTV[NMAX_SIZ_OTV*MAX_KOL_POT];// Буфер ОТветов
int  BSIZ[MAX_KOL_POT];// Буфер размеров ОТветов
TPot POTS[MAX_KOL_POT];// Масив с потоками
int  TrRand;
DWORD  WINAPI  ObrZap(LPVOID lpParam){
    // Чтение данных в большой масив из сокета
    // Ожидание ответа
    // Вывод ответа в сокет
    int NOMPOT=(int)lpParam;
    char*  Zap = new char[DEFAULT_BUFLEN];// Буфер запроса
    int ZapSi;// Количество поступивших данных из интернета
    int OtpSi;// Колчиество отправленых байт клиенту
    SOCKET ClientSocket=POTS[NOMPOT].SOC;
    ZapSi  = recv(
        ClientSocket,
        &BZAP[NOMPOT*NMAX_SIZ_ZAP],
        DEFAULT_BUFLEN,// Максимальное количество данных
        0);// Читаем данные
    TrRand=TrRand+1;// Увеличиваем счетчик запросов
    BZAP[NOMPOT*NMAX_SIZ_ZAP+NMAX_SIZ_ZAP-1]=(unsigned char)TrRand;
    BZAP[NOMPOT*NMAX_SIZ_ZAP+NMAX_SIZ_ZAP-2]=(unsigned char)TrRand;
    BZAP[NOMPOT*NMAX_SIZ_ZAP+NMAX_SIZ_ZAP-3]=(unsigned char)TrRand;
    BZAP[NOMPOT*NMAX_SIZ_ZAP+NMAX_SIZ_ZAP-4]=(unsigned char)TrRand;
    std::cout<<"1"<<std::endl;
    // Передти в спящий режим потоку 0.1 секунды
    // Ожидание обработки запроса видео картой
    Sleep(100);
    while (BSIZ[NOMPOT]==0){
        Sleep(100);
        // Переходим в спящий режим потока на 0.1 сек
    }
    std::cout<<BSIZ[NOMPOT]<<std::endl;
    OtpSi = send(
        ClientSocket, // Сокет в котрый нужно вернуть ответ
        &BOTV[NOMPOT*NMAX_SIZ_OTV], // Адрес раположения ответа
        BSIZ[NOMPOT],// Размер ответа в байтах
        0);// Отдаем данные
    closesocket(ClientSocket);
    BSIZ[NOMPOT]=0;
    POTS[NOMPOT].SVO=true;// Указываем что поток свободен
    return 0;
}
DWORD  WINAPI  Server(LPVOID lpParam){
    SOCKET ListenSocket=(SOCKET)lpParam;
    SOCKET ClientSocket=INVALID_SOCKET;
    do {
        // Accept a client socket
        ClientSocket = accept(ListenSocket, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET)  closesocket(ClientSocket);
        else {
            int f=1;// ищим свободный поток
            while ((f<MAX_KOL_POT)&(POTS[f].SVO!=true)) f++;
            if (f<MAX_KOL_POT){
                POTS[f].SVO=false;// Указываем что поток занят
                POTS[f].SOC=ClientSocket;// Передаем сокет в поток
                CreateThread( // Если Есть места для создания новых потоков
                    NULL,// атрибуты безопасности по умолчанию
                    0,// размер стека используется по умолчанию
                    ObrZap,// функция потока
                    (LPVOID)f,// аргумент функции потока Номер в масиве потока
                    0,// флажки создания используются по умолчанию
                    NULL);// возвращает идентификатор потока
            } else {// Если нет места для создания новых потоков
            }
        }
    } while (true);
}
int main(){
    for (int f=0;f<MAX_KOL_POT;f++) POTS[f].SVO=true;
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0){
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }
    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL;
    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags    = AI_PASSIVE;
    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }
    // Create a SOCKET for connecting to server
    ListenSocket = socket(
        result->ai_family,
        result->ai_socktype,
        result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    // Setup the TCP listening socket
    iResult = bind(
        ListenSocket,
        result->ai_addr,
        (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    freeaddrinfo(result);
    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    // Запуск обработчика запросов на процессоре
    CreateThread( // Если Есть места для создания новых потоков
        NULL,// атрибуты безопасности по умолчанию
        0,// размер стека используется по умолчанию
        Server,// функция потока
        (LPVOID)ListenSocket,// аргумент функции
        0,// флажки создания используются по умолчанию
        NULL);// возвращает идентификатор потока
    // ПОдключение обработчика запросов на GPU
    cl_platform_id platform_id;
    cl_uint ret_num_platforms;
    cl_device_id device_id;
    cl_uint ret_num_devices;
    cl_context context;
    cl_command_queue command_queue;
    cl_program program;
    // Обработчик запроса из интернета
    const char* source_str=
    "struct TStr{" // Структура описвающая строку
    "int  Len;" // Длина строки
    "char C[" SMAX_SIZ_STR "];"// Содержимое строки
    "};"
    // ПРеобразует сишную строку в наш формат собственнй В стиле паскаль
    "void SRav(struct TStr*iStr,char iC[]){"
    "int f;"// Счетчик символов
    "for (f=0;iC[f]!=0;f++)" // Перебираю пока не встречю 0 в строке исходной
    "iStr->C[f]=iC[f];"// Копирую соджрержимое строки
    "iStr->C[f]=0;"// Пишу символ окончания строки в стиле С
    "iStr->Len=f;"// Сохраняю длину строки
    "}"
    "void SAdd(struct TStr*C1,struct TStr*C2){"
    "for (int f=0;f<C2->Len;f++) C1->C[f+C1->Len]=C2->C[f];"
    "C1->C[C1->Len+C2->Len]=0;"
    "C1->Len=C1->Len+C2->Len;"
    "}"
    // Добавление 1 символа в конец строки
    "void SAddC(struct TStr*C1,char C){"
    "C1->C[C1->Len]=C;"
    "C1->Len=C1->Len+1;"
    "C1->C[C1->Len]=0;"
    "}"
    // Копирует строку
    "void SCop(struct TStr*C1,struct TStr*C2){"
    "int f;"               // Счетчик символов
    "for (f=0;f<C2->Len;f++)" // Перебираю пока не встречю 0 в строке исходной
    "C1->C[f]=C2->C[f];"// Копирую соджрержимое строки
    "C1->C[C2->Len]=0;  "// Пишу символ окончания строки в стиле С
    "C1->Len=C2->Len;   "// Сохраняю длину строки
    "}"
    // Чтение из адресной строки страницы и параметров
    "void TrReadAdr(struct TStr*iTrAdr,struct TStr*iTrPar,struct TStr*iStr){"
    "int f,kp;"
    "kp=0;"
    "for (f=0;f<iStr->Len;f++) {"
    "if ((iStr->C[f]==' ')||(iStr->C[f]=='?')) kp=kp+1;"
    "if (kp==1) SAddC(iTrAdr,iStr->C[f]);" // Сдесь читаем адрес
    "if (kp==2) SAddC(iTrPar,iStr->C[f]);" // Сдесь читаем параметр
    "}"
    "}"
    /*
     Пример запроса
    GET /spec.html HTTP/1.1
    Host: www.example.org
    Cookie: Ses=value
    */
    // Чтение кода сессии из запроса
    "void TrReadSes(struct TStr*iTrSes,struct TStr*iStr){"
    "int f,kp,r,EX;"
    "kp=0;r=0;EX=0;"
    "iTrSes->Len=0;"
    "for (f=0;f<iStr->Len;f++) {"
    "SAddC(iTrSes,iStr->C[f]);"
    "if  (iStr->C[f]==' ')   iTrSes->Len=0;"// Если пробел обнуляем результат
    "if  (iStr->C[f]==':')   {kp=kp+1;iTrSes->Len=0;}"
    "if ((kp==1)&&(iStr->C[f]=='='))"
    "if ((iTrSes->C[0]=='S')&&(iTrSes->C[1]=='e')&&(iTrSes->C[2]=='s'))"
    "   {kp=kp+1;iTrSes->Len=0;r=1;}"// Если Ses= читаем значение
    "}"
    "if (r==0) iTrSes->Len=0;"
    "}"
    "int strlen(char s[])"
    "{"
    "int f=0;"
    "while ((s[f]!=0)&(f<" SMAX_SIZ_OTV ")) f++;"
    "return f;"
    "}"
    "void stradd3(char a[],char b[],char c[])"
    "{"
    "for (int f=0;f<strlen(a);f++) c[f]=a[f];"
    "for (int f=0;f<strlen(b);f++) c[f+(strlen(a))]=b[f];"
    "c[strlen(a)+strlen(b)]=0;"
    "}"
    "void stradd2(char a[],char b[])"
    "{"
    "int lenA=strlen(a);"
    "int lenB=strlen(b);"
    "for (int f=0;f<lenB;f++) a[f+lenA]=b[f];"
    "a[lenA+lenB]=0;"
    "}"
    "void strrev(char a[])"
    "{"
    "char c;"
    "int f=0;"
    "int l=strlen(a)-1;"
    "while (f<l) "
    "{c=a[l];a[l]=a[f];a[f]=c;f++;l--;}"
    "}"
    // Второе издание Язык программирования Си («K&R2») на стр. 64 содержало нижеследующую реализацию itoa.
    "void itoa(int n, char s[])"
    "{"
    "    int i, sign;"
    "   if ((sign = n) < 0) "/* записываем знак */
    "       n = -n;          "/* делаем n положительным числом */
    "   i = 0;"
    "   do {      " /* генерируем цифры в обратном порядке */
    "       s[i++] = n % 10 + '0';   "/* берем следующую цифру */
    "   } while ((n /= 10) > 0);    " /* удаляем */
    "   if (sign < 0)"
    "       s[i++] = '-';"
    "   s[i] = '\\0';"
    "   strrev(s);"
    "}"
    // Переводит число в текстовое значение паскалевского типа
    "void Sitoa(int iNom, struct TStr*iStr)"
    "{"
    "itoa(iNom,iStr->C);" // Переводим в текст число
    "iStr->Len=0;"// Изначально длина строки 0
    "while (iStr->C[iStr->Len]!=0) iStr->Len=iStr->Len+1;"
    "}"
    "__kernel void test(__global char* zap,__global char* otv,__global int* siz){"
    //--------------------------------------------------------------
    // Определяем номер потока на котором работаем в GPU
    "int gid = get_global_id(0);" // gid Номер потока
    "int f;"// Переменная для циклов
    //--------------------------------------------------------------
    // Обьявляем используемые стрококовые переменные в стиле Си
    // Читаем запрос для данного потока из буфера всех запросов
    "char CTrZap[" SMAX_SIZ_ZAP"];"
    "for (f=0;zap[" SMAX_SIZ_ZAP "*gid+f]!=0;f++)"
       "CTrZap[f]=zap[" SMAX_SIZ_ZAP "*gid+f];"
    "CTrZap[f]=0;"
    "char CTrHr[]=\"<hr>\";" // Горизонтальная черта
    "char CTrLn[]=\"\\r\\n\";" // Одинарный перевод строки
    "char CTrLnLn[]=\"\\r\\n\\r\\n\";" // Просто двойной перевод строки
    "char CTrHeadStart[]=\"HTTP/1.1 200 OK\\r\\n\""// Начало Html заголовка
              "\"Content-Language: ru\\r\\n\""
              "\"Content-Type: text/html\\r\\n\""
              "\"Set-Cookie: Ses=ZZZ\\r\\n\""
              "\"Content-Length: \";"
    "char CTrSizeContext[7];" // Размер веб страницы в байтах  в виде текста
    // Содержимое веб сраницы
    "char CTrHtmlStart[]=\"<html>\";"
    "char CTrHtmlBody[]=\"<br><br><center>This is text</center>\";"
    "char CTrHtmlEnd  []=\"</html>\";"
    // Конец HTML
    "char CTrHeadEnd[]=\"\\r\\n\""
    "\"Connection: close\\r\\n\\r\\n\";"// Завершающася часть заголовка
    // Обьявляем используемые стрококовые переменные в стиле паскаля
    "struct TStr STrSes;   "// Уникальный номер сесии
    "struct TStr STrAdr;   "// Адрес запрашиваемой страницы
    "struct TStr STrPar;   "// Параметр
    "STrAdr.Len=0;"         // Обнуляем длину строки
    "STrPar.Len=0;"         // Обнуляем длину строки
    "STrSes.Len=0;"         // Обнуляем длину строки
    "struct TStr STrZap;  "// Строка запроса в стиле паскаль
    "struct TStr STrHr;   "// Горизонтальная черточка
    "struct TStr STrLn;   "// Одинарный перевд строки
    "struct TStr STrLnLn; "// Двойной перевод строки
    "struct TStr STrOtv;  "// Готовый ответ
    "struct TStr STrHeadStart;   " // Начало заголовка ответа
    "struct TStr STrSizeContext;   "// Размер страницы в виде текста
    "struct TStr STrHtml;      "// Вся страница целиком
    "struct TStr STrHtmlStart; "// Начало веб страницы
    "struct TStr STrHtmlBody;  "// Содержимое веб страницы
    "struct TStr STrHtmlEnd;   "// Окончание веб страницы
    "struct TStr STrHeadEnd;   "// Завершене заголовка
    // Переводим сишные строкив  свой типа строк типа паскаля
    "SRav(&STrZap,CTrZap);  "// Запрос
    "SRav(&STrHr,CTrHr);    "// Переводим сишный тип в паскалевский
    "SRav(&STrLn,CTrLn);    "// Переводим сишный тип в паскалевский
    "SRav(&STrLnLn,CTrLnLn);"// Переводим сишный тип в паскалевский
    "SRav(&STrHeadStart,CTrHeadStart);"// Переводим сишный тип в паскалевский
    "SRav(&STrHtmlStart,CTrHtmlStart);"// Переводим сишный тип в паскалевский
    "SRav(&STrHtmlBody,CTrHtmlBody);"// Переводим сишный тип в паскалевский
    "SRav(&STrHtmlEnd,CTrHtmlEnd);"// Переводим сишный тип в паскалевский
    "SRav(&STrHeadEnd,CTrHeadEnd);"// Переводим сишный тип в паскалевский
    // Парсим запрос
    "struct TStr LNSTR;"
    "LNSTR.Len=0;"
    "int NOMSTR=0;" // Номер строки из запроса
    "f=0;"
    "while (f<STrZap.Len) { "
    "SAddC(&LNSTR,STrZap.C[f]);"
    "if (STrZap.C[f]==13)  {" // ПОлучаем 1 строку
       // Парсим одну строку
       // СТрока состоит из 2 частей до : и после ))))
             "if (NOMSTR==0)          TrReadAdr(&STrAdr,&STrPar,&LNSTR); " // Чтение адресной строки и параметров
             "else if (STrSes.Len==0) TrReadSes(&STrSes,&LNSTR);" // Чтение номера сессии
             "LNSTR.Len=0;"// ОБнуляем строку
             "NOMSTR=NOMSTR+1;"// Считаем строки
            "};"
    "f++;"
    "};"
    "int NTrRan=(unsigned char)zap[" SMAX_SIZ_ZAP "*gid+" SMAX_SIZ_ZAP "-1];"
    "struct TStr STrRan;   "// ДЛя генерации случайных чисел
    "Sitoa(NTrRan,&STrRan);"
    // Создаем  Срдержимое страницы
    "STrHtml.Len=0;"
    "SAdd(&STrHtml,&STrHtmlStart);"// Начало веб страницы </html>
    "SAdd(&STrHtml,&STrRan);"//
    "SAdd(&STrHtml,&STrHr);"// просто HTML Вертикальная верта
    "SAdd(&STrHtml,&STrSes);"//
    "SAdd(&STrHtml,&STrHr);"// просто HTML Вертикальная верта
    "SAdd(&STrHtml,&STrAdr);"//
    "SAdd(&STrHtml,&STrHr);"//
    "SAdd(&STrHtml,&STrPar);"//
    "SAdd(&STrHtml,&STrHtmlBody);"// Содержимое веб старницы бла бла бла
    // ПОлучаем Строки из запроса
    "LNSTR.Len=0;"
    "f=0;"
    "while (f<STrZap.Len) { "
    "SAddC(&LNSTR,STrZap.C[f]);"
    "if (STrZap.C[f]==13)"
       "{SAdd(&STrHtml,&LNSTR);SAdd(&STrHtml,&STrHr);LNSTR.Len=0; };"
    "f++;"
    "};"
    "SAdd(&STrHtml,&STrHtmlEnd);"// Окончание Веб страницы </html>
    // Определяем размер содержимого Веб страницы
    "Sitoa(STrHtml.Len,&STrSizeContext);"// Длина контекста в виде текста
    // Формируем ответ путем сложения строк
    "STrOtv.Len=0;"
    "SAdd(&STrOtv,&STrHeadStart);"// Начало заголовка
    "SAdd(&STrOtv,&STrSizeContext);"// Размер HTML содержимого в байтах страницы
    "SAdd(&STrOtv,&STrHeadEnd);"// Конец Заголовка Close
    "SAdd(&STrOtv,&STrHtml);"// Веб страница
    "SAdd(&STrOtv,&STrLnLn);"// В конце двойной перевод строки
    // Формирование ответа в буфере ответов
    "f=0;"
    "while (STrOtv.C[f]!=0){"// Копирем ответ в буфер ответов
    "otv[f+(gid*" SMAX_SIZ_OTV ")]=STrOtv.C[f];f++;}"
    "otv[f+(gid*" SMAX_SIZ_OTV ")]=0;"// Записывавем 0 в корнец ответа
    "siz[gid]=STrOtv.Len;"// Указываем размер ответа в байтах
    "}";
    for (int f=0;f<NMAX_SIZ_OTV*MAX_KOL_POT;f++) BOTV[f]=0;
    const char** zzz=&source_str;
    size_t source_size=strlen(source_str);
    size_t* szz =&source_size;
    // получить доступные платформы
    cl_int ret;
    ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    if (ret==0)     std::cout<< "clGetPlatformIDs             OK."<<          std::endl;
        else std::cout<< "clGetPlatformIDs          Error "<<ret<<"."<<std::endl;
    // получить доступные устройства
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
    if (ret==0)     std::cout<< "clGetDeviceIDs               OK."<<          std::endl;
        else std::cout<< "clGetDeviceIDs            Error "<<ret<<"."<<std::endl;
    // создать контекст
    context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
    if (ret==0)     std::cout<< "clCreateContext              OK."<<          std::endl;
        else std::cout<< "clCreateContext           Error "<<ret<<"."<<std::endl;
    // создаем команду
    command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
    if (ret==0)     std::cout<< "clCreateCommandQueue         OK."<<          std::endl;
        else std::cout<< "clCreateCommandQueue      Error "<<ret<<"."<<std::endl;
    // создать бинарник из кода программы
    program = clCreateProgramWithSource(context, 1,(const char **)&source_str, (const size_t *)&source_size, &ret);
    if (ret==0)     std::cout<< "clCreateProgramWithSource    OK."<<          std::endl;
        else std::cout<< "clCreateProgramWithSource Error "<<ret<<"."<<std::endl;
    // скомпилировать программу
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
    if (ret==0)     std::cout<< "clBuildProgram               OK."<<          std::endl;
        else std::cout<< "clBuildProgram            Error "<<ret<<"."<<std::endl;
    // создать кернел
    cl_kernel kernel = clCreateKernel(program, "test", &ret);
    if (ret==0)     std::cout<< "clCreateKernel               OK."<<          std::endl;
        else std::cout<< "clCreateKernel            Error "<<ret<<"."<<std::endl;
    cl_mem MZAP = NULL;// структура описывающая Буфер где храняться запросы
    cl_mem MOTV = NULL;// структура описывающая Буфер где храняться ответы
    cl_mem MSIZ = NULL;// структура описывающая Буфер где храняться размеры ответов
    // создать буфер  для запросов
    //memobj = clCreateBuffer(context, CL_MEM_READ_WRITE, memLenth * sizeof(cl_char), NULL, &ret);
    MZAP = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(BZAP) * sizeof(cl_char), NULL, &ret);
    if (ret==0)     std::cout<< "clCreateBuffer               OK."<<          std::endl;
        else std::cout<< "clCreateBuffer            Error "<<ret<<"."<<std::endl;
    // создать буфер для ответов
    MOTV = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(BOTV) * sizeof(cl_char), NULL, &ret);
    if (ret==0)     std::cout<< "clCreateBuffer               OK."<<          std::endl;
        else std::cout<< "clCreateBuffer            Error "<<ret<<"."<<std::endl;
    // создать буфер для размеров ответов
    MSIZ = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(BSIZ) * sizeof(cl_int), NULL, &ret);
    if (ret==0)     std::cout<< "clCreateBuffer               OK."<<          std::endl;
        else std::cout<< "clCreateBuffer            Error "<<ret<<"."<<std::endl;
    // устанавливаем параметр запросы
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&MZAP);
    if (ret==0)     std::cout<< "clSetKernelArg               OK."<<          std::endl;
        else std::cout<< "clSetKernelArg            Error "<<ret<<"."<<std::endl;
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&MOTV);
    if (ret==0)     std::cout<< "clSetKernelArg               OK."<<          std::endl;
        else std::cout<< "clSetKernelArg            Error "<<ret<<"."<<std::endl;
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&MSIZ);
    if (ret==0)     std::cout<< "clSetKernelArg               OK."<<          std::endl;
        else std::cout<< "clSetKernelArg            Error "<<ret<<"."<<std::endl;
    while (1<2){
        Sleep(1000);
        // записать данные в буфер записываем поступившие запросы
        ret = clEnqueueWriteBuffer(command_queue, MZAP, CL_TRUE, 0, sizeof(BZAP)  , BZAP, 0, NULL, NULL);
        if (ret==0)     std::cout<< "clEnqueueWriteBuffer         OK."<<          std::endl;
            else std::cout<< "clEnqueueWriteBuffer      Error "<<ret<<"."<<std::endl;
        size_t global_work_size[1] = { MAX_KOL_POT };// Количество потоков наверно )))
        // выполнить кернел
        ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, global_work_size, NULL, 0, NULL, NULL);
        if (ret==0)     std::cout<< "clEnqueueNDRangeKernel       OK."<<          std::endl;
            else std::cout<< "clEnqueueNDRangeKernel    Error "<<ret<<"."<<std::endl;
        // считать данные из буфера
        ret = clEnqueueReadBuffer(command_queue, MOTV, CL_TRUE, 0, sizeof(BOTV)  , BOTV, 0, NULL, NULL);
        if (ret==0)     std::cout<< "clEnqueueReadBuffer          OK."<<          std::endl;
            else std::cout<< "clEnqueueReadBuffer       Error "<<ret<<"."<<std::endl;
        ret = clEnqueueReadBuffer(command_queue, MSIZ, CL_TRUE, 0, sizeof(BSIZ)  , BSIZ, 0, NULL, NULL);
        if (ret==0)     std::cout<< "clEnqueueReadBuffer          OK."<<          std::endl;
            else std::cout<< "clEnqueueReadBuffer       Error "<<ret<<"."<<std::endl;
    }
    system("pause");
    closesocket(ClientSocket);
    WSACleanup();
    return 0;
}
