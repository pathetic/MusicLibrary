#ifdef _WIN32 || _WIN64
	#define clear() system("cls");
	#define pause() system("pause");
#else
	#define clear() system("clear");
	#define pause() system("read -p \"Press enter to continue...\"");
#endif