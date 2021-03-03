void writeLog(int logNum, char* folderPath, char* folderNm);

void DocProcess(int selectDoc, char projectPath[], char folderPath[]);

void insertDoc( char* folderPath);

void updateDoc(char projectPath[], char* folderPath);

void deleteDoc(char* folderPath);

void getDocList(char strFolderPath[]);

char* findDocData(int selectDoc, char strFolderPath[]);

void selectDoc(int selectDocNum, char folderPath[]);

